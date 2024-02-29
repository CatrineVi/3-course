using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace test5
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            GL.ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(-10, 10, -10, 10, -1, 1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            CalcP();
        }
        double p1, p2;
        double f1(double x1, double x2)
        {
            return -p1 * (x2 + x1);
        }
        double f2(double x1, double x2)
        {
            return p2 * (x1 - x2);
        }
        double f1T(double x1, double x2, double t)
        {
            return x1 * Math.Cos(t) - x2 * Math.Sin(t);
        }
        double f2T(double x1, double x2, double t)
        {
            return x1 * Math.Sin(t) + x2 * Math.Cos(t);
        }

        double Norm(double x, double y)
        {
            return Math.Sqrt(x*x+y*y);
        }

        void CalcP()
        {
            Random rnd = new Random();
            int N = 100;
            double h = 20.0 / N;
            p = new List<double[]>();
            for(int i = 0; i<=N;i++)
            {
                for (int j = 0; j <= N;j++)
                {
                    p.Add(new double[3] {-10+i*h,-10+j*h,rnd.NextDouble()});
                }
            }
        }

        List<double[,]> DifurPr(int N, double h, double[,] X)
        {
            List<double[,]> Difur = new List<double[,]>();

            for (int j = 0; j < X.GetLength(0); j++)
            {
                double[,] difSolv = new double[N + 1, 2];
                difSolv[0, 0] = X[j, 0]; difSolv[0, 1] = X[j, 1];
                for (int i = 1; i <= N; i++)
                {
                    difSolv[i, 0] = difSolv[i - 1, 0] + h * f1(difSolv[i - 1, 0], difSolv[i - 1, 1]);
                    difSolv[i, 1] = difSolv[i - 1, 1] + h * f2(difSolv[i - 1, 0], difSolv[i - 1, 1]);
                }
                Difur.Add(difSolv);
            }

            return Difur;
        }
        List<double[,]> DifurT(int N, double h, double[,] X, double tMin, double tMax)
        {
            List<double[,]> Difur = new List<double[,]>();

            for (int j = 0; j < X.GetLength(0); j++)
            {
                double[,] difSolv = new double[N + 1, 2];
                double t = tMin;
                for (int i = 0; i <= N; t += h, i++)
                {
                    difSolv[i, 0] = f1T(X[j, 0], X[j, 1], t);
                    difSolv[i, 1] = f2T(X[j, 0], X[j, 1], t);
                }
                Difur.Add(difSolv);
            }

            return Difur;
        }
        double[,] difPoint()
        {
            double[,] X = new double[9, 2];
            for (int i = 0; i < 9; i++)
            {
                X[i, 0] = i; X[i, 1] = i;
            }
            return X;
        }
        void Difur()
        {
            double[,] X = difPoint();
            double tMin = 0; double tMax = 6.28;
            int N = trackBar1.Value;
            double h = (tMax - tMin) / N;
            List<double[,]> difPr = DifurPr(N, h, X);
            List<double[,]> difT = DifurT(N, h, X, tMin, tMax);

            GL.Color3(1.0f, 0.0f, 0.0f);

            for (int j = 0; j < difPr.Count; j++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int i = 0; i <= N; i++)
                    GL.Vertex2(difPr[j][i, 0], difPr[j][i, 1]);
                GL.End();
            }
            GL.Color3(0.0f, 0.0f, 0.0f);
            for (int j = 0; j < difT.Count; j++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int i = 0; i <= N; i++)
                    GL.Vertex2(difT[j][i, 0], difT[j][i, 1]);
                GL.End();
            }
        }
        void DrawDifur()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Difur();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }

        double dMin; double dMax;
        List<double[]> p;
        void Forces()
        {
            GL.Color3(0.6f, 0.6f, 0.6f);
            GL.Begin(PrimitiveType.Lines);
            for (int i = -9; i < 10; i++)
            {
                GL.Vertex2(-10, i);
                GL.Vertex2(10, i);
                GL.Vertex2(i, 10);
                GL.Vertex2(i, -10);
            }
            GL.End();

            List<double[,]> points = new List<double[,]>();
            int y = 9;
            for (int i = 0; i < 19; i++)
            {
                double[,] X = new double[19, 2];
                int k = -9;
                for(int j = 0; j < 19; j++)
                {
                    X[j, 0] = k; X[j, 1] = y; k++;
                }
                y--;
                points.Add(X);
            }

            List<double[,]> pointsSolve = new List<double[,]>();
            y = 9;
            dMin = Norm(f1(points[0][0, 0], points[0][0, 1]), f2(points[0][0, 0], points[0][0, 1]));
            dMax = Norm(f1(points[0][0, 0], points[0][0, 1]), f2(points[0][0, 0], points[0][0, 1]));
            for (int i = 0; i < 19; i++, y--)
            {
                double[,] X = new double[19, 2];
                for (int j = 0; j < 19; j++)
                {
                    X[j, 0] = points[i][j, 0] + 0.9*f1(points[i][j, 0], points[i][j, 1]) / Norm(f1(points[i][j, 0], points[i][j, 1]), f2(points[i][j, 0], points[i][j, 1]));
                    X[j, 1] = points[i][j, 1] + 0.9*f2(points[i][j, 0], points[i][j, 1]) / Norm(f1(points[i][j, 0], points[i][j, 1]), f2(points[i][j, 0], points[i][j, 1]));
                    if (Norm(f1(points[i][j, 0], points[i][j, 1]), f2(points[i][j, 0], points[i][j, 1])) < dMin) dMin = Norm(f1(points[i][j, 0], points[i][j, 1]), f2(points[i][j, 0], points[i][j, 1]));
                    if (Norm(f1(points[i][j, 0], points[i][j, 1]), f2(points[i][j, 0], points[i][j, 1])) > dMax) dMax = Norm(f1(points[i][j, 0], points[i][j, 1]), f2(points[i][j, 0], points[i][j, 1]));
                }
                pointsSolve.Add(X);
            }
            float[] c1 = { 0.6f, 0.6f, 0.6f };
            float[] c2 = { 1.0f, 0.5f, 0.5f };

            for (int j = 0; j < points.Count; j++)
            {
                GL.Begin(PrimitiveType.Lines);
                for (int i = 0; i < 19; i++)
                {
                    double l = (Norm(f1(points[i][j, 0], points[i][j, 1]), f2(points[i][j, 0], points[i][j, 1])) - dMin) / (dMax - dMin);
                    double[] c = { (1 - l) * c1[0] + l * c2[0], (1 - l) * c1[1] + l * c2[1], (1 - l) * c1[2] + l * c2[2] };
                    GL.Color3(c[0], c[1], c[2]);
                    GL.Vertex2(points[j][i, 0], points[j][i, 1]);
                    GL.Vertex2(pointsSolve[j][i, 0], pointsSolve[j][i, 1]);
                }
                GL.End();
            }
            GL.LineWidth(4);
            GL.Begin(PrimitiveType.Lines);
            GL.Color3(c1[0], c1[1], c1[2]);
            GL.Vertex2(10, 9.5);
            GL.Color3(c2[0], c2[1], c2[2]);
            GL.Vertex2(10, 5);
            GL.End();
            GL.LineWidth(1);

            GL.Color3(Color.Indigo);
            GL.Begin(PrimitiveType.Points);
            foreach(var v in p)
            {
                GL.Vertex2(v[0], v[1]);
            }
            GL.End();
        }
        void DrawForces()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Forces();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (timer1.Enabled)
                timer1.Stop();
            else
                timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            p1 = trackBar2.Value / 100.0;
            p2 = trackBar3.Value / 100.0;
            label1.Text = trackBar1.Value.ToString();
            DrawDifur();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            p1 = trackBar2.Value / 100.0;
            p2 = trackBar3.Value / 100.0;
            label2.Text = dMin.ToString();
            label3.Text = dMax.ToString();
            DrawForces();
            CalcNewP();
        }
        double dt = 0.01;
        void CalcNewP()
        {
            for(int i = 0; i < p.Count;i++)
            {
                double x, y;
                x = p[i][0] + dt * p[i][2] * f1(p[i][0], p[i][1]);
                y = p[i][1] + dt * p[i][2] * f2(p[i][0], p[i][1]);
                p[i][0] = x; p[i][1] = y;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (timer2.Enabled)
                timer2.Stop();
            else
                timer2.Start();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            CalcP();
        }

        private void glControl1_Load(object sender, EventArgs e)
        {

        }
    }
}
