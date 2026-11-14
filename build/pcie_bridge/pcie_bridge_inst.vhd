	component pcie_bridge is
		port (
			hip_serial_rx_n_in0   : in  std_logic := 'X'; -- rx_n_in0
			hip_serial_rx_n_in1   : in  std_logic := 'X'; -- rx_n_in1
			hip_serial_rx_n_in2   : in  std_logic := 'X'; -- rx_n_in2
			hip_serial_rx_n_in3   : in  std_logic := 'X'; -- rx_n_in3
			hip_serial_rx_n_in4   : in  std_logic := 'X'; -- rx_n_in4
			hip_serial_rx_n_in5   : in  std_logic := 'X'; -- rx_n_in5
			hip_serial_rx_n_in6   : in  std_logic := 'X'; -- rx_n_in6
			hip_serial_rx_n_in7   : in  std_logic := 'X'; -- rx_n_in7
			hip_serial_rx_n_in8   : in  std_logic := 'X'; -- rx_n_in8
			hip_serial_rx_n_in9   : in  std_logic := 'X'; -- rx_n_in9
			hip_serial_rx_n_in10  : in  std_logic := 'X'; -- rx_n_in10
			hip_serial_rx_n_in11  : in  std_logic := 'X'; -- rx_n_in11
			hip_serial_rx_n_in12  : in  std_logic := 'X'; -- rx_n_in12
			hip_serial_rx_n_in13  : in  std_logic := 'X'; -- rx_n_in13
			hip_serial_rx_n_in14  : in  std_logic := 'X'; -- rx_n_in14
			hip_serial_rx_n_in15  : in  std_logic := 'X'; -- rx_n_in15
			hip_serial_rx_p_in0   : in  std_logic := 'X'; -- rx_p_in0
			hip_serial_rx_p_in1   : in  std_logic := 'X'; -- rx_p_in1
			hip_serial_rx_p_in2   : in  std_logic := 'X'; -- rx_p_in2
			hip_serial_rx_p_in3   : in  std_logic := 'X'; -- rx_p_in3
			hip_serial_rx_p_in4   : in  std_logic := 'X'; -- rx_p_in4
			hip_serial_rx_p_in5   : in  std_logic := 'X'; -- rx_p_in5
			hip_serial_rx_p_in6   : in  std_logic := 'X'; -- rx_p_in6
			hip_serial_rx_p_in7   : in  std_logic := 'X'; -- rx_p_in7
			hip_serial_rx_p_in8   : in  std_logic := 'X'; -- rx_p_in8
			hip_serial_rx_p_in9   : in  std_logic := 'X'; -- rx_p_in9
			hip_serial_rx_p_in10  : in  std_logic := 'X'; -- rx_p_in10
			hip_serial_rx_p_in11  : in  std_logic := 'X'; -- rx_p_in11
			hip_serial_rx_p_in12  : in  std_logic := 'X'; -- rx_p_in12
			hip_serial_rx_p_in13  : in  std_logic := 'X'; -- rx_p_in13
			hip_serial_rx_p_in14  : in  std_logic := 'X'; -- rx_p_in14
			hip_serial_rx_p_in15  : in  std_logic := 'X'; -- rx_p_in15
			hip_serial_tx_n_out0  : out std_logic;        -- tx_n_out0
			hip_serial_tx_n_out1  : out std_logic;        -- tx_n_out1
			hip_serial_tx_n_out2  : out std_logic;        -- tx_n_out2
			hip_serial_tx_n_out3  : out std_logic;        -- tx_n_out3
			hip_serial_tx_n_out4  : out std_logic;        -- tx_n_out4
			hip_serial_tx_n_out5  : out std_logic;        -- tx_n_out5
			hip_serial_tx_n_out6  : out std_logic;        -- tx_n_out6
			hip_serial_tx_n_out7  : out std_logic;        -- tx_n_out7
			hip_serial_tx_n_out8  : out std_logic;        -- tx_n_out8
			hip_serial_tx_n_out9  : out std_logic;        -- tx_n_out9
			hip_serial_tx_n_out10 : out std_logic;        -- tx_n_out10
			hip_serial_tx_n_out11 : out std_logic;        -- tx_n_out11
			hip_serial_tx_n_out12 : out std_logic;        -- tx_n_out12
			hip_serial_tx_n_out13 : out std_logic;        -- tx_n_out13
			hip_serial_tx_n_out14 : out std_logic;        -- tx_n_out14
			hip_serial_tx_n_out15 : out std_logic;        -- tx_n_out15
			hip_serial_tx_p_out0  : out std_logic;        -- tx_p_out0
			hip_serial_tx_p_out1  : out std_logic;        -- tx_p_out1
			hip_serial_tx_p_out2  : out std_logic;        -- tx_p_out2
			hip_serial_tx_p_out3  : out std_logic;        -- tx_p_out3
			hip_serial_tx_p_out4  : out std_logic;        -- tx_p_out4
			hip_serial_tx_p_out5  : out std_logic;        -- tx_p_out5
			hip_serial_tx_p_out6  : out std_logic;        -- tx_p_out6
			hip_serial_tx_p_out7  : out std_logic;        -- tx_p_out7
			hip_serial_tx_p_out8  : out std_logic;        -- tx_p_out8
			hip_serial_tx_p_out9  : out std_logic;        -- tx_p_out9
			hip_serial_tx_p_out10 : out std_logic;        -- tx_p_out10
			hip_serial_tx_p_out11 : out std_logic;        -- tx_p_out11
			hip_serial_tx_p_out12 : out std_logic;        -- tx_p_out12
			hip_serial_tx_p_out13 : out std_logic;        -- tx_p_out13
			hip_serial_tx_p_out14 : out std_logic;        -- tx_p_out14
			hip_serial_tx_p_out15 : out std_logic;        -- tx_p_out15
			refclk0_clk           : in  std_logic := 'X'; -- clk
			refclk1_clk           : in  std_logic := 'X'; -- clk
			pin_perst_reset_n     : in  std_logic := 'X'  -- reset_n
		);
	end component pcie_bridge;

	u0 : component pcie_bridge
		port map (
			hip_serial_rx_n_in0   => CONNECTED_TO_hip_serial_rx_n_in0,   -- hip_serial.rx_n_in0
			hip_serial_rx_n_in1   => CONNECTED_TO_hip_serial_rx_n_in1,   --           .rx_n_in1
			hip_serial_rx_n_in2   => CONNECTED_TO_hip_serial_rx_n_in2,   --           .rx_n_in2
			hip_serial_rx_n_in3   => CONNECTED_TO_hip_serial_rx_n_in3,   --           .rx_n_in3
			hip_serial_rx_n_in4   => CONNECTED_TO_hip_serial_rx_n_in4,   --           .rx_n_in4
			hip_serial_rx_n_in5   => CONNECTED_TO_hip_serial_rx_n_in5,   --           .rx_n_in5
			hip_serial_rx_n_in6   => CONNECTED_TO_hip_serial_rx_n_in6,   --           .rx_n_in6
			hip_serial_rx_n_in7   => CONNECTED_TO_hip_serial_rx_n_in7,   --           .rx_n_in7
			hip_serial_rx_n_in8   => CONNECTED_TO_hip_serial_rx_n_in8,   --           .rx_n_in8
			hip_serial_rx_n_in9   => CONNECTED_TO_hip_serial_rx_n_in9,   --           .rx_n_in9
			hip_serial_rx_n_in10  => CONNECTED_TO_hip_serial_rx_n_in10,  --           .rx_n_in10
			hip_serial_rx_n_in11  => CONNECTED_TO_hip_serial_rx_n_in11,  --           .rx_n_in11
			hip_serial_rx_n_in12  => CONNECTED_TO_hip_serial_rx_n_in12,  --           .rx_n_in12
			hip_serial_rx_n_in13  => CONNECTED_TO_hip_serial_rx_n_in13,  --           .rx_n_in13
			hip_serial_rx_n_in14  => CONNECTED_TO_hip_serial_rx_n_in14,  --           .rx_n_in14
			hip_serial_rx_n_in15  => CONNECTED_TO_hip_serial_rx_n_in15,  --           .rx_n_in15
			hip_serial_rx_p_in0   => CONNECTED_TO_hip_serial_rx_p_in0,   --           .rx_p_in0
			hip_serial_rx_p_in1   => CONNECTED_TO_hip_serial_rx_p_in1,   --           .rx_p_in1
			hip_serial_rx_p_in2   => CONNECTED_TO_hip_serial_rx_p_in2,   --           .rx_p_in2
			hip_serial_rx_p_in3   => CONNECTED_TO_hip_serial_rx_p_in3,   --           .rx_p_in3
			hip_serial_rx_p_in4   => CONNECTED_TO_hip_serial_rx_p_in4,   --           .rx_p_in4
			hip_serial_rx_p_in5   => CONNECTED_TO_hip_serial_rx_p_in5,   --           .rx_p_in5
			hip_serial_rx_p_in6   => CONNECTED_TO_hip_serial_rx_p_in6,   --           .rx_p_in6
			hip_serial_rx_p_in7   => CONNECTED_TO_hip_serial_rx_p_in7,   --           .rx_p_in7
			hip_serial_rx_p_in8   => CONNECTED_TO_hip_serial_rx_p_in8,   --           .rx_p_in8
			hip_serial_rx_p_in9   => CONNECTED_TO_hip_serial_rx_p_in9,   --           .rx_p_in9
			hip_serial_rx_p_in10  => CONNECTED_TO_hip_serial_rx_p_in10,  --           .rx_p_in10
			hip_serial_rx_p_in11  => CONNECTED_TO_hip_serial_rx_p_in11,  --           .rx_p_in11
			hip_serial_rx_p_in12  => CONNECTED_TO_hip_serial_rx_p_in12,  --           .rx_p_in12
			hip_serial_rx_p_in13  => CONNECTED_TO_hip_serial_rx_p_in13,  --           .rx_p_in13
			hip_serial_rx_p_in14  => CONNECTED_TO_hip_serial_rx_p_in14,  --           .rx_p_in14
			hip_serial_rx_p_in15  => CONNECTED_TO_hip_serial_rx_p_in15,  --           .rx_p_in15
			hip_serial_tx_n_out0  => CONNECTED_TO_hip_serial_tx_n_out0,  --           .tx_n_out0
			hip_serial_tx_n_out1  => CONNECTED_TO_hip_serial_tx_n_out1,  --           .tx_n_out1
			hip_serial_tx_n_out2  => CONNECTED_TO_hip_serial_tx_n_out2,  --           .tx_n_out2
			hip_serial_tx_n_out3  => CONNECTED_TO_hip_serial_tx_n_out3,  --           .tx_n_out3
			hip_serial_tx_n_out4  => CONNECTED_TO_hip_serial_tx_n_out4,  --           .tx_n_out4
			hip_serial_tx_n_out5  => CONNECTED_TO_hip_serial_tx_n_out5,  --           .tx_n_out5
			hip_serial_tx_n_out6  => CONNECTED_TO_hip_serial_tx_n_out6,  --           .tx_n_out6
			hip_serial_tx_n_out7  => CONNECTED_TO_hip_serial_tx_n_out7,  --           .tx_n_out7
			hip_serial_tx_n_out8  => CONNECTED_TO_hip_serial_tx_n_out8,  --           .tx_n_out8
			hip_serial_tx_n_out9  => CONNECTED_TO_hip_serial_tx_n_out9,  --           .tx_n_out9
			hip_serial_tx_n_out10 => CONNECTED_TO_hip_serial_tx_n_out10, --           .tx_n_out10
			hip_serial_tx_n_out11 => CONNECTED_TO_hip_serial_tx_n_out11, --           .tx_n_out11
			hip_serial_tx_n_out12 => CONNECTED_TO_hip_serial_tx_n_out12, --           .tx_n_out12
			hip_serial_tx_n_out13 => CONNECTED_TO_hip_serial_tx_n_out13, --           .tx_n_out13
			hip_serial_tx_n_out14 => CONNECTED_TO_hip_serial_tx_n_out14, --           .tx_n_out14
			hip_serial_tx_n_out15 => CONNECTED_TO_hip_serial_tx_n_out15, --           .tx_n_out15
			hip_serial_tx_p_out0  => CONNECTED_TO_hip_serial_tx_p_out0,  --           .tx_p_out0
			hip_serial_tx_p_out1  => CONNECTED_TO_hip_serial_tx_p_out1,  --           .tx_p_out1
			hip_serial_tx_p_out2  => CONNECTED_TO_hip_serial_tx_p_out2,  --           .tx_p_out2
			hip_serial_tx_p_out3  => CONNECTED_TO_hip_serial_tx_p_out3,  --           .tx_p_out3
			hip_serial_tx_p_out4  => CONNECTED_TO_hip_serial_tx_p_out4,  --           .tx_p_out4
			hip_serial_tx_p_out5  => CONNECTED_TO_hip_serial_tx_p_out5,  --           .tx_p_out5
			hip_serial_tx_p_out6  => CONNECTED_TO_hip_serial_tx_p_out6,  --           .tx_p_out6
			hip_serial_tx_p_out7  => CONNECTED_TO_hip_serial_tx_p_out7,  --           .tx_p_out7
			hip_serial_tx_p_out8  => CONNECTED_TO_hip_serial_tx_p_out8,  --           .tx_p_out8
			hip_serial_tx_p_out9  => CONNECTED_TO_hip_serial_tx_p_out9,  --           .tx_p_out9
			hip_serial_tx_p_out10 => CONNECTED_TO_hip_serial_tx_p_out10, --           .tx_p_out10
			hip_serial_tx_p_out11 => CONNECTED_TO_hip_serial_tx_p_out11, --           .tx_p_out11
			hip_serial_tx_p_out12 => CONNECTED_TO_hip_serial_tx_p_out12, --           .tx_p_out12
			hip_serial_tx_p_out13 => CONNECTED_TO_hip_serial_tx_p_out13, --           .tx_p_out13
			hip_serial_tx_p_out14 => CONNECTED_TO_hip_serial_tx_p_out14, --           .tx_p_out14
			hip_serial_tx_p_out15 => CONNECTED_TO_hip_serial_tx_p_out15, --           .tx_p_out15
			refclk0_clk           => CONNECTED_TO_refclk0_clk,           --    refclk0.clk
			refclk1_clk           => CONNECTED_TO_refclk1_clk,           --    refclk1.clk
			pin_perst_reset_n     => CONNECTED_TO_pin_perst_reset_n      --  pin_perst.reset_n
		);

