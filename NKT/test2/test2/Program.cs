using System;

namespace test2
{
    class Program
    {
        static void Main(string[] args)
        {
            Complex z1 = new Complex(5,4);
            Complex z2 = new Complex(6,2);
            Complex z3 = new Complex(7,-3);
            Console.WriteLine((z1/z2).ToString());
            Console.WriteLine(z3.ToString());
            Console.WriteLine();
            Complex[] m1 = Complex.Equation(1, 1, 2);
            for(int i = 0; i < m1.Length; i++)
                Console.WriteLine($"x{i} = {m1[i].ToString()}");
            Console.WriteLine();

            Q q1 = new Q(13, 31);
            Q q2 = new Q(2, 5);
            Q q3 = new Q(3, 4);
            Q q4 = new Q(-15, 15);
            Q q5 = new Q(12, -3);
            Q q6 = new Q(18, 2);
            Q[] m2 = Q.SLAEsolv(q1, q2, q3, q4, q5, q6);
            Console.WriteLine($"{m2[0]} {m2[1]}");

        }
    }
}