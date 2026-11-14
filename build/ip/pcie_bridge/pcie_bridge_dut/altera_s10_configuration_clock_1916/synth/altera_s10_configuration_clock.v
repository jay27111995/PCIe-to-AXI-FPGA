// (C) 2001-2025 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files from any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License Subscription 
// Agreement, Altera IP License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


// $Id: //acds/main/ip/pgm/altera_nd_mailbox_avst_adap/altera_nd_mailbox_avst_adap.sv#2 $
// $Revision: #2 $
// $Date: 2015/10/19 $
// $Author: tgngo $


`timescale 1 ps / 1 ps

module  altera_s10_configuration_clock
    ( 
    clkout
    );

    parameter DEVICE_FAMILY   = " Stratix 10";
    
    output   clkout;
    
    wire  wire_clkout;
    
    assign clkout = wire_clkout;
        
    // -------------------------------------------------------------------
    // Instantiate clock source end point
    // -------------------------------------------------------------------  
    altera_config_clock_source_endpoint s10_config_clk_inst (
        .clk        (wire_clkout)
    );

    
endmodule //altera_int_osc
//VALID FILE
`ifdef QUESTA_INTEL_OEM
`pragma questa_oem_00 "XKVI+O6izDmnuQM+5LgaAoZdpMAW7nEwhzvPkgEomTZHng7+AlZZjAn+1aV5JgCekvOGD/AjVjW5fsxGQI21IQrUdIH+SiihFjpSmpSYvnCwgYkc4TVbv5URhCfh1+OxA5jwzC5HPGlOrA9FA+BhhSTsRx6mP2g9MG+tOMeIaU1HdmlSzzzt3O/2ONV2efL5pt1w6fqRYeG9xrZwFwn9F5ZWnJtM4pHqk38rSILZlh3Y1r258Mo5y3FsbBYCNNzBO2jDg70J7GX+ST2ThJgqFiW3Di+/vEQAJ5FsSSHcApW2rpHRX7R33QDy+r0T38VEmIneihehk5mmpWPYEmmb4p81B2suNcvysQEjWd+Z6jvljMWJ9j6+AV5hv13MDzufB2ufL2fetcEhda1/u8XbTI7Q81PHdyPynBuktiYa1FyLTquiWocBYI0yUMBxJgWsPm9+ac3vqb8X/p6PGGdf85+11LT7Qdo01QOx9dhZgNjNwwk6oOPomKKkTDY/AISobEioZ6bcnw3JvHKzSDWRbK95QAurQiChamnZjjjR7wPXL9sECr4HKVrsimUA5+1qklNlOfXoKjWrVnj6GigeZrWylWjAo6n2RTiBBAlWStU7Hc93sbxfzZGYJV8VfywxZhakaO9BnSZghk9G68hCn5GeUTB/4bMdOKgUM9fymuuUByXYGq6D0kwYHD7qtOKl47YcKZxM43X7XacFGQs21YPh0mzjdvVRvdbyv3rnka97oU0G+g7MtiWXpFIDRv4ZxJ1VPUSxfPNN9yiP9ftiKMz9PypT9shCSpfa9l+DgtSwT4UYJOTNBkvpK3nxLemaKcuPy2pOgcAEUtTSz7WlI47h3sioSDkLxoCy7Az0WrdLWlOFLwxdNTcFJPA+ba7STL1oksudruCCEuYKzuHoZcoRaWdDzqa0qvdx/1aPSQZEu3MN3W+9938ZIXTv3/n738edAK5Rg/B4/NGoB7FrgddEPf1asA27Mta9bOkCVG+MVsN+0f5cDMm5UWacpMhx"
`endif