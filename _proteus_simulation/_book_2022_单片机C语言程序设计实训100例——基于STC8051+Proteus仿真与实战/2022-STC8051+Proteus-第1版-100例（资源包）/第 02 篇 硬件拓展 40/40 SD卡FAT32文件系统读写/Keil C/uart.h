//-----------------------------------------------------------------
// ����: ������������ͷ�ļ�
//-----------------------------------------------------------------
void UART_Init(void);											//����1��ʼ��
void UART_Send_Str(char *s);							//�����ַ���
void UART_Send_Num(u32 dat);							//������ֵ
void Hex2Str(u16 hex,char *str);					//ʮ������ת��Ϊ�ַ���
void UART_Send_StrNum(char *inf,u32 dat);	//�����ַ���+��ֵ
void UART_Send_Hex(u16 hex);							//����16����(������Χ)
void UART_Send_binary(u8 dat);						//����2����
void UART_Send_Enter();
void UART_Send_Byte(u8 dat);