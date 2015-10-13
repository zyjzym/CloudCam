/**
 * �����ڴ��������ϰ��
 * ���һ���ڴ����ģ�飬����ϵͳmalloc��free��strdup�����ƵĽӿڡ�\n
 * �ڴ�����������ڴ�̶��ڴ����һ���ڴ�ռ��ڣ�\n
 * ����һ���ڴ���������Թ㷺��Ӧ�õ���Ŀ�У�����Ƶ��ʹ��ϵͳ��malloc��free�ӿڣ�\n
 * ʹϵͳ����Ƶ����ҳ�л����Ӷ���Ч�������Ч�ʡ�
 *
 */

/**
 * ���ϵ�malloc��free��Գ���������ɼ����Ӱ�죬ͨ���Ծ�̬�ڴ�buff�Ĺ���ʵ���ڴ�ķ���\n
 ����ȿ�����߳�������Ч��
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

	//���������Ŀռ�
	size_t size = 2*msize;
	
	DEBUG("size = %d\n", size);	

	//�ҵ����е����ݽڵ����δ����Ŀռ�
	while(curNode != NULL && (curNode->buf_size - size < sizeof(memNode)) && curNode->flag_use == 1)
	{
		curNode = curNode->next;
	}
	DEBUG("curNode->flag_use = %d\n", curNode->flag_use);
	
	//��ǰ���Ϊ�գ��������꣬�޿��ÿռ䣬���ش���
	if(NULL == curNode)
	{
		printf("allocates memory  failed!!!\n");
		return NULL;
	}
	else
	{
		DEBUG("curNode = %s\n", curNode);
	
		//ʣ��ռ��¼���
		pmemNode newNode = (memNode *)((char *)curNode + sizeof(memNode) + size);

		newNode->data_buf = newNode + 1;
		newNode->buf_size = curNode->buf_size - size - sizeof(memNode);
		newNode->flag_use = 0;

		//ָ���µ�buf�ռ�
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
	//���ط�����ڴ�buf�ռ�
	
}

/**
 * man free
 * return 1�����ͷųɹ���0����ʧ��
 */
static int
mem_free(struct tagMEM *mem, void *ptr)
{
	pmemNode curNode = (char *)ptr - sizeof(memNode);
	
	//�ҵ����е����ݽڵ����δ����Ŀռ�
	if(NULL == curNode || 0 == curNode->flag_use)
	{
		printf("ptr is NULL \n");
		return 0;
	}

	//�ϲ����ÿռ�
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

		//�޸��ϲ�β����bug
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
*������¡�ַ���
*
*/
static char *
mem_strdup(struct tagMEM *mem, const char *str)
{
	//����mem_alloc����ռ�
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

	//��ֵ����
	pMem->alloc = mem_alloc;
	pMem->free = mem_free;
	pMem->strdup = mem_strdup;

	//��ʼ���ṹ��ͷ���
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



