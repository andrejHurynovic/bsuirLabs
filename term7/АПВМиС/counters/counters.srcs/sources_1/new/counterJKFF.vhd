library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity counterJKFF is
    Port ( clock, input, reset : in STD_LOGIC;
           output : out STD_LOGIC_VECTOR (7 downto 0));
end counterJKFF;

architecture Behavioral of counterJKFF is

signal outputData: STD_LOGIC_VECTOR (7 downto 0);
signal invertedOutputData: STD_LOGIC_VECTOR (7 downto 0);

begin
    JKFF0: entity work.JKFF(Behavioral) port map (
    clock             => clock, 
    jump              => input, 
    kill              => input, 
    asynchronousSet   => '0', 
    asynchronousReset => reset,
    output            => outputData(0),
    invertedOutput    => invertedOutputData(0));  
    
    JKFF : for index in 7 downto 1 generate
    begin
        JKFF: entity work.JKFF(Behavioral) port map (
        clock             => invertedOutputData(index-1), 
        jump              => input, 
        kill              => input, 
        asynchronousSet   => '0', 
        asynchronousReset => reset,
        output            => outputData(index),
        invertedOutput    => invertedOutputData(index));
    end generate;
        
    output <= outputData;

end Behavioral;
