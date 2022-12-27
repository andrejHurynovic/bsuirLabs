library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity JKFF is
    Port (
        clock, jump, kill, asynchronousSet, asynchronousReset: in  STD_LOGIC; 
        output: out STD_LOGIC     
    );
end JKFF;

architecture Behavioral of JKFF is
begin
    process(clock, asynchronousSet, asynchronousReset)
        
        variable state: STD_LOGIC := '0';
        begin
        if asynchronousReset = '1' then
            state := '0';
        elsif asynchronousSet = '1' then
            state := '1';
        elsif clock'event and clock = '1' then 
            if jump = '1' and kill = '1' then
                state := not(state);
            elsif kill = '1' then 
                state := '0';
            elsif jump = '1' then
                state := '1';
            end if;
        end if;
        output <= state;   end process;

end Behavioral;
