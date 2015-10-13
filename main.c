
#include "mem.h"

/**
 * 静态内存用于内存分配器调度。
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
		printf("CloudCam:周延军\n");	

		void *ptr1 = mem->alloc(mem, 1024);
		memcpy(ptr1, "the", 6);
		DEBUGP("ptr1 = %s\n", ptr1);	

		void *ptr2 = mem->alloc(mem, 1024);
		memcpy(ptr2, "world", 6);
		DEBUGP("ptr2 = %s\n", ptr2);	

		void *ptr3 = mem->alloc(mem, 1024);
		memcpy(ptr3, "i am", 6);
		DEBUGP("ptr3 = %s\n", ptr3);	

		void *ptr4 = mem->alloc(mem, 1024);
		memcpy(ptr4, "linux", 6);
		DEBUGP("ptr4 = %s\n", ptr4);	
			
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
