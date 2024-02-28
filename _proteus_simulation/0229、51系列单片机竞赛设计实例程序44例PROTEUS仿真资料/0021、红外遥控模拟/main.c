#include <AT89X51.h> 

static bit OP;        //���ⷢ��ܵ�����
static unsigned int count;       //��ʱ������
static unsigned int endcount; //��ֹ��ʱ����
static unsigned char Flag;      //���ⷢ�ͱ�־
char iraddr1;  //ʮ��λ��ַ�ĵ�һ���ֽ�
char iraddr2;  //ʮ��λ��ַ�ĵڶ����ֽ�

void SendIRdata(char p_irdata);
void delay();
char getkey()
{
	  P1=0xfe;P3_6=P3_7=1;P3_3=1;
	  if(!P1_4)return 1;   //ON
	  if(!P1_5)return 2;   //7
	  if(!P1_6)return 3;   //8
	  if(!P1_7)return 4;   //9
	  if(!P3_6)return 5;   //X
	  if(!P3_7)return 6;   //��
	  P1=0xfd;
	  if(!P1_4)return 11; //+-
	  if(!P1_5)return 12; //4
	  if(!P1_6)return 13; //5
	  if(!P1_7)return 14; //6
	  if(!P3_6)return 15; //-
	  if(!P3_7)return 16; //MRC
	  P1=0xfb;
	  if(!P1_4)return 21; //%
	  if(!P1_5)return 22; //1
	  if(!P1_6)return 23; //2
	  if(!P1_7)return 24; //3
	  if(!P3_6)return 25; //+
	  if(!P3_7)return 26; //M-
	  P1=0xf7;
	  if(!P1_4)return 31; //��
	  if(!P1_5)return 32; //0
	  if(!P1_6)return 33; //.
	  if(!P1_7)return 34; //=
	  if(!P3_6)return 35; //+
	  if(!P3_7)return 36; //M+

	  P1=0xfF;P3_3=0;
	  if(!P1_4)return 41; //
	  if(!P1_5)return 42; //
	  if(!P1_6)return 43; //
	  if(!P1_7)return 44; //
	  if(!P3_6)return 45; //
	  if(!P3_7)return 46; //
	  return 0;
}

void main(void) 
{
  char key;
  count = 0;
  Flag = 0;
  OP = 0;
  P3_4 = 1;
  EA = 1; //����CPU�ж� 
  TMOD = 0x11; //�趨ʱ��0��1Ϊ16λģʽ1 
  ET0 = 1; //��ʱ��0�ж����� 

  P1=0xff;
  TH0 = 0xFF; 
  TL0 = 0xE6; //�趨ʱֵ0Ϊ38K Ҳ����ÿ��26us�ж�һ��  
  TR0 = 1;//��ʼ����

  iraddr1=0xff;
  iraddr2=0xff;


  do{
	  key=getkey();
      if(key==1)SendIRdata(0x12);//set
      if(key==11)SendIRdata(0x0b);//exit
      if(key==25||key==35)SendIRdata(0x1a);//+
      if(key==15)SendIRdata(0x1e);//-
      if(key==6)SendIRdata(0x0e);//�� ��
      if(key==16)SendIRdata(0x1d);//�� MRC

      if(key==26)SendIRdata(0x1f);//�� M-
      if(key==36)SendIRdata(0x1b);//�� M+
      if(key==32)SendIRdata(0x00);//0
      if(key==22)SendIRdata(0x01);//1
      if(key==23)SendIRdata(0x02);//2

      if(key==24)SendIRdata(0x03);//3
      if(key==12)SendIRdata(0x04);//4
      if(key==13)SendIRdata(0x05);//5
      if(key==14)SendIRdata(0x06);//6
      if(key==2)SendIRdata(0x07);//7
      if(key==3)SendIRdata(0x08);//8

      if(key==4)SendIRdata(0x09);//9
      if(key==21)SendIRdata(0x2A);//%
      if(key==5)SendIRdata(0x2B);//X
      if(key==33)SendIRdata(0x2C);//.
      if(key==34)SendIRdata(0x2D);//=
      if(key==31)SendIRdata(0x2E);//��

      if(key==41)SendIRdata(0x2F);//
      if(key==42)SendIRdata(0x30);//
      if(key==43)SendIRdata(0x31);//
      if(key==44)SendIRdata(0x32);//
      if(key==45)SendIRdata(0x33);//
      if(key==46)SendIRdata(0x34);//
  }while(1);
} 
//��ʱ��0�жϴ��� 
void timeint(void) interrupt 1 
{ 
  TH0=0xFF; 
  TL0=0xE6; //�趨ʱֵΪ38K Ҳ����ÿ��26us�ж�һ��
  count++;

} 


