#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

#if 0
//头部之前插入,head是链表头指针变量,保存了第1个有数据节点的地址  
STU *insert_link(STU *head, STU tmp) /* tmp是个普通形参,存储在栈区 */
{
    //为待插入的数据申请 堆区空间
    STU *pi = (STU *)calloc(1, sizeof(STU));
    if (pi == NULL)
    {
        perror("calloc");
        exit(-1); //结束进程
    }
    //将tmp数据赋值到 *pi
    *pi = tmp;  /* 相同类型的结构体变量可以直接赋值,但是如果结构体的成员name是指针,就要小心浅拷贝 */
    pi->next = NULL;

    //判断链表是否存在,任何链表都是从第0个节点逐个逐个插入的
	//判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (head == NULL) //不存在
    {
        head = pi; /* 让链表头指针变量指向第一个数据节点*/
        //return head;
    }
    else //存在
    {
		/* 头插法,链表头指针变量永远指向待插入节点*/
        pi->next = head; 
        head = pi;
        //return head;
    }

    return head;
}
#endif

#if 1
//尾部插入,head是链表头指针变量,保存了第1个有数据节点的地址
STU *insert_link(STU *head, STU tmp)
{
    //为待插入的数据申请 堆区空间
    STU *pi = (STU *)calloc(1, sizeof(STU));
    if (pi == NULL)
    {
        perror("calloc");
        exit(-1); //结束进程
    }
    //将tmp数据赋值到 *pi
    *pi = tmp;	/* 相同类型的结构体变量可以直接赋值,但是如果结构体的成员name是指针,就要小心浅拷贝 */
    pi->next = NULL;

    //判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (head == NULL) //不存在
    {
        head = pi;  /* 让链表头指针变量指向第一个数据节点*/
        //return head;
    }
    else //存在
    {
        //寻找链表的尾节点
        STU *pb = head;
        while (pb->next != NULL)
        {
            pb = pb->next;
        }

        //pb就是尾节点
        pb->next = pi;
    }

    return head;
}
#endif

#if 0
//有序插入,head是链表头指针变量,保存了第1个有数据节点的地址
STU *insert_link(STU *head, STU tmp)
{
    //为待插入的数据申请 空间
    STU *pi = (STU *)calloc(1, sizeof(STU));
    if (pi == NULL)
    {
        perror("calloc");
        exit(-1); //结束进程
    }
    //将tmp数据赋值到 *pi
    *pi = tmp;
    pi->next = NULL;

    //判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (head == NULL) //待插入节点是该链表的第一个数据节点
    {
        head = pi; /* 让链表头指针变量指向第一个数据节点*/
        //return head;
    }
    else // 该链表之前就存在数据节点,待插入节点根据学号大小插入链表的合适位置
    {
        //寻找插入点的位置
        STU *pb = head, *pf = head;
		
		/* 当退出该循环,就找到待插入节点应该插入链表的位置,pf应该指向待插入节点,待插入节点的next指向pb,
		   如果待插入节点的学号是最大的,那就把待插入节点插入尾节点  */
        while ((pb->num < pi->num) && (pb->next != NULL)) /* pb->next != NULL表示此时pb指向链表尾节点 */
        {
			/* pf是pb的跟屁虫,如果待插入节点的学号不是最大的,当找到待插入节点在链表中的插入位置时,pf应该
			   指向待插入节点,待插入节点的next指向pb */
            pf = pb;  
            pb = pb->next; 
        }
		/* 跳出上面while()的条件有2个,得仔细判断 */
		
		/* 待插入节点的学号小于pb->num */
        if (pb->num >= pi->num) //在链表的头部或者中部插入
        {
            if (head == pb) //头部之前插入
            {
                pi->next = head;
                head = pi;
            }
            else //中部插入
            {
                pf->next = pi;
                pi->next = pb;
            }
        }
        else //待插入节点的学号在当前链表中是最大的,所以尾部插入该待插入节点
        {
            pb->next = pi;
        }
    }

    return head;
}
#endif

