#include <stdio.h>
main()
{
	int num1,num2,result;
	printf("请随机输入两个正整数（先大后小）：");
	scanf("%d%d",&num1,&num2);
	//1.求公约数 
	result=num2;
	while(result>=1)
	{
		if(num1%result==0 && num2%result==0)break;
		result--;
	}
	if(result==1)printf("%d和%d不存在最大公约数\n",num1,num2);
	else         printf("%d和%d的最大公约数是%d\n",num1,num2,result);
	//2.求公倍数 
	result=num1;
	while(1) //或者result<=num1*num2 
	{
		if(result%num1==0 && result%num2==0)break;
		result++;
	}
	printf("%d和%d的最小公倍数是%d\n",num1,num2,result);
}
