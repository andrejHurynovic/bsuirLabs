library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity DFF is
    Port ( input, clock, asynchronousSet, asynchronousReset : in STD_LOGIC;
           output, invertedOutput : out STD_LOGIC);
end DFF;

architecture Behavioral of DFF is
    signal containedState: STD_LOGIC;
begin
    process(clock, asynchronousSet, asynchronousReset)
        begin
            if(asynchronousReset = '1') then
                output <= '0';
                invertedOutput <= '1';
            elsif ((asynchronousSet = '1')) then
                output <= '1';
                invertedOutput <= '0';
            elsif (clock'event AND clock = '1') then 
                output <= input;
                invertedOutput <= not(input);
            end if;
        end process;
        
end Behavioral;
