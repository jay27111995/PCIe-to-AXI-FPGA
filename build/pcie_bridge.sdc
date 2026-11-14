# PCIe-to-AXI Bridge Timing Constraints
# These are basic constraints - the PCIe IP generates its own detailed constraints.

# Reference clock (100MHz from PCIe slot)  
create_clock -name refclk0 -period 10.000 [get_ports refclk0_clk]
create_clock -name refclk1 -period 10.000 [get_ports refclk1_clk]

# False paths for async resets
set_false_path -from [get_ports pin_perst_n_reset_n]

# The PCIe IP generates clocks internally (e.g. 500MHz coreclk)
# Those constraints come from the IP's auto-generated SDC file.

# Cut paths between clock domains (if any)
# set_clock_groups -asynchronous -group {clk_a} -group {clk_b}

# Relax timing on debug/status signals if needed
# set_false_path -to [get_registers {*debug*}]
