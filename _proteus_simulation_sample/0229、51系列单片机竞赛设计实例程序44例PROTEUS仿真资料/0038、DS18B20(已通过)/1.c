unsigned char  TempBuffer0[17]={0x54,0x48,0x3a,0x2b,0x31,0x32,0x35,0x20,
								0x54,0x4c,0x3a,0x2b,0x31,0x32,0x34,0x43,'\0'};
								//��ʾ�¶�������,�ϵ�ʱ��ʾTH:+125 TL:+124C	
void covert0( char TH, char TL)	//���¶�������ת��ΪLCD��ʾ������
{ 
   if(TH>0x7F)                    //�ж�����,���Ϊ����,����ת��Ϊ�����ֵ
   {
    TempBuffer0[3]=0x2d;	     //0x2dΪ"-"��ASCII��
	TH=~TH+1;
   }
   else TempBuffer0[0]=0x2b;	//0x2BΪ"+"��ASCII��

   if(TL>0x7f)
   {
   TempBuffer0[11]=0x2d;	     //0x2dΪ"-"��ASCII��
   TL=~TL+1;
   }
   else TempBuffer0[11]=0x2b;	//0x2BΪ"+"��ASCII��

  TempBuffer0[4]=TH/100+0x30;		             //�����TH�İ�ʮ��λ
  if( TempBuffer0[4]==0x30) TempBuffer0[4]=0xfe; //��λ������
  TempBuffer0[5]=(TH%100)/10+0x30;				//�����ʮλ
  TempBuffer0[6]=(TH%100)%10+0x30;	 			//�������λ
  TempBuffer0[12]=TH/100+0x30;		             //�����TL�İ�ʮ��λ
  if( TempBuffer0[12]==0x30) TempBuffer0[12]=0xfe; //��λ������
  TempBuffer0[13]=(TH%100)/10+0x30;				//�����ʮλ
  TempBuffer0[14]=(TH%100)%10+0x30;	 			//�������λ

