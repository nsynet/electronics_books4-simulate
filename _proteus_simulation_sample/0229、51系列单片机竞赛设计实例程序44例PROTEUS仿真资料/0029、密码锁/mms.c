#include<AT89x51.h> 
#include"intrins.h"
#include"key.h"
#include"xsh.h"
#include"24c02.h"
#define ulong unsigned long
bit  BJCB=0;//������־					  
     XG=0,//�޸������־λ
     BJ=0,//������־λ
     SJ=0;//�����̱�־λ
    // xg=0;//�޸������־λ
uchar PSWD0_0[16]={0};//�������뻺��洢��Ԫ
//uchar code PSWD0_1[16]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};//�û���ʼ����洢��Ԫ
//uchar PSWD1_0[16]={0};//�������뻺��洢��Ԫ
uchar PSWD1_1[16]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};////����Ա��ʼ����洢��Ԫ
sbit OUT=P3^5;//����˿�
sbit L1=P0^2;//�ϵ�ָʾ
sbit L2=P0^1;//����ָʾ
sbit L3=P0^0;//����ָʾ
uint   mg=0,//�������
       KSC=0,//��������
       BJC=0,//��������
	   TCNTY=0,//�û�������ʱ�����ۼ�
	   TCNTG=0,//����Ա�������붨ʱ����
	   yhsh,//�û������־λ
	   glsh,//����Ա���־λ
	   shw;//���������־λ
void yhmimaxig();//�����޸ĳ���
void glmimaxig();//����Ա�޸ĳ���
void bjyin(ulong t)
{
 ulong c;
 uint n;
 for(c=0;c<t;c++)
{
 for(n=0;n<50;n++); //��ʱ
 BEEP=~BEEP; //ȡ����������ȵ��ź�
}
}
 void delay_10ms(void)
{
	uint i = 1000;
	while(i--);
}
//////////////��ʱ�жϷ�����//////////////////////////////////////
 void timer0() interrupt 1 
{ 
 uint i;
 TH0=(65536-50000)/256; //��TH0 TL0��ֵ50MS��ʱ
 TL0=(65536-50000)%256; //��װ������ֵ
 if(yhsh==1) 
 {
  TCNTY++;//�û���ʱ����
  if(shw==1)
 {
  TR0=0;
  TCNTY=0;
  }
  if(TCNTY==400)
  { 
   TR0=0;//�ر�T0��ʱ��
   TCNTY=0;
    mg=0;//�����������
	L1=1;
	for(i=0;i<2;i++)//���ⱨ����·
	 {
		  L3=0;
		  bjyin(1000);
		  L3=1;
		  delay(1000);
	  } 
	  L1=0; 
     }
    } 
	else if(glsh==1)
	    {
		 TCNTG++;//����Ա��ʱ����
         if(shw==1)
        {
           TR0=0;
           TCNTG=0;
         }
       if(TCNTG==400)
       { 
        TR0=0;//�ر�T0��ʱ��
        TCNTG=0;
        mg=0;//�����������
		L1=1;
	     for(i=0;i<2;i++)//���ⱨ����·
	    {
		  L3=0;
		  bjyin(1000);
		  L3=1;
		  delay(1000);
		 }
		 L1=0; 
		}
		}   	
		}	     	 
	    
