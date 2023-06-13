#include <stdio.h>
typedef struct
{
    char name[16];
    int atk;
    int def;
} HERO;
void test01()
{
    HERO hero[] = {{"德玛西亚", 50, 80}, {"小法", 70, 30}, {"盲僧", 80, 80}};
    int n = sizeof(hero) / sizeof(hero[0]);

    FILE *fp = fopen("hero.txt", "w");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    fwrite(hero, sizeof(HERO), n, fp);

    fclose(fp);
}

#include <string.h>
void test02()
{
    HERO hero[3];
    memset(hero, 0, sizeof(hero));

    FILE *fp = fopen("hero.txt", "r");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
	/* 将磁盘文件的数据原样输入到内存 */
    fread(hero, sizeof(HERO), 3, fp);

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        printf("%s %d %d\n", hero[i].name, hero[i].atk, hero[i].def);
    }

    fclose(fp);
}

void test03()
{
    HERO hero[] = {{"德玛西亚", 50, 80}, {"小法", 70, 30}, {"盲僧", 80, 80}};
    int n = sizeof(hero) / sizeof(hero[0]);

    FILE *fp = fopen("hero.txt", "w");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    //格式化写fprintf
    int i = 0;
    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%s %d %d\n ", hero[i].name, hero[i].atk, hero[i].def);
    }

    fclose(fp);
}

void test04()
{
    HERO hero[3];
    memset(hero, 0, sizeof(hero));

    FILE *fp = fopen("hero.txt", "r");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        fscanf(fp, "%s %d %d", hero[i].name, &hero[i].atk, &hero[i].def);
    }

    for (i = 0; i < 3; i++)
    {
        printf("%s %d %d\n", hero[i].name, hero[i].atk, hero[i].def);
    }

    fclose(fp);
}

void test05()
{
    FILE *fp = fopen("c.txt", "w+");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    //写
    fputs("hello file", fp);

    long len = ftell(fp);
    printf("文件的大小:%ld\n", len);

    fclose(fp);
}

#include <stdlib.h>
#include <string.h>
void test06()
{
    FILE *fp = fopen("c.txt", "r");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
	/* 把文件流指针定位到文件末尾 */
    fseek(fp, 0, 2);
	
	/* ftell()会返回此时的文件流指针距离文件首部的字节数,
	  此时文件流指针已经定位到文件末尾,所以ftell(fp)的结果是
	  文件总大小 */
    long len = ftell(fp);
	
    //复位文件流指针,让文件流指针定位到文件开头,这样才能读取文件数据
    rewind(fp);
    printf("文件总大小:len=%ld\n", len);

	/* unsigned char类型的变量的值范围是 0-255;calloc()申请堆区空间
	   之后会将该堆区空间里面的数据清零;申请的堆区空间大小应该是文件
	   大小+1,多出的1个字节是为了方便在字符串末尾加上'\0',因为从文件
	   读取到的字符串末尾是没有'\0'的,得程序猿手动加上 */
    unsigned char *text = (unsigned char *)calloc(1, len + 1);
	/* 读取len个字节的数据,只需要读1块数据就行  */
    fread(text, len, 1, fp);
	/* %s打印是遇到'\0'就停止打印 */
    printf("%s\n", text);
    fclose(fp); /* 必须要关闭已经打开的文件 */

    //释放堆区空间（不是必须,因为有可能别的函数需要使用该堆区空间的数据）
    if (text != NULL)
    {
        free(text);
        text = NULL;
    }
}
int main(int argc, char const *argv[])
{
    test06();
    return 0;
}
