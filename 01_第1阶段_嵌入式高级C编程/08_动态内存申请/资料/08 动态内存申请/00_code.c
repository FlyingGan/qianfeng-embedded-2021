#include <stdio.h>
#include <stdlib.h>
void test01()
{
    //空間申請
    int *p = NULL;
    p = (int *)malloc(sizeof(int));
    if (p == NULL)
    {
        return;
    }

    *p = 100;

    printf("*p = %d\n", *p);

    //空间释放
    free(p);
}

#include <string.h>
void test02()
{
    int n = 0;
    printf("请输入int元素的个数:");
    scanf("%d", &n);

    //根据元素的个数申请空间
    int *p = NULL;
	
	/* p表示申请的这块堆区空间的起始地址,p+1会跳过4个字节的宽度 */
    p = (int *)malloc(n * sizeof(int)); /* 如果n=5,类似于数组 int arr[5] */
    if (p == NULL)
    {
        return;
    }
    //将堆区空间清0
    memset(p, 0, n * sizeof(int));

    //获取键盘输入
    int i = 0;
    for (i = 0; i < n; i++)
    {
		/* p表示申请的这块堆区空间的起始地址 */
        scanf("%d", p + i);
    }

    //遍历数组元素
    for (i = 0; i < n; i++)
    {
        printf("%d ", p[i]); //*(p+i)
    }
    printf("\n");

    //释放堆区空间,只需要传入这块堆区空间的起始地址就行
    free(p);  /* 一块动态申请的内存只能 free 一次， 不能多次 free */

	/* 使用free()释放这一块堆区空间之后,p还保存着这一块堆区空间的起始地址,但是
	   程序猿已经没有权限使用这一块堆区空间,所以应该给P赋值为NULL,以免p变成野指针 */
	p = NULL;
	
    return;
}
void *get_addr(int n, int elem_size)
{
    return calloc(n, elem_size);
}
void input_int_array(int *p, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%d", p + i);
    }
}
void print_int_array(int *p, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");
}
void test03()
{
    int n = 0;
    printf("请输入int元素的个数:");
    scanf("%d", &n);

    //根据元素个数 申请空间
    int *p = NULL;
    p = (int *)get_addr(n, sizeof(int));
    if (p == NULL)
    {
        return;
    }

    //获取键盘输入
    input_int_array(p, n);

    //遍历
    print_int_array(p, n);

    //释放堆区空间,只需要传入这块堆区空间的起始地址就行
    free(p); /* 一块动态申请的内存只能 free 一次， 不能多次 free */
	
	/* 使用free()释放这一块堆区空间之后,p还保存着这一块堆区空间的起始地址,但是
	   程序猿已经没有权限使用这一块堆区空间,所以应该给P赋值为NULL,以免p变成野指针 */
	p = NULL;
}

void test04()
{
    int n = 0;
    printf("请输入int元素的个数:");
    scanf("%d", &n);

    //根据元素的个数申请空间
    int *p = NULL;
    p = (int *)calloc(n, sizeof(int));
    if (p == NULL)
    {
        return;
    }

    //获取键盘输入
    int i = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%d", p + i);
    }

    //遍历数组元素
    for (i = 0; i < n; i++)
    {
        printf("%d ", p[i]); //*(p+i)
    }
    printf("\n");

    printf("请输入你要新增的元素个数:");
    int new_n = 0;
    scanf("%d", &new_n);

    //追加空间,大小为旧的堆区空间大小+新的堆区空间大小
    p = (int *)realloc(p, (n + new_n) * sizeof(int));

    printf("请输入%d个新增元素:", new_n);
    //请输入新增的元素,在原来的元素末尾开始追加新的元素
    for (i = n; i < n + new_n; i++)
    {
        scanf("%d", p + i);
    }

    //遍历数组元素
    for (i = 0; i < n + new_n; i++)
    {
        printf("%d ", p[i]); //*(p+i)
    }
    printf("\n");

	//释放堆区空间,只需要传入这块堆区空间的起始地址就行
    free(p); /* 一块动态申请的内存只能 free 一次， 不能多次 free */
	
	/* 使用free()释放这一块堆区空间之后,p还保存着这一块堆区空间的起始地址,但是
	   程序猿已经没有权限使用这一块堆区空间,所以应该给P赋值为NULL,以免p变成野指针 */
	p = NULL;
}

//在32位平台
void test05()
{
    //字符数组 在栈区 开辟12字节 存放"hello world"
    char str1[] = "hello world";

    //str2字符指针变量 在栈区 4B 保存文字常量区"hello world"的首元素地址
    char *str2 = "hello world";

    //str3字符指针变量 在栈区 4B 保存堆区128B空间的起始地址
    char *str3 = (char *)malloc(128, 1);
    //将字符串"hello world"拷贝到str3指向的堆区空间
    strcpy(str3, "hello world");
}

//在32位平台
char a;
int b;
//void fun(char str4[128])
void fun(char *str4)
{
    printf("%lu\n", sizeof(str4)); //4
}
void test06()
{
    char str1[] = "hello";
    char *str2 = "hello";
    char *str3 = (char *)malloc(128);
    printf("%lu\n", sizeof(a));    //1
    printf("%lu\n", sizeof(b));    //4
    printf("%lu\n", sizeof(str1)); //6
    printf("%lu\n", sizeof(str2)); //4
    printf("%lu\n", sizeof(str3)); //4
}

void test07()
{
    int *p = NULL;

    p = (int *)calloc(1, sizeof(int));

    *p = 100;
    printf("*p = %d\n", *p);

    if (p != NULL)
    {
        free(p);
        p = NULL;
    }

    if (p != NULL)
    {
        free(p);
        p = NULL;
    }

    return;
}

void test08()
{
    char *p = (char *)calloc(1, 128);
    strcpy(p, "hello world");

	//释放堆区空间,只需要传入这块堆区空间的起始地址就行
    free(p); /* 一块动态申请的内存只能 free 一次， 不能多次 free */
	
	/* 使用free()释放这一块堆区空间之后,p还保存着这一块堆区空间的起始地址,但是
	   程序猿已经没有权限使用这一块堆区空间,所以应该给P赋值为NULL,以免p变成野指针 */
	//p = NULL;   
    printf("%s\n", p);//不确定
}
int main(int argc, char const *argv[])
{
    test08();
    return 0;
}
