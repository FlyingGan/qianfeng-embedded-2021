#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct stu
{
    //数据域
    int num;
    char name[32];

    //指针域
    struct stu *pre;
    struct stu *next;
} STU;

STU *head = NULL;

void insert_link(STU **p_head, STU tmp);
void print_link(STU *head);
STU *search_link(STU *head, int num);
void delete_link(STU **p_head, int num);
void free_link(STU **p_head);

int main(int argc, char const *argv[])
{
    int n = 0;
    printf("请输入学生的个数:");
    scanf("%d", &n);
    int i = 0;
    for (i = 0; i < n; i++)
    {
        printf("请输入第%d个学员的信息:", i + 1);
        STU tmp;
        scanf("%d %s", &tmp.num, tmp.name);

        insert_link(&head, tmp);
    }

    //遍历链表
    print_link(head);

    //查询
    printf("请输入你要查询的学号:");
    int num = 0;
    scanf("%d", &num);
    STU *ret = search_link(head, num);
    if (ret != NULL)
    {
        printf("查询的结果:%d %s\n", ret->num, ret->name);
    }

    //删除指定节点
    printf("请输入你要删除的学号:");
    scanf("%d", &num);

    delete_link(&head, num);

    //遍历链表
    print_link(head);

    //释放这个链表
    free_link(&head);

    //遍历链表
    print_link(head);
    return 0;
}

//尾插法:内部变量想要改变外部变量,函数参数得传入外部变量的地址
void insert_link(STU **p_head, STU tmp)
{
    STU *head = *p_head;

    //为插入的节点申请空间
    STU *pi = (STU *)calloc(1, sizeof(STU));
    *pi = tmp;
    pi->next = NULL;
    pi->pre = NULL;

    //判断链表是否为空
    if (NULL == head)
    {
        head = pi;
        pi->next = pi;
        pi->pre = pi;
    }
    else
    {
        head->pre->next = pi;
        pi->next = head;
        pi->pre = head->pre;
        head->pre = pi;
    }

    //更新外部的head
    *p_head = head;
}

void print_link(STU *head)
{
    //判断链表是否存在
    if (NULL == head)
    {
        printf("link not exist\n");
        return;
    }
    else
    {
        STU *pn = head;
        STU *pr = head->pre;

        while (1)
        {
            if (pn == pr) // 循环结束条件:双向循环链表数据节点为奇数个
            {
                printf("%d %s\n", pn->num, pn->name);
                break;
            }
            else if (pn->next == pr) //// 循环结束条件:双向循环链表节点为偶数个
            {
                printf("%d %s\n", pn->num, pn->name);
                printf("%d %s\n", pr->num, pr->name);
                break;
            }
            else
            {
				/* 同时从左右两边向中间遍历 */
                printf("%d %s\n", pn->num, pn->name);
                printf("%d %s\n", pr->num, pr->name);
                pn = pn->next;
                pr = pr->pre;
            }
        }
    }
    return;
}

STU *search_link(STU *head, int num)
{
    //判断链表是否存在
    if (NULL == head)
    {
        printf("link not exist\n");
        return NULL;
    }
    else
    {
        STU *pn = head;
        STU *pr = head->pre;
		
		/* 从链表左右两边向中间找,循环结束的条件是:如果该链表数据节点的个数是奇数个,那么
		   pn = pr 时说明找完全部数据节点了;如果该链表数据节点的个数是偶数个,那么
		   pn->next = pr 时说明找完全部数据节点了 */
        while ((pn->num != num) && (pr->num != num) && (pn != pr) && (pn->next != pr))
        {
            pn = pn->next;
            pr = pr->pre;
        }

        if (pn->num == num)
        {
            return pn;
        }
        else if (pr->num == num)
        {
            return pr;
        }
        else
        {
            printf("没有找到相关节点\n");
        }
    }

    return NULL;
}

#if 0 
void delete_link(STU **p_head, int num)
{
    STU *head = *p_head;

    if (NULL == head)
    {
        printf("link not exist\n");
        return;
    }
    else
    {
        STU *pn = head;
        STU *pr = head->pre;

		/* 从链表左右两边向中间找,循环结束的条件是:如果该链表数据节点的个数是奇数个,那么
		   pn = pr 时说明找完全部数据节点了;如果该链表数据节点的个数是偶数个,那么
		   pn->next = pr 时说明找完全部数据节点了 */
        while ((pn->num != num) && (pr->num != num) && (pn != pr) && (pn->next != pr))
        {
            pn = pn->next;
            pr = pr->pre;
        }

        if (pn->num == num) //头部、中部节点
        {
            if (pn == head) //删除头节点
            {
                head->next->pre = head->pre;
                head->pre->next = head->next;
                head = head->next;
                //free(pn);
            }
            else //删除中部节点
            {
                pn->pre->next = pn->next;
                pn->next->pre = pn->pre;
                //free(pn);
            }
            printf("成功删除节点:%d %s\n", pn->num, pn->name);
            free(pn);
        }
        else if (pr->num == num) //尾部、中部
        {
            pr->pre->next = pr->next;
            pr->next->pre = pr->pre;
            printf("成功删除节点:%d %s\n", pr->num, pr->name);
            free(pr);
        }
        else
        {
            printf("没有找到相关节点\n");
        }
    }

    *p_head = head;
}
#endif

#if 1
void delete_link(STU **p_head, int num)
{
    STU *head = *p_head;

    if (NULL == head)
    {
        printf("link not exist\n");
        return;
    }
    else
    {
        STU *pn = head;
        STU *pr = head->pre;

		/* 从链表左右两边向中间找,循环结束的条件是:如果该链表数据节点的个数是奇数个,那么
		   pn = pr 时说明找完全部数据节点了;如果该链表数据节点的个数是偶数个,那么
		   pn->next = pr 时说明找完全部数据节点了 */
        while ((pn->num != num) && (pr->num != num) && (pn != pr) && (pn->next != pr))
        {
            pn = pn->next;
            pr = pr->pre;
        }

        if (pn->num == num) //头部、中部节点
        {
            pn->next->pre = pn->pre;
            pn->pre->next = pn->next;
            if (pn == head) //删除头节点
            {
                head = head->next;
            }

            printf("成功删除节点:%d %s\n", pn->num, pn->name);
            free(pn);
        }
        else if (pr->num == num) //尾部、中部
        {
            pr->pre->next = pr->next;
            pr->next->pre = pr->pre;
            printf("成功删除节点:%d %s\n", pr->num, pr->name);
            free(pr);
        }
        else
        {
            printf("没有找到相关节点\n");
        }
    }

    *p_head = head;
}
#endif

/* 单向释放,即从第1个数据节点释放到最后一个数据节点 */
void free_link(STU **p_head)
{
    STU *head = *p_head;
	
	/* 判断链表是否为空 */
    if (NULL == head)
    {
        printf("link not exist\n");
        return;
    }
    else /* 能进入这个语句,说明链表至少存在1个数据节点 */
    {
        STU *pn = head;
		
		/* 可以先释放数据节点,再进行判断pn != (*p_head) */
        do
        {
            head = head->next;
            free(pn);  /* 释放该节点,只是系统回收该进场对该节点的使用权限,pn还是保存着该节点的地址 */
            pn = head;
        } while (pn != (*p_head)); /* *p_head指向的节点被释放了,但是*p_head还是保存着该节点的地址,只是没有权限再使用 */
    }

    *p_head = NULL;  /* 最后让 *p_head指向 NULL */
    return;
}