void SendIRdata(char p_irdata)
{
  int i;
  char irdata=p_irdata;

  //����9ms����ʼ��
  endcount=223;
  Flag=1;
  count=0;
  P3_4=0;
  do{}while(count<endcount);

  //����4.5ms�Ľ����
  endcount=117;
  Flag=0;
  count=0;
  P3_4=1;
  do{}while(count<endcount);

  //����ʮ��λ��ַ��ǰ��λ
  irdata=iraddr1;
  for(i=0;i<8;i++)
  {

     //�ȷ���0.56ms��38KHZ���Ⲩ����������0.56ms�ĵ͵�ƽ��
     endcount=10;
     Flag=1;
     count=0;
	 P3_4=0;
     do{}while(count<endcount);

    //ֹͣ���ͺ����źţ��������еĸߵ�ƽ��
     if(irdata-(irdata/2)*2)  //�ж϶���������λΪ1����0
     {
       endcount=15;  //1Ϊ��ĸߵ�ƽ
     }
    else
     {
     endcount=41;   //0Ϊխ�ĸߵ�ƽ
     }
    Flag=0;
    count=0;
	P3_4=1;
    do{}while(count<endcount);

    irdata=irdata>>1;
  }

  //����ʮ��λ��ַ�ĺ��λ
  irdata=iraddr2;
  for(i=0;i<8;i++)
  {
     endcount=10;
     Flag=1;
     count=0;
	 P3_4=0;
     do{}while(count<endcount);

     if(irdata-(irdata/2)*2)
     {
        endcount=15;
     }
     else
     {
       endcount=41;
     }
     Flag=0;
     count=0;
	 P3_4=1;
     do{}while(count<endcount);

     irdata=irdata>>1;
  }

  //���Ͱ�λ����
  irdata=~p_irdata;
  for(i=0;i<8;i++)
  {
     endcount=10;
     Flag=1;
     count=0;
	 P3_4=0;
     do{}while(count<endcount);

     if(irdata-(irdata/2)*2)
     {
         endcount=15;
     }
     else
     {
       endcount=41;
     }
     Flag=0;
     count=0;
	 P3_4=1;
     do{}while(count<endcount);

     irdata=irdata>>1;
  }

  //���Ͱ�λ���ݵķ���
  irdata=p_irdata;
  for(i=0;i<8;i++)
  {
     endcount=10;
     Flag=1;
     count=0;
	 P3_4=0;
     do{}while(count<endcount);

     if(irdata-(irdata/2)*2)
     {
         endcount=15;
     }
     else
     {
       endcount=41;
     }
     Flag=0;
     count=0;
	 P3_4=1;
     do{}while(count<endcount);

     irdata=irdata>>1;
  }

  endcount=10;
  Flag=1;
  count=0;
  P3_4=0;
 do{}while(count<endcount);
  P3_4=1;
  Flag=0;
}

void delay()
{
  int i,j;
  for(i=0;i<400;i++)
  {
    for(j=0;j<100;j++)
    {
    }
  }
}


