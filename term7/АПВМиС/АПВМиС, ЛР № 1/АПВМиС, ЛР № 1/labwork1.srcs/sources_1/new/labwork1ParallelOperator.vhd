library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity labwork1ParallelOperator is
    Port (
          aIn, bIn, cIn, dIn: in std_logic;
          notBI: in std_logic;
          notRBI: in std_logic;
          notLT: in std_logic;
          
          notRBO: out std_logic;
          aOut, bOut, cOut, dOut, eOut, fOut, gOut: out std_logic
          );
end labwork1ParallelOperator;

architecture Behavioral of labwork1ParallelOperator is
    signal temp: std_logic_vector (7 downto 0);
    signal LT, pass: std_logic;

    begin

    temp(0) <= not aIn when pass = '1' else '0';
    temp(1) <= not(temp(0));
    temp(2) <= not bIn when pass = '1' else '0';
    temp(3) <= not(temp(2));
    temp(4) <= not cIn when pass = '1' else '0';
    temp(5) <= not(temp(4));
    temp(6) <= not dIn when pass = '1' else '0';
    temp(7) <= not(temp(6));


    LT <= not notLT when notBI = '1' else '0';
    notRBO <= '0' when notBI = '0' else '1' when LT = '1' else not(not(aIn or bIn or cIn or dIn) and (not notRBI));
    pass <= notBI and not(not(aIn or bIn or cIn or dIn) and (not notRBI));

    aOut <= not((temp(3) and temp(7)) or (temp(0) and temp(5)) or (temp(1) and temp(2) and temp(4) and temp(6))) or LT;
    bOut <= not((temp(3) and temp(7)) or (temp(1) and temp(2) and temp(5)) or (temp(0) and temp(3) and temp(5))) or LT;
    cOut <= not((temp(5) and temp(7)) or (temp(0) and temp(3) and temp(4))) or LT;
    dOut <= not((temp(1) and temp(2) and temp(4)) or (temp(0) and temp(2) and temp(5)) or (temp(1) and temp(3) and temp(5))) or LT;
    eOut <= not(temp(1) or (temp(2) and temp(5))) or LT;
    fOut <= not((temp(1) and temp(3)) or (temp(3) and temp(4)) or (temp(1) and temp(4) and temp(6))) or LT;
    gOut <= not((temp(1) and temp(3) and temp(5)) or (temp(2) and temp(4) and temp(6) and notLT)) or LT;
     
end Behavioral;
