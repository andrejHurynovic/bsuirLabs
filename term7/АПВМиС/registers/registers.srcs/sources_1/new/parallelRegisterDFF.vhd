library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity parallelRegisterDFF is
    Port ( 
        input : in STD_LOGIC_VECTOR (7 downto 0);
        output : out STD_LOGIC_VECTOR (7 downto 0);
        clock : in STD_LOGIC
    );
end parallelRegisterDFF;

architecture Behavioral of parallelRegisterDFF is

begin

dffGenerate: for index in 7 downto 0 generate
    
    DFF: entity work.DFF port map (
    input             => input(index),
    clock             => clock,
    asynchronousSet   => '0',
    asynchronousReset => '0',
    output            => output(index)
    );
    
end generate;

end Behavioral;
