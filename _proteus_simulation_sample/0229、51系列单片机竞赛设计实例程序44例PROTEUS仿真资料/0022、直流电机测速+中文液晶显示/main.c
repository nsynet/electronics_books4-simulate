#include <showfun.h>
#include <stdio.h>

extern char fnLCMInit(); // LCM ��ʼ��
extern void at(unsigned char x,unsigned char y);/*�趨�ı�x,yֵ*/
extern void cls();	 // ����
extern void charout(unsigned char *str); //ASCII(8*8) ��ʾ����
extern void fnSetPos(unsigned char urow, unsigned char  ucol);	// ���õ�ǰ��ַ
extern uchar dprintf(uchar x,uchar y,char *fmt);// ASCII(8*16) �� ����(16*16) ��ʾ����
extern uchar fnPR12(uchar uCmd); // д�޲�����ָ��
extern uchar fnPR13(uchar uData); // д����
extern unsigned int Adc0832(unsigned char channel);
extern void Line( unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, bit Mode);
extern void Pixel(unsigned char PointX,unsigned char PointY, bit Mode);



uchar dsp[10]={0,0,0,0,0,0,0,0,0,0,};
char abc[3]={0,0,0,};
uchar key=0;
uint a=100;
uchar n=5;
uchar count=1; 
uint k1=0;

uchar GeyKey();
void delay(uchar i);
void control();


main()
{  
     
 	fnLCMInit();
	fnSetPos(0,0);
	dprintf(0,0,"ֱ�������-���ټ�����ϵͳ");
	dprintf(0,12,"����+:��������");
	dprintf(0,24,"����-:��������");
	dprintf(0,36,"����=:˳ʱ��ת");
	dprintf(0,48,"����on/c:��ʱ��ת");
     
     dprintf(0,72,"����:");
  	 dprintf(0,84,"ת��:");  
    
	 P1_1=0;
     TMOD=0x15;
	 TH1=0x3c;
	 TL1=0xb0;
     TH0=0x00;
	 TL0=0x00;
	 ET0=1;
	 ET1=1;
	 TR0=1;
	 TR1=1;
    
    while(1)
	{  key=GeyKey();
      switch(key)
       {   case '1': {          a=10;
	                            //sprintf(abc,"%3.2f",a/255.0);
		                        dprintf(0,96,"  5    r/min");   
                                //dprintf(0,96,abc);  
                                dprintf(60,96,"r/min");
	                            break;      }
	       case '2': {          a=25;dprintf(0,96,"  25    r/min");    break;      }
		   case '3': {          a=40; dprintf(0,96," 40    r/min");   break;      }
		   case '4': {          a=55; dprintf(0,96," 60    r/min");   break;      }
		   case '5': {          a=70; dprintf(0,96," 80    r/min");   break;      }
		   case '6': {          a=90; dprintf(0,96,"100    r/min");   break;      }
		   case '7': {          a=110; dprintf(0,96,"120    r/min");   break;      }
		   case '8': {          a=130; dprintf(0,96,"135    r/min");   break;      }
		   case '9': {          a=150; dprintf(0,96,"150    r/min");   break;      }
	       case '+': {          dprintf(0,72,"����: ˳ʱ��");
	                            control();
								break;
						}
           case '-': {         P1_0=0;
		                        dprintf(0,72,"����: ��ʱ��");
		                         control();
		                        break;
					}
           case '=': {P1_0=1;dprintf(0,72,"����: ˳ʱ��");break;}
           case 'c': {P1_0=0;dprintf(0,72,"����: ��ʱ��");break;}
           case '/': {dprintf(0,72,"����: ˳ʱ��");
	                            control();}
		   default:  break;
        }
    }
}


uchar GeyKey()
{
 	P1_4=0;
 	P1_5=1;
 	P1_6=1;
 	P1_7=1;
	P3_0=1;
	P3_1=1;
	P3_2=1;
    P3_3=1;
	_nop_();_nop_();
	if(!P3_0)return '7';
 	if(!P3_1)return '8';
 	if(!P3_2)return '9';
    if(!P3_3)return '/';
 	P1_4=1;
 	P1_5=0;
 	P1_6=1;
 	P1_7=1;
	_nop_();_nop_();
	if(!P3_0)return '4';
 	if(!P3_1)return '5';
 	if(!P3_2)return '6';
    if(!P3_3)return '*';

 	P1_4=1;
 	P1_5=1;
 	P1_6=0;
 	P1_7=1;
	_nop_();_nop_();
	if(!P3_0)return '1';
 	if(!P3_1)return '2';
 	if(!P3_2)return '3';
    if(!P3_3)return '-';


 	P1_4=1;
 	P1_5=1;
 	P1_6=1;
 	P1_7=0;
	_nop_();_nop_();
	if(!P3_0)return 'c';
 	if(!P3_1)return '0';
 	if(!P3_2)return '=';
    if(!P3_3)return '+';

	return 0;
}


void delay(uchar i)
{  uchar j,k;
    for(;i>0;i--)
    for(j=15;j>0;j--)
    for(k=11;k>0;k--);
}
	
	
	
void time()interrupt 3 
{    
     TR1=0;
     count++;
     k1+=TL0;
	 if(count==51)
	 {     
	      sprintf(dsp,"%3d",k1);
		  dprintf(0,108,dsp);   
          dprintf(60,108,"r/min");   
		  count=1;
          k1=0;
      }
	  TH1=0x3c;
	  TL1=0xb0;
	  TH0=0x00;
	  TL0=0x00;
	  TR1=1;

}

void control()
{                            
       EA=1;
	   while(1)
	   {    if(a>=150) 
               a=150;
			if(a<=10) 
			    a=10;
			 P1_1=0; 
			 delay(160-a);
			 P1_1=1;
			 delay(a);
			 key=GeyKey();
			 if(key=='-') a-=n;
			 else 
			   if(key=='+') a+=n;
			 else 
			   if(key=='=')
			   {  P1_0=1;
				   dprintf(0,72,"����: ˳ʱ��");
			 }
			 else 
			 if(key=='c') 
			 {  P1_0=0;
			   dprintf(0,72,"����: ��ʱ��");
			 }
			 else  
			  if(key=='*')
			  {   P1_1=0;
			      break;
			  }
			  else
			 if(key!=0)
			   break;
			 }
		 EA=0;
}


