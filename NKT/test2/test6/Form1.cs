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

namespace test6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void glControl1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            GL.ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            GL.MatrixMode(MatrixMode.Projection);
            Matrix4 M = Matrix4.CreatePerspectiveFieldOfView((float)(60*Math.PI/180), 1.0f, 0.1f, 300.0f);
            GL.LoadMatrix(ref M);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
        }

        float eyeX()
        {
            return (float)(trackBar3.Value/20.0 * Math.Cos(trackBar2.Value * Math.PI / 180) * Math.Cos(trackBar1.Value * Math.PI / 180));
        }
        float eyeY()
        {
            return (float)(trackBar3.Value/20.0 * Math.Cos(trackBar2.Value * Math.PI / 180) * Math.Sin(trackBar1.Value * Math.PI / 180));
        }
        float eyeZ()
        {
            return (float)(trackBar3.Value/20.0 * Math.Sin(trackBar2.Value * Math.PI / 180));
        }


        void Lines()
        {
            GL.LineWidth(1);
            GL.Begin(PrimitiveType.Lines);
            GL.Color3(Color.Blue);
            GL.Vertex3(0, 0, -30);
            GL.Vertex3(0, 0, 30);
            GL.Color3(Color.Green);
            GL.Vertex3(0, -30, 0);
            GL.Vertex3(0, 30, 0);
            GL.Color3(Color.Red);
            GL.Vertex3(-30, 0, 0);
            GL.Vertex3(30, 0, 0);
            GL.End();
            GL.LineWidth(1);
        }

        double xMax = 2*Math.PI;
        double xMin = 0;
        double yMax = Math.PI/2;
        double yMin = -Math.PI/2;
        double f1(double t1, double t2)
        {
            return 10 * Math.Cos(t2)*Math.Cos(t1);
        }
        double f2(double t1, double t2)
        {
            return 10 * Math.Cos(t2) * Math.Sin(t1);
        }
        double f3(double t1, double t2)
        {
            return 10 * Math.Sin(t2);
        }
        void Mesh()
        {
            double[,,] mesh = new double[px+1, py+1, 3];
            double dx=(xMax-xMin)/px;
            double dy=(yMax-yMin)/py;
            double alfa, beta, gamma;
            for (int i = 0; i <= px; i++)
                for(int j = 0; j <= py; j++)
                {
                    alfa = xMin + dx*i;
                    beta = yMin + dy*j;
                    mesh[i, j, 0] = f1(alfa,beta);
                    mesh[i, j, 1] = f2(alfa, beta);
                    mesh[i, j, 2] = f3(alfa, beta);
                }
            GL.Color3(Color.LightGray);
            for (int i = 0; i <= px; i++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int j = 0; j <= py; j++)
                {
                    GL.Vertex3(mesh[i, j, 0], mesh[i, j, 1], mesh[i,j,2]);
                }
                GL.End();
            }
            for (int j = 0; j <= py; j++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int i = 0; i <= px; i++)
                {
                    GL.Vertex3(mesh[i, j, 0], mesh[i, j, 1], mesh[i, j, 2]);
                }
                GL.End();
            }

        }
        void Mesh2()
        {
            double[,,] meshXY = new double[61, 61, 3];
            
            for (int i = 0; i <= 60; i++)
                for (int j = 0; j <= 60; j++)
                {

                    meshXY[i, j, 0] = i - 30;
                    meshXY[i, j, 1] = j - 30;
                    meshXY[i, j, 2] = -30;
                }
            GL.Color3(Color.LightGray);
            for (int i = 0; i <= 60; i++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int j = 0; j <= 60; j++)
                {
                    GL.Vertex3(meshXY[i, j, 0], meshXY[i, j, 1], meshXY[i, j, 2]);
                }
                GL.End();
            }
            for (int j = 0; j <= 60; j++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int i = 0; i <= 60; i++)
                {
                    GL.Vertex3(meshXY[i, j, 0], meshXY[i, j, 1], meshXY[i, j, 2]);
                }
                GL.End();
            }
            double[,,] meshXZ = new double[61, 61, 3];

            for (int i = 0; i <= 60; i++)
                for (int j = 0; j <= 60; j++)
                {

                    meshXZ[i, j, 0] = i - 30;
                    meshXZ[i, j, 1] = -30;
                    meshXZ[i, j, 2] = j - 30;
                }
            GL.Color3(Color.LightGray);
            for (int i = 0; i <= 60; i++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int j = 0; j <= 60; j++)
                {
                    GL.Vertex3(meshXZ[i, j, 0], meshXZ[i, j, 1], meshXZ[i, j, 2]);
                }
                GL.End();
            }
            for (int j = 0; j <= 60; j++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int i = 0; i <= 60; i++)
                {
                    GL.Vertex3(meshXZ[i, j, 0], meshXZ[i, j, 1], meshXZ[i, j, 2]);
                }
                GL.End();
            }
            double[,,] meshYZ = new double[61, 61, 3];

            for (int i = 0; i <= 60; i++)
                for (int j = 0; j <= 60; j++)
                {

                    meshYZ[i, j, 0] = -30;
                    meshYZ[i, j, 1] = i - 30;
                    meshYZ[i, j, 2] = j - 30;
                }
            GL.Color3(Color.LightGray);
            for (int i = 0; i <= 60; i++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int j = 0; j <= 60; j++)
                {
                    GL.Vertex3(meshYZ[i, j, 0], meshYZ[i, j, 1], meshYZ[i, j, 2]);
                }
                GL.End();
            }
            for (int j = 0; j <= 60; j++)
            {
                GL.Begin(PrimitiveType.LineStrip);
                for (int i = 0; i <= 60; i++)
                {
                    GL.Vertex3(meshYZ[i, j, 0], meshYZ[i, j, 1], meshYZ[i, j, 2]);
                }
                GL.End();
            }
        }
        void CoordinateSystem()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Matrix4 LA = Matrix4.LookAt(eyeX(), eyeY(), eyeZ(), 0, 0, 0, 0, 0, 1);
            GL.LoadMatrix(ref LA);
            Mesh();
            Lines();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        double dif1(double x, double y, double z)
        {
            return px * (y - x);
        }
        double dif2(double x, double y, double z)
        {
            return x * (py - z) - y;
        }
        double dif3(double x, double y, double z)
        {
            return x * y - pz * z;
        }
        List<double[]> difList;
        void DifStart()
        {
            difList = new List<double[]>();
            for (int i = 0; i < 1000; i++)
                difList.Add(new double[3] {1,1,-10});
        }
        void DifurPr(double h)
        {
            difList.RemoveAt(0);
            difList.Add(new double[3] {difList[difList.Count - 1][0] + h * dif1(difList[difList.Count - 1][0], difList[difList.Count - 1][1], difList[difList.Count - 1][2]),
                difList[difList.Count - 1][1] + h * dif2(difList[difList.Count - 1][0], difList[difList.Count - 1][1], difList[difList.Count - 1][2]),
                difList[difList.Count - 1][2] + h * dif3(difList[difList.Count - 1][0], difList[difList.Count - 1][1], difList[difList.Count - 1][2])});
        }
        List<double[,,]> DifurPr(int N, double h)
        {
            List<double[,,]> dif = new List<double[,,]>();
            for (int i = 0; i <= 100; i++)
            {
                double[,,] difSolv = new double[100 + 1, N + 1, 3];
                difSolv[i, 0, 0] = i - 50; difSolv[i, 0, 1] = i - 50; difSolv[i, 0, 2] = i - 50;
                for (int k = 1; k <= N; k++)
                {
                    difSolv[i, k, 0] = difSolv[i, k - 1, 0] + h * dif1(difSolv[i, k - 1, 0], difSolv[i, k - 1, 1], difSolv[i, k - 1, 2]);
                    difSolv[i, k, 1] = difSolv[i, k - 1, 1] + h * dif2(difSolv[i, k - 1, 0], difSolv[i, k - 1, 1], difSolv[i, k - 1, 2]);
                    difSolv[i, k, 2] = difSolv[i, k - 1, 2] + h * dif3(difSolv[i, k - 1, 0], difSolv[i, k - 1, 1], difSolv[i, k - 1, 2]);
                }
                dif.Add(difSolv);
            }
            return dif;
        }
        void difur()
        {
            double h = 0.01;
            DifurPr(h);
            float[] c1 = { 0.0f, 0.0f, 0.0f };
            float[] c2 = { 1.0f, 0.0f, 0.0f };
            GL.Begin(PrimitiveType.LineStrip);
            GL.PointSize(3);
            for(int i = 0; i < difList.Count; i++)
            {
                double l = (double)i / difList.Count;
                double[] c = { (1 - l) * c1[0] + l * c2[0], (1 - l) * c1[1] + l * c2[1], (1 - l) * c1[2] + l * c2[2] };
                GL.Color3(c[0], c[1], c[2]);
                GL.Vertex3(difList[i][0], difList[i][1], difList[i][2]);
            }
            GL.End();
            GL.PointSize(1);
            
        }
        void DrawDifur()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Matrix4 LA = Matrix4.LookAt(eyeX(), eyeY(), eyeZ(), 0, 0, 0, 0, 0, 1);
            GL.LoadMatrix(ref LA);
            Mesh2();
            Lines();
            difur();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        double dif21(double x, double y, double z)
        {
            return -x / Math.Pow(x * x + y * y + z * z, 3.0/2);
        }
        double dif22(double x, double y, double z)
        {
            return -y / Math.Pow(x * x + y * y + z * z, 3.0/2);
        }
        double dif23(double x, double y, double z)
        {
            return -z / Math.Pow(x * x + y * y + z * z, 3.0/2);
        }
        void DifStart2()
        {
            difList = new List<double[]>();
            for (int i = 0; i < 1000; i++)
                difList.Add(new double[6] { 1, 1, -4, 0, 0, 0.5 });
        }
        void DifurPr2(double h)
        {
            difList.RemoveAt(0);
            difList.Add(new double[6] {
                difList[difList.Count - 1][0] + h * difList[difList.Count - 1][3],
                difList[difList.Count - 1][1] + h * difList[difList.Count - 1][4],
                difList[difList.Count - 1][2] + h * difList[difList.Count - 1][5],
                difList[difList.Count - 1][3] + h * dif21(difList[difList.Count - 1][0], difList[difList.Count - 1][1], difList[difList.Count - 1][2]),
                difList[difList.Count - 1][4] + h * dif22(difList[difList.Count - 1][0], difList[difList.Count - 1][1], difList[difList.Count - 1][2]),
                difList[difList.Count - 1][5] + h * dif23(difList[difList.Count - 1][0], difList[difList.Count - 1][1], difList[difList.Count - 1][2])});
        }
        void Difur2()
        {
            double h = 0.01;
            DifurPr2(h);
            float[] c1 = { 0.0f, 0.0f, 0.0f };
            float[] c2 = { 1.0f, 0.0f, 0.0f };
            GL.Begin(PrimitiveType.LineStrip);
            for (int i = 0; i < difList.Count; i++)
            {
                double l = (double)i / difList.Count;
                double[] c = { (1 - l) * c1[0] + l * c2[0], (1 - l) * c1[1] + l * c2[1], (1 - l) * c1[2] + l * c2[2] };
                GL.Color3(c[0], c[1], c[2]);
                GL.Vertex3(difList[i][0], difList[i][1], difList[i][2]);
            }
            GL.End();
        }
        void DrawDifur2()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Matrix4 LA = Matrix4.LookAt(eyeX(), eyeY(), eyeZ(), 0, 0, 0, 0, 0, 1);
            GL.LoadMatrix(ref LA);
            Mesh2();
            Lines();
            Difur2();
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
        int px, py, pz;

        private void timer2_Tick(object sender, EventArgs e)
        {
            px = trackBar4.Value;
            py = trackBar5.Value;
            pz = trackBar6.Value;
            label1.Text = trackBar4.Value.ToString();
            label2.Text = trackBar5.Value.ToString();
            label3.Text = trackBar6.Value.ToString();
            label4.Text = trackBar7.Value.ToString();
            DrawDifur();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DifStart();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (timer3.Enabled)
                timer3.Stop();
            else
                timer3.Start();
            DifStart2();
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            DrawDifur2();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            DifStart2();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (timer2.Enabled)
                timer2.Stop();
            else
                timer2.Start();
            DifStart();
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            px = trackBar4.Value;
            py = trackBar5.Value;
            label1.Text = px.ToString();
            label2.Text = py.ToString();
            CoordinateSystem();
        }
    }
}
