VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "监控界面"
   ClientHeight    =   6105
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   10125
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6105
   ScaleWidth      =   10125
   StartUpPosition =   3  '窗口缺省
   Begin VB.PictureBox Picture1 
      BackColor       =   &H8000000E&
      Height          =   4455
      Left            =   480
      ScaleHeight     =   4395
      ScaleWidth      =   7155
      TabIndex        =   4
      Top             =   720
      Width           =   7215
      Begin VB.Line Line17 
         BorderColor     =   &H0000FF00&
         X1              =   0
         X2              =   7080
         Y1              =   0
         Y2              =   0
      End
      Begin VB.Line Line16 
         BorderColor     =   &H0000FF00&
         X1              =   0
         X2              =   7095
         Y1              =   864
         Y2              =   879
      End
      Begin VB.Line Line15 
         BorderColor     =   &H0000FF00&
         X1              =   0
         X2              =   7095
         Y1              =   1728
         Y2              =   1743
      End
      Begin VB.Line Line14 
         BorderColor     =   &H0000FF00&
         X1              =   0
         X2              =   7095
         Y1              =   2592
         Y2              =   2607
      End
      Begin VB.Line Line13 
         BorderColor     =   &H0000FF00&
         X1              =   0
         X2              =   7095
         Y1              =   3456
         Y2              =   3471
      End
      Begin VB.Line Line12 
         BorderColor     =   &H0000FF00&
         X1              =   0
         X2              =   7080
         Y1              =   4320
         Y2              =   4320
      End
      Begin VB.Line Line11 
         BorderColor     =   &H0000FF00&
         X1              =   5664
         X2              =   5679
         Y1              =   0
         Y2              =   4455
      End
      Begin VB.Line Line10 
         BorderColor     =   &H0000FF00&
         X1              =   4248
         X2              =   4263
         Y1              =   0
         Y2              =   4455
      End
      Begin VB.Line Line9 
         BorderColor     =   &H0000FF00&
         X1              =   2832
         X2              =   2847
         Y1              =   0
         Y2              =   4455
      End
      Begin VB.Line Line8 
         BorderColor     =   &H0000FF00&
         X1              =   1416
         X2              =   1431
         Y1              =   0
         Y2              =   4455
      End
      Begin VB.Line Line7 
         BorderColor     =   &H0000FF00&
         X1              =   7080
         X2              =   7080
         Y1              =   0
         Y2              =   4440
      End
      Begin VB.Line Line6 
         BorderColor     =   &H0000FF00&
         X1              =   6372
         X2              =   6387
         Y1              =   0
         Y2              =   4455
      End
      Begin VB.Line Line5 
         BorderColor     =   &H0000FF00&
         X1              =   4956
         X2              =   4971
         Y1              =   0
         Y2              =   4455
      End
      Begin VB.Line Line4 
         BorderColor     =   &H0000FF00&
         X1              =   3540
         X2              =   3555
         Y1              =   0
         Y2              =   4455
      End
      Begin VB.Line Line3 
         BorderColor     =   &H0000FF00&
         X1              =   2124
         X2              =   2139
         Y1              =   4455
         Y2              =   0
      End
      Begin VB.Line Line2 
         BorderColor     =   &H0000FF00&
         X1              =   708
         X2              =   723
         Y1              =   4455
         Y2              =   0
      End
      Begin VB.Line Line1 
         BorderColor     =   &H0000FF00&
         X1              =   0
         X2              =   0
         Y1              =   0
         Y2              =   4440
      End
   End
   Begin VB.Timer Timer1 
      Interval        =   20
      Left            =   9360
      Top             =   960
   End
   Begin VB.CommandButton Command2 
      Caption         =   "退出"
      Height          =   375
      Left            =   8400
      TabIndex        =   2
      Top             =   4680
      Width           =   1455
   End
   Begin VB.TextBox Text2 
      Height          =   270
      Left            =   9120
      TabIndex        =   0
      Top             =   3000
      Width           =   615
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   9240
      Top             =   120
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Label Label20 
      Caption         =   "0"
      Height          =   255
      Left            =   240
      TabIndex        =   22
      Top             =   4920
      Width           =   255
   End
   Begin VB.Label Label19 
      Caption         =   "1"
      Height          =   255
      Left            =   240
      TabIndex        =   21
      Top             =   4080
      Width           =   255
   End
   Begin VB.Label Label18 
      Caption         =   "2"
      Height          =   255
      Left            =   240
      TabIndex        =   20
      Top             =   3240
      Width           =   255
   End
   Begin VB.Label Label17 
      Caption         =   "3"
      Height          =   255
      Left            =   240
      TabIndex        =   19
      Top             =   2400
      Width           =   255
   End
   Begin VB.Label Label16 
      Caption         =   "4"
      Height          =   255
      Left            =   240
      TabIndex        =   18
      Top             =   1440
      Width           =   255
   End
   Begin VB.Label Label15 
      Caption         =   "5V"
      Height          =   255
      Left            =   240
      TabIndex        =   17
      Top             =   600
      Width           =   255
   End
   Begin VB.Label Label14 
      Caption         =   "1.0S"
      Height          =   255
      Left            =   7440
      TabIndex        =   16
      Top             =   5160
      Width           =   615
   End
   Begin VB.Label Label13 
      Caption         =   "0.9"
      Height          =   255
      Left            =   6840
      TabIndex        =   15
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label12 
      Caption         =   "0.8"
      Height          =   255
      Left            =   6120
      TabIndex        =   14
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label11 
      Caption         =   "0.7"
      Height          =   255
      Left            =   5400
      TabIndex        =   13
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label10 
      Caption         =   "0.6"
      Height          =   255
      Left            =   4680
      TabIndex        =   12
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label9 
      Caption         =   "0.5"
      Height          =   255
      Left            =   3960
      TabIndex        =   11
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label8 
      Caption         =   "0.4"
      Height          =   255
      Left            =   3240
      TabIndex        =   10
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label7 
      Caption         =   "0.3"
      Height          =   255
      Left            =   2520
      TabIndex        =   9
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label6 
      Caption         =   "0.2S"
      Height          =   255
      Left            =   1800
      TabIndex        =   8
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label5 
      Caption         =   "0.1"
      Height          =   255
      Left            =   1080
      TabIndex        =   7
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label4 
      Caption         =   "0"
      Height          =   255
      Left            =   480
      TabIndex        =   6
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label3 
      Caption         =   "趋势曲线（每秒更新一次）"
      Height          =   255
      Left            =   480
      TabIndex        =   5
      Top             =   360
      Width           =   2535
   End
   Begin VB.Label Label1 
      Caption         =   "V"
      Height          =   255
      Left            =   9840
      TabIndex        =   3
      Top             =   3000
      Width           =   135
   End
   Begin VB.Label Label2 
      Caption         =   "当前电压值："
      Height          =   255
      Left            =   8040
      TabIndex        =   1
      Top             =   3000
      Width           =   1095
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public i As Integer
Private pdate(50) As Variant



