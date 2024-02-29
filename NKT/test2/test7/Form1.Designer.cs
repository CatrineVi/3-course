namespace test7
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.glControl1 = new OpenTK.GLControl();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.button5 = new System.Windows.Forms.Button();
            this.richTextBox2 = new System.Windows.Forms.RichTextBox();
            this.button6 = new System.Windows.Forms.Button();
            this.richTextBox3 = new System.Windows.Forms.RichTextBox();
            this.richTextBox4 = new System.Windows.Forms.RichTextBox();
            this.richTextBox5 = new System.Windows.Forms.RichTextBox();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.richTextBox6 = new System.Windows.Forms.RichTextBox();
            this.richTextBox7 = new System.Windows.Forms.RichTextBox();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // glControl1
            // 
            this.glControl1.BackColor = System.Drawing.Color.Black;
            this.glControl1.Location = new System.Drawing.Point(162, 11);
            this.glControl1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.glControl1.Name = "glControl1";
            this.glControl1.Size = new System.Drawing.Size(800, 800);
            this.glControl1.TabIndex = 0;
            this.glControl1.VSync = false;
            this.glControl1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MouseDown);
            this.glControl1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MouseMove);
            this.glControl1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.MouseUp);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.HotPink;
            this.button1.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button1.Location = new System.Drawing.Point(21, 16);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(120, 51);
            this.button1.TabIndex = 1;
            this.button1.Text = "graph";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.HotPink;
            this.button2.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button2.Location = new System.Drawing.Point(22, 73);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(119, 51);
            this.button2.TabIndex = 2;
            this.button2.Text = "graphDraw";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.HotPink;
            this.button3.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button3.Location = new System.Drawing.Point(22, 130);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(120, 51);
            this.button3.TabIndex = 3;
            this.button3.Text = "ArcGraph";
            this.button3.UseVisualStyleBackColor = false;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.Color.HotPink;
            this.button4.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button4.Location = new System.Drawing.Point(22, 187);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(120, 51);
            this.button4.TabIndex = 4;
            this.button4.Text = "MinWeight";
            this.button4.UseVisualStyleBackColor = false;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(978, 130);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(230, 684);
            this.richTextBox1.TabIndex = 5;
            this.richTextBox1.Text = "";
            // 
            // button5
            // 
            this.button5.BackColor = System.Drawing.Color.HotPink;
            this.button5.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button5.Location = new System.Drawing.Point(22, 244);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(120, 51);
            this.button5.TabIndex = 6;
            this.button5.Text = "path";
            this.button5.UseVisualStyleBackColor = false;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // richTextBox2
            // 
            this.richTextBox2.Location = new System.Drawing.Point(978, 12);
            this.richTextBox2.Name = "richTextBox2";
            this.richTextBox2.Size = new System.Drawing.Size(230, 32);
            this.richTextBox2.TabIndex = 7;
            this.richTextBox2.Text = "";
            // 
            // button6
            // 
            this.button6.BackColor = System.Drawing.Color.HotPink;
            this.button6.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button6.Location = new System.Drawing.Point(3, 301);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(48, 51);
            this.button6.TabIndex = 8;
            this.button6.Text = "BF";
            this.button6.UseVisualStyleBackColor = false;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // richTextBox3
            // 
            this.richTextBox3.Location = new System.Drawing.Point(978, 47);
            this.richTextBox3.Name = "richTextBox3";
            this.richTextBox3.Size = new System.Drawing.Size(72, 33);
            this.richTextBox3.TabIndex = 9;
            this.richTextBox3.Text = "";
            // 
            // richTextBox4
            // 
            this.richTextBox4.Location = new System.Drawing.Point(1056, 47);
            this.richTextBox4.Name = "richTextBox4";
            this.richTextBox4.Size = new System.Drawing.Size(76, 33);
            this.richTextBox4.TabIndex = 10;
            this.richTextBox4.Text = "";
            // 
            // richTextBox5
            // 
            this.richTextBox5.Location = new System.Drawing.Point(1138, 47);
            this.richTextBox5.Name = "richTextBox5";
            this.richTextBox5.Size = new System.Drawing.Size(70, 33);
            this.richTextBox5.TabIndex = 11;
            this.richTextBox5.Text = "";
            // 
            // button7
            // 
            this.button7.BackColor = System.Drawing.Color.HotPink;
            this.button7.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button7.Location = new System.Drawing.Point(57, 301);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(51, 51);
            this.button7.TabIndex = 12;
            this.button7.Text = "BF2";
            this.button7.UseVisualStyleBackColor = false;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button8
            // 
            this.button8.BackColor = System.Drawing.Color.HotPink;
            this.button8.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button8.Location = new System.Drawing.Point(114, 301);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(48, 51);
            this.button8.TabIndex = 13;
            this.button8.Text = "BF3";
            this.button8.UseVisualStyleBackColor = false;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // richTextBox6
            // 
            this.richTextBox6.Location = new System.Drawing.Point(978, 85);
            this.richTextBox6.Name = "richTextBox6";
            this.richTextBox6.Size = new System.Drawing.Size(111, 39);
            this.richTextBox6.TabIndex = 14;
            this.richTextBox6.Text = "";
            // 
            // richTextBox7
            // 
            this.richTextBox7.Location = new System.Drawing.Point(1095, 85);
            this.richTextBox7.Name = "richTextBox7";
            this.richTextBox7.Size = new System.Drawing.Size(113, 39);
            this.richTextBox7.TabIndex = 15;
            this.richTextBox7.Text = "";
            // 
            // button9
            // 
            this.button9.BackColor = System.Drawing.Color.HotPink;
            this.button9.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button9.Location = new System.Drawing.Point(22, 358);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(119, 48);
            this.button9.TabIndex = 16;
            this.button9.Text = "Dijjkstra";
            this.button9.UseVisualStyleBackColor = false;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // button10
            // 
            this.button10.BackColor = System.Drawing.Color.HotPink;
            this.button10.ForeColor = System.Drawing.Color.LavenderBlush;
            this.button10.Location = new System.Drawing.Point(22, 412);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(119, 48);
            this.button10.TabIndex = 17;
            this.button10.Text = "mesh";
            this.button10.UseVisualStyleBackColor = false;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(1220, 826);
            this.Controls.Add(this.button10);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.richTextBox7);
            this.Controls.Add(this.richTextBox6);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.richTextBox5);
            this.Controls.Add(this.richTextBox4);
            this.Controls.Add(this.richTextBox3);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.richTextBox2);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.glControl1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private OpenTK.GLControl glControl1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.RichTextBox richTextBox2;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.RichTextBox richTextBox3;
        private System.Windows.Forms.RichTextBox richTextBox4;
        private System.Windows.Forms.RichTextBox richTextBox5;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.RichTextBox richTextBox6;
        private System.Windows.Forms.RichTextBox richTextBox7;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Timer timer1;
    }
}

