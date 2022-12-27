library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity counterJKFFsimulation is
end counterJKFFsimulation;

architecture Behavioral of counterJKFFsimulation is

    component counterJKFF
        Port ( clock, input, reset : in STD_LOGIC;
               output : out STD_LOGIC_VECTOR (7 downto 0)
               );
    end component;
     
    signal clock  : STD_LOGIC;   
    signal input  : STD_LOGIC;    
    signal reset  : STD_LOGIC;    
    signal output : STD_LOGIC_VECTOR (7 downto 0);

begin

    UUT: counterJKFF port map (
    clock  => clock ,
    input  => input ,
    reset  => reset ,
    output => output
    );
    
    clocking: process
    begin
        clock <= '0';
        wait for 10 ns;
        clock <= '1';
        wait for 10 ns;
    end process;
    
    simulation: process
    begin
        input <= '0';
        reset <= '1';
        wait for 40 ns;
        reset <= '0';
        input <= '1';
        wait for 5500 ns;
    end process;

end Behavioral;
