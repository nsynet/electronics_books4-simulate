using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace STC8051以太网应用客户端程序
{
  public partial class Form_Main : Form
  {
    private delegate void SetTextCallBack(string strValue); //定义回调
    private SetTextCallBack setCallBack;//声明

    //定义接收服务端发送消息的回调
    //private delegate void ReceiveMsgCallBack(string strMsg);
    private delegate void ReceiveMsgCallBack(byte[] datbuff);
    private ReceiveMsgCallBack receiveCallBack; //声明
    //创建连接的Socket
    Socket socketSend = null;
    //创建接收客户端发送消息的线程
    Thread threadReceive = null;
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
        Control.CheckForIllegalCrossThreadCalls = false;
        Environment.Exit(0);//强制关闭程序（强行终止Listener）
      }
    }
    //--------------------------------------------------------------------
    // 退出系统
    //--------------------------------------------------------------------
    private void button_退出_Click(object sender, EventArgs e)
    {
      ////MessageBox.Show("不能写入数据流", "终止", MessageBoxButtons.OK, MessageBoxIcon.Stop);
      //if (tcpClient != null) tcpClient.Close();
      //if (ns != null) ns.Close();
      this.Close();
    }
    private void Receive()
    {
      try
      {
        while (true)
        {
          byte[] buffer = new byte[2048];
          //实际接收到的字节数
          int r = socketSend.Receive(buffer);
          if (r == 0) break;
          else
          {
            //string str = Encoding.Default.GetString(buffer, 0, r);
            textBox_按键状态.Invoke(receiveCallBack, buffer);
            //statusStrip1.Invoke(receiveCallBack, "STC15地址:" + socketSend.RemoteEndPoint + " MSG:" + str);
          }
        }
      }
      catch (Exception ex)
      {
        MessageBox.Show("接收服务端发送的消息出错:" + ex.ToString());
      }
    }
    private void SetValue(string strValue)
    {
      toolStripStatusLabel1.Text = strValue;
    }
    private void ShowData(byte[] buff)
    {
      if (buff.Length < 4) return;
      textBox_按键状态.Text = "SW" + ((int)(buff[3])).ToString() + "闭合";
      Show_ADC(buff);
    }
    private void button_连接网络_Click(object sender, EventArgs e)
    {
      if (socketSend != null) { this.statusStrip1.Invoke(setCallBack, "已连接！"); return; }
      //this.statusStrip1.Invoke(setCallBack, "正在连接，请稍候...");
      try
      {
        socketSend = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        IPAddress ip = IPAddress.Parse(IP_TextBox.Text.Trim());
        socketSend.Connect(ip, Convert.ToInt32(Port_TextBox.Text.Trim()));
        //实例化回调
        setCallBack = new SetTextCallBack(SetValue);
        receiveCallBack = new ReceiveMsgCallBack(ShowData);
        this.statusStrip1.Invoke(setCallBack, "连接成功！");
        //开启一个新的线程不停的接收服务器发送消息的线程
        threadReceive = new Thread(new ThreadStart(Receive));
        //设置为后台线程
        threadReceive.IsBackground = true;
        threadReceive.Start();
      }
      catch (Exception ex)
      {
        timer1.Stop();
        MessageBox.Show("连接服务端出错:" + ex.ToString(), "提示", 
          MessageBoxButtons.OK, MessageBoxIcon.Information);
      }
    }
    private void button_LED滚动显示_Click(object sender, EventArgs e)
    {
      SendMessageToSTC8051("L1");
    }

    private void button_LED闪烁显示_Click(object sender, EventArgs e)
    {
      SendMessageToSTC8051("L2");
    }

    private void button_LED停止显示_Click(object sender, EventArgs e)
    {
      SendMessageToSTC8051("L0");
    }
    private void button_继电器闭合_Click(object sender, EventArgs e)
    {
      SendMessageToSTC8051("RO");
    }
    private void button_继电器断开_Click(object sender, EventArgs e)
    {
      SendMessageToSTC8051("RK");
    }
    private void butto_采集数据_Click(object sender, EventArgs e)
    {
      if (socketSend != null && threadReceive != null) timer1.Start();
      else timer1.Stop();
    }
    private void timer1_Tick(object sender, EventArgs e)
    {
      if (!SendMessageToSTC8051("GD")) timer1.Stop();
    }
    private void button_停止采集_Click(object sender, EventArgs e)
    {
      timer1.Stop(); SendMessageToSTC8051("GX");
    }
    private bool SendMessageToSTC8051(string msg)
    {
      if (socketSend == null || threadReceive == null) {
        MessageBox.Show("请点击连接后再发送!", "提示", MessageBoxButtons.OK, 
            MessageBoxIcon.Information);
        timer1.Stop();
        return false;
      }
      try
      {
        byte[] buffer = new byte[2048];
        buffer = Encoding.Default.GetBytes(msg);
        int receive = socketSend.Send(buffer);
      }
      catch 
      {
        MessageBox.Show("发送消息出错！请确保连接成功后再发送!", "提示", 
            MessageBoxButtons.OK, MessageBoxIcon.Error);
        if (socketSend != null) socketSend.Close();
        if (threadReceive != null) threadReceive.Abort();
        socketSend = null;
        threadReceive = null;
        return false;
      }
      return true;
    }

    private void button_断开网络_Click(object sender, EventArgs e)
    {
      if (socketSend != null) socketSend.Close();//关闭socket
      if (threadReceive != null) threadReceive.Abort();//终止线程
      socketSend = null;
      threadReceive = null;
      //this.txtRecvMssg.Invoke(setCallBack, "连接已断开！");
      this.statusStrip1.Invoke(setCallBack, "连接已断开！");
    }


    //--------------------------------------------------------------------
    // 代理函数
    //--------------------------------------------------------------------
    public delegate void ShowCallBack(string s);
    //--------------------------------------------------------------------
    // 显示代理函数
    //--------------------------------------------------------------------
    double curr_volt;
    double pre_volt;
    int x0 = 0; bool first = true; int ap;
    private void Show_ADC(byte[] buff)
    {
      x0 += 5; ap = pictureBox1.Height;
      try
      {
        //刷新数据显示
        double voltage = (double)Math.Round( (int)(buff[1]<<8 | buff[2]) / 1023.0 * 5.0, 2);
        //备份上次电压值并取得当前电压值
        pre_volt = curr_volt; curr_volt = voltage;
        //如果是首次获取则上次与本次电压值相同
        if (first) pre_volt = voltage;
        //刷新图形显示
        int y0 = (int)(ap * (1 - pre_volt / 5.0));
        int y1 = (int)(ap * (1 - curr_volt / 5.0));
        pictureBox1.CreateGraphics().DrawLine(new Pen(new SolidBrush(Color.Red), 
            (float)1.5), new Point(x0, y0), new Point(x0 + 5, y1));
      }
      catch { }
      if (first) first = false;
      //如果X已达显示区域最右边则清屏.
      if (x0 + 5 > pictureBox1.Width)
      {
        Graphics g = pictureBox1.CreateGraphics();
        g.Clear(pictureBox1.BackColor); x0 = 0;
      }
    }
  }
}