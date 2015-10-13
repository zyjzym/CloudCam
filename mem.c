/**
 * 基础内存分配器练习。
 * 设计一个内存分配模块，有与系统malloc，free，strdup相类似的接口。\n
 * 内存分配器调度内存固定在传入的一块内存空间内，\n
 * 这样一个内存分配器可以广泛地应用到项目中，避免频繁使用系统的malloc，free接口，\n
 * 使系统进行频繁的页切换，从而有效提高运行效率。
 *
 */

/**
 * 不断的malloc和free会对程序性能造成极大的影响，通过对静态内存buff的管理实现内存的分配\n
 与调度可以提高程序运行效率
 */

#include "mem.h"
#include <string.h>
#include <stdlib.h>

/**
 * man malloc
 * 
 */
static void *
mem_alloc(struct tagMEM *mem, size_t  msize)
{
	pmemNode headNode = (memNode *)(mem + 1);
	pmemNode curNode = NULL;
	curNode = headNode;

	//扩大两倍的空间
	size_t size = 2*msize;
	
	DEBUG("size = %d\n", size);	

	//找到空闲的数据节点或者未分配的空间
	while(curNode != NULL && (curNode->buf_size - size < sizeof(memNode)) && curNode->flag_use == 1)
	{
		curNode = curNode->next;
	}
	DEBUG("curNode->flag_use = %d\n", curNode->flag_use);
	
	//当前结点为空，链表走完，无可用空间，返回错误
	if(NULL == curNode)
	{
		printf("allocates memory  failed!!!\n");
		return NULL;
	}
	else
	{
		DEBUG("curNode = %s\n", curNode);
	
		//剩余空间记录结点
		pmemNode newNode = (memNode *)((char *)curNode + sizeof(memNode) + size);

		newNode->data_buf = newNode + 1;
		newNode->buf_size = curNode->buf_size - size - sizeof(memNode);
		newNode->flag_use = 0;

		//指定新的buf空间
		if(curNode->next != NULL)
		{
			curNode->next->prev = newNode;
		}
		
		newNode->next = curNode->next;
		if(curNode == headNode)
		{
			newNode->next = NULL;
		}
		
		curNode->next = newNode;
		newNode->prev = curNode;

		//curNode->data_buf = headNode + 1;
		curNode->buf_size = size;
		
		curNode->flag_use = 1;
		DEBUG("curNode = %s\n", curNode);	
		
	}

	return curNode->data_buf;
	//返回分配的内存buf空间
	
}

/**
 * man free
 * return 1代表释放成功，0代表失败
 */
static int
mem_free(struct tagMEM *mem, void *ptr)
{
	pmemNode curNode = (char *)ptr - sizeof(memNode);
	
	//找到空闲的数据节点或者未分配的空间
	if(NULL == curNode || 0 == curNode->flag_use)
	{
		printf("ptr is NULL \n");
		return 0;
	}

	//合并可用空间
	curNode->flag_use = 0;
	
	if(curNode->prev != NULL && curNode->prev->flag_use == 0)
	{
		DEBUG("\n");

		curNode->prev->buf_size =curNode->prev->buf_size + sizeof(memNode)+curNode->buf_size;
		DEBUG("\n");
		
		if(curNode->next != NULL)
		{
			curNode->next->prev = curNode->prev;
		}

		curNode->prev->next = curNode->next;
		DEBUG("\n");

		//修复合并尾结点的bug
		curNode = curNode->prev;
	}
	DEBUG("\n");

	if(curNode->next != NULL && curNode->next->flag_use == 0)
	{
		pmemNode pTmp = NULL;
		curNode->buf_size = curNode->buf_size + sizeof(memNode)+curNode->next->buf_size;
		
		pTmp = curNode->next->next;
		DEBUG("curNode->next->next=%s\n", pTmp);

		curNode->next=curNode->next->next;
		DEBUG("\n");

		//???????????????????????????????pTmp ??curNode->next->next????
		//if(curNode->next->next != NULL)??????????
		if(pTmp != NULL)
		{
			DEBUG("\n");
			curNode->next->next->prev = curNode;
		}
			
	}
	return 1;
}

/**
 * man strdup
 * 
 */
/*
*拷贝克隆字符串
*
*/
static char *
mem_strdup(struct tagMEM *mem, const char *str)
{
	//调用mem_alloc分配空间
   char *buff = (char *)mem->alloc(mem, strlen(str)+1);

   if (NULL == buff)
   {
   		printf("malloc failed\n");
  		return NULL;
   }
   
   	memcpy(buff,str,strlen(str)+1);
	return buff;
}




pstMEM
MEM_create(void *buf, size_t sz)
{
	pstMEM pMem = (stMEM *)buf;//calloc(1, sizeof(stMEM)+sizeof(memNode));
	pmemNode dataNode = (memNode *)(pMem +1);

	//赋值函数
	pMem->alloc = mem_alloc;
	pMem->free = mem_free;
	pMem->strdup = mem_strdup;

	//初始化结构体头结点
	dataNode->data_buf = (char *)pMem + sizeof(stMEM) + sizeof(memNode);
	dataNode->buf_size = sz - sizeof(memNode)-sizeof(stMEM);
	dataNode->flag_use = 0;
	dataNode->prev = NULL;
	dataNode->next = NULL;
	
	return pMem;
}

void
MEM_release(pstMEM *mem)
{
	return ;
}



