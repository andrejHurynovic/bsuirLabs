--Copyright (C) 1991-2009 Altera Corporation
--Your use of Altera Corporation's design tools, logic functions 
--and other software and tools, and its AMPP partner logic 
--functions, and any output files from any of the foregoing 
--(including device programming or simulation files), and any 
--associated documentation or information are expressly subject 
--to the terms and conditions of the Altera Program License 
--Subscription Agreement, Altera MegaCore Function License 
--Agreement, or other applicable license agreement, including, 
--without limitation, that your use is for the sole purpose of 
--programming logic devices manufactured by Altera and sold by 
--Altera or its authorized distributors.  Please refer to the 
--applicable agreement for further details.


FUNCTION lpm_decode0 
(
	data[3..0],
	enable
)

RETURNS (
	eq0,
	eq1,
	eq10,
	eq11,
	eq12,
	eq13,
	eq14,
	eq15,
	eq2,
	eq3,
	eq4,
	eq5,
	eq6,
	eq7,
	eq8,
	eq9
);
