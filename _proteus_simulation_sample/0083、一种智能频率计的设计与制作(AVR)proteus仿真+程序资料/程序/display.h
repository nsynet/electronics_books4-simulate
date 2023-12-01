#ifndef display_h
  #define display_h

//*******
  #define in 0
  #define out 0xff
//*********
  #define data_port  PA     //pa����
  #define data_direc DDRA
  #define data_in    PINA
  #define data_out  PORTA
  #define rs 5              //�ӵ�pb
  #define rw 6
  #define e  7
//****************
  void clearall( void ); //����ָ��
  void yj_set( uchar xsh, uchar gb, uchar dt ); //��ʾ����
  void makecg( uchar address, uchar* cg ); //�����ֿ�
  void showstr( uchar* str, uchar xpot, uchar ypot, uchar num ); //Һ����ʾ

#endif
