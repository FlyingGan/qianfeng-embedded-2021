#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void print_help();
void get_file_name(char *dest_file_name, char *src_file_name);
char *read_src_file(unsigned long int *file_length, char *src_file_name);
char *file_text_encrypt(char *src_file_text, unsigned long int length, unsigned int password);
void save_file(char *text, unsigned long int length, char *file_name);
int main(int argc, char const *argv[])
{
    while (1)
    {
        char src_file[32] = "";  /* 数组名代表首元素的地址 */
        char dst_file[32] = "";
        char *data = NULL;
        unsigned long int file_length = 0; /* 文件长度 */
        unsigned int password = 0;  /* 进行文件加密的密码 */

        print_help();
        int cmd = 0;
        scanf("%d", &cmd);  /* 获取操作指令 */

		/* case语句下面不能定义变量,否则编译器会报错 */
        switch (cmd)
        {
        case 1:
            //获取源文件和目标文件名
            get_file_name(dst_file, src_file);
            //读取源文件的内容,data保存了堆区空间地址,该堆区空间用于保存文件数据
            data = read_src_file(&file_length, src_file);
            //对 data 指向的堆区空间内容进行加密
            printf("please input your unsigned int passworld:");
            scanf("%u", &password);
            data = file_text_encrypt(data, file_length, password);
            //对内容保存
            save_file(data, file_length, dst_file);
            break;
        case 2:
            //获取源文件和目标文件名
            //读取源文件的内容
            //对内容解密
            //对内容保存
            break;
        case 3:
            return 0;
        }
    }
    return 0;
}
void print_help()
{
    printf("********1:加密文件***********\n");
    printf("********2:解密文件***********\n");
    printf("********3:退出程序***********\n");
}

/* 获取文件名 */
void get_file_name(char *dest_file_name, char *src_file_name)
{
    printf("请输入你的原文件名称(30个字符):");
    scanf("%s", src_file_name);
    printf("请输入你的目的文件名称(30个字符):");
    scanf("%s", dest_file_name);
    return;
}

/* 读取源文件的内容,返回值是函数内部申请的堆区空间首地址,该堆区空间用于保存文件数据 */
char *read_src_file(unsigned long int *file_length, char *src_file_name)
{
    FILE *fp = fopen(src_file_name, "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(-1); //結束進程
    }
	/* 把文件流指针定位到文件末尾 */
    fseek(fp, 0, 2);
	
	/* ftell()会返回此时的文件流指针距离文件首部的字节数,
	  此时文件流指针已经定位到文件末尾,所以ftell(fp)的结果是
	  文件总大小 */
    //*file_length 等价于 外界的文件长度变量file_length
    *file_length = ftell(fp);
	
	//复位文件流指针,让文件流指针定位到文件开头,这样才能读取文件数据
    rewind(fp);

	/* unsigned char类型的变量的值范围是 0-255;calloc()申请堆区空间
	   之后会将该堆区空间里面的数据清零;申请的堆区空间大小应该是文件
	   大小+1,多出的1个字节是为了方便在字符串末尾加上'\0',因为从文件
	   读取到的字符串末尾是没有'\0'的,得程序猿手动加上 */
    char *p = (char *)calloc(1, *file_length + 1);
    if (p == NULL)
    {
        perror("calloc");
        exit(-1); //結束進程
    }

	/* 一次性读取 *file_length 个字节的数据,只需要读1块数据就行  */
    fread(p, *file_length, 1, fp);
	
    fclose(fp); /* 必须要关闭已经打开的文件 */

    return p;
}

/* 加密堆区空间数据,返回值是加密后的数据的第0个元素的堆区空间地址 */
char *file_text_encrypt(char *src_file_text, unsigned long int length, unsigned int password)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
		/* src_file_text指向堆区空间,保存着从源文件读取到的数据 */
        src_file_text[i] += password;
    }

    return src_file_text;
}

/* 把解密后的数据写入目标文件 */
void save_file(char *text, unsigned long int length, char *file_name)
{
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(-1); //結束進程
    }

    fwrite(text, length, 1, fp);

    fclose(fp); /* 必须要关闭已经打开的文件 */

    //释放堆区空间
    if (text != NULL)
    {
        free(text);
        text = NULL;
    }
    return;
}