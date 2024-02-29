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

namespace test7
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
            GL.Ortho(-20, 20, -20, 20, -1, 1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            rnd = new Random();
        }
        Random rnd;
        int N = 500;
        double h = 0.5;
        int[,] adjMat;
        List<double[]> graph;
        double r = 0.5;
        List<int[]> E;
        void AdjMatrix()
        {
            adjMat = new int[N,N];
            for(int i = 0; i < N; i++)
                for(int j = 0; j < N; j++)
                {
                    //if (j < i)
                    //    adjMat[i, j] = rnd.Next(0,2);
                    //else adjMat[i, j] = 0;
                    if(i != j)
                        adjMat[i, j] = rnd.Next(0, 2);
                }
        }
        void GraphMatrix()
        {
            graph = new List<double[]>();
            graph.Add(new double[2] { rnd.Next(-19, 20) * rnd.NextDouble(), rnd.Next(-19, 20) * rnd.NextDouble() });
            while(graph.Count < N)
            {
                double[] v = new double[2] { rnd.Next(-19, 20) * rnd.NextDouble(), rnd.Next(-19, 20) * rnd.NextDouble() };
                if(Check(v))
                    graph.Add(v);
            }
        }
        bool Check(double[] v)
        {
            for(int i = 0; i < graph.Count; i++)
            {
                if (Math.Abs(graph[i][0] - v[0]) < r && Math.Abs(graph[i][1] - v[1]) < r)
                    return false;
            }
            return true;
        }
        void ArcWeights()
        {
            E = new List<int[]>();
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (adjMat[i, j] == 1)
                    {
                        int k = rnd.Next(1,4);
                        int[] d = new int[k + 2];
                        d[0] = i; d[1] = j;
                        for (int l = 2; l < k + 2; l++)
                            d[l] = rnd.Next(1, 3);
                        E.Add(d);
                    }
                }
            }
        }
        double f1(double r, double t)
        {
            return r * Math.Cos(t);
        }
        double f2(double r, double t)
        {
            return r * Math.Sin(t);
        }
        void Circle1(int i)
        {
            double tMin = 0;
            double tMax = 2 * Math.PI;
            int grid = 100;
            double delta = (tMax - tMin) / grid;
            GL.Color3(Color.Gold);
            GL.PushMatrix();
            GL.Translate(graph[i][0], graph[i][1], 0);
            GL.Begin(PrimitiveType.Polygon);
            for (double t = tMin; t < tMax; t += delta)
                GL.Vertex2(f1(r, t), f2(r, t));
            GL.End();
            GL.PopMatrix();
        }
        void Circle2(int i)
        {
            double tMin = 0;
            double tMax = 2 * Math.PI;
            int grid = 100;
            double delta = (tMax - tMin) / grid;
            GL.Color3(Color.Purple);
            GL.PushMatrix();
            GL.Translate(graph[i][0], graph[i][1], 0);
            GL.Begin(PrimitiveType.LineLoop);
            for (double t = tMin; t < tMax; t += delta)
                GL.Vertex2(f1(r, t), f2(r, t));
            GL.End();
            GL.PopMatrix();
        }
        void Circle3(int i)
        {
            double tMin = 0;
            double tMax = 2 * Math.PI;
            int grid = 100;
            double delta = (tMax - tMin) / grid;
            GL.Color3(Color.Cyan);
            GL.PushMatrix();
            GL.Translate(graph[i][0], graph[i][1], 0);
            GL.Begin(PrimitiveType.Polygon);
            for (double t = tMin; t < tMax; t += delta)
                GL.Vertex2(f1(r, t), f2(r, t));
            GL.End();
            GL.PopMatrix();
        }
        void N0(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineLoop);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.End();
        }
        void N1(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.End();
        }
        void N2(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + h / 2.0 +(h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.End();
        }
        void N3(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.End();
        }
        void N4(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1]);
            GL.End();
        }
        void N5(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.End();
        }
        void N6(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.End();
        }
        void N7(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1]);
            //GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.End();
        }
        void N8(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.End();
        }
        void N9(int i, int k, double s, int j)
        {
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1]);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h);
            GL.Vertex2(graph[i][0] + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.Vertex2(graph[i][0] + h / 2.0 + (h / 2.0 + s) * j, graph[i][1] + h / 2.0);
            GL.End();
        }
        void DrawNumber()
        {
            GL.Color3(Color.Black);
            double s = h / 5.0;
            for(int i = 0; i < N; i++)
            {
                string number = i.ToString();
                int k = number.Length;
                GL.PushMatrix();
                if (k % 2 == 0)
                    GL.Translate(-(h / 2.0 * k / 2 + k / 2 * s), -r / 2.0, 0);
                if (k % 2 != 0)
                    GL.Translate(-(k / 2.0 * (h / 2.0 + s)), -r / 2.0, 0);
                for (int j = 0; j < k; j++)
                {
                    if (number[j] == '0')
                        N0(i, k, s, j);
                    if (number[j] == '1')
                        N1(i, k, s, j);
                    if (number[j] == '2')
                        N2(i, k, s, j);
                    if (number[j] == '3')
                        N3(i, k, s, j);
                    if (number[j] == '4')
                        N4(i, k, s, j);
                    if (number[j] == '5')
                        N5(i, k, s, j);
                    if (number[j] == '6')
                        N6(i, k, s, j);
                    if (number[j] == '7')
                        N7(i, k, s, j);
                    if (number[j] == '8')
                        N8(i, k, s, j);
                    if (number[j] == '9')
                        N9(i, k, s, j);
                }
                
                GL.PopMatrix();
            }
        }
        
        void Graph()
        {
            GL.Color3(Color.HotPink);
            GL.Begin(PrimitiveType.Lines);
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    if(adjMat[i,j] == 1)
                    {
                        GL.Vertex2(graph[i][0],graph[i][1]);
                        GL.Vertex2(graph[j][0],graph[j][1]);
                    }
                }
            }
            GL.End();
            for (int i = 0; i < N; i++)
            { Circle1(i); Circle2(i); }
        }
        void DrawGraph()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph();
            DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        void arrow(double p1,double p2)
        {
            double l = 0.8;
            double beta = 15*Math.PI/180;
            double[] n = new double[2] { p1, p2 };
            double[] q1 = new double[2] { n[0] - l * Math.Cos(-beta), n[1] - l * Math.Sin(-beta) };
            double[] q2 = new double[2] { n[0] - l * Math.Cos(beta), n[1] - l * Math.Sin(beta) };
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(q1[0],q1[1]);
            GL.Vertex2(n[0],n[1]);
            GL.Vertex2(q2[0],q2[1]);
            GL.End();
        }
        double Norm(int p0, int p1)
        {
            return Math.Sqrt(Math.Pow(graph[p1][0] - graph[p0][0], 2) + Math.Pow(graph[p1][1] - graph[p0][1], 2));
        }
        double Norm(double[]a, double[]b)
        {
            return Math.Sqrt(Math.Pow(b[0] - a[0], 2) + Math.Pow(b[1] - a[1], 2));
        }
        double b1(double t, double[] p0, double[] p1, double[]p2)
        {
            return Math.Pow(1 - t, 2) * p0[0] + 2 * (1 - t) * t * p1[0] + Math.Pow(t, 2) * p2[0];
        }
        double b2(double t, double[] p0, double[] p1, double[] p2)
        {
            return Math.Pow(1 - t, 2) *p0[1] + 2 * (1 - t) * t * p1[1] + Math.Pow(t, 2) * p2[1];
        }
        void DrawArc(int[] e)
        {
            double[] u = graph[e[0]];
            double[] v = graph[e[1]];
            double norm = Norm(u, v);
            double alfa;
            if (v[1] - u[1] >= 0) alfa = Math.Acos((v[0] - u[0]) / norm);
            else alfa = 2 * Math.PI - Math.Acos((v[0] - u[0]) / norm);
            GL.PushMatrix();
            GL.Translate(u[0], u[1], 0);
            GL.Rotate(alfa * 180 / Math.PI, 0, 0, 1);
            for (int i = 2; i < e.Length; i++)
            {
                double[] p0 = new double[2] { 0, 0 };
                double[] p2 = new double[2] { norm, 0 };
                double[]p1=new double[2] { norm/2, 1.5*(i-1) };
                GL.Begin(PrimitiveType.LineStrip);
                double a1 = 0, a2 = 0;
                for (double t = 0; t <= 1; t += 0.005)
                {
                    GL.Vertex2(b1(t, p0, p1, p2), b2(t, p0, p1, p2));
                    if (Math.Abs(t - 0.5) < 0.0001)
                    {
                        a1 = b1(t, p0, p1, p2);
                        a2 = b2(t, p0, p1, p2);
                    }
                }
                GL.End();
                arrow(a1, a2);
            }
            GL.PopMatrix();
        }
        string s;
        void Graph2()
        {
            s = "";
            GL.Color3(Color.HotPink);
            for(int i = 0; i < E.Count; i++)
            {
                DrawArc(E[i]);
                s += E[i][0] + "->" + E[i][1] + ": ";
                for(int j = 2; j < E[i].Length; j++)
                    s += E[i][j].ToString() + " ";
                s += "\n";
            }
            richTextBox1.Text = s;
            for (int i = 0; i < N; i++)
            { Circle1(i); Circle2(i); }
        }
        void DrawGraph2()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph2();
            DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        int MinWeight(int[]e)
        {
            int m = 2;
            for (int i = 2; i < e.Length; i++)
                if(e[i] < e[m]) m = i;
            return m;
        }
        void MinWeight()
        {
            minW = new List<int[]>();
            for(int i = 0; i < E.Count; i++)
            {
                minW.Add(new int[3] { E[i][0], E[i][1], E[i][MinWeight(E[i])] });
            }
        }
        List<int[]> minW;
        void DrawArc2(int[] e)
        {
            double[] u = graph[e[0]];
            double[] v = graph[e[1]];
            double norm = Norm(u, v);
            double alfa;
            if (v[1] - u[1] >= 0) alfa = Math.Acos((v[0] - u[0]) / norm);
            else alfa = 2 * Math.PI - Math.Acos((v[0] - u[0]) / norm);
            GL.PushMatrix();
            GL.Translate(u[0], u[1], 0);
            GL.Rotate(alfa * 180 / Math.PI, 0, 0, 1);
            double[] p0 = new double[2] { 0, 0 };
            double[] p2 = new double[2] { norm, 0 };
            double[] p1 = new double[2] { norm / 2, 1.5 * (1) };
            GL.Color3(Color.HotPink);
            GL.Begin(PrimitiveType.LineStrip);
            double a1 = 0, a2 = 0;
            for (double t = 0; t <= 1; t += 0.005)
            {
                GL.Vertex2(b1(t, p0, p1, p2), b2(t, p0, p1, p2));
                if (Math.Abs(t - 0.5) < 0.0001)
                {
                    a1 = b1(t, p0, p1, p2);
                    a2 = b2(t, p0, p1, p2);
                }
            }
            GL.End();
            arrow(a1, a2);
            GL.PopMatrix();
        }
        void DrawArc3(int[] e)
        {
            double[] u = graph[e[0]];
            double[] v = graph[e[1]];
            double norm = Norm(u, v);
            double alfa;
            if (v[1] - u[1] >= 0) alfa = Math.Acos((v[0] - u[0]) / norm);
            else alfa = 2 * Math.PI - Math.Acos((v[0] - u[0]) / norm);
            GL.PushMatrix();
            GL.Translate(u[0], u[1], 0);
            GL.Rotate(alfa * 180 / Math.PI, 0, 0, 1);
            double[] p0 = new double[2] { 0, 0 };
            double[] p2 = new double[2] { norm, 0 };
            double[] p1 = new double[2] { norm / 2, 1.5 * (1) };
            GL.Color3(Color.Purple);
            GL.Begin(PrimitiveType.LineStrip);
            double a1 = 0, a2 = 0;
            for (double t = 0; t <= 1; t += 0.005)
            {
                GL.Vertex2(b1(t, p0, p1, p2), b2(t, p0, p1, p2));
                if (Math.Abs(t - 0.5) < 0.0001)
                {
                    a1 = b1(t, p0, p1, p2);
                    a2 = b2(t, p0, p1, p2);
                }
            }
            GL.End();
            arrow(a1, a2);
            GL.PopMatrix();
        }
        void Graph3()
        {
            s = "";
            for (int i = 0; i < minW.Count; i++)
            {
                DrawArc2(E[i]);
                s += minW[i][0] + "->" + minW[i][1] + ": " + minW[i][2] + "\n";
            }
            richTextBox1.Text = s;
            for (int i = 0; i < N; i++)
            { Circle1(i); Circle2(i); }
        }
        void DrawGraph3()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph3();
            DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        List<int> Path(string[] S)
        {
            List<int> list = new List<int>();
            s += S[0];
            list.Add(Int32.Parse(S[0]));
            for(int i = 0; i < S.Length - 1; i++)
            {
                int f = 0;
                for ( int j = 0; j < minW.Count; j++)
                {
                    if (S[i] == minW[j][0].ToString() && S[i + 1] == minW[j][1].ToString())
                    {
                        s += "->" + S[i + 1];
                        list.Add(minW[j][1]);
                        f = 1;
                        break;
                    }
                }
                if (f == 0) break;
            }
            return list;
        }
        bool Check(int i, List<int>l)
        {
            for (int j = 0; j < l.Count; j++)
                if (l[j] == i)
                    return true;
            return false;
        }
        bool Check(int m1, int m2, List<int> l)
        {
            for (int j = 0; j < l.Count-1; j++)
                if (l[j] == m1 && l[j+1] == m2)
                    return true;
            return false;
        }
        void Graph4()
        {
            s = richTextBox2.Text;
            string[]S = s.Split(' ');
            s = "";
            List<int> l = Path(S);
            richTextBox1.Text = s;
            GL.Color3(Color.HotPink);
            for (int i = 0; i < minW.Count; i++)
            {
                if (Check(minW[i][0], minW[i][1], l))
                    DrawArc3(minW[i]);
                else DrawArc2(minW[i]);
            }
            for (int i = 0; i < N; i++)
            {
                if (Check(i, l))
                    Circle3(i);
                else Circle1(i);
                Circle2(i);
            }
        }
        void DrawGraph4()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph4();
            DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        int[,] A;
        void AMatrix()
        {
            A = new int[N,N];
            for(int i = 0; i < N; i++)
                for(int j = 0; j < N; j++)
                    A[i,j] = Int32.MaxValue;
            for(int i = 0; i < minW.Count; i++)
                A[minW[i][0],minW[i][1]] = minW[i][2];
            
        }
        List<int> BF()
        {
            s = richTextBox3.Text;
            int start = Int32.Parse(s);
            s = richTextBox4.Text;
            int end = Int32.Parse(s);
            int[,] d = new int[N, N];
            for (int i = 0; i < N; i++)
                for(int j = 0; j < N; j++)
                    d[i,j] = Int32.MaxValue;
            int[,] I = new int[N, N];
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                    I[i, j] = -1;
            }
            d[0,start] = 0;
            I[0,start] = start;
            for(int k = 1; k < N; k++)
            {
                for (int i = 0; i < N; i++)
                {
                    d[k, i] = d[k - 1, i];
                    I[k, i] = i;
                    for (int j = 0; j < N; j++)
                        if (d[k - 1, j] != Int32.MaxValue && A[j, i] != Int32.MaxValue && d[k - 1, j] + A[j, i] < d[k, i])
                        {
                            d[k, i] = d[k - 1, j] + A[j, i];
                            I[k, i] = j;
                        }
                }
            }

            int K = N;
            if (bf == 6)
                K = Int32.Parse(richTextBox5.Text) + 1;            
            List<int> p = new List<int>();
            for (int i = 0; i < K; i++)
                p.Add(0);
            int q = end;
            for(int i = K-1; i >= 0; i--)
            {
                p[i] = q;
                q = I[i, q];
            }
            s = "";
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                    s += d[i, j] + " ";
                s += "\n";
            }
            s += "\n";
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                    s += I[i, j] + " ";
                s += "\n";
            }
            s += "\n";
            for (int i = 0; i < p.Count; i++)
                s += p[i] + " ";
            richTextBox1.Text = s;
            return p;
        }
        void Graph5()
        {
            List<int> l = BF();
            richTextBox1.Text = s;
            GL.Color3(Color.HotPink);
            for (int i = 0; i < minW.Count; i++)
            {
                if (Check(minW[i][0], minW[i][1], l))
                    DrawArc3(minW[i]);
                else DrawArc2(minW[i]);
            }
            for (int i = 0; i < N; i++)
            {
                if (Check(i, l))
                    Circle3(i);
                else Circle1(i);
                Circle2(i);
            }
        }
        void DrawGraph5()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph5();
            DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        void Graph6()
        {
            List<int> l = BF();
            richTextBox1.Text = s;
            GL.Color3(Color.HotPink);
            for (int i = 0; i < minW.Count; i++)
            {
                if (Check(minW[i][0], minW[i][1], l))
                    DrawArc3(minW[i]);
                else DrawArc2(minW[i]);
            }
            for (int i = 0; i < N; i++)
            {
                if (Check(i, l))
                    Circle3(i);
                else Circle1(i);
                Circle2(i);
            }
        }
        void DrawGraph6()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph6();
            DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        List<int> SolveBF()
        {
            s = richTextBox3.Text;
            int start = Int32.Parse(s);
            s = richTextBox4.Text;
            int end = Int32.Parse(s);
            int[] d = new int[N];
            for (int i = 0; i < N; i++)
                d[i] = Int32.MaxValue;
            int[] I = new int[N];
            for (int i = 0; i < N; i++)
                I[i] = -1;
            d[start] = 0;
            I[start] = start;
            for(int k = 1 ; k < N; k++)
                for (int i = 0; i < N; i++)
                    for (int j = 0; j < N; j++)
                        if (d[j] != Int32.MaxValue && A[j, i] != Int32.MaxValue && d[j] + A[j, i] < d[i])
                        {
                            d[i] = d[j] + A[j, i];
                            I[i] = j;
                        }

            int K = N;
            List<int> p = new List<int>();
            int q = end;
            p.Add(q);
            while (q != start)
            {
                q = I[q];
                p.Add(q);
            }
            p.Reverse();
            s = "";
            for (int i = 0; i < N; i++)
                s += I[i] + " ";
            s += "\n";
            for (int i = 0; i < N; i++)
                s += d[i] + " ";
            s += "\n";
            for (int i = 0; i < p.Count; i++)
                s += p[i] + " ";
            richTextBox1.Text = s;
            return p;
        }
        void Graph7()
        {
            List<int> l = SolveBF();
            richTextBox1.Text = s;
            GL.Color3(Color.HotPink);
            for (int i = 0; i < minW.Count; i++)
            {
                if (Check(minW[i][0], minW[i][1], l))
                    DrawArc3(minW[i]);
                else DrawArc2(minW[i]);
            }
            for (int i = 0; i < N; i++)
            {
                if (Check(i, l))
                    Circle3(i);
                else Circle1(i);
                Circle2(i);
            }
        }
        void DrawGraph7()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph7();
            DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        List<int> Dijlstra()
        {
            s = richTextBox3.Text;
            int start = Int32.Parse(s);
            s = richTextBox4.Text;
            int end = Int32.Parse(s);
            List<int> p = new List<int>();
            int[] I = new int[N];
            int[] d = new int[N];
            bool[] IsV = new bool[N];
            for (int i = 0; i < N; i++)
            {
                d[i] = Int32.MaxValue;
                IsV[i] = false;
                I[i] = -1;
            }
            d[start] = 0;
            I[start] = start;
            int index;
            do
            {
                int min = Int32.MaxValue;
                index = Int32.MaxValue;
                for (int i = 0; i < N; i++)
                {
                    if (!IsV[i] && d[i] < min)
                    {
                        min = d[i];
                        index = i;
                    }
                }
                if (index != Int32.MaxValue)
                {
                    for (int i = 0; i < N; i++)
                        if (A[index, i] != Int32.MaxValue && d[index] + A[index, i] < d[i])
                        {
                            d[i] = d[index] + A[index, i];
                            I[i] = index;
                        }
                    IsV[index] = true;
                }
            } while (index < Int32.MaxValue);
                
            int q = end;
            int w = d[end];
            p.Add(q);
            while (q != start)
            {
                q = I[q];
                p.Add(q);
            }
            //while (q != start)
            //{
            //    for (int i = 0; i < N; i++)
            //        if (A[i, q] != Int32.MaxValue && w - A[i, q] == d[i])
            //        {
            //            q = i;
            //            w = w - A[i, q];
            //            p.Add(q);
            //        }
            //}
            p.Reverse();
            s = "";
            for (int i = 0; i < N; i++)
                s += I[i] + " ";
            s += "\n";
            for (int i = 0; i < N; i++)
                s += d[i] + " ";
            s += "\n";
            for (int i = 0; i < p.Count; i++)
                s += p[i] + " ";
            richTextBox1.Text = s;
            return p;
        }
        void Graph8()
        {
            List<int> l = Dijlstra();
            richTextBox1.Text = s;
            GL.Color3(Color.HotPink);
            for (int i = 0; i < minW.Count; i++)
            {
                if (Check(minW[i][0], minW[i][1], l))
                    DrawArc3(minW[i]);
                else DrawArc2(minW[i]);
            }
            for (int i = 0; i < N; i++)
            {
                if (Check(i, l))
                    Circle3(i);
                else Circle1(i);
                Circle2(i);
            }
        }
        void DrawGraph8()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph8();
            DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            AdjMatrix();
            GraphMatrix();
            ArcWeights();
            MinWeight();
            DrawGraph2();
            richTextBox1.Text = "";
        }
        private void button2_Click(object sender, EventArgs e)
        {
            DrawGraph();
            richTextBox1.Text = "";
        }
        private void button3_Click(object sender, EventArgs e)
        {
            DrawGraph2();
        }
        private void button4_Click(object sender, EventArgs e)
        {
            DrawGraph3();
        }
        private void button5_Click(object sender, EventArgs e)
        {
            DrawGraph4();
        }
        int bf;
        private void button6_Click(object sender, EventArgs e)
        {
            bf = 0;
            AMatrix();
            DrawGraph5();
        }
        private void button7_Click(object sender, EventArgs e)
        {
            bf = 6;
            AMatrix();
            DrawGraph6();
        }
        private void button8_Click(object sender, EventArgs e)
        {
            AMatrix();
            DrawGraph7();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            AMatrix();
            DrawGraph8();
        }

        private bool enableMoving = false;
        private Point initialClickedPoint;
        struct Vert
        {
            int a,b;
        };
        bool[,] G;
        int[,] W;
        List<Vert> BW;
        int[,] Im;
        int n, m;
        void StartMesh()
        {
            n = Int32.Parse(richTextBox6.Text);
            m = Int32.Parse(richTextBox7.Text);

        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (timer1.Enabled)
                timer1.Stop();
            else
                timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

        }
        private void MouseDown(object sender, MouseEventArgs e)
        {
            enableMoving = true;
            initialClickedPoint = e.Location;
            richTextBox1.Text = e.X.ToString() + " " + e.Y.ToString();
        }

        private void MouseUp(object sender, MouseEventArgs e)
        {
            enableMoving = false;
        }

        private void MouseMove(object sender, MouseEventArgs e)
        {

        }
    }
}
