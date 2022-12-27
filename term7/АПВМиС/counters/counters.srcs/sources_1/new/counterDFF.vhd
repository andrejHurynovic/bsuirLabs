library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity counterDFF is
    Port ( 
    clock : in STD_LOGIC;
           input : in STD_LOGIC;
           reset : in STD_LOGIC;
           output : out STD_LOGIC_VECTOR (7 downto 0)
           );
end counterDFF;

architecture Behavioral of counterDFF is

signal outputs: STD_LOGIC_VECTOR (7 downto 0);
signal invertedOutputs: STD_LOGIC_VECTOR (7 downto 0);
signal invertedInput: STD_LOGIC;
begin
    
    invertedInput <= input;
    DFF0: entity work.DFF(Behavioral) port map (
        input             => invertedOutputs(0),
        clock             => invertedInput,
        asynchronousSet   => '0',
        asynchronousReset => reset,
        output            => outputs(0),
        invertedOutput    => invertedOutputs(0) 
    );
    
    DFF: for index in 7 downto 1 generate 
        DFF: entity work.DFF(Behavioral) port map (
        input             => invertedOutputs(index),
        clock             => invertedOutputs(index - 1),
        asynchronousSet   => '0',
        asynchronousReset => reset,
        output            => outputs(index),
        invertedOutput    => invertedOutputs(index) 
        );
    end generate;

    output <= invertedOutputs;
end Behavioral;
