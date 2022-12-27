library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity shiftRegisterJKFFsimulation is
end shiftRegisterJKFFsimulation;

architecture Behavioral of shiftRegisterJKFFsimulation is

    component shiftRegisterJKFF
        Port ( 
                clock, input, reset : in STD_LOGIC;
                output : out STD_LOGIC_VECTOR (7 downto 0)
            );
    end component;

    signal clock, input, reset :  STD_LOGIC;
    signal output :  STD_LOGIC_VECTOR (7 downto 0);

begin

    UUT: shiftRegisterJKFF port map (
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
        wait for 10 ns;
        reset <= '0';
        wait for 20 ns;
        input <= '1';
        wait for 10 ns;
        input <= '0';
        wait for 110 ns;
        wait for 40 ns;
        input <= '1';
        wait for 30 ns;
        input <= '0';
        
        wait for 1000 ns;
    end process;

end Behavioral;
