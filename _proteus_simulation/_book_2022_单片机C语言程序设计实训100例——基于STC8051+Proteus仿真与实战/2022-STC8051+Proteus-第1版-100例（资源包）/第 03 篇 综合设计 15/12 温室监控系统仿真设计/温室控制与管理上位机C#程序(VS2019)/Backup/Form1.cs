using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;

namespace 温室控制程序
{
    public partial class Form_Main : Form
    {
        public Form_Main()
        {
            InitializeComponent();
        }

        //--------------------------------------------------------------------
        // 代理函数
        //--------------------------------------------------------------------
        delegate void SetTextCallBack(string s);
        //--------------------------------------------------------------------
        // 关闭窗体时提示确认
        //--------------------------------------------------------------------
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show("您确定要退出系统吗?", "确认", 
                MessageBoxButtons.YesNo, MessageBoxIcon.Question, 
                MessageBoxDefaultButton.Button2) == DialogResult.No)
            {
                e.Cancel = true;
            }
        }
        //--------------------------------------------------------------------
        // 获取串口列表
        //--------------------------------------------------------------------
        public void GetComList()
        {
            RegistryKey keyCom = Registry.LocalMachine.OpenSubKey("Hardware\\DeviceMap\\SerialComm");
            if (keyCom != null)
            {
                string[] sSubKeys = keyCom.GetValueNames();
                comboBox1.Items.Clear();
                foreach (string sName in sSubKeys)
                {
                    string sValue = (string)keyCom.GetValue(sName);
                    comboBox1.Items.Add(sValue);
                }
            }
        }
        //--------------------------------------------------------------------
        // 退出系统
        //--------------------------------------------------------------------
        private void button_退出_Click(object sender, EventArgs e)
        {        
            this.Close();
        }
        //--------------------------------------------------------------------
        //打开串口
        //--------------------------------------------------------------------
        private void button_打开串口_Click(object sender, EventArgs e)
        {
            if (button_打开串口.Text == "打开串口")
            {
                if (serialPort1.IsOpen) serialPort1.Close();
                serialPort1.PortName = comboBox1.Text;
                try
                {
                    serialPort1.Open();
                    toolStripStatusLabel1.Text = comboBox1.Text + " 打开";
                    button_打开串口.Text = "关闭串口";
                }
                catch { toolStripStatusLabel1.Text = "端口打开错误!!!"; }
            }
            else
            {
                serialPort1.Close();
                toolStripStatusLabel1.Text = "端口关闭";
                button_打开串口.Text = "打开串口";
            }
        }
        //--------------------------------------------------------------------
        // 加载窗体时执行
        //--------------------------------------------------------------------
        private void Form_Main_Load(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            GetComList(); 
            if (comboBox1.Items.Count != 0) comboBox1.SelectedIndex = 1;
            RegistryKey reg = Registry.LocalMachine.OpenSubKey("SOFTWARE\\温室监控系统2010",true);
            if (reg == null) 
            {
                reg = Registry.LocalMachine.CreateSubKey("SOFTWARE\\温室监控系统2010");
            }
            if (reg != null)
            {
                comboBox1.Text = (string)reg.GetValue("端口");
            }
        }
        //--------------------------------------------------------------------
        // 关闭窗体时将当前串口选项写入注册表
        //--------------------------------------------------------------------
        private void Form_Main_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serialPort1.IsOpen) serialPort1.Close();
            RegistryKey reg = Registry.LocalMachine.OpenSubKey("SOFTWARE\\温室监控系统2010",true);
            if (reg != null) reg.SetValue("端口", comboBox1.Text);   
        }
        //--------------------------------------------------------------------
        // 喷灌按钮操作
        //--------------------------------------------------------------------
        private void button_喷灌_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            { MessageBox.Show("串口未打开,控制命令无法发送!", "提示"); return; }
            if (button_喷灌.Text == "喷灌")
            {
                //发送控制指令 开启继电器
                serialPort1.WriteLine("$PUMP_OPEN");
                button_喷灌.Text = "停止喷灌";
            }
            else
            {
                //发送控制指令 关闭继电器
                serialPort1.WriteLine("$PUMP_CLOSE");
                button_喷灌.Text = "喷灌";
            }
        }
        //--------------------------------------------------------------------
        // 通风按钮操作
        //--------------------------------------------------------------------
        private void button_通风_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            { MessageBox.Show("串口未打开,控制命令无法发送!", "提示"); return; }
            if (button_通风.Text == "通风")
            {
                //发送控制指令 开启电机1
                serialPort1.WriteLine("$WIND_OPEN");
                button_通风.Text = "停止通风";
            }
            else
            {
                //发送控制指令 关闭电机1
                serialPort1.WriteLine("$WIND_CLOSE");
                button_通风.Text = "通风";
            }
        }
        //--------------------------------------------------------------------
        // 采光按钮操作
        //--------------------------------------------------------------------
        private void button_采光_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            { MessageBox.Show("串口未打开,控制命令无法发送!", "提示"); return; }
            if (button_采光.Text == "采光")
            {
                //发送控制指令 开启电机2
                serialPort1.WriteLine("$LIGHT_OPEN");
                button_采光.Text = "停止采光";
            }
            else
            {
                //发送控制指令 关闭电机2
                serialPort1.WriteLine("$LIGHT_CLOSE");
                button_采光.Text = "采光";
            }
        }
        //--------------------------------------------------------------------
        // 显示代理函数
        //--------------------------------------------------------------------
        private void SetText(string s)
        {
            if (label_温度.InvokeRequired)
            {
                SetTextCallBack d = new SetTextCallBack(SetText);
                Invoke(d, new object[] { s });
            }
            else
            {
                label_温度.Text = s.Trim() + " ℃";
                label_温度.Refresh();
            }
        }
        //--------------------------------------------------------------------
        // 串口接收温度数据并通过代理程序显示
        //--------------------------------------------------------------------
        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try { SetText(serialPort1.ReadLine()); } catch { }
        }
    }
}
