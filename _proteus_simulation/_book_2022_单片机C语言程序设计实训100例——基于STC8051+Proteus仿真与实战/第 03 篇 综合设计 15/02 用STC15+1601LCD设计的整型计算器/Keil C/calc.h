//-------------------------- calc.h -------------------------------
// calc.h ͷ�ļ�
//-----------------------------------------------------------------
#define MAX_DISPLAY_CHAR 9	//�����ʺ���Ļ��ʾ��ASCII�ַ���������
enum ERROR { OK = 0, SLEEP = 1, ERROR = 2};	// ������״̬
//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
void Operator_Process(char token);
int  calc_chkerror(long num);
void LCD_Disp_String(char buf[]);
void Initialise_LCD();
char GetKeyChar();
void Clearscreen();
