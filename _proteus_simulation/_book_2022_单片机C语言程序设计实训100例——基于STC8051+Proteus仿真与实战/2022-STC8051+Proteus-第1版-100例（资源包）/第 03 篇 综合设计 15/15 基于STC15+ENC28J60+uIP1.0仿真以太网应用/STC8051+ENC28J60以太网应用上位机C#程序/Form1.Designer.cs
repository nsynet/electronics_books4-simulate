namespace STC8051以太网应用客户端程序
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
			this.button_LED滚动显示 = new System.Windows.Forms.Button();
			this.button_继电器闭合 = new System.Windows.Forms.Button();
			this.button_LED闪烁显示 = new System.Windows.Forms.Button();
			this.button_退出 = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.textBox_按键状态 = new System.Windows.Forms.TextBox();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.IP_TextBox = new System.Windows.Forms.TextBox();
			this.Port_TextBox = new System.Windows.Forms.TextBox();
			this.button_连接网络 = new System.Windows.Forms.Button();
			this.button_LED停止显示 = new System.Windows.Forms.Button();
			this.button_继电器断开 = new System.Windows.Forms.Button();
			this.button_断开网络 = new System.Windows.Forms.Button();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
			this.label1 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.butto_采集数据 = new System.Windows.Forms.Button();
			this.button_停止采集 = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.statusStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// button_LED滚动显示
			// 
			this.button_LED滚动显示.BackColor = System.Drawing.SystemColors.Control;
			this.button_LED滚动显示.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_LED滚动显示.Location = new System.Drawing.Point(563, 24);
			this.button_LED滚动显示.Name = "button_LED滚动显示";
			this.button_LED滚动显示.Size = new System.Drawing.Size(106, 30);
			this.button_LED滚动显示.TabIndex = 1;
			this.button_LED滚动显示.Text = "LED滚动显示";
			this.button_LED滚动显示.UseVisualStyleBackColor = false;
			this.button_LED滚动显示.Click += new System.EventHandler(this.button_LED滚动显示_Click);
			// 
			// button_继电器闭合
			// 
			this.button_继电器闭合.BackColor = System.Drawing.SystemColors.Control;
			this.button_继电器闭合.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_继电器闭合.Location = new System.Drawing.Point(432, 116);
			this.button_继电器闭合.Name = "button_继电器闭合";
			this.button_继电器闭合.Size = new System.Drawing.Size(108, 30);
			this.button_继电器闭合.TabIndex = 3;
			this.button_继电器闭合.Text = "继电器闭合";
			this.button_继电器闭合.UseVisualStyleBackColor = false;
			this.button_继电器闭合.Click += new System.EventHandler(this.button_继电器闭合_Click);
			// 
			// button_LED闪烁显示
			// 
			this.button_LED闪烁显示.BackColor = System.Drawing.SystemColors.Control;
			this.button_LED闪烁显示.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_LED闪烁显示.Location = new System.Drawing.Point(563, 60);
			this.button_LED闪烁显示.Name = "button_LED闪烁显示";
			this.button_LED闪烁显示.Size = new System.Drawing.Size(106, 30);
			this.button_LED闪烁显示.TabIndex = 2;
			this.button_LED闪烁显示.Text = "LED闪烁显示";
			this.button_LED闪烁显示.UseVisualStyleBackColor = false;
			this.button_LED闪烁显示.Click += new System.EventHandler(this.button_LED闪烁显示_Click);
			// 
			// button_退出
			// 
			this.button_退出.BackColor = System.Drawing.SystemColors.Control;
			this.button_退出.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_退出.Location = new System.Drawing.Point(432, 199);
			this.button_退出.Name = "button_退出";
			this.button_退出.Size = new System.Drawing.Size(237, 63);
			this.button_退出.TabIndex = 3;
			this.button_退出.Tag = "6";
			this.button_退出.Text = "退出系统";
			this.button_退出.UseVisualStyleBackColor = false;
			this.button_退出.Click += new System.EventHandler(this.button_退出_Click);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(14, 256);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(407, 12);
			this.label2.TabIndex = 7;
			this.label2.Text = "开发环境: Microsoft Visual C# 2019 运行环境: .Net Framework 4.5以上";
			// 
			// groupBox1
			// 
			this.groupBox1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.groupBox1.BackColor = System.Drawing.Color.Transparent;
			this.groupBox1.Controls.Add(this.textBox_按键状态);
			this.groupBox1.Controls.Add(this.pictureBox1);
			this.groupBox1.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.groupBox1.ForeColor = System.Drawing.Color.Black;
			this.groupBox1.Location = new System.Drawing.Point(13, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(403, 169);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "数据采集与显示(STC8051随机发送)：";
			// 
			// textBox_按键状态
			// 
			this.textBox_按键状态.ForeColor = System.Drawing.SystemColors.MenuHighlight;
			this.textBox_按键状态.Location = new System.Drawing.Point(306, 140);
			this.textBox_按键状态.Name = "textBox_按键状态";
			this.textBox_按键状态.ReadOnly = true;
			this.textBox_按键状态.Size = new System.Drawing.Size(91, 23);
			this.textBox_按键状态.TabIndex = 8;
			this.textBox_按键状态.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// pictureBox1
			// 
			this.pictureBox1.BackColor = System.Drawing.Color.Black;
			this.pictureBox1.Location = new System.Drawing.Point(7, 22);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(390, 142);
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			// 
			// IP_TextBox
			// 
			this.IP_TextBox.Location = new System.Drawing.Point(84, 199);
			this.IP_TextBox.Name = "IP_TextBox";
			this.IP_TextBox.Size = new System.Drawing.Size(91, 21);
			this.IP_TextBox.TabIndex = 8;
			this.IP_TextBox.Text = "192.168.0.230";
			// 
			// Port_TextBox
			// 
			this.Port_TextBox.Location = new System.Drawing.Point(84, 226);
			this.Port_TextBox.Name = "Port_TextBox";
			this.Port_TextBox.Size = new System.Drawing.Size(91, 21);
			this.Port_TextBox.TabIndex = 8;
			this.Port_TextBox.Text = "4001";
			// 
			// button_连接网络
			// 
			this.button_连接网络.BackColor = System.Drawing.SystemColors.Control;
			this.button_连接网络.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_连接网络.ForeColor = System.Drawing.Color.Black;
			this.button_连接网络.Location = new System.Drawing.Point(181, 212);
			this.button_连接网络.Name = "button_连接网络";
			this.button_连接网络.Size = new System.Drawing.Size(91, 29);
			this.button_连接网络.TabIndex = 3;
			this.button_连接网络.Tag = "6";
			this.button_连接网络.Text = "连接STC8051";
			this.button_连接网络.UseVisualStyleBackColor = false;
			this.button_连接网络.Click += new System.EventHandler(this.button_连接网络_Click);
			// 
			// button_LED停止显示
			// 
			this.button_LED停止显示.BackColor = System.Drawing.SystemColors.Control;
			this.button_LED停止显示.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_LED停止显示.Location = new System.Drawing.Point(563, 96);
			this.button_LED停止显示.Name = "button_LED停止显示";
			this.button_LED停止显示.Size = new System.Drawing.Size(106, 30);
			this.button_LED停止显示.TabIndex = 2;
			this.button_LED停止显示.Text = "LED停止显示";
			this.button_LED停止显示.UseVisualStyleBackColor = false;
			this.button_LED停止显示.Click += new System.EventHandler(this.button_LED停止显示_Click);
			// 
			// button_继电器断开
			// 
			this.button_继电器断开.BackColor = System.Drawing.SystemColors.Control;
			this.button_继电器断开.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_继电器断开.Location = new System.Drawing.Point(432, 152);
			this.button_继电器断开.Name = "button_继电器断开";
			this.button_继电器断开.Size = new System.Drawing.Size(108, 30);
			this.button_继电器断开.TabIndex = 3;
			this.button_继电器断开.Text = "继电器断开";
			this.button_继电器断开.UseVisualStyleBackColor = false;
			this.button_继电器断开.Click += new System.EventHandler(this.button_继电器断开_Click);
			// 
			// button_断开网络
			// 
			this.button_断开网络.BackColor = System.Drawing.SystemColors.Control;
			this.button_断开网络.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_断开网络.ForeColor = System.Drawing.Color.Black;
			this.button_断开网络.Location = new System.Drawing.Point(278, 212);
			this.button_断开网络.Name = "button_断开网络";
			this.button_断开网络.Size = new System.Drawing.Size(91, 29);
			this.button_断开网络.TabIndex = 3;
			this.button_断开网络.Tag = "6";
			this.button_断开网络.Text = "断开连接";
			this.button_断开网络.UseVisualStyleBackColor = false;
			this.button_断开网络.Click += new System.EventHandler(this.button_断开网络_Click);
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
			this.statusStrip1.Location = new System.Drawing.Point(0, 274);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(684, 22);
			this.statusStrip1.TabIndex = 16;
			// 
			// toolStripStatusLabel1
			// 
			this.toolStripStatusLabel1.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Bold);
			this.toolStripStatusLabel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
			this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
			this.toolStripStatusLabel1.Padding = new System.Windows.Forms.Padding(6, 0, 0, 0);
			this.toolStripStatusLabel1.Size = new System.Drawing.Size(6, 17);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(11, 202);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(71, 12);
			this.label1.TabIndex = 17;
			this.label1.Text = "STC主机IP：";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(18, 229);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(65, 12);
			this.label3.TabIndex = 17;
			this.label3.Text = "主机端口：";
			// 
			// timer1
			// 
			this.timer1.Interval = 1000;
			this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
			// 
			// butto_采集数据
			// 
			this.butto_采集数据.BackColor = System.Drawing.SystemColors.Control;
			this.butto_采集数据.Cursor = System.Windows.Forms.Cursors.Hand;
			this.butto_采集数据.Location = new System.Drawing.Point(432, 24);
			this.butto_采集数据.Name = "butto_采集数据";
			this.butto_采集数据.Size = new System.Drawing.Size(108, 30);
			this.butto_采集数据.TabIndex = 3;
			this.butto_采集数据.Text = "采集数据";
			this.butto_采集数据.UseVisualStyleBackColor = false;
			this.butto_采集数据.Click += new System.EventHandler(this.butto_采集数据_Click);
			// 
			// button_停止采集
			// 
			this.button_停止采集.BackColor = System.Drawing.SystemColors.Control;
			this.button_停止采集.Cursor = System.Windows.Forms.Cursors.Hand;
			this.button_停止采集.Location = new System.Drawing.Point(432, 56);
			this.button_停止采集.Name = "button_停止采集";
			this.button_停止采集.Size = new System.Drawing.Size(108, 30);
			this.button_停止采集.TabIndex = 3;
			this.button_停止采集.Text = "停止采集";
			this.button_停止采集.UseVisualStyleBackColor = false;
			this.button_停止采集.Click += new System.EventHandler(this.button_停止采集_Click);
			// 
			// Form_Main
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(684, 296);
			this.Controls.Add(this.IP_TextBox);
			this.Controls.Add(this.Port_TextBox);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.statusStrip1);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.button_LED滚动显示);
			this.Controls.Add(this.button_断开网络);
			this.Controls.Add(this.button_连接网络);
			this.Controls.Add(this.button_退出);
			this.Controls.Add(this.button_LED停止显示);
			this.Controls.Add(this.button_LED闪烁显示);
			this.Controls.Add(this.button_停止采集);
			this.Controls.Add(this.butto_采集数据);
			this.Controls.Add(this.button_继电器断开);
			this.Controls.Add(this.button_继电器闭合);
			this.Controls.Add(this.groupBox1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "Form_Main";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "STC8051以太网应用客户端程序 [简易版] V1.0 （pw95aaa@foxmail.com)";
			this.TopMost = true;
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion
		private System.Windows.Forms.Button button_LED滚动显示;
		private System.Windows.Forms.Button button_LED闪烁显示;
		private System.Windows.Forms.Button button_继电器闭合;
		private System.Windows.Forms.Button button_退出;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.TextBox IP_TextBox;
		private System.Windows.Forms.TextBox Port_TextBox;
		private System.Windows.Forms.Button button_连接网络;
		private System.Windows.Forms.Button button_LED停止显示;
		private System.Windows.Forms.Button button_继电器断开;
		private System.Windows.Forms.Button button_断开网络;
		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.Button butto_采集数据;
		private System.Windows.Forms.Button button_停止采集;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.TextBox textBox_按键状态;
	}
}