Private Sub Command2_Click()
Unload Me
End Sub

Private Sub Form_Load()
MSComm1.CommPort = 4 'COM4
MSComm1.Settings = "1200,n,8,1" '1200BSP，无校验位，8个数据位，1个停止位
MSComm1.PortOpen = True '打开串口
MSComm1.InputMode = comInputModeBinary '以2进制形式接收数据
MSComm1.RThreshold = 1 '1个字符引发事件
i = 0
Picture1.Scale (0, 6)-(50, 0)
End Sub

Private Sub MSComm1_OnComm()
Dim indata As Variant
Dim bte(0) As Byte

Select Case MSComm1.CommEvent '通讯事件发生
Case comEvReceive
indata = MSComm1.Input
bte(0) = AscB(indata) '读入数据
test = bte(0) / 255 * 5 '测量值/255*实际量程
ptest = Round(test, 3) '小数点后3位四舍五入
Text2.Text = ptest
pdate(i) = ptest
MSComm1.InBufferCount = 0 '接收缓冲区清空

If i < 50 Then
   i = i + 1
   Exit Sub
Else
Picture1.Cls
   i = 0
   Do Until i > 50
   If i = 0 Then
      Picture1.PSet (i, pdate(i))
   Else
      Picture1.Line -(i, pdate(i))
      End If
      i = i + 1
      Loop
   i = 0
End If



End Select
End Sub

Private Sub Timer1_Timer()
Dim num As Integer
Dim outbte(0) As Byte

outbte(0) = CByte(1) '发送01查询单片机
MSComm1.OutBufferCount = 0 '发送缓冲区清空
MSComm1.Output = outbte() '动态数组

End Sub
