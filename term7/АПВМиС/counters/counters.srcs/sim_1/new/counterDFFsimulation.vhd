library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity counterDFFsimulation is
end counterDFFsimulation;

architecture Behavioral of counterDFFsimulation is
    component counterDFF
        Port ( 
            clock : in STD_LOGIC;
            input : in STD_LOGIC;
            reset : in STD_LOGIC;
            output : out STD_LOGIC_VECTOR (7 downto 0)
        );
    end component;
    
    signal clock, input, reset: STD_LOGIC;
    signal output: STD_LOGIC_VECTOR (7 downto 0);
begin

    UUT: counterDFF port map (
        clock  => clock,         
        input  => input,     
        reset  => reset,     
        output => output    
    );

    clocking: process
    begin
        clock <= '0';
        wait for 10 ns; 
        clock <= '1';
        wait for 10 ns;
    end process;
    
        resetPro: process
    begin
        reset <= '1';
        wait for 10 ns;
        reset <= '0';
        wait for 5000 ns;
        end process;
    
    simulation: process
    begin

        input <= '0';      
        wait for 10 ns;
        input <= '1';
        wait for 30 ns;
    end process;


end Behavioral;
