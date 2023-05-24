using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Lemer
{
    public class Lehmer
    {
        private const int a = 193;
        private const int m = 101;
        private const int c = 1223;
        private int seed;
        public static int e = 100;  //число итераций для моделирования
        public static double d = 0.005; //желаемая точность
        public Lehmer(int seed)
        {
            if (seed <= 0 || seed == int.MaxValue)
                throw new Exception("Bad seed");
            this.seed = seed;

        }
        public int Next2()
        {
            int z1 = (a * Program.ri + c) % m;
            return z1;
        }
        class Program
        {
            public static int ri = 37;
            static void Main(string[] args)
            {
                double[,] part1 = { { 0.2, 0.2, 0.6 },
                                    { 0.4, 0.5, 0.1 },
                                    { 0.6, 0.1, 0.3 } };    //матрица вер-сти переходов 1 

                double[,] part2 = { { 0.7, 0.2, 0.1 },
                                    { 0.3, 0.5, 0.2 },
                                    { 0.0, 0.0, 1.0 } };    //матрица вер-сти переходов 2 

                double[] counts = new double[part1.GetLength(0)];
                double[] diff = new double[counts.Length];

                Lehmer lehmer = new Lehmer(1);
                int state = 0;

                // Part 1
                for (int i = 0; i < e; ++i)
                {
                    ri = lehmer.Next2();
                    if (ri <= part1[state, 0] * 100)    //определение следующего состояния
                        state = 0;
                    else if (ri >= (1 - part1[state, 2]) * 100)
                        state = 2;
                    else
                        state = 1;
                    ++counts[state];
                    Console.Write("S" + state);
                    if (i == e - 1)      //на последнем проходе, достигнута ли желаемая точночть d,
                    {                    //да - завершаем, нет - увеличиваем число итераций
                        for (int j = 0; j < diff.Length; j++)
                        {
                            diff[j] = (counts[j] + 1) / (e + 2) - counts[j] / (e + 1);
                            if (Math.Abs(diff[j]) > d)
                            {
                                e++;
                                break;
                            }
                        }
                    }
                    if (i < e - 1)  //оформление
                        Console.Write(" -> ");
                }
                Console.WriteLine('\n');

                for (int i = 0; i < counts.Length; ++i)
                {
                    Console.WriteLine("P" + i + ": " + counts[i] / e);
                }
                Console.WriteLine("Steps: " + e);
                Console.ReadLine();

                // Part 2
                int goalstate = 0;      //определение поглощающего состояния
                for (int i = 0; i < part2.GetLength(0); i++)
                {
                    for (int j = 0; j < part2.GetLength(1); j++)
                    {
                        if (part2[i, j] == 1.0)
                        {
                            goalstate = i;
                            break;
                        }
                    }
                }

                int[] middlestep = new int[part2.GetLength(0)];
                for (int k = 0; k < m; k++) //т.к. генерация псевдослучайная, перебираем все возможные ri
                {
                    Console.Write("\n**********************************************");
                    for (int i = 0; i < part2.GetLength(0); i++)    //определение кол-ва шагов из каждого
                    {                                               //начального состояния S0,S1,S2
                        state = i;
                        int step = 0;
                        ri = k;
                        Console.Write("\nS" + state);
                        while (state != goalstate)                  //подсчёт шагов методом из part 1
                        {
                            Console.Write(" -> ");
                            ri = lehmer.Next2();
                            if (ri <= part2[state, 0] * 100)
                                state = 0;
                            else if (ri >= (1 - part2[state, 2]) * 100)
                                state = 2;
                            else
                                state = 1;
                            ++step;
                            Console.Write("S" + state);
                        }
                        middlestep[i] += step;      //подсчет суммарного чиисла шагов за все испытания
                    }                               //их всего на самом деле 101
                }
                Console.WriteLine("\n**************************************\n");
                for (int i = 0; i < middlestep.Length; i++) //вывод средних рез-татов испытаний
                    Console.WriteLine("S" + i + " -> S" + goalstate + " за " 
                        + Math.Round((double)middlestep[i] / m, 2) + " шагов");
                Console.ReadLine();
            }
        }
    }
}