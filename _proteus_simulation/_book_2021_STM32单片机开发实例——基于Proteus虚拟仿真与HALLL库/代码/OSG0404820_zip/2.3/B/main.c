#include <stdio.h>
main()
{
	int num1,num2,result;
	printf("����������������������ȴ��С����");
	scanf("%d%d",&num1,&num2);
	//1.��Լ�� 
	result=num2;
	while(result>=1)
	{
		if(num1%result==0 && num2%result==0)break;
		result--;
	}
	if(result==1)printf("%d��%d���������Լ��\n",num1,num2);
	else         printf("%d��%d�����Լ����%d\n",num1,num2,result);
	//2.�󹫱��� 
	result=num1;
	while(1) //����result<=num1*num2 
	{
		if(result%num1==0 && result%num2==0)break;
		result++;
	}
	printf("%d��%d����С��������%d\n",num1,num2,result);
}
