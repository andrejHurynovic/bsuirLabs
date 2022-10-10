library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity labwork1SerialOperatorSimulation is
end labwork1SerialOperatorSimulation;

architecture Behavioral of labwork1SerialOperatorSimulation is

    component labwork1SerialOperator
        Port (
            aIn, bIn, cIn, dIn: in std_logic;
            notBI: in std_logic;
            notRBI: in std_logic;
            notLT: in std_logic;

            notRBO: out std_logic;
            aOut, bOut, cOut, dOut, eOut, fOut, gOut: out std_logic
        );
    end component;

    SIGNAL aIn, bIn, cIn, dIn: std_logic;
    SIGNAL notBI: std_logic;
    SIGNAL notRBO: std_logic;
    SIGNAL notRBI: std_logic;
    SIGNAL notLT: std_logic;
    SIGNAL aOut, bOut, cOut, dOut, eOut, fOut, gOut: std_logic;
        begin
        UUT : labwork1SerialOperator port map(
        aIn => aIn,
        bIn => bIn,
        cIn => cIn,
        dIn => dIn,
        notBI => notBI,
        notRBO => notRBO,
        notRBI => notRBI,
        notLT => notLT,
        aOut => aOut,
        bOut => bOut,
        cOut => cOut,
        dOut => dOut,
        eOut => eOut,
        fOut => fOut,
        gOut => gOut);

        stimulus: process
            begin
            --0
            notBI <= '1';
            aIn <= '0';
            bIn <= '0';
            cIn <= '0';
            dIn <= '0';
            notRBI <= '1';
            notLT <= '1';

            --1
            wait for 10 ns;
            aIn <= '1';
            notRBI <= 'X';

            --2
            wait for 10 ns;
            aIn <= '0';
            bIn <= '1';

            --3
            wait for 10 ns;
            aIn <= '1';

            --4
            wait for 10 ns;
            aIn <= '0';
            bIn <= '0';
            cIn <= '1';

            --5
            wait for 10 ns;
            aIn <= '1';

            --6
            wait for 10 ns;
            aIn <= '0';
            bIn <= '1';

            --7
            wait for 10 ns;
            aIn <= '1';

            --8
            wait for 10 ns;
            aIn <= '0';
            bIn <= '0';
            cIn <= '0';
            dIn <= '1';

            --9
            wait for 10 ns;
            aIn <= '1';

            --10
            wait for 10 ns;
            aIn <= '0';
            bIn <= '1';

            --11
            wait for 10 ns;
            aIn <= '1';

            --12
            wait for 10 ns;
            aIn <= '0';
            bIn <= '0';
            cIn <= '1';

            --13
            wait for 10 ns;
            aIn <= '1';

            --14
            wait for 10 ns;
            aIn <= '0';
            bIn <= '1';

            --15
            wait for 10 ns;
            aIn <= '1';

            --BI
            wait for 10 ns;
            notBI <= '0';
            aIn <= 'X';
            bIn <= 'X';
            cIn <= 'X';
            dIn <= 'X';
            notRBI <= 'X';
            notLT <= 'X';

            --RBI
            wait for 10 ns;
            notBI <= '1';
            aIn <= '0';
            bIn <= '0';
            cIn <= '0';
            dIn <= '0';
            notRBI <= '0';
            notLT <= '1';

            --LT
            wait for 10 ns;
            aIn <= 'X';
            bIn <= 'X';
            cIn <= 'X';
            dIn <= 'X';
            notRBI <= 'X';
            notLT <= '0';

            wait for 10 ns;

        end process;
end Behavioral;
