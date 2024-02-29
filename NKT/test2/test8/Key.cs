using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace test8
{
    public class Key : IComparable
    {
        public int k, i, j;


        public Key(int k, int i, int j)
        {
            this.k = k;
            this.i = i;
            this.j = j;
        }

        public int CompareTo(Object kk)
        {
            Key k1 = kk as Key;
            if (k == k1.k && i == k1.i && j == k1.j)
                return 0;
            else
            {
                if (k > k1.k)
                    return 1;
                else if (k < k1.k)
                    return -1;
                else
                {
                    if (i == k1.i)
                        return j > k1.j ? 1 : -1;
                    else return i > k1.i ? 1 : -1;
                }
            }
        }
            
    }
}
