library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity JKFFsimulation is
end JKFFsimulation;

architecture Behavioral of JKFFsimulation is
    
    component JKFF 
        Port (
                clock, jump, kill, asynchronousSet, asynchronousReset: in  STD_LOGIC; 
                output: out STD_LOGIC     
            );
    end component;
    
    signal clock, jump, kill, asynchronousSet, asynchronousReset: STD_LOGIC; 
    signal output: STD_LOGIC;    
    
begin
    UUT: JKFF port map (
    clock             => clock, 
    jump              => jump, 
    kill              => kill, 
    asynchronousSet   => asynchronousSet, 
    asynchronousReset => asynchronousReset,
    output            => output);
    
    clocking: process
        begin
            clock <= '0';
            wait for 10 ns;
            clock <= '1';
            wait for 10 ns;    
    end process;
    
    simulation: process
        begin
 
        jump              <= '0';
        kill              <= '0';
        asynchronousSet   <= '0';
        asynchronousReset <= '0';

        wait for 30 ns; 
        jump <= '1';
        wait for 10 ns;
        jump <= '0';
        wait for 10 ns;
        kill <= '1';
        wait for 10 ns;
        kill <= '0';
        
        wait for 10 ns;
        jump <= '1';
        kill <= '1';
        wait for 100 ns;
        
        kill <= '1';
        jump <= '0';
        wait for 20 ns;
        jump <= '1';
        kill <= '0';
        wait for 10 ns;
        jump <= '0';
        wait for 25 ns;
        asynchronousReset <= '1';
        wait for 5 ns;
        asynchronousReset <= '0';
        wait for 20 ns;
        
        wait for 5 ns;
        asynchronousSet <= '1';
        wait for 5 ns;
        asynchronousSet <= '0';

        end process;
        
end Behavioral;
