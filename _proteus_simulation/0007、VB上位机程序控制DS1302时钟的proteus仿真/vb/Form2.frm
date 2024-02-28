VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "说明"
   ClientHeight    =   2295
   ClientLeft      =   60
   ClientTop       =   405
   ClientWidth     =   3720
   LinkTopic       =   "Form2"
   ScaleHeight     =   2295
   ScaleWidth      =   3720
   StartUpPosition =   3  '窗口缺省
   Visible         =   0   'False
   Begin VB.TextBox Text1 
      Height          =   1455
      Left            =   240
      MultiLine       =   -1  'True
      TabIndex        =   1
      Text            =   "Form2.frx":0000
      Top             =   120
      Width           =   3135
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   375
      Left            =   1440
      TabIndex        =   0
      Top             =   1680
      Width           =   735
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Unload Me
End Sub

