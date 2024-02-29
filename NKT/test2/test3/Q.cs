using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace test3
{
    class Q
    {
        int m;
        int n;

        public static int ev(int a, int b)
        {
            a=Math.Abs(a); ;
            b=Math.Abs(b);
            if (b == 0) return a;
            else return ev(b, a % b);
        }

        public Q(int _m, int _n)
        {
            if (_n == 0) throw new DivideByZeroException();
            else if (_m == 0)
            {
                m = 0;
                n = 1;
            }
            else
            {
                int e = ev(_m, _n);
                if (_n < 0)
                {
                    m = -_m / e;
                    n = -_n / e;
                }
                else
                {
                    m = _m / e;
                    n = _n / e;
                }

            }
        }

        public override string ToString()
        {
            if (n == 1) return m.ToString();
            else return m + "/" + n;
        }

        public static Q operator +(Q a, Q b)
        {
            return new Q((a.m * b.n) + (a.n * b.m), (a.n * b.n));
        }

        public static Q operator -(Q a, Q b)
        {
            return new Q((a.m * b.n) - (a.n * b.m), (a.n * b.n));
        }
        public static Q operator *(Q a, Q b)
        {
            return new Q(a.m * b.m, a.n * b.n);
        }
        public static Q operator /(Q a, Q b)
        {
            return new Q(a.m * b.n, a.n * b.m);
        }
        public static Q operator +(Q a, int c)
        {
            return new Q(a.m + c * a.n, a.n);
        }
        public static Q operator +(int c, Q a)
        {
            return new Q(a.m + c * a.n, a.n);
        }
        public static Q operator -(Q a, int c)
        {
            return new Q(a.m - c * a.n, a.n);
        }
        public static Q operator -(int c, Q a)
        {
            return new Q(c * a.n - a.m, a.n);
        }
        public static Q operator *(Q a, int c)
        {
            return new Q(a.m * c, a.n);
        }
        public static Q operator *(int c, Q a)
        {
            return new Q(a.m * c, a.n);
        }
        public static Q operator /(Q a, int c)
        {
            return new Q(a.m, a.n * c);
        }
        public static Q operator /(int c, Q a)
        {
            return new Q(c * a.n, a.m);
        }
        
        public static bool operator ==(Q a, Q b)
        {
            return (a.m * b.n == b.m * a.n);
        }
        public static bool operator ==(Q a, int b)
        {
            return (a.m == b && a.n == 1);
        }
        public static bool operator ==(int b, Q a)
        {
            return (a.m == b && a.n == 1);
        }

        public static bool operator !=(Q a, Q b)
        {
            return !(a == b);
        }
        public static bool operator !=(Q a, int b)
        {
            return !(a == b);
        }
        public static bool operator !=(int b, Q a)
        {
            return !(a == b);
        }
         
        public Q(int _m)
        {
            m = _m; n = 1;
        }
        public static Q[] SLAEsolv1(Q a1, Q b1, Q c1, Q a2, Q b2, Q c2)
        {
            Q det = a1 * b2 - a2 * b1;
            if (det == 0) return null;
            else
            {
                Q det1 = c1 * b2 - b1 * c2;
                Q det2 = a1 * c2 - c2 * a2;
                return new Q[2] { det1 / det, det2 / det };
            }
        }
        public static Q[] SLAEsolv1(Q[] a)
        {
            Q det = a[0] * a[4] - a[3] * a[1];
            if (det == 0) return null;
            else
            {
                Q det1 = a[2] * a[4] - a[1] * a[5];
                Q det2 = a[0] * a[5] - a[3] * a[2];
                return new Q[2] { det1 / det, det2 / det };
            }
        }
        public static explicit operator double(Q a)
        {
            return (double)a.m / a.n;
        }
        public static double[] SLAEsolv2(Q[] _a)
        {
            double[] a = { (double)(_a[0]), (double)(_a[1]), (double)(_a[2]), (double)(_a[3]), (double)(_a[4]), (double)(_a[5]) };
            double det = a[0] * a[4] - a[3] * a[1];
            if (det == 0) return null;
            else
            {
                double det1 = a[2] * a[4] - a[1] * a[5];
                double det2 = a[0] * a[5] - a[3] * a[2];
                return new double[2] { det1 / det, det2 / det };
            }
        }
    }
}
