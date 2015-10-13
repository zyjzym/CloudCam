
#include "mem.h"

/**
 * ��̬�ڴ������ڴ���������ȡ�
 */
static unsigned
_cache[1024 * 1024];

int
main(int argc, char *argv[])
{
	pstMEM mem = MEM_create(_cache, sizeof(_cache));
	DEBUG("\n");
	if(NULL != mem)
	{
		void *ptr = mem->alloc(mem, 1024);
		
		memcpy(ptr, "hello", 6);
		printf("CloudCam:���Ӿ�\n");	

		void *ptr1 = mem->alloc(mem, 1024);
		memcpy(ptr1, "the", 6);

                printf("CloudCam:���Ӿ�\n");

		void *ptr2 = mem->alloc(mem, 1024);
		memcpy(ptr2, "world", 6);
	

		void *ptr3 = mem->alloc(mem, 1024);
		memcpy(ptr3, "i am", 6);

		void *ptr4 = mem->alloc(mem, 1024);
		memcpy(ptr4, "linux", 6);
	        printf("CloudCam:���Ӿ�\n");		
	
		mem->free(mem, ptr);
		ptr = NULL;

		mem->free(mem, ptr1);
		ptr1 = NULL;
		
		mem->free(mem, ptr2);
		ptr2 = NULL;
		
		mem->free(mem, ptr3);
		ptr3 = NULL;

		mem->free(mem, ptr4);
		ptr4 = NULL;


		MEM_release(&mem);
		
	}

	return 0;
}
