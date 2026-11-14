	component pcie_bridge_axi_bridge_hw_0 is
		port (
			Clk_i                    : in  std_logic                      := 'X';             -- clk
			Rstn_i                   : in  std_logic                      := 'X';             -- reset_n
			rx_st0_payload_i         : in  std_logic_vector(255 downto 0) := (others => 'X'); -- data
			rx_st0_sop_i             : in  std_logic                      := 'X';             -- startofpacket
			rx_st0_eop_i             : in  std_logic                      := 'X';             -- endofpacket
			rx_st0_dvalid_i          : in  std_logic                      := 'X';             -- valid
			rx_st0_empty_i           : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- empty
			rx_st_ready_o            : out std_logic;                                         -- ready
			rx_st1_payload_i         : in  std_logic_vector(255 downto 0) := (others => 'X'); -- data
			rx_st1_sop_i             : in  std_logic                      := 'X';             -- startofpacket
			rx_st1_eop_i             : in  std_logic                      := 'X';             -- endofpacket
			rx_st1_dvalid_i          : in  std_logic                      := 'X';             -- valid
			rx_st1_empty_i           : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- empty
			rx_st2_payload_i         : in  std_logic_vector(255 downto 0) := (others => 'X'); -- data
			rx_st2_sop_i             : in  std_logic                      := 'X';             -- startofpacket
			rx_st2_eop_i             : in  std_logic                      := 'X';             -- endofpacket
			rx_st2_dvalid_i          : in  std_logic                      := 'X';             -- valid
			rx_st2_empty_i           : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- empty
			rx_st3_payload_i         : in  std_logic_vector(255 downto 0) := (others => 'X'); -- data
			rx_st3_sop_i             : in  std_logic                      := 'X';             -- startofpacket
			rx_st3_eop_i             : in  std_logic                      := 'X';             -- endofpacket
			rx_st3_dvalid_i          : in  std_logic                      := 'X';             -- valid
			rx_st3_empty_i           : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- empty
			rx_st_hcrdt_init_o       : out std_logic_vector(2 downto 0);                      -- rx_st_Hcrdt_init
			rx_st_hcrdt_update_o     : out std_logic_vector(2 downto 0);                      -- rx_st_Hcrdt_update
			rx_st_hcrdt_update_cnt_o : out std_logic_vector(5 downto 0);                      -- rx_st_Hcrdt_update_cnt
			rx_st_hcrdt_init_ack_i   : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- rx_st_Hcrdt_init_ack
			rx_st_dcrdt_init_o       : out std_logic_vector(2 downto 0);                      -- rx_st_Dcrdt_init
			rx_st_dcrdt_update_o     : out std_logic_vector(2 downto 0);                      -- rx_st_Dcrdt_update
			rx_st_dcrdt_update_cnt_o : out std_logic_vector(11 downto 0);                     -- rx_st_Dcrdt_update_cnt
			rx_st_dcrdt_init_ack_i   : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- rx_st_Dcrdt_init_ack
			rx_st0_header_i          : in  std_logic_vector(127 downto 0) := (others => 'X'); -- rx_st0_hdr
			rx_st0_tlp_prfx_i        : in  std_logic_vector(31 downto 0)  := (others => 'X'); -- rx_st0_prefix
			rx_st0_hvalid_i          : in  std_logic                      := 'X';             -- rx_st0_hvalid
			rx_st0_pvalid_i          : in  std_logic                      := 'X';             -- rx_st0_pvalid
			rx_st0_bar_i             : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- rx_st0_bar
			rx_st1_header_i          : in  std_logic_vector(127 downto 0) := (others => 'X'); -- rx_st1_hdr
			rx_st1_tlp_prfx_i        : in  std_logic_vector(31 downto 0)  := (others => 'X'); -- rx_st1_prefix
			rx_st1_hvalid_i          : in  std_logic                      := 'X';             -- rx_st1_hvalid
			rx_st1_pvalid_i          : in  std_logic                      := 'X';             -- rx_st1_pvalid
			rx_st1_bar_i             : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- rx_st1_bar
			rx_st2_header_i          : in  std_logic_vector(127 downto 0) := (others => 'X'); -- rx_st2_hdr
			rx_st2_tlp_prfx_i        : in  std_logic_vector(31 downto 0)  := (others => 'X'); -- rx_st2_prefix
			rx_st2_hvalid_i          : in  std_logic                      := 'X';             -- rx_st2_hvalid
			rx_st2_pvalid_i          : in  std_logic                      := 'X';             -- rx_st2_pvalid
			rx_st2_bar_i             : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- rx_st2_bar
			rx_st3_header_i          : in  std_logic_vector(127 downto 0) := (others => 'X'); -- rx_st3_hdr
			rx_st3_tlp_prfx_i        : in  std_logic_vector(31 downto 0)  := (others => 'X'); -- rx_st3_prefix
			rx_st3_hvalid_i          : in  std_logic                      := 'X';             -- rx_st3_hvalid
			rx_st3_pvalid_i          : in  std_logic                      := 'X';             -- rx_st3_pvalid
			rx_st3_bar_i             : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- rx_st3_bar
			tx_st0_payload_o         : out std_logic_vector(255 downto 0);                    -- data
			tx_st0_sop_o             : out std_logic;                                         -- startofpacket
			tx_st0_eop_o             : out std_logic;                                         -- endofpacket
			tx_st0_dvalid_o          : out std_logic;                                         -- valid
			tx_st_ready_i            : in  std_logic                      := 'X';             -- ready
			tx_st1_payload_o         : out std_logic_vector(255 downto 0);                    -- data
			tx_st1_sop_o             : out std_logic;                                         -- startofpacket
			tx_st1_eop_o             : out std_logic;                                         -- endofpacket
			tx_st1_dvalid_o          : out std_logic;                                         -- valid
			tx_st2_payload_o         : out std_logic_vector(255 downto 0);                    -- data
			tx_st2_sop_o             : out std_logic;                                         -- startofpacket
			tx_st2_eop_o             : out std_logic;                                         -- endofpacket
			tx_st2_dvalid_o          : out std_logic;                                         -- valid
			tx_st3_payload_o         : out std_logic_vector(255 downto 0);                    -- data
			tx_st3_sop_o             : out std_logic;                                         -- startofpacket
			tx_st3_eop_o             : out std_logic;                                         -- endofpacket
			tx_st3_dvalid_o          : out std_logic;                                         -- valid
			tx_st0_header_o          : out std_logic_vector(127 downto 0);                    -- tx_st0_hdr
			tx_st1_header_o          : out std_logic_vector(127 downto 0);                    -- tx_st1_hdr
			tx_st2_header_o          : out std_logic_vector(127 downto 0);                    -- tx_st2_hdr
			tx_st3_header_o          : out std_logic_vector(127 downto 0);                    -- tx_st3_hdr
			tx_st_hcrdt_init_i       : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- tx_st_Hcrdt_init
			tx_st_hcrdt_update_i     : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- tx_st_Hcrdt_update
			tx_st_hcrdt_update_cnt_i : in  std_logic_vector(5 downto 0)   := (others => 'X'); -- tx_st_Hcrdt_update_cnt
			tx_st_hcrdt_init_ack_o   : out std_logic_vector(2 downto 0);                      -- tx_st_Hcrdtt_init_ack
			tx_st_dcrdt_init_i       : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- tx_st_Dcrdt_init
			tx_st_dcrdt_update_i     : in  std_logic_vector(2 downto 0)   := (others => 'X'); -- tx_st_Dcrdt_update
			tx_st_dcrdt_update_cnt_i : in  std_logic_vector(11 downto 0)  := (others => 'X'); -- tx_st_Dcrdt_update_cnt
			tx_st_dcrdt_init_ack_o   : out std_logic_vector(2 downto 0);                      -- tx_st_Dcrdt_init_ack
			tx_st0_prefix_o          : out std_logic_vector(31 downto 0);                     -- tx_st0_prefix
			tx_st0_hvalid_o          : out std_logic;                                         -- tx_st0_hvalid
			tx_st0_pvalid_o          : out std_logic;                                         -- tx_st0_pvalid
			tx_st1_prefix_o          : out std_logic_vector(31 downto 0);                     -- tx_st1_prefix
			tx_st1_hvalid_o          : out std_logic;                                         -- tx_st1_hvalid
			tx_st1_pvalid_o          : out std_logic;                                         -- tx_st1_pvalid
			tx_st2_prefix_o          : out std_logic_vector(31 downto 0);                     -- tx_st2_prefix
			tx_st2_hvalid_o          : out std_logic;                                         -- tx_st2_hvalid
			tx_st2_pvalid_o          : out std_logic;                                         -- tx_st2_pvalid
			tx_st3_prefix_o          : out std_logic_vector(31 downto 0);                     -- tx_st3_prefix
			tx_st3_hvalid_o          : out std_logic;                                         -- tx_st3_hvalid
			tx_st3_pvalid_o          : out std_logic                                          -- tx_st3_pvalid
		);
	end component pcie_bridge_axi_bridge_hw_0;

	u0 : component pcie_bridge_axi_bridge_hw_0
		port map (
			Clk_i                    => CONNECTED_TO_Clk_i,                    --         clk.clk
			Rstn_i                   => CONNECTED_TO_Rstn_i,                   --       reset.reset_n
			rx_st0_payload_i         => CONNECTED_TO_rx_st0_payload_i,         --      rx_st0.data
			rx_st0_sop_i             => CONNECTED_TO_rx_st0_sop_i,             --            .startofpacket
			rx_st0_eop_i             => CONNECTED_TO_rx_st0_eop_i,             --            .endofpacket
			rx_st0_dvalid_i          => CONNECTED_TO_rx_st0_dvalid_i,          --            .valid
			rx_st0_empty_i           => CONNECTED_TO_rx_st0_empty_i,           --            .empty
			rx_st_ready_o            => CONNECTED_TO_rx_st_ready_o,            --            .ready
			rx_st1_payload_i         => CONNECTED_TO_rx_st1_payload_i,         --      rx_st1.data
			rx_st1_sop_i             => CONNECTED_TO_rx_st1_sop_i,             --            .startofpacket
			rx_st1_eop_i             => CONNECTED_TO_rx_st1_eop_i,             --            .endofpacket
			rx_st1_dvalid_i          => CONNECTED_TO_rx_st1_dvalid_i,          --            .valid
			rx_st1_empty_i           => CONNECTED_TO_rx_st1_empty_i,           --            .empty
			rx_st2_payload_i         => CONNECTED_TO_rx_st2_payload_i,         --      rx_st2.data
			rx_st2_sop_i             => CONNECTED_TO_rx_st2_sop_i,             --            .startofpacket
			rx_st2_eop_i             => CONNECTED_TO_rx_st2_eop_i,             --            .endofpacket
			rx_st2_dvalid_i          => CONNECTED_TO_rx_st2_dvalid_i,          --            .valid
			rx_st2_empty_i           => CONNECTED_TO_rx_st2_empty_i,           --            .empty
			rx_st3_payload_i         => CONNECTED_TO_rx_st3_payload_i,         --      rx_st3.data
			rx_st3_sop_i             => CONNECTED_TO_rx_st3_sop_i,             --            .startofpacket
			rx_st3_eop_i             => CONNECTED_TO_rx_st3_eop_i,             --            .endofpacket
			rx_st3_dvalid_i          => CONNECTED_TO_rx_st3_dvalid_i,          --            .valid
			rx_st3_empty_i           => CONNECTED_TO_rx_st3_empty_i,           --            .empty
			rx_st_hcrdt_init_o       => CONNECTED_TO_rx_st_hcrdt_init_o,       -- rx_st0_misc.rx_st_Hcrdt_init
			rx_st_hcrdt_update_o     => CONNECTED_TO_rx_st_hcrdt_update_o,     --            .rx_st_Hcrdt_update
			rx_st_hcrdt_update_cnt_o => CONNECTED_TO_rx_st_hcrdt_update_cnt_o, --            .rx_st_Hcrdt_update_cnt
			rx_st_hcrdt_init_ack_i   => CONNECTED_TO_rx_st_hcrdt_init_ack_i,   --            .rx_st_Hcrdt_init_ack
			rx_st_dcrdt_init_o       => CONNECTED_TO_rx_st_dcrdt_init_o,       --            .rx_st_Dcrdt_init
			rx_st_dcrdt_update_o     => CONNECTED_TO_rx_st_dcrdt_update_o,     --            .rx_st_Dcrdt_update
			rx_st_dcrdt_update_cnt_o => CONNECTED_TO_rx_st_dcrdt_update_cnt_o, --            .rx_st_Dcrdt_update_cnt
			rx_st_dcrdt_init_ack_i   => CONNECTED_TO_rx_st_dcrdt_init_ack_i,   --            .rx_st_Dcrdt_init_ack
			rx_st0_header_i          => CONNECTED_TO_rx_st0_header_i,          --            .rx_st0_hdr
			rx_st0_tlp_prfx_i        => CONNECTED_TO_rx_st0_tlp_prfx_i,        --            .rx_st0_prefix
			rx_st0_hvalid_i          => CONNECTED_TO_rx_st0_hvalid_i,          --            .rx_st0_hvalid
			rx_st0_pvalid_i          => CONNECTED_TO_rx_st0_pvalid_i,          --            .rx_st0_pvalid
			rx_st0_bar_i             => CONNECTED_TO_rx_st0_bar_i,             --            .rx_st0_bar
			rx_st1_header_i          => CONNECTED_TO_rx_st1_header_i,          --            .rx_st1_hdr
			rx_st1_tlp_prfx_i        => CONNECTED_TO_rx_st1_tlp_prfx_i,        --            .rx_st1_prefix
			rx_st1_hvalid_i          => CONNECTED_TO_rx_st1_hvalid_i,          --            .rx_st1_hvalid
			rx_st1_pvalid_i          => CONNECTED_TO_rx_st1_pvalid_i,          --            .rx_st1_pvalid
			rx_st1_bar_i             => CONNECTED_TO_rx_st1_bar_i,             --            .rx_st1_bar
			rx_st2_header_i          => CONNECTED_TO_rx_st2_header_i,          --            .rx_st2_hdr
			rx_st2_tlp_prfx_i        => CONNECTED_TO_rx_st2_tlp_prfx_i,        --            .rx_st2_prefix
			rx_st2_hvalid_i          => CONNECTED_TO_rx_st2_hvalid_i,          --            .rx_st2_hvalid
			rx_st2_pvalid_i          => CONNECTED_TO_rx_st2_pvalid_i,          --            .rx_st2_pvalid
			rx_st2_bar_i             => CONNECTED_TO_rx_st2_bar_i,             --            .rx_st2_bar
			rx_st3_header_i          => CONNECTED_TO_rx_st3_header_i,          --            .rx_st3_hdr
			rx_st3_tlp_prfx_i        => CONNECTED_TO_rx_st3_tlp_prfx_i,        --            .rx_st3_prefix
			rx_st3_hvalid_i          => CONNECTED_TO_rx_st3_hvalid_i,          --            .rx_st3_hvalid
			rx_st3_pvalid_i          => CONNECTED_TO_rx_st3_pvalid_i,          --            .rx_st3_pvalid
			rx_st3_bar_i             => CONNECTED_TO_rx_st3_bar_i,             --            .rx_st3_bar
			tx_st0_payload_o         => CONNECTED_TO_tx_st0_payload_o,         --      tx_st0.data
			tx_st0_sop_o             => CONNECTED_TO_tx_st0_sop_o,             --            .startofpacket
			tx_st0_eop_o             => CONNECTED_TO_tx_st0_eop_o,             --            .endofpacket
			tx_st0_dvalid_o          => CONNECTED_TO_tx_st0_dvalid_o,          --            .valid
			tx_st_ready_i            => CONNECTED_TO_tx_st_ready_i,            --            .ready
			tx_st1_payload_o         => CONNECTED_TO_tx_st1_payload_o,         --      tx_st1.data
			tx_st1_sop_o             => CONNECTED_TO_tx_st1_sop_o,             --            .startofpacket
			tx_st1_eop_o             => CONNECTED_TO_tx_st1_eop_o,             --            .endofpacket
			tx_st1_dvalid_o          => CONNECTED_TO_tx_st1_dvalid_o,          --            .valid
			tx_st2_payload_o         => CONNECTED_TO_tx_st2_payload_o,         --      tx_st2.data
			tx_st2_sop_o             => CONNECTED_TO_tx_st2_sop_o,             --            .startofpacket
			tx_st2_eop_o             => CONNECTED_TO_tx_st2_eop_o,             --            .endofpacket
			tx_st2_dvalid_o          => CONNECTED_TO_tx_st2_dvalid_o,          --            .valid
			tx_st3_payload_o         => CONNECTED_TO_tx_st3_payload_o,         --      tx_st3.data
			tx_st3_sop_o             => CONNECTED_TO_tx_st3_sop_o,             --            .startofpacket
			tx_st3_eop_o             => CONNECTED_TO_tx_st3_eop_o,             --            .endofpacket
			tx_st3_dvalid_o          => CONNECTED_TO_tx_st3_dvalid_o,          --            .valid
			tx_st0_header_o          => CONNECTED_TO_tx_st0_header_o,          -- tx_st0_misc.tx_st0_hdr
			tx_st1_header_o          => CONNECTED_TO_tx_st1_header_o,          --            .tx_st1_hdr
			tx_st2_header_o          => CONNECTED_TO_tx_st2_header_o,          --            .tx_st2_hdr
			tx_st3_header_o          => CONNECTED_TO_tx_st3_header_o,          --            .tx_st3_hdr
			tx_st_hcrdt_init_i       => CONNECTED_TO_tx_st_hcrdt_init_i,       --            .tx_st_Hcrdt_init
			tx_st_hcrdt_update_i     => CONNECTED_TO_tx_st_hcrdt_update_i,     --            .tx_st_Hcrdt_update
			tx_st_hcrdt_update_cnt_i => CONNECTED_TO_tx_st_hcrdt_update_cnt_i, --            .tx_st_Hcrdt_update_cnt
			tx_st_hcrdt_init_ack_o   => CONNECTED_TO_tx_st_hcrdt_init_ack_o,   --            .tx_st_Hcrdtt_init_ack
			tx_st_dcrdt_init_i       => CONNECTED_TO_tx_st_dcrdt_init_i,       --            .tx_st_Dcrdt_init
			tx_st_dcrdt_update_i     => CONNECTED_TO_tx_st_dcrdt_update_i,     --            .tx_st_Dcrdt_update
			tx_st_dcrdt_update_cnt_i => CONNECTED_TO_tx_st_dcrdt_update_cnt_i, --            .tx_st_Dcrdt_update_cnt
			tx_st_dcrdt_init_ack_o   => CONNECTED_TO_tx_st_dcrdt_init_ack_o,   --            .tx_st_Dcrdt_init_ack
			tx_st0_prefix_o          => CONNECTED_TO_tx_st0_prefix_o,          --            .tx_st0_prefix
			tx_st0_hvalid_o          => CONNECTED_TO_tx_st0_hvalid_o,          --            .tx_st0_hvalid
			tx_st0_pvalid_o          => CONNECTED_TO_tx_st0_pvalid_o,          --            .tx_st0_pvalid
			tx_st1_prefix_o          => CONNECTED_TO_tx_st1_prefix_o,          --            .tx_st1_prefix
			tx_st1_hvalid_o          => CONNECTED_TO_tx_st1_hvalid_o,          --            .tx_st1_hvalid
			tx_st1_pvalid_o          => CONNECTED_TO_tx_st1_pvalid_o,          --            .tx_st1_pvalid
			tx_st2_prefix_o          => CONNECTED_TO_tx_st2_prefix_o,          --            .tx_st2_prefix
			tx_st2_hvalid_o          => CONNECTED_TO_tx_st2_hvalid_o,          --            .tx_st2_hvalid
			tx_st2_pvalid_o          => CONNECTED_TO_tx_st2_pvalid_o,          --            .tx_st2_pvalid
			tx_st3_prefix_o          => CONNECTED_TO_tx_st3_prefix_o,          --            .tx_st3_prefix
			tx_st3_hvalid_o          => CONNECTED_TO_tx_st3_hvalid_o,          --            .tx_st3_hvalid
			tx_st3_pvalid_o          => CONNECTED_TO_tx_st3_pvalid_o           --            .tx_st3_pvalid
		);