/* head是链表头指针变量,保存了第1个有数据节点的地址 */
void print_link(STU *head)
{
    //判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (head == NULL)
    {
        printf("link not exits\n");
        return;
    }
    else
    {
		/* 不要去轻易修改链表头指针变量的指向,因为只有它保存了第1个有数据节点的地址 */
        STU *pb = head;
        while (pb != NULL) /* 说明该链表存在有数据节点 */
        {
            printf("%d %s %f\n", pb->num, pb->name, pb->score);
            pb = pb->next;
        }
    }
    return;
}

STU *search_link(STU *head, char *name)
{
    //判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (NULL == head)
    {
        printf("link not exist\n");
        return NULL;
    }
    else //链表存在
    {
		/* 不要去轻易修改链表头指针变量的指向,因为只有它保存了第1个有数据节点的地址 */
        STU *pb = head;
        while ((strcmp(pb->name, name) != 0) && (pb->next != NULL))
        {
            pb = pb->next;
        }

        //找到符合该名字的节点
        if (strcmp(pb->name, name) == 0)
        {
            return pb;
        }
    }

    printf("未找到相关数据\n");
    return NULL;
}

/* head是链表头指针变量,保存了第1个有数据节点的地址 */
STU *delete_link(STU *head, int num)
{
    //判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (NULL == head)
    {
        printf("link not exist\n");
        return head;
    }
    else
    {
        //查找删除的点
        STU *pb = head, *pf = head;
        while ((pb->num != num) && (pb->next != NULL))
        {
            pf = pb;
            pb = pb->next;
        }

        if (pb->num == num) //找到
        {
            //判断删除点的位置
            if (pb == head) //删除头节点
            {
                head = head->next; /* head一开始保存着链表第1个数据节点的地址,
								      所以head->next指向第2个数据节点 */
                //free(pb);
            }
            else //删除中尾部节点
            {
                pf->next = pb->next;
                //free(pb);
            }
            free(pb);
            printf("已成功删除num=%d的节点\n", num);
        }
        else //未找到
        {
            printf("未找到需要删除的节点\n");
        }
    }
    return head;
}

/* head是链表头指针变量,保存了第1个有数据节点的地址 */
STU *free_link(STU *head)
{
    ///判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (NULL == head)
    {
        printf("link not exist\n");
    }
    else
    {
        STU *pb = head; /* pb指向第一个数据节点 */
        while (pb != NULL) /* 说明数据节点存在 */
        {
            head = pb->next;
            free(pb);
            pb = head;
        }
    }
    return NULL;
}

STU *reverse_link(STU *head)
{
    //判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (NULL == head)
    {
        printf("link not exist\n");
        //return head;
    }
    else
    {
        STU *pb = head->next;
        STU *pn = NULL;
        head->next = NULL;

        while (pb != NULL)
        {
            //纪录pb下一个节点位置
            pn = pb->next;
            //pb连接上一个节点
            pb->next = head;
            head = pb;
            pb = pn;
        }

        printf("链表翻转成功\n");
    }

    return head;
}
/* head是链表头指针变量,保存了第1个有数据节点的地址 */
void sort_link(STU *head)
{
    //判断链表是否存在,即是否存在数据节点,如果存在数据节点,就表示该链表存在
    if (NULL == head)
    {
        printf("link not exist\n");
        return;
    }
    else
    {
        STU *p_i = head, *p_j = head; //int i=0,j=0;
        while (p_i->next != NULL)     //for(i=0;i<n-1;i++)
        {
            STU *p_min = p_i;   //int min = i;
            p_j = p_min->next;  //j=min+1;
            while (p_j != NULL) //for(;j<n;j++)
            {
                if (p_min->num > p_j->num) //if(arr[min] > arr[j])
                    p_min = p_j;           //min = j;

                p_j = p_j->next; //j++
            }
            if (p_i != p_min) //if(i != min)
            {
                //交换数据
				
				/* 第1步:整体交换两个结构体变量的内容,包含数据域和指针域 */
                STU tmp = *p_i;
                *p_i = *p_min;
                *p_min = tmp;
				
				/*  第2步:只交换两个结构体变量的指针域 */
                tmp.next = p_i->next;
                p_i->next = p_min->next;
                p_min->next = tmp.next;
            }

            p_i = p_i->next; //i++
        }
    }
    return;
}