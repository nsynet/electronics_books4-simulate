//***********************************************************************************************************
//�������������������ʾ�������������ť
//
//***********************************************************************************************************	    
#include<reg51.h>
#include <intrins.h>

#define seg P0	   //�������
#define pianxuan P3//��Ƭѡ
#define motor P2   //�ӵ��

sbit kaishi=P1^0;  //������ʼ
sbit tingzhi=P1^1; //ͣ��
sbit set=P1^2;	   //���ð�ť
sbit jia=P1^3;	   //��
sbit jian=P1^4;	   //��
sbit TX=P1^5;	   //�ӳ�����ģ�飬���źŸ�������
sbit RX=P1^6;	   //�ӳ�����ģ�飬���ճ������ĸߵ�ƽ�ź�
sbit speaker=P1^7; //������

char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98,0xbf}; //����
char code pulse[]={0x91,0x83,0xc2,0x46,0x64,0x2c,0x38,0x19};		  //��������������ݣ������������4λ�͵�4λ���������֣��������������෴
char code pianxuan_lab[]={0xfe,0xfd,0xfb,0xf7};		  //Ƭѡ

int gewei;		   //���λ����Ϣ
int shiwei=5;	   //��ʮλ����Ϣ
int shiwei_set=0;  //��ʮλ��������Ϣ����ʼ�趨ֵΪ1.0��
int baiwei=1;	   //���λ����Ϣ
int baiwei_set=1;  //���λ��������Ϣ
int qianwei;	   //��ǧλ����Ϣ
int k=7;			   //��������ĵڼ������ݣ���ʼ����Ӧ���ǵ��˵�8�����ݣ�����K�ĳ�ʼ��ֵ��Ϊ7��
bit fangxiang=0;	   //�������Ϊ0��ת������Ϊ1��תɲ��
int sudu=0;			   //����ٶ�
int pinlv1=0;		   //����Ƶ��1
int pinlv2=0;		   //����Ƶ��2
bit set_biaozhi=0;	   //���ñ�־λ
bit yunxing_biaozhi=0; //���б�־λ
unsigned long juli;			   //ʵ�ʳ�������������
unsigned int juli_set;		   //���ÿ�ʼ��ʾ���룬�ټ�ȥ0.5�׾��Ǳ���
bit baojing=0;		   //������־λ
bit tishi=0;		   //��ʾ��־λ
int time2ms;		   //2ms�Ĵ���
int time;			   //������ʱ��
bit t0_flag;		   //T0�����־λ
int weizhi;			   //�����Ƭѡʱ��λ��

saomiao();			   //ɨ���ӳ���
chushihua();		   //�����ʼ���ӳ���
yunxing();			   //�����ӳ���
delay(int);			   //��ʱ�ӳ���
jisuan();			   //��������ӳ���

main()
{

chushihua();		   // ���ó�ʼ������ӳ���
speaker=1;			   // ����������
RX=1;				   //��Ϊ����ˣ�����Ϊ1

    TMOD=0x11;		   //��T0,T1Ϊ��ʱ����ʽ1
	TH0=0;			   //T0��ʼֵΪ0�����ر�ʱ��TH0��TL0����ֵ���Ǵ�T0�����ص�ʱ��
	TL0=0;             //
	TH1=(65536-50000)/256;		   //50MS��ʱ
	TL1=(65536-50000)%256;
	ET0=1;             //����T0�ж�
	ET1=1;			   //����T1�ж�
	TR1=1;			   //������ʱ��1
	EA=1;			   //�������ж�

	while(1)		   //����ѭ��
	{	
	
    if(set==0)						  //���ð�ť��һ����set_biaozhiȡ��
	    {while(set==0);	  //
		 set_biaozhi=~set_biaozhi;	  //
		 }
	if(set_biaozhi==1)				  //���set_biaozhiΪ1����������״̬�����ԼӺͼ�
	    {if(jia==0)					  //��
		     {while(jia==0); //
			  shiwei_set++;			  //���λ��
			  }						  
		 if(jian==0)				  //��
		     {while(jian==0);//
			  shiwei_set--;			  //���λ��
			  }
		}
	if(shiwei_set==10){shiwei_set=0;baiwei_set++;}	//�������������ݴ�����Χ��0��2.9��
	if(shiwei_set==-1){shiwei_set=9;baiwei_set--;}	//
	if(baiwei_set==3)baiwei_set=0;					//
	if(baiwei_set==-1)baiwei_set=2;					//
	
	if(kaishi==0&&set_biaozhi==0){yunxing_biaozhi=1;fangxiang=0;baojing=0;}	  //������ť���²���û������״̬�����б�־Ϊ1������Ϊ0������Ϊ0
	if(tingzhi==0&&set_biaozhi==0){yunxing_biaozhi=0;speaker=1;tishi=0;}			  //ֹͣ��ť���²���û������״̬�����б�־Ϊ0

	

	//if(RX==0){while(RX==0)saomiao();shiwei++;}//***������
	//if(TX==0){while(TX==0)saomiao();shiwei--;}//***������
	//if(shiwei==10){shiwei=0;baiwei++;}//***********������
	//if(shiwei==-1){shiwei=9;baiwei--;}//***********������
	//if(baiwei==3)baiwei=0;//***********************������
	//if(baiwei==-1)baiwei=2;//***********************������

	//juli=baiwei*10+shiwei;			  //�ϲ�ʵ�ʲ�������********������
	juli_set=baiwei_set*100+shiwei_set*10;//�ϲ���������

	if((juli>(juli_set-20))&&(juli<juli_set)&&yunxing_biaozhi==1)  //ʵ�ʾ����ڣ��趨���룭0.2�ף������趨���룩֮�䣬����ʾ
	    { 
		   tishi=1;												  //��ʾ��־Ϊ1
		  
		   if(baojing==1){yunxing_biaozhi=0;speaker=1;baojing=0;tishi=0;}			  //�б�����־����ʾ�ӱ���״̬�������ģ���ͣ�����ط�����
		   						 		   		  
		}

	if(juli<=(juli_set-20)&&yunxing_biaozhi==1)					  //ʵ�ʾ�����С�ڻ���ڣ��趨���룭0.2�ף�ʱ���򱨾�
	    {
		  
		  fangxiang=1;											 //�����ת�������Ϊǿ��ɲ����
		  baojing=1;											 //������־Ϊ1
		  tishi=0;
		}

	if(juli>=juli_set&&yunxing_biaozhi==1)						 //�ڰ�ȫ����
	     {
		  if(baojing==1){yunxing_biaozhi=0;speaker=1;baojing=0;tishi=0;}			 //���������־Ϊ1����ʾ�ӱ���״̬�������ģ���ͣ�����ط�����
		  speaker=1;											 //
	     }

										 
	     
																 //***********����ʱ��ʱ����
	if(RX==1)
	     {
		 TR0=1;			    //��������
	     while(RX==1);			//��RXΪ1�������ȴ�
	     TR0=0;				//�رռ���
         jisuan();			//����
		 }


	
	}

}


