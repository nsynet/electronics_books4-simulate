#include <stdio.h>
#define uint unsigned int  //�궨�� 
void AscendSort(uint num,uint *p); 
main()
{
	uint a[5],i;
	for(i=0;i<5;i++)
	{
		scanf("%d",a+i); //a+iҲ����д��&a[i] 
	}
	AscendSort(5,a);
	for(i=0;i<5;i++)
	{
		printf("%d ",a[i]);
	}
}

/******************************
length�����鳤��
*p�������׵�ַָ�� 
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

