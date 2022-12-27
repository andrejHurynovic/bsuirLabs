library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity DFFsimulation is
end DFFsimulation;

architecture Behavioral of DFFsimulation is
    component DFF 
        Port (
            input, clock, asynchronousSet, asynchronousReset : in STD_LOGIC;
            output : out STD_LOGIC
        ); 
    end component;

    signal input, clock, asynchronousSet, asynchronousReset: STD_LOGIC;
    signal output: STD_LOGIC;
begin
    UUT: DFF port map (
        input => input, 
        clock => clock, 
        output => output,
        asynchronousSet => asynchronousSet,
        asynchronousReset => asynchronousReset
    );
    simulation: process
        begin
            input <= '1';
            clock <= '0';
            asynchronousSet <= '0';
            asynchronousReset <= '0';
            wait for 10 ns;
            
            clock <= '1';
            wait for 10 ns;
            clock <= '0';
            wait for 10 ns;
            
            clock <= '1';
            wait for 10 ns;
            clock <= '0';
            wait for 10 ns;
            
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
                            
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
            
            
            
            asynchronousReset <= '1';
            
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
                            
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
            
            asynchronousReset <= '0';
            
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
                            
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
            
            input <= '0';
   
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
   
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
            
            clock <= '1';   
            wait for 5 ns; 
            asynchronousSet <= '1';
            wait for 5 ns; 
            clock <= '0';   
            wait for 10 ns; 
   
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
                        
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
            asynchronousSet <= '0';
            
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns; 
                        
            clock <= '1';   
            wait for 10 ns; 
            clock <= '0';   
            wait for 10 ns;
            
        end process;
end Behavioral;
