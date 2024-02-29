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

namespace test8
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
            GL.Ortho(0, glControl1.Width, glControl1.Height, 0, -1, 1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            rnd = new Random();
        }
        private bool enableMoving = false;
        private Point initialClickedPoint;
        struct Vert
        {
            public int i, j;
            public Vert(int i, int j)
            {
                this.i = i;
                this.j = j;
            }
            public static bool operator ==(Vert a, Vert b) => (a.i == b.i && a.j == b.j);
            public static bool operator !=(Vert a, Vert b) => !(a.i == b.i && a.j == b.j);

        };
        Random rnd;
        bool[,] A;
        int[,] B; 
        int[,] W;
        List<Vert> BW;
        SortedSet<Key> SL;
        int[,] I;
        List<Vert> I2;
        int n, m;
        int x, y;
        Vert start;
        Vert end;
        void StartMesh()
        {
            n = glControl1.Width;
            m = glControl1.Height;
            A = new bool[n, m];
            B = new int[n, m];
            W = new int[n, m];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                {
                    A[i, j] = true;
                    B[i, j] = rnd.Next(1, 51);
                    W[i, j] = -1;
                }
            start = new Vert(0, 0);
            end = new Vert(0, 0);
            method = "1";
        }
        private void MouseDown(object sender, MouseEventArgs e)
        {
            enableMoving = true;
            initialClickedPoint = e.Location;
            x = e.X;y = e.Y;
            if (button == "start" && A[e.X, e.Y])
            {
                start = new Vert(e.X, e.Y);
            }
            else if (button == "end" && A[e.X, e.Y])
            {
                end = new Vert(e.X, e.Y);
            }
        }

        private void MouseMove(object sender, MouseEventArgs e)
        {
            if (enableMoving && button == "block")
            {
                for(int i = x;i < e.X;i++)
                    for(int j = y;j < e.Y;j++)
                        A[i,j] = false;
            }
        }

        private void MouseUp(object sender, MouseEventArgs e)
        {
            enableMoving = false;
        }
        void Lee()
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                {
                    W[i, j] = -1;
                }
            BW = new List<Vert>();
            BW.Add(start);
            W[start.i, start.j] = 0;
            bool a = true, b = true;
            int r = 0;
            while (a)
            {
                List<Vert> l = new List<Vert>();
                for (int i = 0; i < BW.Count; i++)
                {
                    if (BW[i].i + 1 < n )
                    {
                        if (W[BW[i].i + 1, BW[i].j] == -1 && A[BW[i].i + 1, BW[i].j])
                        {
                            W[BW[i].i + 1, BW[i].j] = W[BW[i].i, BW[i].j] + 1;
                            Vert v = new Vert(BW[i].i + 1, BW[i].j);
                            if (v == end)
                                a = false;
                            l.Add(v);
                        }
                    }
                    if (BW[i].j + 1 < m)
                    {
                        if (W[BW[i].i, BW[i].j + 1] == -1 && A[BW[i].i, BW[i].j + 1])
                        {
                            W[BW[i].i, BW[i].j + 1] = W[BW[i].i, BW[i].j] + 1;
                            Vert v = new Vert(BW[i].i, BW[i].j + 1);
                            if (v == end)
                                a = false;
                            l.Add(v);
                        }
                    }
                    if (BW[i].i > 0)
                    {
                        if (W[BW[i].i - 1, BW[i].j] == -1 && A[BW[i].i - 1, BW[i].j])
                        {
                            W[BW[i].i - 1, BW[i].j] = W[BW[i].i, BW[i].j] + 1;
                            Vert v = new Vert(BW[i].i - 1, BW[i].j);
                            if (v == end)
                                a = false;
                            l.Add(v);
                        }
                    }
                    if (BW[i].j > 0)
                    {
                        if (W[BW[i].i, BW[i].j - 1] == -1 && A[BW[i].i, BW[i].j - 1])
                        {
                            W[BW[i].i, BW[i].j - 1] = W[BW[i].i, BW[i].j] + 1;
                            Vert v = new Vert(BW[i].i, BW[i].j - 1);
                            if (v == end)
                                a = false;
                            l.Add(v);
                        }
                    }
                }
                BW.Clear();
                BW = l;
                r++;
                if (r > n * m)
                { a = false; b = false; }
            }
            if (!b)
                I = null;
            else
            {
                int q = end.i, k = end.j;
                I = new int[W[q, k] + 1, 2];
                I[W[q, k], 0] = end.i;
                I[W[q, k], 1] = end.j;
                for (int i = W[q, k] - 1; i >= 0; i--)
                {
                    if (W[q + 1, k] == i)
                    {
                        q++;
                        I[i, 0] = q;
                        I[i, 1] = k;
                    }
                    else if (W[q, k + 1] == i)
                    {
                        k++;
                        I[i, 0] = q;
                        I[i, 1] = k;
                    }
                    else if (W[q - 1, k] == i)
                    {
                        q--;
                        I[i, 0] = q;
                        I[i, 1] = k;
                    }
                    else if (W[q, k - 1] == i)
                    {
                        k--;
                        I[i, 0] = q;
                        I[i, 1] = k;
                    }
                }
            }
        }

        void LeeDi()
        {
            SL = new SortedSet<Key>();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                {
                    W[i, j] = -1;
                }
            SL.Add(new Key(0, start.i, start.j));
            Key key;
            W[start.i, start.j] = 0;
            bool a = true, b = true;
            int r = 0;
            while (a)
            {
                key = new Key(SL.Min.k,SL.Min.i,SL.Min.j);
                if (key.i + 1 < n)
                {
                   if (W[key.i + 1, key.j] == -1 && A[key.i + 1, key.j])
                   {
                        W[key.i + 1, key.j] = W[key.i, key.j] + B[key.i + 1, key.j];
                        SL.Add(new Key(W[key.i + 1, key.j], key.i + 1, key.j));
                        if (new Vert(key.i + 1, key.j) == end)
                            a = false;
                   }
                }
                if (key.j + 1 < m)
                {
                    if (W[key.i, key.j + 1] == -1 && A[key.i, key.j + 1])
                    {
                        W[key.i, key.j + 1] = W[key.i, key.j] + B[key.i, key.j + 1];
                        SL.Add(new Key(W[key.i, key.j + 1], key.i, key.j + 1));
                        if (new Vert(key.i, key.j + 1) == end)
                            a = false;
                    }
                }
                if (key.i > 0)
                {
                    if (W[key.i - 1, key.j] == -1 && A[key.i - 1, key.j])
                    {
                        W[key.i - 1, key.j] = W[key.i, key.j] + B[key.i - 1, key.j];
                        SL.Add(new Key(W[key.i - 1, key.j], key.i - 1, key.j));
                        if (new Vert(key.i - 1, key.j) == end)
                            a = false;
                    }
                }
                if (key.j > 0)
                {
                    if (W[key.i, key.j - 1] == -1 && A[key.i, key.j - 1])
                    {
                        W[key.i, key.j - 1] = W[key.i, key.j] + B[key.i, key.j - 1];
                        SL.Add(new Key(W[key.i, key.j - 1], key.i, key.j - 1));
                        if (new Vert(key.i, key.j - 1) == end)
                            a = false;
                    }
                }
                SL.Remove(key);
                
                r++;
                if (r > n * m)
                { a = false; b = false; }
            }
            if (!b)
                I2 = null;
            else
            {
                int q = end.i, k = end.j;
                I2 = new List<Vert>();
                I2.Add(end);
                int v = W[q, k];
                while (v != 0)
                {
                    if (W[q + 1, k] == W[q, k] - B[q,k])
                    {
                        v -= B[q, k];
                        q++;
                        I2.Add(new Vert(q, k));
                    }
                    else if (W[q, k + 1] == W[q, k] - B[q, k])
                    {
                        v -= B[q, k];
                        k++;
                        I2.Add(new Vert(q, k));
                    }
                    else if (W[q - 1, k] == W[q, k] - B[q, k])
                    {
                        v -= B[q, k];
                        q--;
                        I2.Add(new Vert(q, k));
                    }
                    else if (W[q, k - 1] == W[q, k] - B[q, k])
                    {
                        v -= B[q, k];
                        k--;
                        I2.Add(new Vert(q, k));
                    }
                }
            }
        }

        void Draw()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            if (method == "1") Lee();
            else if (method == "2") LeeDi();
            GL.Begin(PrimitiveType.Points);
            float[] c1 = { 1.0f, 1.0f, 0.0f };
            float[] c2 = { 0.0f, 1.0f, 1.0f };
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if(A[i, j] && W[i,j] == -1)
                    {
                        GL.Color3(Color.HotPink);
                        GL.Vertex2(i, j);
                    }
                    else if (A[i, j] && W[i,j]!=-1)
                    {
                        //GL.Color3(Color.Gold);
                        double l = W[i,j] * 1.0 / W[end.i, end.j];
                        double[] c = { (1 - l) * c1[0] + l * c2[0], (1 - l) * c1[1] + l * c2[1], (1 - l) * c1[2] + l * c2[2] };
                        GL.Color3(c[0], c[1], c[2]);
                        GL.Vertex2(i, j);
                    }
                    else
                    {
                        GL.Color3(Color.Purple);
                        GL.Vertex2(i, j);
                    }
                        
                }
            }
            if (I != null && method == "1")
            {
                for (int k = 0; k < I.GetLength(0); k++)
                {
                    GL.Color3(Color.Blue);
                    GL.Vertex2(I[k, 0], I[k, 1]);
                }
            }
            if (I2 != null && method == "2")
            {
                for (int k = 0; k < I2.Count; k++)
                {
                    GL.Color3(Color.Blue);
                    GL.Vertex2(I2[k].i, I2[k].j);
                }
            }
            GL.Color3(Color.Red);
            GL.Vertex2(start.i, start.j);
            GL.Color3(Color.Black);
            GL.Vertex2(end.i, end.j);

            GL.End();

            richTextBox1.Text = W[end.i, end.j].ToString();
            glControl1.SwapBuffers();
        }

        string button, method;
        /// <summary>
        /// start
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click_1(object sender, EventArgs e)
        {
            button = "start";
        }
        /// <summary>
        /// end
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            button = "end";
        }
        /// <summary>
        /// block
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            button = "block";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            method = "1";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            method = "2";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Draw();
        }
        /// <summary>
        /// draw
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            if (timer1.Enabled)
                timer1.Stop();
            else
                timer1.Start();
            StartMesh();
        }
    }
}
