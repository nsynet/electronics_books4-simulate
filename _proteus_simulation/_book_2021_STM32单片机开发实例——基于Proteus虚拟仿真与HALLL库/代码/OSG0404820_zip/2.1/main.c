#include <stdio.h>
#define PI 3.141592
main()
{
	float r,c,s,S,v; //半径、圆周长、圆面积、球面面积、球体积
	//const float PI=3.14;
	printf("请输入半径："); 
	scanf("%f",&r);
	c=2*PI*r;
	s=PI*r*r;
	S=4*PI*r*r;
	v=4*PI*r*r*r/3;
	printf("圆周长：%f，圆面积：%f，球面面积：%f，球体积：%f\n",c,s,S,v);
}
