//-----------------------------------------------------------------------------
// axi_sniffer.sv - Simple RAM-based AXI Bus Trace
//
// Direct 64-bit AXI interface - host reads RAM directly.
// Used for both AXI Slave (BAR access) and AXI Master (DMA) sniffing.
//
// Memory Map (0x000-0x7FF within sniffer region):
//   0x000: control/status  - write [0]=start, [1]=stop, [2]=clear
//                          - read  [0]=running, [1]=full
//   0x008: write_ptr       - [5:0] current entry (0-63)
//   0x010: entry_count     - [6:0] entries captured
//   0x018: aw_count        - AW transactions seen
//   0x020: ar_count        - AR transactions seen
//   0x028: timestamp       - current global timestamp
//   0x030-0x03F: reserved
//   0x040-0x7FF: trace entries (64 entries x 32 bytes each)
//
// Trace entry format (256 bits = 4 QWs = 32 bytes):
//   QW0 [63:0]:    {32'b0, addr[31:0]}
//   QW1 [127:64]:  data[63:0]
//   QW2 [191:128]: {reserved, timestamp[31:0]}
//   QW3 [255:192]: {reserved, channel, phase, strb_resp[7:0]}
//-----------------------------------------------------------------------------
module axi_sniffer #(
    parameter DEPTH = 64
)(
    input  logic        clk,
    input  logic        rst_n,

    // Global timestamp
    input  logic [31:0] global_timestamp,

    // Snoop AXI Write Channel
    input  logic [31:0] axi_awaddr,
    input  logic        axi_awvalid,
    input  logic        axi_awready,
    input  logic [63:0] axi_wdata,
    input  logic [7:0]  axi_wstrb,
    input  logic        axi_wvalid,
    input  logic        axi_wready,
    input  logic [1:0]  axi_bresp,
    input  logic        axi_bvalid,
    input  logic        axi_bready,

    // Snoop AXI Read Channel
    input  logic [31:0] axi_araddr,
    input  logic        axi_arvalid,
    input  logic        axi_arready,
    input  logic [63:0] axi_rdata,
    input  logic [1:0]  axi_rresp,
    input  logic        axi_rvalid,
    input  logic        axi_rready,

    // AXI-lite interface (directly from bridge)
    input  logic [10:0] s_araddr,
    input  logic        s_arvalid,
    output logic        s_arready,
    output logic [63:0] s_rdata,
    output logic        s_rvalid,
    input  logic        s_rready,

    input  logic [10:0] s_awaddr,
    input  logic [63:0] s_wdata,
    input  logic        s_awvalid,
    input  logic        s_wvalid,
    output logic        s_awready,
    output logic        s_wready,
    output logic        s_bvalid,
    input  logic        s_bready
);

    localparam PTR_W = $clog2(DEPTH);

    //=========================================================================
    // State registers
    //=========================================================================
    logic running;
    logic full;
    logic [PTR_W-1:0] write_ptr;
    logic [PTR_W:0] entry_count;
    logic [31:0] aw_count, ar_count;

    // Pending AW address
    logic [31:0] pending_awaddr;
    logic pending_awvalid;

    //=========================================================================
    // Trace RAM: 64 entries x 4 QWs = 256 x 64-bit words
    //=========================================================================
    logic [63:0] trace_ram [0:DEPTH*4-1];

    //=========================================================================
    // AXI Transaction Detection
    //=========================================================================
    wire aw_handshake = axi_awvalid && axi_awready;
    wire w_handshake  = axi_wvalid  && axi_wready;
    wire ar_handshake = axi_arvalid && axi_arready;
    wire r_handshake  = axi_rvalid  && axi_rready;

    wire capture_ok = running && !full;

    //=========================================================================
    // Capture logic
    //=========================================================================
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            running <= 0;
            full <= 0;
            write_ptr <= 0;
            entry_count <= 0;
            aw_count <= 0;
            ar_count <= 0;
            pending_awaddr <= 0;
            pending_awvalid <= 0;
        end else begin
            // Track AW for pairing with W
            if (aw_handshake) begin
                pending_awaddr <= axi_awaddr;
                pending_awvalid <= 1;
                aw_count <= aw_count + 1;
            end

            // Capture write data (paired with pending AW)
            if (w_handshake && pending_awvalid && capture_ok) begin
                trace_ram[{write_ptr, 2'd0}] <= {32'b0, pending_awaddr};
                trace_ram[{write_ptr, 2'd1}] <= axi_wdata;
                trace_ram[{write_ptr, 2'd2}] <= {32'b0, global_timestamp};
                trace_ram[{write_ptr, 2'd3}] <= {54'b0, 1'b0, 1'b0, axi_wstrb};  // channel=0 (write), phase=0 (req)
                pending_awvalid <= 0;
                write_ptr <= write_ptr + 1;
                if (entry_count < DEPTH) entry_count <= entry_count + 1;
                if (write_ptr == PTR_W'(DEPTH - 1)) full <= 1;
            end else if (w_handshake) begin
                pending_awvalid <= 0;
            end

            // Capture read request
            if (ar_handshake) begin
                ar_count <= ar_count + 1;
                if (capture_ok) begin
                    trace_ram[{write_ptr, 2'd0}] <= {32'b0, axi_araddr};
                    trace_ram[{write_ptr, 2'd1}] <= 64'b0;
                    trace_ram[{write_ptr, 2'd2}] <= {32'b0, global_timestamp};
                    trace_ram[{write_ptr, 2'd3}] <= {54'b0, 1'b1, 1'b0, 8'b0};  // channel=1 (read), phase=0 (req)
                    write_ptr <= write_ptr + 1;
                    if (entry_count < DEPTH) entry_count <= entry_count + 1;
                    if (write_ptr == PTR_W'(DEPTH - 1)) full <= 1;
                end
            end

            // Capture read response
            if (r_handshake && capture_ok) begin
                trace_ram[{write_ptr, 2'd0}] <= 64'b0;  // No address for response
                trace_ram[{write_ptr, 2'd1}] <= axi_rdata;
                trace_ram[{write_ptr, 2'd2}] <= {32'b0, global_timestamp};
                trace_ram[{write_ptr, 2'd3}] <= {54'b0, 1'b1, 1'b1, 6'b0, axi_rresp};  // channel=1, phase=1 (resp)
                write_ptr <= write_ptr + 1;
                if (entry_count < DEPTH) entry_count <= entry_count + 1;
                if (write_ptr == PTR_W'(DEPTH - 1)) full <= 1;
            end

            // Control writes
            if (s_awvalid && s_wvalid && s_awaddr[10:3] == 0) begin
                if (s_wdata[0]) running <= 1;  // start
                if (s_wdata[1]) running <= 0;  // stop
                if (s_wdata[2]) begin          // clear
                    write_ptr <= 0;
                    entry_count <= 0;
                    full <= 0;
                    aw_count <= 0;
                    ar_count <= 0;
                end
            end
        end
    end

    //=========================================================================
    // Write response
    //=========================================================================
    logic wr_pending;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wr_pending <= 0;
        end else begin
            if (s_awvalid && s_wvalid && !wr_pending)
                wr_pending <= 1;
            else if (wr_pending && s_bready)
                wr_pending <= 0;
        end
    end
    assign s_awready = !wr_pending;
    assign s_wready = !wr_pending;
    assign s_bvalid = wr_pending;

    //=========================================================================
    // Read logic
    //=========================================================================
    logic [63:0] rdata_next;
    logic rd_pending;
    logic [10:0] rd_addr;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rd_pending <= 0;
            rd_addr <= 0;
            s_rdata <= 0;
            s_rvalid <= 0;
        end else begin
            if (s_arvalid && s_arready) begin
                rd_pending <= 1;
                rd_addr <= s_araddr;
            end else if (rd_pending && !s_rvalid) begin
                s_rdata <= rdata_next;
                s_rvalid <= 1;
                rd_pending <= 0;
            end else if (s_rvalid && s_rready) begin
                s_rvalid <= 0;
            end
        end
    end
    assign s_arready = !rd_pending && !s_rvalid;

    // Read data mux
    always_comb begin
        rdata_next = 64'hDEAD_0002;  // Default for debug

        if (rd_addr < 11'h040) begin
            // Status registers 0x000-0x03F
            case (rd_addr[5:3])
                3'd0: rdata_next = {62'b0, full, running};          // 0x000
                3'd1: rdata_next = {58'b0, write_ptr};              // 0x008
                3'd2: rdata_next = {57'b0, entry_count};            // 0x010
                3'd3: rdata_next = {32'b0, aw_count};               // 0x018
                3'd4: rdata_next = {32'b0, ar_count};               // 0x020
                3'd5: rdata_next = {32'b0, global_timestamp};       // 0x028
                default: rdata_next = 64'b0;
            endcase
        end else begin
            // Trace RAM 0x040+
            // Entry N at 0x040 + N*0x20, QW M at offset M*8
            // rd_addr[10:5] = entry index (0-63)
            // rd_addr[4:3] = QW index (0-3)
            if (rd_addr >= 11'h040) begin
                rdata_next = trace_ram[{rd_addr[10:5] - 6'd2, rd_addr[4:3]}];
            end
        end
    end

endmodule
