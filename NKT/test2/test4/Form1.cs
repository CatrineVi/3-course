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

namespace test4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            glControl1.MouseMove += new MouseEventHandler(MouseMove);
        }

        private void glControl1_Load(object sender, EventArgs e)
        {
            
        }

        private bool enableMoving = false;
        private Point initialClickedPoint;

        double[,] points = { { -5, -5 }, { 5, 0 }, { -5, 5 }, { 0, -5 } }; // Bezier
        double x; double y;
        int pInd;

        private void MouseDown(object sender, MouseEventArgs e)
        {
            enableMoving = true;
            initialClickedPoint = e.Location;
            x = -10 + 20.0 * e.X / glControl1.Width;
            y = -10 + 20.0 * (glControl1.Height - e.Y) / glControl1.Height;
            double r = 20.0 / glControl1.Width;
            for (int i = 0; i < points.GetLength(0); i++)
            {
                if (Math.Abs(points[i, 0] - x) <= 5 * r && Math.Abs(points[i, 1] - y) <= 5 * r)
                {
                    pInd = i;
                    break;
                }
            }
        }

        private void MouseUp(object sender, MouseEventArgs e)
        {
            enableMoving = false;
        }

        private void MouseMove(object sender, MouseEventArgs e)
        {
            if (enableMoving)
            {
                x = -10 + 20.0 * e.X / glControl1.Width;
                y = -10 + 20.0 * (glControl1.Height - e.Y) / glControl1.Height;
                points[pInd, 0] = x;
                points[pInd, 1] = y;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            GL.ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(-10, 10, -10, 10, -1, 1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
        }

        double fi = (-1 + Math.Sqrt(5)) / 2;
        double[] points1; double[] points2;
        double[] PentaPoints1()
        {
            double[] points1 = {4 * Math.Cos(Math.PI / 2), 4 * Math.Sin(Math.PI / 2),
                                 4 * Math.Cos(Math.PI / 2 + 2 * Math.PI / 5), 4 * Math.Sin(Math.PI / 2 + 2 * Math.PI / 5),
                                 4 * Math.Cos(Math.PI / 2 + 4 * Math.PI / 5), 4 * Math.Sin(Math.PI / 2 + 4 * Math.PI / 5),
                                 4 * Math.Cos(Math.PI / 2 + 6 * Math.PI / 5), 4 * Math.Sin(Math.PI / 2 + 6 * Math.PI / 5),
                                 4 * Math.Cos(Math.PI / 2 + 8 * Math.PI / 5), 4 * Math.Sin(Math.PI / 2 + 8 * Math.PI / 5)};
            return points1;
        }
        double[] PentaPoints2()
        {
            double[] points2 = { points1[2] + (points1[8] - points1[2]) * fi, points1[3] + (points1[9] - points1[3]) * fi,
                                 points1[8] + (points1[2] - points1[8]) * fi, points1[9] + (points1[3] - points1[9]) * fi,
                                 points1[0] + (points1[6] - points1[0]) * fi, points1[1] + (points1[7] - points1[1]) * fi,
                                 points1[8] + (points1[4] - points1[8]) * fi, points1[9] + (points1[5] - points1[9]) * fi,
                                 points1[0] + (points1[4] - points1[0]) * fi, points1[1] + (points1[5] - points1[1]) * fi};
            return points2;
        }
        
        void Penta()
        {
            points1 = PentaPoints1();
            points2 = PentaPoints2();

            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.Triangles);

            GL.Vertex2(points1[0], points1[1]);
            GL.Vertex2(points2[0], points2[1]);
            GL.Vertex2(points2[2], points2[3]);

            GL.Vertex2(points1[8], points1[9]);
            GL.Vertex2(points2[0], points2[1]);
            GL.Vertex2(points2[4], points2[5]);

            GL.Vertex2(points1[6], points1[7]);
            GL.Vertex2(points2[6], points2[7]);
            GL.Vertex2(points2[4], points2[5]);

            GL.Vertex2(points1[4], points1[5]);
            GL.Vertex2(points2[6], points2[7]);
            GL.Vertex2(points2[8], points2[9]);

            GL.Vertex2(points1[2], points1[3]);
            GL.Vertex2(points2[2], points2[3]);
            GL.Vertex2(points2[8], points2[9]);
            GL.End();


            GL.Color3(0.0f, 1.0f, 1.0f);
            GL.Begin(PrimitiveType.Polygon);
            GL.Vertex2(points2[2], points2[3]);
            GL.Vertex2(points2[0],points2[1]);
            GL.Vertex2(points2[4],points2[5]);
            GL.Vertex2(points2[6],points2[7]);
            GL.Vertex2(points2[8],points2[9]);
            GL.End();
        }
        void PentaLineLoop()
        {
            points1 = PentaPoints1();
            points2 = PentaPoints2();
            //GL.PushMatrix();
            GL.LineWidth(1);
            //GL.Rotate(45, 0, 0, 10);
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineLoop);
            GL.Vertex2(points1[0], points1[1]);
            GL.Vertex2(points1[6], points1[7]);
            GL.Vertex2(points1[2], points1[3]);
            GL.Vertex2(points1[8], points1[9]);
            GL.Vertex2(points1[4], points1[5]);
            GL.End();
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.Points);
            GL.Vertex2(points2[0], points2[1]);
            GL.End();
            //GL.PopMatrix();
        }
        void DrawPenta()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit|ClearBufferMask.DepthBufferBit);
            Penta();
            PentaLineLoop();
            glControl1.SwapBuffers();
        }
        void DrawPentaLineLoop()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            PentaLineLoop();
            glControl1.SwapBuffers();
        }
        void DrawPointsLines()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PointSize(5);
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.Points);
            GL.Vertex2(-5, 5);
            GL.Vertex2(5, 5);
            GL.Vertex2(-5, -5);
            GL.Vertex2(5,-5);
            GL.End();

            GL.LineWidth(5);
            GL.Color3(1.0f, 1.0f, 0.0f);
            GL.Begin(PrimitiveType.Lines);
            GL.Vertex2(-4, 5);
            GL.Vertex2(4, 5);

            GL.Vertex2(5, 4);
            GL.Vertex2(5,-4);

            GL.Vertex2(4,-5); ;
            GL.Vertex2(-4,-5);

            GL.Vertex2(-5, -4);
            GL.Vertex2(-5, 4);
            GL.End();

            GL.LineWidth(2);
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            GL.Vertex2(-2, -3);
            GL.Vertex2(0, 0);
            GL.Vertex2(-2, 1);
            GL.Vertex2(-2, -1);
            GL.Vertex2(2, 1);
            GL.Vertex2(2, -1);
            GL.Vertex2(0, 0);
            GL.Vertex2(2, -3);
            GL.End();
            glControl1.SwapBuffers();
        }

        void LetterK(int a)
        {
            GL.PushMatrix();
            GL.Translate(4 * Math.Cos(Math.PI / 2), 4 * Math.Sin(Math.PI / 2), 0);
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.Lines);
            GL.Vertex2(0, 0);
            GL.Vertex2(0, a);
            GL.Vertex2(0, a / 1.8);
            GL.Vertex2(a / 2.0, a);
            GL.Vertex2(0, a / 1.8);
            GL.Vertex2(a / 2.0, 0);
            GL.End();
            GL.PopMatrix();
        }
        void LetterA(int a)
        {
            GL.PushMatrix();
            GL.Translate(4 * Math.Cos(Math.PI / 2 + 8 * Math.PI / 5), 4 * Math.Sin(Math.PI / 2 + 8 * Math.PI / 5), 0);
            GL.Rotate((8*Math.PI/5)*180/Math.PI, 0, 0, 1);
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.Lines);
            GL.Vertex2(a/3.0, 0);
            GL.Vertex2(0, a);
            GL.Vertex2(-a/3.0, 0);
            GL.Vertex2(0, a);
            GL.Vertex2(-a/4.0, a / 3.0);
            GL.Vertex2(a / 4.0, a/3.0);
            GL.End();
            GL.PopMatrix();
        }
        void LetterT1(int a)
        {
            GL.PushMatrix();
            GL.Translate(4 * Math.Cos(Math.PI / 2 + 6 * Math.PI / 5), 4 * Math.Sin(Math.PI / 2 + 6 * Math.PI / 5), 0);
            GL.Rotate(6 * Math.PI / 5 * 180 / Math.PI, 0, 0, 1);
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.Lines);
            GL.Vertex2(0, 0);
            GL.Vertex2(0, a);
            GL.Vertex2(-a / 2.0, a);
            GL.Vertex2(a / 2.0, a);
            GL.End();
            GL.PopMatrix();
        }
        void LetterT2(int a)
        {
            GL.PushMatrix();
            GL.Translate(4 * Math.Cos(Math.PI / 2 + 4 * Math.PI / 5), 4 * Math.Sin(Math.PI / 2 + 4 * Math.PI / 5), 0);
            GL.Rotate(4 * Math.PI / 5 * 180 / Math.PI, 0, 0, 1);
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.Lines);
            GL.Vertex2(0, 0);
            GL.Vertex2(0, a);
            GL.Vertex2(-a / 2.0, a);
            GL.Vertex2(a / 2.0, a);
            GL.End();
            GL.PopMatrix();
        }
        void LetterE(int a)
        {
            GL.PushMatrix();
            GL.Translate(4 * Math.Cos(Math.PI / 2 + 2 * Math.PI / 5), 4 * Math.Sin(Math.PI / 2 + 2 * Math.PI / 5), 0);
            GL.Rotate(2 * Math.PI / 5*180/Math.PI, 0, 0, 1);
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.Lines);
            GL.Vertex2(0, 0);
            GL.Vertex2(0, a);
            GL.Vertex2(0, a);
            GL.Vertex2(a / 2.0, a);
            GL.Vertex2(0, a/1.8);
            GL.Vertex2(a / 2.0, a/1.8);
            GL.Vertex2(0, 0);
            GL.Vertex2(a / 2.0, 0);
            GL.End();
            GL.PopMatrix();
        }

        int b = 0;
        void DrawLetter(int a)
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            GL.Rotate(b, 0, 0, 1);
            GL.LineWidth(2);
            LetterK(a);
            LetterA(a);
            LetterT1(a);
            LetterT2(a);
            LetterE(a);
            GL.PopMatrix();
            glControl1.SwapBuffers();
            b += 5;
        }

        double f1(int r, double t)
        {
            return r * Math.Cos(t);
        }
        double f2(int r, double t)
        {
            return r * Math.Sin(t);
        }

        int ReadTrackBar1()
        {
            return trackBar1.Value;
        }
        int ReadTrackBar2()
        {
            return trackBar2.Value;
        }

        void Circle()
        {
            double tMin = 0;
            double tMax = 2 * Math.PI;
            int grid = ReadTrackBar1();
            int r = ReadTrackBar2();
            double delta = (tMax - tMin) / grid;
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineLoop);
            for(double t = tMin; t< tMax;t+=delta)
                GL.Vertex2(f1(r,t), f2(r,t));
            GL.End();
        }

        void DrawCircle()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Circle();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        double c1(double r, double x)
        {
            return Math.Sqrt(r * r - x * x);
        }
        void Circle2()
        {
            double tMin = 0;
            double tMax = Math.PI;
            int grid = ReadTrackBar1();
            int r = 5;
            double delta = (tMax - tMin) / grid;

            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = tMin; t < tMax; t += delta)
                GL.Vertex2(f1(r, t), f2(r, t));
            GL.End();

            GL.Color3(1.0f, 1.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            tMin = -r; tMax = r;
            delta = (tMax - tMin) / grid;
            for (double t = tMin;t<tMax;t+=delta)
                GL.Vertex2(t,c1(r, t));
            GL.End();
        }
        void DrawCircle2()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Circle2();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }

        double g1(double t)
        {
            return 4.4 * (Math.Cos(t) + Math.Cos(1.1 * t) * 1.1);
        }
        double g2(double t)
        {
            return 4.4*(Math.Sin(t) - Math.Sin(1.1 * t) * 1.1);
        }
        void Gipozikloid()
        {
            double tMin = 0;
            double tMax = 20 * Math.PI;
            int grid = ReadTrackBar1();
            double delta = (tMax - tMin) / grid;
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineLoop);
            for (double t = tMin; t < tMax; t += delta)
                GL.Vertex2(g1(t), g2(t));
            GL.End();
        }
        void DrawGipozikloid()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Gipozikloid();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }

        int kof;
        int d(int i, int N)
        {
            return kof * i % N;
        }
        void Cardioida()
        {
            double tMin = 0;
            double tMax = 2*Math.PI;
            int grid = ReadTrackBar1();
            int r = ReadTrackBar2();
            double delta = (tMax - tMin) / grid;
            double[,] points = new double[grid, 2];
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineLoop);
            
            for (int i = 0; i < grid; i++)
            {
                GL.Vertex2(f1(r,tMin+i*delta), f2(r,tMin+i*delta));
                points[i, 0] = f1(r, tMin+i*delta);
                points[i, 1] = f2(r, tMin+i*delta);
            }
            GL.End();
            kof = trackBar3.Value;
            GL.Begin(PrimitiveType.Lines);
            for(int j = 0; j < grid; j++)
            {
                GL.Vertex2(points[j,0],points[j,1]);
                GL.Vertex2(points[d(j,grid),0],points[d(j,grid),1]);
            }
            GL.End();
        }
        void DrawCardioida()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Cardioida();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }

        double b1(double t, double[,] p)
        {
            double s = 0;
            for(int i=0; i<p.GetLength(0); i++)
            {
                s += Com(p.GetLength(0)-1, i) * Math.Pow(1 - t, p.GetLength(0)-1 - i) * Math.Pow(t, i) * p[i, 0];
            }
            return s;
        }
        double b2(double t, double[,] p)
        {
            double s = 0;
            for (int i = 0; i < p.GetLength(0); i++)
            {
                s += Com(p.GetLength(0)-1, i) * Math.Pow(1 - t, p.GetLength(0)-1 - i) * Math.Pow(t, i) * p[i, 1];
            }
            return s;
        }
        double Com(int k, int i)
        {
            if (i == 0 || i == k)
                return 1;
            else return Com(k - 1, i - 1) + Com(k - 1, i);
        }
        
        void Bezier()
        {
            double delta = 0.005;
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.PointSize(5);
            GL.Begin(PrimitiveType.Points);
            for (int i = 0; i < points.GetLength(0); i++)
                GL.Vertex2(points[i, 0], points[i, 1]);
            GL.End();
            GL.Begin(PrimitiveType.LineStrip);
            for(int i = 0; i < points.GetLength(0); i++)
                GL.Vertex2(points[i, 0], points[i, 1]);
            GL.End();
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t+=delta)
                GL.Vertex2(b1(t, points),b2(t,points));
            GL.End();
        }
        void DrawBezier()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Bezier();
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }        

        private void button1_Click(object sender, EventArgs e) // Penta
        {
            DrawPenta();
        }

        private void button2_Click(object sender, EventArgs e) // pentaLineLoop
        {
            DrawPentaLineLoop();
        }

        private void button3_Click(object sender, EventArgs e) // pointsLines
        {
            DrawPointsLines();
        }

        private void button4_Click(object sender, EventArgs e) // timer1 Letter
        {
            if (timer1.Enabled)
                timer1.Stop();
            else
                timer1.Start();
        }

        private void button5_Click(object sender, EventArgs e) // timer2 circle
        {
            if (timer2.Enabled)
                timer2.Stop();
            else
                timer2.Start();
        }

        private void button6_Click(object sender, EventArgs e) // timer3 gipozikloid
        {
            if (timer3.Enabled)
                timer3.Stop();
            else
                timer3.Start();
        }

        private void button7_Click(object sender, EventArgs e) // timer4 circle2
        {
            if (timer4.Enabled)
                timer4.Stop();
            else
                timer4.Start();
        }

        private void button8_Click(object sender, EventArgs e) // timer5 cardioida
        {
            if (timer5.Enabled)
                timer5.Stop();
            else
                timer5.Start();
        }

        private void button9_Click(object sender, EventArgs e) // Bezier 
        {
            if (timer6.Enabled)
                timer6.Stop();
            else
                timer6.Start();
        }

        private void timer1_Tick(object sender, EventArgs e) // letter
        {
            DrawLetter(2);
        }

        private void timer2_Tick(object sender, EventArgs e) // circle
        {
            DrawCircle();
        }

        private void timer3_Tick(object sender, EventArgs e) // gipozicloid
        {
            DrawGipozikloid();
        }

        private void timer4_Tick(object sender, EventArgs e) // circle2
        {
            label1.Text = trackBar1.Value.ToString();
            DrawCircle2();
        }

        private void timer5_Tick(object sender, EventArgs e) // cardioida
        {
            label1.Text = trackBar1.Value.ToString();
            DrawCardioida();
        }

        private void timer6_Tick(object sender, EventArgs e) // bezier 
        {
            DrawBezier();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {

        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {

        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        
    }
}