saomiao()
{	seg=0xff;
	pianxuan=pianxuan_lab[weizhi];
	if(set_biaozhi==0)
	     {
		 if(weizhi==0)seg=tab[gewei];
		 if(weizhi==1)seg=tab[shiwei];
		 if(weizhi==2)seg=tab[baiwei]&0x7f;		//��С����
		 if(weizhi==3)seg=0xff;	//����ʾ
		 }
	
	if(set_biaozhi==1)
		 {
		 if(weizhi==0)seg=tab[10];	//����ʱ��ʾ���š�����
		 if(weizhi==1)seg=tab[shiwei_set]; //����ʱ��ʾ
		 if(weizhi==2)seg=tab[baiwei_set]&0x7f;	//��С����//����ʱ��ʾ
		 if(weizhi==3)seg=tab[10];	//����ʱ��ʾ���š�����
		 }

		 	
	weizhi++;
	if(weizhi==4)weizhi=0;

}	
	
chushihua()			//��ʼ���ӳ�����Ϊ���һ��ʼ��֪��ʲô�Ƕȣ�������ʱ��һ��ʼ�϶����
{					 //�����ڿ���֮ǰ���ϳ�ʼ�����򣬸�4�������϶���ͣ�ڵ�8�����Ǹ�λ��
					 //�������������ٿ��Ƶ��ʱ���Ͳ�����ֻε������ˡ�
					 //ʵ�ʵ�����������ʱ��Ҫ��
	int y;
	for(y=0;y<8;y++)
	{motor=pulse[y];					 
	delay(100);}
}

yunxing()
{
 
 
        if(fangxiang==1) k++;		  //��תʱ����������ȡ
	    if(fangxiang==0) k--;		  //��תʱ����������ȡ
		if(k==8)k=0;			  //����
		if(k==-1)k=7;			  //����
		motor=pulse[k];				  //�͸����������
	   
	
}

jisuan()						//
{
	 time=TH0*256+TL0;			//���ʱ��
	 TH0=0;
	 TL0=0;
	
	 juli=(time*1.7)/100;     //�������
	 if((juli>=300)||t0_flag==1) //����������Χ��ʾ��-��
	 {	 
	  t0_flag=0;
	  gewei=10;	       //��-��
	  shiwei=10;	   //��-��
	  baiwei=10;	   //��-��
	 }
	 else							//��4λ��������
	 {
	  baiwei=juli%1000/100;
	  shiwei=juli%1000%100/10;
	  gewei=juli%1000%100%10;
	 }
}

void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
{
    t0_flag=1;							 //�ж������־
}

void  zd3()  interrupt 3 		 //T1�ж�����ɨ������ܺͼ�800MS����ģ��
{
int c;	 
	 TH1=0xf8;
	 TL1=0x30;
	 saomiao();
	 time2ms++;					 //
	 if(time2ms>=400)			 //
	 {
	  time2ms=0;
	  TX=1;			                //800MS  ����һ��ģ��//***********����ʱ��ʱ����	  
	  for(c=0;c<20;c++)			//
	  {_nop_();} 					//	  
	  TX=0;							//800MS  ����һ��ģ��//***********����ʱ��ʱ����
	 }
	 
	 sudu++;					   //2ms��sudu��1���ӵ�1ʱ��2ms,��������У�������һ��
	 if(sudu==1)
	     {sudu=0;
		     if(yunxing_biaozhi==1)yunxing();//			    
		 } 

	pinlv1++;					 //2ms��pinlv1��1���ӵ�250ʱ��500ms,�������ʾ״̬���������ȡ��
	if(pinlv1==250)				 //
	   {pinlv1=0;
	         if(tishi==1)speaker=~speaker;	 //
		}

	 pinlv2++;					//2ms��pinlv2��1���ӵ�100ʱ��200ms,����Ǳ���״̬���������ȡ��
	 if(pinlv2==100)
	   {pinlv2=0;
	         if(baojing==1)speaker=~speaker; //
		}
	if((tishi==0)&&(baojing==0))speaker=1;	 //���û����ʾ��־�ͱ�����־��	����������
}

delay(int x)
{int i,j;
	for(i=0;i<x;i++)
	for(j=0;j<120;j++);
}

//*************************************************************************