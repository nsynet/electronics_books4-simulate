//-------------------------------------------------------
// 名称：GP2D12 乘幂拟合函数相关参数求解程序
//-------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <conio.h>
int x[] = {120,68,48,38,31,27,24,21};
int y[] = {10,20,30,40,50,60,70,80};
void main()
{
	clrscr();
	int n = 10; double s_x,s_y, s_xx,s_yy, s_xy, a,b, lx,ly;
	for (int i = 0; i< n ; i++) 
	{	lx = log(x[i]); ly = log(y[i]); s_x += lx; s_y += ly;
		s_xx += lx * lx; s_yy += ly * ly; s_xy += lx * ly;
	}
	b = (n * s_xy - s_x * s_y) / (n * s_xx - s_x * s_x);
	a = exp((s_xx*s_y - s_x * s_xy) / (n*s_xx - s_x*s_x));
	//或者：a = exp((s_y / n) - b*(s_x/n));
	printf("y = %fx^%f\n", a, b);
	printf("s_x:%f\ns_y:%f\ns_xx:%f\ns_yy:%f\ns_xy:%f\n",
			s_x,s_y,s_xx,s_yy,s_xy);
	getch();
}
