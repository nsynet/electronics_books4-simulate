#include <stdio.h>
#define PI 3.141592
main()
{
	float r,c,s,S,v; //�뾶��Բ�ܳ���Բ�������������������
	//const float PI=3.14;
	printf("������뾶��"); 
	scanf("%f",&r);
	c=2*PI*r;
	s=PI*r*r;
	S=4*PI*r*r;
	v=4*PI*r*r*r/3;
	printf("Բ�ܳ���%f��Բ�����%f�����������%f���������%f\n",c,s,S,v);
}
