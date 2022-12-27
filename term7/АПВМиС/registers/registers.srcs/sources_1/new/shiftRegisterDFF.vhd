library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity shiftRegisterDFF is
    Port ( 
        clock, input, reset : in STD_LOGIC;
        output : out STD_LOGIC_VECTOR (7 downto 0)
    );
end shiftRegisterDFF;

architecture Behavioral of shiftRegisterDFF is

signal outputs: STD_LOGIC_VECTOR (7 downto 0);
signal invertedOutputs: STD_LOGIC_VECTOR (7 downto 0);
begin

    DFF0: entity work.DFF port map (
    input             => input,
    clock             => clock,
    asynchronousSet   => '0',
    asynchronousReset => reset,
    output            => outputs(0),
    invertedOutput    => invertedOutputs(0) 
    );
    
    DFFgenerate: for index in 7 downto 1 generate
    begin 
    
    DFF: entity work.DFF port map (
    input             => outputs(index - 1),
    clock             => clock,
    asynchronousSet   => '0',
    asynchronousReset => reset,
    output            => outputs(index),
    invertedOutput    => invertedOutputs(index) 
    );
    
    end generate; 
    
    output <= outputs;

end Behavioral;
