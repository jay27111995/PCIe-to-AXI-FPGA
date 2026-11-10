//-----------------------------------------------------------------------------
// rtile_pkg.sv - R-Tile PCIe Gen5 x16 + AXI-Lite definitions
//-----------------------------------------------------------------------------
package rtile_pkg;

    //=========================================================================
    // AXI-Lite
    //=========================================================================
    typedef enum logic [1:0] {
        AXI_OKAY   = 2'b00,
        AXI_EXOKAY = 2'b01,
        AXI_SLVERR = 2'b10,
        AXI_DECERR = 2'b11
    } axi_resp_e;

    // Gen5 x16: 4 segments × 256b = 1024b @ 500MHz
    localparam int NUM_SEG    = 4;
    localparam int SEG_DW     = 256;
    localparam int HDR_DW     = 128;
    localparam int PREFIX_DW  = 32;

    // Credit types: [0]=Posted, [1]=Non-Posted, [2]=Completion
    typedef enum logic [1:0] { CRDT_P=0, CRDT_NP=1, CRDT_CPL=2 } crdt_e;

    // TLP Fmt[2:0] + Type[4:0]
    typedef enum logic [7:0] {
        TLP_MRD32  = 8'b000_00000,
        TLP_MRD64  = 8'b001_00000,
        TLP_MWR32  = 8'b010_00000,
        TLP_MWR64  = 8'b011_00000,
        TLP_CPL    = 8'b000_01010,
        TLP_CPLD   = 8'b010_01010
    } tlp_e;

    // Completion status
    typedef enum logic [2:0] { SC=0, UR=1, CRS=2, CA=4 } cpl_stat_e;

    // LTSSM (key states only)
    localparam logic [5:0] LTSSM_L0 = 6'h11;

    // Header field extraction from 128b header
    function automatic logic [2:0]  hdr_fmt(logic [127:0] h);   return h[127:125]; endfunction
    function automatic logic [4:0]  hdr_type(logic [127:0] h);  return h[124:120]; endfunction
    function automatic logic [9:0]  hdr_len(logic [127:0] h);   return h[105:96];  endfunction
    function automatic logic [15:0] hdr_rid(logic [127:0] h);   return h[95:80];   endfunction
    function automatic logic [7:0]  hdr_tag(logic [127:0] h);   return h[79:72];   endfunction
    function automatic logic [3:0]  hdr_lbe(logic [127:0] h);   return h[71:68];   endfunction
    function automatic logic [3:0]  hdr_fbe(logic [127:0] h);   return h[67:64];   endfunction
    function automatic logic [63:0] hdr_addr64(logic [127:0] h); return h[63:0];   endfunction
    function automatic logic [31:0] hdr_addr32(logic [127:0] h); return h[63:32];  endfunction

    function automatic logic has_data(logic [2:0] fmt);  return fmt[1]; endfunction
    function automatic logic is_4dw(logic [2:0] fmt);    return fmt[0]; endfunction

endpackage
