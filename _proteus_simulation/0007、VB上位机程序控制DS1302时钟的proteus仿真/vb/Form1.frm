VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "日期、时间设置"
   ClientHeight    =   3060
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   3645
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   3060
   ScaleWidth      =   3645
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command3 
      Caption         =   "说明"
      Height          =   375
      Left            =   1440
      TabIndex        =   15
      Top             =   2400
      Width           =   735
   End
   Begin VB.TextBox sdate 
      Height          =   375
      Left            =   2280
      TabIndex        =   8
      Text            =   "00"
      Top             =   480
      Width           =   375
   End
   Begin VB.TextBox smonth 
      Height          =   375
      Left            =   1440
      TabIndex        =   7
      Text            =   "00"
      Top             =   480
      Width           =   375
   End
   Begin VB.TextBox shour 
      Height          =   375
      Left            =   600
      TabIndex        =   6
      Text            =   "00"
      Top             =   1320
      Width           =   375
   End
   Begin VB.TextBox smin 
      Height          =   375
      Left            =   1440
      TabIndex        =   5
      Text            =   "00"
      Top             =   1320
      Width           =   375
   End
   Begin VB.TextBox ssec 
      Height          =   375
      Left            =   2280
      TabIndex        =   4
      Text            =   "00"
      Top             =   1320
      Width           =   375
   End
   Begin VB.TextBox syear 
      Height          =   375
      Left            =   600
      TabIndex        =   3
      Text            =   "00"
      Top             =   480
      Width           =   375
   End
   Begin VB.Frame Frame1 
      Height          =   1935
      Left            =   360
      TabIndex        =   2
      Top             =   120
      Width           =   2895
      Begin VB.Label Label6 
         Caption         =   "秒"
         Height          =   375
         Left            =   2400
         TabIndex        =   14
         Top             =   1320
         Width           =   375
      End
      Begin VB.Label Label5 
         Caption         =   "分"
         Height          =   375
         Left            =   1560
         TabIndex        =   13
         Top             =   1320
         Width           =   375
      End
      Begin VB.Label Label4 
         Caption         =   "时"
         Height          =   375
         Left            =   720
         TabIndex        =   12
         Top             =   1320
         Width           =   375
      End
      Begin VB.Label Label3 
         Caption         =   "日"
         Height          =   375
         Left            =   2400
         TabIndex        =   11
         Top             =   480
         Width           =   375
      End
      Begin VB.Label Label2 
         Caption         =   "月"
         Height          =   375
         Left            =   1560
         TabIndex        =   10
         Top             =   480
         Width           =   375
      End
      Begin VB.Label Label1 
         Caption         =   "年"
         Height          =   375
         Left            =   720
         TabIndex        =   9
         Top             =   480
         Width           =   375
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "退出"
      Height          =   375
      Left            =   2520
      TabIndex        =   1
      Top             =   2400
      Width           =   735
   End
   Begin VB.CommandButton Command1 
      Caption         =   "设置"
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   2400
      Width           =   735
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   3000
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
Dim i As Integer
Dim sentnum(0 To 6) As Integer
Dim outbte(0 To 6) As Byte
sentnum(0) = Val(ssec.Text)
sentnum(1) = Val(smin.Text)
sentnum(2) = Val(shour.Text)
sentnum(3) = Val(sdate.Text)
sentnum(4) = Val(smonth.Text)
sentnum(5) = Val(syear.Text)
sentnum(6) = Val(syear.Text)

outbte(0) = CByte(sentnum(0))
outbte(1) = CByte(sentnum(1))
outbte(2) = CByte(sentnum(2))
outbte(3) = CByte(sentnum(3))
outbte(4) = CByte(sentnum(4))
outbte(5) = CByte(sentnum(5))
outbte(6) = CByte(sentnum(6))
MSComm1.OutBufferCount = 0 '发送缓冲区清空
MSComm1.Output = outbte() '动态数组

End Sub

Private Sub Command2_Click()
Unload Me
End Sub

Private Sub Command3_Click()
Form2.Visible = True
End Sub

Private Sub Form_Load()
MSComm1.CommPort = 4 'COM1
MSComm1.Settings = "1200,n,8,1" '1200BSP，无校验位，8个数据位，1个停止位
MSComm1.OutBufferSize = 7
MSComm1.PortOpen = True '打开串口
MSComm1.InputMode = comInputModeBinary '以2进制形式接收数据
MSComm1.RThreshold = 1 '1个字符引发事件
End Sub


