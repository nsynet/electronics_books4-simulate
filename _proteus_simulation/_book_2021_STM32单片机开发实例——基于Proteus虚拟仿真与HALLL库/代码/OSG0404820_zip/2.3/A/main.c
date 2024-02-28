#include <stdio.h>
main()
{
	unsigned int num[5],i,max,min;
	printf("请依次输入五个正整数：");
	for(i=0;i<5;i++)
	{
		scanf("%d",&num[i]);
	}
	max=min=num[0];
	for(i=1;i<5;i++)
	{
		if(max<num[i])max=num[i];
		if(min>num[i])min=num[i];
	}
	printf("最大值：%d；最小值：%d\n",max,min);
}
