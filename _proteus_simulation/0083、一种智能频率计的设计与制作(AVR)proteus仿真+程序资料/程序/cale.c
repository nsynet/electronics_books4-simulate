#ifndef cale_c
  #define cale_c
  #include "main.h"
//-------------------------------------------------------------------------
// //���ڷ�   �ȱ�����
//-------------------------------------------------------------------------
  void cale_t( uchar* back )
  {
    ulint count_all; //������� max 16m min 16k
    uint z_sh;      
    ulint y_sh;     
    uchar test;      
//*******************����С������  
    count_all = t1_cont * 50000+TCNT1; 
	if(count_all>max_t)
	count_all=max_t;
    z_sh = max_t / count_all;          
	#if pc
    y_sh=max_t-count_all*z_sh;
	y_sh*=10;
    count_all/=100;
#else
    y_sh = ( max_t % count_all )* 1000; 
#endif
//*******************�������㲿��
    *back++ = z_sh / 100;
    z_sh = z_sh % 100;
    *back++ = z_sh / 10;
    *back++ = z_sh % 10; 
//***************С������ 
    z_sh = y_sh / count_all; 
    *back++ = z_sh / 100;
    z_sh = z_sh % 100;

    *back = z_sh / 10;
    z_sh = z_sh % 10;
//************�������������
    test=0; 
    if ( z_sh >= 5 )
    {
	send_char(z_sh);
      *back += 1; //
      if ( *back == 10 )
      {
	    test++;
        *back-- = 0;
        *back += 1; 
        if ( *back == 10 )
        {
	    test++;
          *back-- = 0; 
          *back += 1; //
          if ( *back == 10 )
          {
	    test++;
            *back-- = 0;
            *back += 1; //
            if ( *back == 10 )
            {
	    test++;
              *back-- = 0;
              *back += 1; 
            }
          }
        }
      }
    }
    back-=(4-test); 

//****************ת��ascii��
    for ( test = 5; test > 0; test-- )
    {
      *back++ = * back + 0x30;
    }
back-=5;
//****************���С����
    back[5] = back[4]; 
    back[4] = back[3];
    back[3] = '.';

//****************ȥ����Ҫ��0

    for ( test = 3; test > 0; test-- )
    { 
      if ( *back == 0x30 )
      {
        *back++ = * back - 0x30;
      }
      else
      {
        break;
      }
    }
  }

//-------------------------------------------------------------------------
//       //������ 
//-------------------------------------------------------------------------
  void cale_f( uchar* back )
  {
    ulint count_all;  
    uchar test;       

    count_all = t1_cont * 50000+TCNT1; //ԭʼֵ
//*****************���� ����������
    *back++   = count_all / 1000000; //���λ
    count_all = count_all % 1000000; //ȥ�����λ
    *back++   = count_all / 100000; //100kλ
    count_all = count_all % 100000; //ȥ��
    *back++   = count_all / 10000;
    count_all = count_all % 10000;
    *back++   = count_all / 1000;
    count_all = count_all % 1000;
    *back++   = count_all / 100;
    count_all = count_all % 100;
    *back++   = count_all / 10;   //ʮλ
    *back     = count_all % 10;   //��λ

    back = back - 6;

//ת��ascii�ַ�
    for ( test = 7; test > 0; test-- )
    {
      *back++ = * back + 0x30;
    }
    back = back - 7; //ָ���˻�
//����ǰ���0
    while ( *back == 0x30 )
    {
      *back++ = * back - 0x30;
    }
  }
#endif