void main()
{  
   uint i;
   TMOD=0x01;  //��ʱ�������ڷ�ʽ1
   ET0=1; 
   EA=1;
   TH0=(65536-50000)/256; //��TH0 TL0��ֵ
   TL0=(65536-50000)%256; //ʹ��ʱ��0.05���ж�һ��
  //Read_page24c02(0x00,PSWD1_1,16);//��24c02����û���ʼ����
   //i2cWrite24LC16B(0,0X20);
 /////////////��һ����24c02��д���ʼ����Ա���롢�û����롢��������/////////////////////
   for(i=0;i<16;i++)	//��һ��дһ����24c02��д
  {
   i2cWrite24LC16B(PSWD1_1[i],i);
   delay_10ms;  
  } 
   for(i=0;i<16;i++)	//��һ��дһ����24c02��д
  {
   i2cWrite24LC16B(PSWD1_1[i],0x10+i);
   delay_10ms;  
  }  //proteus����ʱ�ã��ճ���ʱ����һ���ã��ڶ��β��á�
  KSC=i2cRead24LC16B(0X20);
 loop:  L1=0;//�ϵ�����
		L2=1;//�����ɹ����̵���
		L3=1;//���ʱ�Ƶ�������
		OUT=0;//���źŹر�
       display_0(KSC);//����ǰ��ʾ
            
///////////��������/////////////////
 if(SJ==0)//�����̱�־λΪ0
 { 
  do
   {
    flag=0;//���̱�־λ
    key();
	if(flag==1&&num==12) //�ж��Ƿ�Ϊ����Ա���ܼ�����
	{
	 goto gl;
   	}
   	if(flag==1&&num<=9)
	 {
	  PSWD0_0[mg]=num;
	  mg++;//�������
	 }
	 if(flag==1&&num==14&&mg>=1)//�������ɾ��
	 {
	   mg=mg-1;
	   } 
	 if(mg==1) //����������¿���ʱ����ʱ
	 {
	  TR0=1;
	  yhsh=1; 
	  }
   }	
   while(num!=15);
   if(mg!=16)
   {
    for(i=mg;i<16;i++)
	{
	 PSWD0_0[i]=0;
	}
   }   
/////////////////����Ƚϵ�·////////////////////////////
 if(flag==1&&num==15)  
 { flag=0;
   yhsh=0;
   shw=1;
   num=0;
  for(i=0;i<16;i++)	//��24c02�����16������
  {
    PSWD1_1[i]=i2cRead24LC16B(i);
    delay_10ms;  
  }
  for(i=0;i<16;i++)
 {
   if(PSWD1_1[i]!=PSWD0_0[i])
   {
     BJCB=1;
     break;
	}
   else
   BJCB=0;	
   
  }
 }
   if(BJCB!=0)
       { 
	     BJC++; 
		 if(BJC!=3)   	
	    {
		 BJCB=0; //��һ�κ͵ڶ��α���
	     delay(500);
		 mg=0;//�����������
		 L1=1;
		 for(i=0;i<3;i++)//���ⱨ����·
		 {
		  L3=0;
		  display_3();
		  bjyin(1000);
		  L3=1;
		  delay(1000);
		  }
		 goto loop;	 
		}
	  else if(BJC==3)
	    {
		 BJC=0;
	     BJCB=0;
	     display_5();//������������ʧ��,����
	     SJ=1;//�����̱�־λ
	     mg=0;//�����������
		 L1=1;
		 for(i=0;i<2;i++)//���ⱨ����·
		 {
		  L3=0;
		  bjyin(1000);
		  L3=1;
		  delay(1000);
		  }
	     goto loop;
		} 
		}     	  
	   else 
	   if(BJCB==0)
	  {
	   KSC++;
	   display_1(KSC);
	   i2cWrite24LC16B(KSC,0X20);
	   if(KSC==100)
	   {
	    SJ=1; 
		 }
	   L2=0;
	   L1=1;
	   OUT=1;
	   mg=0;//�����������
 loop1:do	   //����ɨ��ȴ����ܼ�����
	   {
	    flag=0;
	    key();
		if(flag)
	   {	
	     flag=0;
	    switch(num)
	   {   
	    case 13:	   
	        {
			  display_2();
             do
            {
             flag=0;//���̱�־λ
             key();
        	if(flag==1&&num<=9)
	       {
	         PSWD0_0[mg]=num;
	         mg++;//�������
	        }
	       if(flag==1&&num==14&&mg>=1)//�������ɾ��
	      {
	       mg=mg-1;
	      }
	      if(mg==16)
	     {
	       do	   //����ɨ��ȴ����ܼ�����
	     {
	       flag=0;
	       key();
	     }
	    while(num!=15);
	   } 
       }	
       while(num!=15);
      if(mg!=16&&num==15)
     {
      for(i=mg;i<16;i++)
	 {
	   PSWD0_0[i]=0;
	  }
	 }
	if(flag==1&&num==15)
   { 
     flag=0;	
	 mg=0;
   for(i=0;i<16;i++)	//��һ��дһ����24c02��д
  {
   i2cWrite24LC16B(PSWD0_0[i],i);
   delay_10ms;  
  } 
  display_1(KSC);
   do	   //����ɨ��ȴ����ܼ�����
   {
	 flag=0;
	 key();
	}
	while(num!=11); //���·��ؼ����������� 
	{
      goto loop;
	}
    }
	};break;
		
   case 11: {
		       goto loop;
				  //break;           
		    }
		    }
			}
			}
	  while(flag!=0);//����������������
	  goto loop1;
 // i2cWrite24c02_page(0x00,PSWD1_1,mg);
   } 
   }
 else
    { 
	 do
    {
    flag=0;
    key();
	}
	while(num!=12);//�ж��Ƿ�Ϊ����Ա���ܼ�����	  
  gl:do//����Ա��������
     { 
     flag=0;
     key();
   	 if(flag==1&&num<=9)
	 {
	  PSWD0_0[mg]=num;
	  mg++;//�������
	 }
	 if(flag==1&&num==14&&mg>=1)//ɾ��������
	 {
	   mg=mg-1;
	 } 
	 if(mg==1)
	  {
	   TR0=1;
	  }//����ʱ��TO��5�뿪��
      }	
   while(num!=15);
   if(mg!=16&&num==15)
   {
    for(i=mg;i<16;i++)
	{
	 PSWD0_0[i]=0;
	}
   }
  //////////����Ա����Ƚ�///////////////////////
 //Read_page24c02(0x10,PSWD0_1,16)
for(i=0;i<16;i++)	//��24c02�����16������
{
    PSWD1_1[i]=i2cRead24LC16B((0x10+i));
    delay_10ms;  
}	
if(flag==1&&num==15)  
{  flag=0;
   shw=1;
   num=0;
  for(i=0;i<mg;i++)
 {
   if(PSWD1_1[i]!=PSWD0_0[i])
   { BJCB=1;
     break;
	}
   else	
   BJCB=0;
   }
   }
   if(BJCB!=0)
       { 
	     BJC++; 
		 if(BJC!=3)   	
	    { 
		 BJCB=0; //��һ�κ͵ڶ��α���
	     
		 mg=0;//�����������
		 L1=1;
		 for(i=0;i<2;i++)//���ⱨ����·
		 {
		  L3=0;
		  display_3();
		  bjyin(1000);
		  L3=1;
		  delay(1000);
		  }
		 display_1(KSC);
		 goto loop;	 
		}
	  else
	    {
		 BJCB=0;
	     display_5();//������������ʧ��,����
	     mg=0;//�����������
		 delay(10000);
		 display_1(KSC);
	     goto loop; 
		}     	
	   }   
	   else 
	  { 
	   SJ=0;
	   display_4();//����Ա������ʾ
       mg=0;
	   L2=0;
	   L1=1;
	   L3=0;//�����������
	   do	   //����ɨ��ȴ����ܼ�����
	   {
	    flag=0;
	    key();
	   }
	   while(flag==0); //����������������
	   if(flag==1&&num==13)
	   {
	     flag=0;
	     display_2();
             do
            {
             flag=0;//���̱�־λ
             key();
        	if(flag==1&&num<=9)
	       {
	         PSWD0_0[mg]=num;
	         mg++;//�������
	        }
	       if(flag==1&&num==14&&mg>=1)//�������ɾ��
	     {
	       mg=mg-1;
	      }
	      if(mg==16)
	     {
	       do	   //����ɨ��ȴ����ܼ�����
	     {
	       flag=0;
	       key();
	     }
	    while(num!=15);
	   } 
       }	
       while(num!=15);
      if(mg!=16&&num==15)
     {
      for(i=mg;i<16;i++)
	 {
	   PSWD0_0[i]=0;
	  }
	 }
	if(flag==1&&num==15)
   { 
     flag=0;	
	 mg=0;
   for(i=0;i<16;i++)	//��һ��дһ����24c02��д
  {
   i2cWrite24LC16B(PSWD0_0[i],(0x10+i));
   delay_10ms;  
  } 
  display_4();
   do	   //����ɨ��ȴ����ܼ�����
   {
	 flag=0;
	 key();
	}
	while(num!=11); //���·��ؼ����������� 
	{
      goto loop;
	}
    }
	   }
	   if(flag==1&&num==10)
	   {
	    KSC=0;
		i2cWrite24LC16B(KSC,0X20);
		display_1(KSC);
	    do	   //����ɨ��ȴ����ܼ�����
	   {
	    flag=0;
	    key();
	   }
	   while(num!=11);//���·��ؼ����������� 
	    goto loop; 
       }
	   if(flag==1&&num==11)//���·��ؼ����������� 
	   {
	    goto loop;
		}
       }
	   }
	   }