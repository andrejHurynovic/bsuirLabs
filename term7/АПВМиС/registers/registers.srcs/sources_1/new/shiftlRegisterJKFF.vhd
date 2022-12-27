library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity shiftRegisterJKFF is
    Port 
        ( clock : in STD_LOGIC;
        reset : in STD_LOGIC;
        input : in STD_LOGIC;
        output : out STD_LOGIC_VECTOR (7 downto 0)
        );
end shiftRegisterJKFF;

architecture Behavioral of shiftRegisterJKFF is

signal outputs : STD_LOGIC_VECTOR (7 downto 0);
signal notOutputs : STD_LOGIC_VECTOR (7 downto 0);

signal notInput: STD_LOGIC;

begin 

    notInput <= not(input);

    JKFF0: entity work.JKFF port map (
        clock => clock,
        jump => input,
        kill => notInput,
        asynchronousSet => '0',
        asynchronousReset => reset,
        output => outputs(0),
        invertedOutput => notOutputs(0)
    );
    
    JKFFgenerate: for index in 7 downto 1 generate
        JKFF: entity work.JKFF port map (
            clock => clock,
            jump => outputs(index - 1),
            kill => notOutputs(index - 1),
            asynchronousSet => '0',
            asynchronousReset => reset,
            output => outputs(index),
            invertedOutput => notOutputs(index)
        );
    end generate;

    output <= outputs;

end Behavioral;
