using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace test2
{
    class Complex
    {
        double re;
        double im;
        public double Re
        {
            get { return re; }
        }
        public double Im
        {
            get { return im; }
        }
        public double Mod
        {
            get { return Math.Sqrt(re*re+im*im); }
        }
        public double Arg
        {
            get
            {
                if (re == 0 && im == 0) return 0;
                else if (re != 0 && im < 0) return 2 * Math.PI - Math.Acos(re / Mod);
                else return Math.Acos(re / Mod); 
            }
        }
        public double RadToDeg
        {
            get { return Arg * 180 / Math.PI; }
        }
        public Complex(double _re, double _im)
        {
            re = _re; im = _im;
        }
        public Complex(double _re)
        {
            re = _re; im = 0;
        }
        //public override string ToString()
        //{
        //    return "(" + re + " ," + im + ")";
        //}
        public override string ToString()
        {
            if (re != 0 && im > 0) return re + " + i" + im;
            else if (re != 0 && im < 0) return re + " - i" + -im;
            else if (re != 0 && im == 0) return re.ToString();
            else if (re == 0 && im > 0) return "i" + im;
            else if (re == 0 && im < 0) return "-i" + -im;
            else return "0";
        }
        public Complex GetSopr()
        { return new Complex(re, -im); }

        public static Complex operator -(Complex z)
        {
            return new Complex(-z.re,-z.im);
        }
        public static Complex operator +(Complex z1, Complex z2)
        {
            return new Complex(z1.re + z2.re, z1.im + z2.im);
        }
        public static Complex operator +(Complex z, double a)
        {
            return new Complex(z.re + a, z.im);
        }
        public static Complex operator +(double a, Complex z)
        {
            return new Complex(z.re + a, z.im);
        }

        public static Complex operator -(Complex z1, Complex z2)
        {
            return new Complex(z1.re - z2.re, z1.im - z2.im);
        }
        public static Complex operator -(Complex z, double a)
        {
            return new Complex(z.re - a, z.im);
        }
        public static Complex operator -(double a, Complex z)
        {
            return new Complex(a - z.re, -z.im);
        }

        public static Complex operator*(Complex z1, Complex z2)
        {
            return new Complex(z1.re * z2.re - z1.im * z2.im, z1.re * z2.im + z1.im * z2.re);
        }
        public static Complex operator*(Complex z, double a)
        {
            return new Complex(a*z.re, a * z.im);
        }
        public static Complex operator *(double a, Complex z)
        {
            return new Complex(a * z.re, a * z.im);
        }

        public static Complex operator/(Complex z1,Complex z2)
        {
            return new Complex((z1.re*z2.re+z1.im*z2.im)/(z2.re*z2.re+z2.im*z2.im), (z1.im*z2.re - z1.re*z2.im)/(z2.re * z2.re + z2.im * z2.im));
        }
        public static Complex operator/(Complex z, double a)
        {
            return new Complex(z.re / a, z.im / a);
        }
        public static Complex operator /(double a, Complex z)
        {
            return new Complex((a*z.re) / (z.re * z.re + z.im * z.im), (-a*z.im) / (z.re * z.re + z.im * z.im));
        }

        public static bool operator==(Complex z1, Complex z2)
        {
            return z1.re == z2.re && z1.im == z2.im;
        }
        public static bool operator==(Complex z, double a)
        {
            return (z.re == a) && (z.im == 0);
        }
        public static bool operator ==(double a, Complex z)
        {
            return (z.re == a) && (z.im == 0);
        }

        public static bool operator !=(Complex z1, Complex z2)
        {
            return !(z1 == z2);
        }
        public static bool operator !=(Complex z, double a)
        {
            return !(z == a);
        }
        public static bool operator !=(double a, Complex z)
        {
            return !(z == a);
        }

        public static Complex[] Equation(double a, double b, double c)
        {
            if (a != 0)
            {
                double d = b * b - 4 * a * c;
                if (d >= 0)
                    return new Complex[2] { new Complex((-b + Math.Sqrt(d)) / (2 * a)), new Complex((-b - Math.Sqrt(d)) / (2 * a)) };
                else return new Complex[2] { new Complex(-b / (2 * a), Math.Sqrt(-d) / (2 * a)), new Complex(-b / (2 * a), -Math.Sqrt(-d) / (2 * a)) };
            }
            else return null;
        }

    }
}
