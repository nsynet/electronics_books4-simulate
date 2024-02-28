#include <stdio.h>
#define uint unsigned int  //宏定义 
void AscendSort(uint num,uint *p); 
main()
{
	uint a[5],i;
	for(i=0;i<5;i++)
	{
		scanf("%d",a+i); //a+i也可以写成&a[i] 
	}
	AscendSort(5,a);
	for(i=0;i<5;i++)
	{
		printf("%d ",a[i]);
	}
}

/******************************
length：数组长度
*p：数组首地址指针 
******************************/
void AscendSort(uint length,uint *p)
{
	uint i,j,t;
	for(i=0;i<length-1;i++)
	{
		for(j=i+1;j<length;j++)
		{
			if(*(p+i)>*(p+j)){t=*(p+i);*(p+i)=*(p+j);*(p+j)=t;}
		}
	}
}

