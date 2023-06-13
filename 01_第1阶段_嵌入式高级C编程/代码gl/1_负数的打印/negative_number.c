/* ************************************************************************
 *       Filename:  negative_number.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2023年06月06日 16时10分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  gl
 *        Company:  
 * ************************************************************************/


#include <stdio.h>


void test01()
{
	printf("%lu\n", sizeof(3.14));
	printf("%lu\n", sizeof(3.14f));
	
}
void test02()
{
	//=号两边类型必须匹配
	//float f=3.14;//3.14为double类型 而f为float类型 所以类型不匹配
	float f = 0.0f;

	printf("请输入一个浮点数:");
	scanf("%f", &f);
	
	printf("f = %f\n", f);

	double d = 0.0;
	printf("请输入一个浮点数:");
	scanf("%lf", &d);
	printf("d = %lf\n", d);
	
}
void test03()
{
	//
	int num = 123;
	printf("%#o\n", num);
	printf("%d\n", num);
	printf("%#x\n", num);
}


void test04()
{
	char ch1=-10;  /* -10 的补码=1111 0110=0xf6 */
	printf("ch1=%#x\n", ch1);

	char ch2=6;  /* 6的补码=0000 0110=0x06 */
	printf("ch2=%#x\n", ch2);

	
}

void test05()
{
	unsigned char ch1 = 300;  /* 补码=0001 0010 1100,由于ch1只占1个字节,所以实质上ch1=0010 1100 = 0x2c */
	printf("ch1 = %#x\n", ch1);  /* 计算机对数据无符号读取 */
	printf("ch1 = %d\n", ch1);  /* 计算机对数据有符号读取 */
	printf("ch1 = %u\n", ch1);  /* 计算机对数据无符号读取 */
	
	printf("\n");
	
	ch1 += 1;
	printf("ch1 = %#x\n", ch1);  /* 计算机对数据无符号读取 */
	printf("ch1 = %d\n", ch1);  /* 计算机对数据有符号读取 */
	printf("ch1 = %u\n", ch1);  /* 计算机对数据无符号读取 */
}

void test06()
{
	char ch1 = 0;
	
	for(; ch1<1000; ch1++)
	{
//		if(ch1 >= 127)
//		{
			printf("循环内 ch1 = %d \n", ch1);
//		}
	}
	printf("ch1 = %d \n", ch1);
}

int main(int argc, char *argv[])
{
	test06();
	return 0;
}


