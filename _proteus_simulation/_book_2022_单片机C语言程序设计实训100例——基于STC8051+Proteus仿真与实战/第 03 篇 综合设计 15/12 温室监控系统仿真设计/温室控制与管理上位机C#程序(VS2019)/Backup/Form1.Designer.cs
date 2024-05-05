namespace 温室控制程序
{
    partial class Form_Main
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_Main));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label_温度 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button_通风 = new System.Windows.Forms.Button();
            this.button_喷灌 = new System.Windows.Forms.Button();
            this.button_采光 = new System.Windows.Forms.Button();
            this.button_退出 = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.button_打开串口 = new System.Windows.Forms.Button();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.groupBox1.BackColor = System.Drawing.Color.Transparent;
            this.groupBox1.Controls.Add(this.label_温度);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.ForeColor = System.Drawing.Color.Black;
            this.groupBox1.Location = new System.Drawing.Point(12, 25);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(393, 88);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "温室温度监测";
            // 
            // label_温度
            // 
            this.label_温度.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label_温度.Font = new System.Drawing.Font("Arial Black", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_温度.ForeColor = System.Drawing.Color.Red;
            this.label_温度.Location = new System.Drawing.Point(89, 25);
            this.label_温度.Name = "label_温度";
            this.label_温度.Size = new System.Drawing.Size(259, 47);
            this.label_温度.TabIndex = 1;
            this.label_温度.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(16, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(76, 21);
            this.label1.TabIndex = 0;
            this.label1.Text = "温度：";
            // 
            // button_通风
            // 
            this.button_通风.Location = new System.Drawing.Point(12, 137);
            this.button_通风.Name = "button_通风";
            this.button_通风.Size = new System.Drawing.Size(92, 44);
            this.button_通风.TabIndex = 1;
            this.button_通风.Text = "通风";
            this.button_通风.UseVisualStyleBackColor = true;
            this.button_通风.Click += new System.EventHandler(this.button_通风_Click);
            // 
            // button_喷灌
            // 
            this.button_喷灌.Location = new System.Drawing.Point(230, 137);
            this.button_喷灌.Name = "button_喷灌";
            this.button_喷灌.Size = new System.Drawing.Size(175, 44);
            this.button_喷灌.TabIndex = 3;
            this.button_喷灌.Text = "喷灌";
            this.button_喷灌.UseVisualStyleBackColor = true;
            this.button_喷灌.Click += new System.EventHandler(this.button_喷灌_Click);
            // 
            // button_采光
            // 
            this.button_采光.Location = new System.Drawing.Point(110, 137);
            this.button_采光.Name = "button_采光";
            this.button_采光.Size = new System.Drawing.Size(94, 44);
            this.button_采光.TabIndex = 2;
            this.button_采光.Text = "采光";
            this.button_采光.UseVisualStyleBackColor = true;
            this.button_采光.Click += new System.EventHandler(this.button_采光_Click);
            // 
            // button_退出
            // 
            this.button_退出.Location = new System.Drawing.Point(453, 34);
            this.button_退出.Name = "button_退出";
            this.button_退出.Size = new System.Drawing.Size(137, 79);
            this.button_退出.TabIndex = 3;
            this.button_退出.Tag = "6";
            this.button_退出.Text = "退出系统";
            this.button_退出.UseVisualStyleBackColor = true;
            this.button_退出.Click += new System.EventHandler(this.button_退出_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4"});
            this.comboBox1.Location = new System.Drawing.Point(453, 137);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(65, 20);
            this.comboBox1.Sorted = true;
            this.comboBox1.TabIndex = 4;
            this.comboBox1.Tag = "4";
            // 
            // button_打开串口
            // 
            this.button_打开串口.Location = new System.Drawing.Point(525, 137);
            this.button_打开串口.Name = "button_打开串口";
            this.button_打开串口.Size = new System.Drawing.Size(65, 23);
            this.button_打开串口.TabIndex = 5;
            this.button_打开串口.Tag = "5";
            this.button_打开串口.Text = "打开串口";
            this.button_打开串口.UseVisualStyleBackColor = true;
            this.button_打开串口.Click += new System.EventHandler(this.button_打开串口_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel2,
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 217);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(625, 22);
            this.statusStrip1.TabIndex = 6;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(479, 17);
            this.toolStripStatusLabel2.Text = "[单片机C语言程序设计实训100例---基于8051+PROTEUS仿真(第2版)] 电子工业出版社出版";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripStatusLabel1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold);
            this.toolStripStatusLabel1.ForeColor = System.Drawing.Color.Red;
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(159, 17);
            this.toolStripStatusLabel1.Text = "                      ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 199);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(383, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "开发环境:Microsoft Visual C# 2008, 运行环境: .Net Framework 2.0";
            // 
            // Form_Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(625, 239);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.button_通风);
            this.Controls.Add(this.button_打开串口);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.button_退出);
            this.Controls.Add(this.button_采光);
            this.Controls.Add(this.button_喷灌);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form_Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "温室管理与控制程序[简易版] V1.0 (E-mail:pw95aaa@foxmail.com)";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.Form_Main_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form_Main_FormClosed);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label_温度;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_通风;
        private System.Windows.Forms.Button button_采光;
        private System.Windows.Forms.Button button_喷灌;
        private System.Windows.Forms.Button button_退出;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button button_打开串口;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.Label label2;
    }
}

