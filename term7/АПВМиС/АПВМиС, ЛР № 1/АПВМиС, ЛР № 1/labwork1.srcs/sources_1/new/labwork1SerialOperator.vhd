library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity labwork1SerialOperator is
    Port (
          aIn, bIn, cIn, dIn: in std_logic;
          notBI: in std_logic;
          notRBI: in std_logic;
          notLT: in std_logic;
          
          notRBO: out std_logic;
          aOut, bOut, cOut, dOut, eOut, fOut, gOut: out std_logic
          );
end labwork1SerialOperator;

architecture Behavioral of labwork1SerialOperator is
    begin
    process(aIn, bIn, cIn, dIn, notBI, notRBI, notLT)
        begin
        if(notBI = '0') then aOut <= '0'; bOut <= '0'; cOut <= '0'; dOut <= '0'; eOut <= '0'; fOut <= '0'; gOut <= '0'; notRBO <= '0';
        elsif (notLT = '0') then aOut <= '1'; bOut <= '1'; cOut <= '1'; dOut <= '1'; eOut <= '1'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        elsif (notLT = '1' and notRBI = '0' and dIn = '0' and cIn = '0' and bIn = '0' and aIn = '0' and notBI = '0') then aOut <= '0'; bOut <= '0'; cOut <= '0'; dOut <= '0'; eOut <= '0'; fOut <= '0'; gOut <= '0'; notRBO <= '0';
        --0
        elsif (notLT = '1' and notRBI = '1' and dIn = '0' and cIn = '0' and bIn = '0' and aIn = '0') then aOut <= '1'; bOut <= '1'; cOut <= '1'; dOut <= '1'; eOut <= '1'; fOut <= '1'; gOut <= '0'; notRBO <= '1';
        --1
        elsif (notLT = '1' and dIn = '0' and cIn = '0' and bIn = '0' and aIn = '1') then aOut <= '0'; bOut <= '1'; cOut <= '1'; dOut <= '0'; eOut <= '0'; fOut <= '0'; gOut <= '0'; notRBO <= '1';
        --2
        elsif (notLT = '1' and dIn = '0' and cIn = '0' and bIn = '1' and aIn = '0') then aOut <= '1'; bOut <= '1'; cOut <= '0'; dOut <= '1'; eOut <= '1'; fOut <= '0'; gOut <= '1'; notRBO <= '1';
        --3
        elsif (notLT = '1' and dIn = '0' and cIn = '0' and bIn = '1' and aIn = '1') then aOut <= '1'; bOut <= '1'; cOut <= '1'; dOut <= '1'; eOut <= '0'; fOut <= '0'; gOut <= '1'; notRBO <= '1';
        --4
        elsif (notLT = '1' and dIn = '0' and cIn = '1' and bIn = '0' and aIn = '0') then aOut <= '0'; bOut <= '1'; cOut <= '1'; dOut <= '0'; eOut <= '0'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        --5
        elsif (notLT = '1' and dIn = '0' and cIn = '1' and bIn = '0' and aIn = '1') then aOut <= '1'; bOut <= '0'; cOut <= '1'; dOut <= '1'; eOut <= '0'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        --6
        elsif (notLT = '1' and dIn = '0' and cIn = '1' and bIn = '1' and aIn = '0') then aOut <= '0'; bOut <= '0'; cOut <= '1'; dOut <= '1'; eOut <= '1'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        --7
        elsif (notLT = '1' and dIn = '0' and cIn = '1' and bIn = '1' and aIn = '1') then aOut <= '1'; bOut <= '1'; cOut <= '1'; dOut <= '0'; eOut <= '0'; fOut <= '0'; gOut <= '0'; notRBO <= '1';
        --8
        elsif (notLT = '1' and dIn = '1' and cIn = '0' and bIn = '0' and aIn = '0') then aOut <= '1'; bOut <= '1'; cOut <= '1'; dOut <= '1'; eOut <= '1'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        --9
        elsif (notLT = '1' and dIn = '1' and cIn = '0' and bIn = '0' and aIn = '1') then aOut <= '1'; bOut <= '1'; cOut <= '1'; dOut <= '0'; eOut <= '0'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        --10
        elsif (notLT = '1' and dIn = '1' and cIn = '0' and bIn = '1' and aIn = '0') then aOut <= '0'; bOut <= '0'; cOut <= '0'; dOut <= '1'; eOut <= '1'; fOut <= '0'; gOut <= '1'; notRBO <= '1';
        --11
        elsif (notLT = '1' and dIn = '1' and cIn = '0' and bIn = '1' and aIn = '1') then aOut <= '0'; bOut <= '0'; cOut <= '1'; dOut <= '1'; eOut <= '0'; fOut <= '0'; gOut <= '1'; notRBO <= '1';
        --12
        elsif (notLT = '1' and dIn = '1' and cIn = '1' and bIn = '0' and aIn = '0') then aOut <= '0'; bOut <= '1'; cOut <= '0'; dOut <= '0'; eOut <= '0'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        --13
        elsif (notLT = '1' and dIn = '1' and cIn = '1' and bIn = '0' and aIn = '1') then aOut <= '1'; bOut <= '0'; cOut <= '0'; dOut <= '1'; eOut <= '0'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        --14
        elsif (notLT = '1' and dIn = '1' and cIn = '1' and bIn = '1' and aIn = '0') then aOut <= '0'; bOut <= '0'; cOut <= '0'; dOut <= '1'; eOut <= '1'; fOut <= '1'; gOut <= '1'; notRBO <= '1';
        --15
        elsif (notLT = '1' and dIn = '1' and cIn = '1' and bIn = '1' and aIn = '1') then aOut <= '0'; bOut <= '0'; cOut <= '0'; dOut <= '0'; eOut <= '0'; fOut <= '0'; gOut <= '0'; notRBO <= '1';
        end if;
    end process;
end Behavioral;
