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

namespace wterdg
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            AdjMatrix();
            GraphMatrix();
            DrawGraph();
            ArcWeights();
        }

        private void glControl1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            GL.ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(-20, 20, -20, 20, -1, 1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
        }
        int N = 7;
        int[,] adjMat;
        List<double[]> graph;
        double r = 0.5;
        double h = 0.5;
        List<int[]> E;

        void AdjMatrix() //матрица смежности
        {
            Random rnd = new Random();
            adjMat = new int[N, N];
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                {
                    if (j != i)
                        adjMat[i, j] = rnd.Next(0, 2);
                }
        }

        void GraphMatrix()  //граф
        {
            Random rnd = new Random();
            graph = new List<double[]>();
            graph.Add(new double[2] { rnd.Next(-9, 10) * rnd.NextDouble(), rnd.Next(-9, 10) * rnd.NextDouble() });
            while (graph.Count < N)
            {
                double[] v = new double[2] { rnd.Next(-9, 10) * rnd.NextDouble(), rnd.Next(-9, 10) * rnd.NextDouble() };
                if (Check(v))
                    graph.Add(v);
            }
        }

        bool Check(double[] v)
        {
            for (int i = 0; i < graph.Count; i++)
            {
                if (Math.Abs(graph[i][0] - v[0]) < r && Math.Abs(graph[i][1] - v[1]) < r)
                    return false;
            }
            return true;
        }
        void ArcWeights()  //веса
        {
            Random rnd = new Random();
            E = new List<int[]>();
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (adjMat[i, j] == 1)
                    {
                        int k = rnd.Next(1, 4);
                        int[] m = new int[k + 2];
                        m[0] = i; m[1] = j;
                        for (int s = 2; s < k + 1; s++)
                            m[s] = rnd.Next(1, 11);
                        E.Add(m);
                    }
                }
            }
        }

        void Vert(int i)
        {
            double tMin = 0;
            double tMax = 2 * Math.PI;
            int grid = 100;
            double delta = (tMax - tMin) / grid;
            GL.Color3(Color.Red);
            GL.PushMatrix();
            GL.Translate(graph[i][0], graph[i][1], 0);
            GL.Begin(PrimitiveType.Polygon);
            for (double t = tMin; t < tMax; t += delta)
                GL.Vertex2(r * Math.Cos(t), r * Math.Sin(t));
            GL.End();
            GL.PopMatrix();
        }

        void Graph()
        {
            GL.Color3(Color.Blue);
            GL.Begin(PrimitiveType.Lines);
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (adjMat[i, j] == 1)
                    {
                        GL.Vertex2(graph[i][0], graph[i][1]);
                        GL.Vertex2(graph[j][0], graph[j][1]);
                    }
                }
            }
            GL.End();
            for (int i = 0; i < N; i++)
            { Vert(i); }
        }
        void DrawGraph()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Graph();
            //DrawNumber();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }

    }
}
