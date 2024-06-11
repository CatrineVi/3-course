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

namespace lab1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            glControl1.MouseMove += new MouseEventHandler(MouseMove);
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
        double b1(double t, double[,] p)
        {
            double s = 0;
            for (int i = 0; i < p.GetLength(0); i++)
            {
                s += Com(p.GetLength(0) - 1, i) * Math.Pow(1 - t, p.GetLength(0) - 1 - i) * Math.Pow(t, i) * p[i, 0];
            }
            return s;
        }
        double b2(double t, double[,] p)
        {
            double s = 0;
            for (int i = 0; i < p.GetLength(0); i++)
            {
                s += Com(p.GetLength(0) - 1, i) * Math.Pow(1 - t, p.GetLength(0) - 1 - i) * Math.Pow(t, i) * p[i, 1];
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
            for (int i = 0; i < points.GetLength(0); i++)
                GL.Vertex2(points[i, 0], points[i, 1]);
            GL.End();
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, points), b2(t, points));
            GL.End();
        }
        void DrawBezier()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            Bezier();
            Uppercase();
            Lowercase();
            e(0,0);
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }

        void Uppercase()
        {
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.PointSize(5);
            GL.Begin(PrimitiveType.LineLoop);
            GL.Vertex2(-5, -5);
            GL.Vertex2(2, -5);
            GL.Vertex2(2, 5);
            GL.Vertex2(-5, 5);
            GL.End();
        }
        void Lowercase()
        {
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.PointSize(5);
            GL.Begin(PrimitiveType.LineLoop);
            GL.Vertex2(2, -5);
            GL.Vertex2(6, -5);
            GL.Vertex2(6, 1);
            GL.Vertex2(2, 1);
            GL.End();
        }
        double[,] kx(double k, double[,] _x)
        {
            double[,] x = _x;
            for (int i = 0; i < x.GetLength(0); i++)
            {
                x[i, 0] = x[i, 0] * k;
                x[i, 1] = x[i, 1] * k;
            }
            return x;
        }
        double[,] trans(double x, double y, double[,] _x)
        {
            double[,] X = _x;
            for (int i = 0; i < X.GetLength(0); i++)
            {
                X[i, 0] = X[i, 0] + x;
                X[i, 1] = X[i, 1] + y;
            }
            return X;
        }
        void test(double x, double y)
        {
            GL.LineWidth(2);
            double delta = 0.005;
            double[,] p1 = { { (-1.61961367013373), (-4.7196261682243) }, { (5.80980683506687), (7.42990654205607) },
                { (-8.87072808320951), (6.30841121495327) }, { (-1.67904903417533), (-4.81308411214953) } };
            p1 = kx(scale, p1);
            p1 = trans(x,y, p1);
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p1), b2(t, p1));
            GL.End();
            GL.LineWidth(1);
        }
        void A(double x, double y)
        {
            GL.LineWidth(2);
            double delta = 0.005;
            double[,] p1 = { {x + ( -3.89261744966443), y + (-4.95327102803738) }, { x + (-0.838926174496644), y + (-5) },
                { x + (-1.0402684563758), y + (-0.280373831775702) }, { x + (1.97986577181208), y + (5) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p1), b2(t, p1));
            GL.End();
            double[,] p2 = { { x + (1.87919463087248), y + (-3.64485981308411) }, { x + (0.234899328859061), y + (-7.28971962616822) }, 
                { x + (-0.134228187919463), y + (-2.80373831775701) }, { x + (1.94630872483221), y + (4.81308411214953) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p2), b2(t, p2));
            GL.End();
            double[,] p3 = { {  x + (-3.89261744966443), y + (-4.95327102803738) }, { x + (-7.01342281879195), y + (-3.41121495327103) },
                { x + (-3.02013422818792), y + (1.1214953271028) }, { x + (1.30872483221476), y + (0.280373831775702) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p3), b2(t, p3));
            GL.End();
            double[,] p4 = { { x + (-4.29530201342282), y + (-1.63551401869159) }, { x + (-4.73154362416107), y + (-4.62616822429907) },
                { x + (-3.08724832214765), y +(-4.34579439252336) }, { x + (-1.71140939597315), y + (-2.71028037383178) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p4), b2(t, p4));
            GL.End();
            double[,] p5 = { { x + (1.47651006711409), y + (-4.4392523364486) }, { x + (0.134228187919463), y + (-4.39252336448598) },
                { x + (1.10738255033557), y + (0.327102803738319) }, { x + (1.71140939597315), y + (3.97196261682243) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p5), b2(t, p5));
            GL.End();
            double[,] p6 = { { x + (-1.77852348993289), y + (-2.75700934579439) }, { x + (-0.805369127516778), y + (-1.30841121495327)},
                { x + (-0.167785234899329), y + (1.35514018691589) }, { x + (1.67785234899329), y + (4.57943925233645) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p6), b2(t, p6));
            GL.End();
            GL.LineWidth(1);
        }
        void a(double x, double y)
        {
            GL.LineWidth(2);
            double delta = 0.005;
            double[,] p1 = { { x + (4.56375838926174), y + (-4.01869158878505) }, { x + (-0.369127516778523), y + (-7.99065420560748) },
                { x + (3.18791946308725), y + (3.45794392523364) }, { x + (5.16778523489933), y + (0.327102803738319) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p1), b2(t, p1));
            GL.End();
            double[,] p2 = { { x + (6.91275167785235), y + (-4.20560747663551) }, { x + (3.05369127516779), y + (-6.86915887850467) },
                { x + (4.76510067114094), y + (-0.280373831775702) }, { x + (5.46979865771812), y + (0.700934579439252) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p2), b2(t, p2));
            GL.End();
            double[,] p3 = { { x + (5.43624161073826), y + (0.373831775700934) }, { x + (4.86577181208054), y + (-0.747663551401869) },
                { x + (4.19463087248322), y + (-4.90654205607477) }, { x + (6.24161073825503), y + (-4.62616822429907) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p3), b2(t, p3));
            GL.End();
            double[,] p4 = { { x + (3.8255033557047), y + (-4.57943925233645) }, { x + (1.30872483221476), y + (-4.90654205607477) },
                { x + (3.42281879194631), y + (1.72897196261682) }, { x + (4.86577181208054), y + (0.654205607476635) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p4), b2(t, p4));
            GL.End();
            GL.LineWidth(1);
        }
        void C(double x, double y)
        {
            GL.LineWidth(2);
            double delta = 0.005;
            double[,] p1 = { { x + (-0.520059435364042), y + (-4.95327102803738) }, { x + (-7.94947994056464), y + (-5.46728971962617) },
                { x + (-5.15601783060921), y + (6.07476635514019) }, { x + (1.2927191679049), y + (5) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p1), b2(t, p1));
            GL.End();
            double[,] p2 = { { x + (2.15453194650817), y + (4.62616822429907) }, { x + (0.341753343239228), y + (1.77570093457944) },
                { x + (3.19465081723625), y + (3.36448598130841) }, { x + (1.2927191679049), y + (5) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p2), b2(t, p2));
            GL.End();
            double[,] p3 = { {  x + (-0.520059435364042), y + (-4.95327102803738) }, { x + (0.549777117384844), y + (-4.53271028037383) },
                { x + (1.61961367013373), y + (-3.41121495327103) }, { x + (2.03566121842496), y + (-2.42990654205607) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p3), b2(t, p3));
            GL.End();
            double[,] p4 = { {  x + (0.401188707280832), y + (-4.39252336448598) }, { x + (-5.57206537890045), y + (-5.14018691588785) },
                { x + (-5), y + (5) }, { x + (0.401188707280832), y + (5.04672897196262) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p4), b2(t, p4));
            GL.End();
            GL.LineWidth(1);
        }
        void e(double x, double y)
        {
            GL.LineWidth(2);
            double delta = 0.005;
            double[,] p1 = { { x + (3.99702823179792), y + (0.934579439252337) }, { x + (1.53046062407132), y + (-1.21495327102804) },
                { x + (1.14413075780089), y + (-5.2803738317757) }, { x + (4.14561664190193), y + (-4.95327102803738)} };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p1), b2(t, p1));
            GL.End();
            double[,] p2 = { { x + (4.02674591381872), y + (0.934579439252337) }, { x + (5.80980683506687), y + (1.58878504672897) },
                { x + (5.89895988112927), y + (-1.30841121495327) }, { x + (1.94650817236256), y + (-4.20560747663551) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p2), b2(t, p2));
            GL.End();
            double[,] p3 = { {  x + (4.11589895988113), y + (-4.90654205607477) }, { x + (1.2630014858841), y + (-3.22429906542056) },
                { x + (3.28380386329866), y + (0.140186915887851) }, { x + (3.99702823179792), y + (0.934579439252337) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p3), b2(t, p3));
            GL.End();
            double[,] p4 = { {  x + (4.05646359583952), y + (-4.90654205607477) }, { x + (5.54234769687964), y + (-4.95327102803738) },
                { x + (6.1961367013373), y + (-4.67289719626168) }, { x + (6.91275167785235), y + (-4.20560747663551) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p4), b2(t, p4));
            GL.End();
            GL.LineWidth(1);
        }
        void h(double x, double y) 
        {
            GL.LineWidth(2);
            double delta = 0.005;
            double[,] p1 = { { x + (2.00594353640416), y + (-4.90654205607477) }, { x + (3.96731054977712), y + (-2.57009345794393) },
                { x + (3.28380386329866), y + (1.54205607476636) }, { x + (5.15601783060921), y + (5.18691588785047) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p1), b2(t, p1));
            GL.End();
            double[,] p2 = { { x + (4.02674591381872), y + (0.186915887850468) }, { x + (5.12630014858841), y + (2.19626168224299) },
                { x + (6.01783060921248), y + (-0.186915887850468) }, { x + (5.45319465081724), y + (-1.63551401869159) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p2), b2(t, p2));
            GL.End();
            double[,] p3 = { {  x + (5.06686478454681), y + (5.09345794392523) }, { x + (5.89895988112927), y + (6.02803738317757) },
                { x + (6.3150074294205), y + (5.09345794392523) }, { x + (5.12630014858841), y + (3.13084112149533) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p3), b2(t, p3));
            GL.End();
            double[,] p4 = { {  x + (5.21545319465082), y + (5.2803738317757) }, { x + (3.49182763744428), y + (1.44859813084112) },
                { x + (3.87815750371471), y + (-3.92523364485981) }, { x + (2.06537890044577), y + (-4.90654205607477) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p4), b2(t, p4));
            GL.End();
            double[,] p5 = { { x + (5.45319465081724), y + (-1.58878504672897) }, { x + (3.96731054977712), y + (-5.51401869158879) },
                {x + (5.66121842496285), y + (-5.09345794392523) }, { x + (6.91275167785235), y + (-4.20560747663551) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p5), b2(t, p5));
            GL.End(); 
            double[,] p6 = { { x + (4.88855869242199), y + (-2.05607476635514) }, { x + (5.60178306092125), y + (-1.16822429906542) },
                { x + (4.9479940564636), y + (2.47663551401869) }, { x + (3.7890044576523), y + (-0.280373831775702) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p6), b2(t, p6));
            GL.End();
            double[,] p7 = { { x + (6.91275167785235), y + (-4.20560747663551) }, { x + (5.72065378900446), y + (-5.18691588785047) },
                { x + (3.7592867756315), y + (-5.8411214953271) }, { x + (4.88855869242199), y + (-2.05607476635514) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p7), b2(t, p7));
            GL.End();
            double[,] p8 = { { x + (5.15601783060921), y + (3.22429906542056) }, { x + (3.61069836552749), y + (0.747663551401869) },
                { x + (3.31352154531947), y + (-1.16822429906542) }, { x + (1.97622585438336), y + (-4.20560747663551) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p8), b2(t, p8));
            GL.End();
            GL.LineWidth(1);
        }
        void i(double x, double y) 
        {
            GL.LineWidth(2);
            double delta = 0.005;
            double[,] p1 = { { x + (2.09509658246657), y + (-4.20560747663551) }, { x + (6.01783060921248), y + (-0.327102803738319) },
                { x + (4.35364041604755), y + (4.34579439252336) }, { x + (3.6998514115899), y + (-2.80373831775701) } };
            p1 = kx(scale, p1);
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p1), b2(t, p1));
            GL.End();
            double[,] p2 = { { x + (6.91275167785235), y + (-4.20560747663551) }, { x + (4.41307578008915), y + (-5.88785046728972) },
                { x + (3.6998514115899), y + (-4.57943925233645) }, { x + (3.6998514115899), y + (-2.70373831775701) } };
            p2 = kx(scale, p2);
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p2), b2(t, p2));
            GL.End();
            double[,] p3 = { {  x + (5.98811292719168), y + (-4.67289719626168) }, { x + (5.36404160475483), y + (-4.85981308411215) },
                { x + (3.13521545319465), y + (-5.51401869158879) }, { x + (4.20505200594354), y + (0.327102803738319) } };
            p3 = kx(scale, p3);
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p3), b2(t, p3));
            GL.End();
            double[,] p4 = { { x + (4.62109955423477), y + (1.58878504672897) }, { x + (5.75037147102526), y + (2.99065420560748) },
                { x + (4.50222882615156), y + (4.11214953271028) }, { x + (4.62109955423477), y + (1.58878504672897) } };
            p4 = kx(scale, p4);
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p4), b2(t, p4));
            GL.End();
            GL.LineWidth(1);
        }
        void n(double x, double y) 
        {
            GL.LineWidth(2);
            double delta = 0.005;
            double[,] p1 = { { x + (2.42199108469539), y + (-4.95327102803738) }, { x + (3.49182763744428), y + (-3.83177570093458) },
                { x + (3.96731054977712), y + (-1.02803738317757) }, { x + (3.67013372956909), y + (0.934579439252337) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p1), b2(t, p1));
            GL.End();
            double[,] p2 = { { x + (4.02674591381872), y + (0.186915887850468) }, { x + (5.12630014858841), y + (2.19626168224299) },
                { x + (6.01783060921248), y + (-0.186915887850468) }, { x + (5.45319465081724), y + (-1.63551401869159) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p2), b2(t, p2));
            GL.End();
            double[,] p3 = { { x + (3.55126300148588), y + (0.467289719626168) }, { x + (3.6998514115899), y + (-1.54205607476636) },
                { x + (2.98662704309064), y + (-3.97196261682243) }, { x + (2.4517087667162), y + (-4.95327102803738) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p3), b2(t, p3));
            GL.End();
            double[,] p4 = { { x + (1.94650817236256), y + (-4.20560747663551) }, { x + (4.9777117384844), y + (-1.44859813084112) },
                { x + (3.31352154531947), y + (2.75700934579439) }, { x + (3.55126300148588), y + (0.280373831775702) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p4), b2(t, p4));
            GL.End();
            double[,] p5 = { { x + (5.45319465081724), y + (-1.58878504672897) }, { x + (3.96731054977712), y + (-5.51401869158879) },
                {x + (5.66121842496285), y + (-5.09345794392523) }, { x + (6.91275167785235), y + (-4.20560747663551) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p5), b2(t, p5));
            GL.End();
            double[,] p6 = { { x + (4.88855869242199), y + (-2.05607476635514) }, { x + (5.60178306092125), y + (-1.16822429906542) },
                { x + (4.9479940564636), y + (2.47663551401869) }, { x + (3.7890044576523), y + (-0.280373831775702) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p6), b2(t, p6));
            GL.End();
            double[,] p7 = { { x + (6.91275167785235), y + (-4.20560747663551) }, { x + (5.72065378900446), y + (-5.18691588785047) },
                { x + (3.7592867756315), y + (-5.8411214953271) }, { x + (4.88855869242199), y + (-2.05607476635514) } };
            GL.Color3(0.0f, 0.0f, 0.0f);
            GL.Begin(PrimitiveType.LineStrip);
            for (double t = 0; t <= 1; t += delta)
                GL.Vertex2(b1(t, p7), b2(t, p7));
            GL.End();
            GL.LineWidth(1);
        }
        void r(double x, double y) 
        {

        }
        void t(double x, double y) { }

        private void button1_Click(object sender, EventArgs e)
        {

            if (timer1.Enabled)
                timer1.Stop();
            else
                timer1.Start();
        }
        private void timer1_Tick(object sender, EventArgs e) // bezier 
        {
            DrawBezier();
            textBox1.Text = "x + (" + points[0, 0].ToString() + "), y + (" + points[0, 1].ToString() + ")";
            textBox2.Text = "x + (" + points[1, 0].ToString() + "), y + (" + points[1, 1].ToString() + ")";
            textBox3.Text = "x + (" + points[2, 0].ToString() + "), y + (" + points[2, 1].ToString() + ")";
            textBox4.Text = "x + (" + points[3, 0].ToString() + "), y + (" + points[3, 1].ToString() + ")";
        }

        private void button2_Click(object sender, EventArgs e)  //clear
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            GL.PopMatrix();
            glControl1.SwapBuffers();
            timer1.Stop();
            timer2.Stop();
            points[0, 0] = -5; points[0, 1] = -5;
            points[1, 0] = 5; points[1, 1] = 0;
            points[2, 0] = -5; points[2, 1] = 5;
            points[3, 0] = 0; points[3, 1] = -5;
        }

        private void button3_Click(object sender, EventArgs e) //write
        {
            if (timer2.Enabled)
                timer2.Stop();
            else
                timer2.Start();
        }
        string phrase;
        double scale;
        void Write(double _scale)
        {
            
            List<double[]> letters = new List<double[]>();
            letters.Add(new double[2] { -5*_scale-9, 5*_scale+9 });
            GL.Begin(PrimitiveType.Points);
            GL.Color3(1.0f, 0.0f, 0.0f);
            GL.Vertex2(letters[0][0], letters[0][1]);
            GL.Vertex2(-9, 9);
            GL.End();
            for (int s = 0; s < phrase.Length - 1; s++)
            {
                if (phrase[s] == 'A') A(letters[s][0], letters[s][1]);
                else if (phrase[s] == 'a') a(letters[s][0] - 5, letters[s][1]);
                else if (phrase[s] == 'C') C(letters[s][0], letters[s][1]);
                else if (phrase[s] == 'e') e(letters[s][0] - 5, letters[s][1]);
                else if (phrase[s] == 'h') h(letters[s][0] - 5, letters[s][1]);
                else if (phrase[s] == 'i') i(letters[s][0] - 5, letters[s][1]);
                else if (phrase[s] == 'n') n(letters[s][0] - 5, letters[s][1]);
                else if (phrase[s] == 'r') r(letters[s][0] - 5, letters[s][1]);
                else if (phrase[s] == 't') t(letters[s][0] - 5, letters[s][1]);
                else if (phrase[s] == 'o') test(letters[s][0], letters[s][1]);
                if (letters[s][0] >= 9 + 7*_scale)
                    letters.Add(new double[2] { -9, letters[s][1] - 10*_scale });
                else if ("QWERTYUIOPASDFGHJKLZXCVBNM".Contains(phrase[s + 1]))
                    letters.Add(new double[2] { letters[s][0] + 7*_scale, letters[s][1] });
                else if ("qwertyuiopasdfghjklzxcvbnm ".Contains(phrase[s + 1]))
                    letters.Add(new double[2] { letters[s][0] + 5*_scale, letters[s][1] });
                else if ("\n".Contains(phrase[s + 1]))
                    letters.Add(new double[2] { -9 - 6*_scale, letters[s][1] - 10*_scale });
            }
        }
        void DrawWrite()
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.PushMatrix();
            //GL.Scale(scale, scale, 1);
            Write(scale);
            GL.PopMatrix();
            glControl1.SwapBuffers();
        }
        private void timer2_Tick(object sender, EventArgs e)
        {
            phrase = richTextBox1.Text + '&';
            scale = Convert.ToDouble(trackBar1.Value) / 10.0;
            DrawWrite();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {

        }
    }
}
