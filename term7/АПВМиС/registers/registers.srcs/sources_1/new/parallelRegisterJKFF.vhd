library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity parallelRegisterJKFF is
    Port ( 
        clock : in STD_LOGIC;
        input : in STD_LOGIC_VECTOR (7 downto 0);
        output : out STD_LOGIC_VECTOR (7 downto 0)
    );
end parallelRegisterJKFF;

architecture Behavioral of parallelRegisterJKFF is
    signal notInputs: STD_LOGIC_VECTOR (7 downto 0);
begin

    notInputs <= not(input);

    JKFFgenerate: for index in 7 downto 0 generate
    
        JKFF: entity work.JKFF port map (
            clock => clock,
            jump => input(index),
            kill => notInputs(index),
            asynchronousSet => '0',
            asynchronousReset => '0',
            output => output(index)
        );
    
    end generate;

end Behavioral;
