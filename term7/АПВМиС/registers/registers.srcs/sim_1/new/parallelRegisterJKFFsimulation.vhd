library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity parallelRegisterJKFFsimulation is
end parallelRegisterJKFFsimulation;

architecture Behavioral of parallelRegisterJKFFsimulation is

    component parallelRegisterJKFF
        Port ( 
        input : in STD_LOGIC_VECTOR (7 downto 0);
        output : out STD_LOGIC_VECTOR (7 downto 0);
        clock : in STD_LOGIC
    );
    end component;

    signal input : STD_LOGIC_VECTOR (7 downto 0);
    signal output : STD_LOGIC_VECTOR (7 downto 0);
    signal clock : STD_LOGIC;

begin

    UUT: parallelRegisterJKFF port map ( 
        input => input,
        output => output,
        clock => clock
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
        input <= x"00";
        wait for 30 ns;
        input <= x"f3";
        wait for 10 ns;
        input <= x"00";
        wait for 100 ns;
    end process;
    
    

end Behavioral;
