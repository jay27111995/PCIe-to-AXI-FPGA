	component pcie_bridge_resetIP is
		port (
			ninit_done : out std_logic   -- reset
		);
	end component pcie_bridge_resetIP;

	u0 : component pcie_bridge_resetIP
		port map (
			ninit_done => CONNECTED_TO_ninit_done  -- ninit_done.reset
		);

