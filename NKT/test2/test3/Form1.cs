using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace test3
{
    public partial class Form1 : Form
    {
        string s;

        Q[] qs_orig;
        double[] ds_orig;
        Q[] qs;
        double[] ds;
        public Form1()
        {
            InitializeComponent();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }
        private void richTextBox2_TextChanged(object sender, EventArgs e)
        {
            
        }
        Q ReadBar()
        {
            return new Q(trackBar1.Value, 100);
        }
        Q[] ReadSLAE()
        {
            s = richTextBox1.Text;
            string[] S = s.Split(' ');
            Q[] qs = new Q[S.Length];
            for (int i = 0; i < S.Length; i++)
            {
                if (S[i].Contains("/"))
                {
                    string[] S2 = S[i].Split('/');
                    qs[i] = new Q(Convert.ToInt32(S2[0]), Convert.ToInt32(S2[1])) + ReadBar();
                }
                else qs[i] = new Q(Convert.ToInt32(S[i])) + ReadBar();
            }
            return qs;
        }
        void Calculate()
        {
            qs = Q.SLAEsolv1(ReadSLAE());
            ds = Q.SLAEsolv2(ReadSLAE());
        }
        void WriteResult()
        {
            s = String.Empty;
            if (qs == null) s = "There's no solution";
            else
            {
                s = "Solution in Q: ";
                for (int i = 0; i < qs.Length; i++) s += qs[i].ToString() + " ";
                s += "\nSolution in double: ";
                for (int i = 0; i < ds.Length; i++) s += ds[i].ToString() + " ";
            }
            s += "\ndelta = " + ReadBar().ToString();
            Q[] dif_Q = { qs_orig[0] - qs[0], qs_orig[1] - qs[1] };
            double[] dif_d = {ds_orig[0] - ds[0], ds_orig[1] - ds[1] };
            s += "\ndifference Q: ";
            for (int i = 0; i < dif_Q.Length; i++) s += dif_Q[i].ToString() + " ";
            s += "\ndifference double: ";
            for (int i = 0; i < dif_d.Length; i++) s += dif_d[i].ToString() + " ";
            richTextBox2.Text = s;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (timer1.Enabled)
            {
                timer1.Stop();
            }
            else
            {
                qs_orig = Q.SLAEsolv1(ReadSLAE());
                ds_orig = Q.SLAEsolv2(ReadSLAE());
                timer1.Start();
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Calculate();
            WriteResult();
        }
    }
}
