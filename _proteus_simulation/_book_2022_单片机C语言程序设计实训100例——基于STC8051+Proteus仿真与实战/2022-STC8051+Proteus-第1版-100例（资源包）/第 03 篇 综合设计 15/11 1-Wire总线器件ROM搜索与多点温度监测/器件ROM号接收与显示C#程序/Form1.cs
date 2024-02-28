using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;

namespace 器件ROM号接收与显示C程序
{
    public partial class Form_Main : Form
    {
        public Form_Main()
        {
            InitializeComponent();
        }

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
            if (button_打开串口.Text == "开始搜索")
            {
                if (serialPort1.IsOpen) serialPort1.Close();
                serialPort1.PortName = comboBox1.Text;
                try
                {
                    serialPort1.Open();
                    serialPort1.DiscardNull = true;
                    serialPort1.NewLine = "\r\n";
                    toolStripStatusLabel1.Text = "端口:" + comboBox1.Text + " 打开";
                    button_打开串口.Text = "停止搜索";
                }
                catch { toolStripStatusLabel1.Text = "端口打开错误!!!"; }
            }
            else
            {
                serialPort1.Close();
                toolStripStatusLabel1.Text = "停止搜索";
                button_打开串口.Text = "开始搜索";
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
            RegistryKey reg = Registry.LocalMachine.OpenSubKey("SOFTWARE\\器件ROM号接收与显示2012",true);
            if (reg == null) 
            {
                reg = Registry.LocalMachine.CreateSubKey("SOFTWARE\\器件ROM号接收与显示2012");
            }
            if (reg != null)
            {
                comboBox1.Text = (string)reg.GetValue("端口");
            }


            //for (int i = 0;
        }
        //--------------------------------------------------------------------
        // 关闭窗体时将当前串口选项写入注册表
        //--------------------------------------------------------------------
        private void Form_Main_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serialPort1.IsOpen) serialPort1.Close();
            RegistryKey reg = Registry.LocalMachine.OpenSubKey("SOFTWARE\\器件ROM号接收与显示2012", true);
            if (reg != null) reg.SetValue("端口", comboBox1.Text);   
        }

        //--------------------------------------------------------------------
        // 通风按钮操作
        //--------------------------------------------------------------------
        private void button_AD控制_Click(object sender, EventArgs e)
        {

        }
    

        //--------------------------------------------------------------------
        // 代理函数
        //--------------------------------------------------------------------
        public delegate void ShowCallBack(string s);
        int total = 0;
        //--------------------------------------------------------------------
        // 显示代理函数
        //--------------------------------------------------------------------
        private void Show_ROM_Device(string s)
        {

            if (s == "NEW") { listView1.Items.Clear(); total = 0;  return; }
            else if (s.Length != 16) return;
            total++;
            string device_name="", ROMCODE=s, device_State="在线";
            if (s.Substring(14, 2) == "28") device_name = "DS18B20,温度传感器";
            if (s.Substring(14, 2) == "01") device_name = "DS11990,序号器";
            if (s.Substring(14, 2) == "14") device_name = "DS2430, EEPROM";
            if (s.Substring(14, 2) == "3A") device_name  = "DS2413P,可寻址开关";

            //string[] subItem1 = { "汪兰", "财会电算化管理", "西南财经大学" };
            this.listView1.Items.Add(new ListViewItem(new string[]{device_name, ROMCODE, device_State}));
            this.label1.Text = "在线器件数: " + total.ToString();
 
        }
        //--------------------------------------------------------------------
        // 串口接收温度数据并通过代理程序显示
        //--------------------------------------------------------------------
        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            //方法1
            //try { SetText(serialPort1.ReadLine()); } catch { }
            //this.Invoke(new EventHandler(Show_Recv_Info));
            this.Invoke(new ShowCallBack(Show_ROM_Device), new object[] { serialPort1.ReadLine() });

            //方法2:
            //this.BeginInvoke(new EventHandler(Show_Recv_Info)); 

            //this.BeginInvoke(new SetTextCallBack(SetTextXXXXXX), new object[] { serialPort1.ReadExisting() });
        }

        //显示接收到的串口信息
       private void Show_Recv_Info(object sender, EventArgs e)
       {
           this.Text = e.ToString();
       }
  

    }
}
