/**
 * 基础内存分配器练习。
 * 设计一个内存分配模块，有与系统malloc，free，strdup相类似的接口。\n
 * 内存分配器调度内存固定在传入的一块内存空间内，\n
 * 这样一个内存分配器可以广泛地应用到项目中，避免频繁使用系统的malloc，free接口，\n
 * 使系统进行频繁的页切换，从而有效提高运行效率。
 *
 */

/**
@file   mem.h
@brief 内存分配器模块头文件，


主要实现在开辟的静态数组空间内进行内存的分配，释放和数据拷贝功能，类似实现标准库中的malloc
free和strdup函数的功能

@author  zhouyj
@version V1.1 \n
			1.优化代码\n
			2.在需要分配的内存空间基础扩大一倍分配空间，减少内存碎片的产生\n

			
@version V1.0
@date     2015-4-1
**/

#include <stdio.h>
#include <stdlib.h>

#ifndef PRACTICE_MEM_H_
#define PRACTICE_MEM_H_
#if defined(__cplusplus) && __cplusplus
extern "C" {
#endif

//#define __DEBUG__  
#ifdef __DEBUG__  
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"", __LINE__, ##__VA_ARGS__)  
#else  
#define DEBUG(format,...)  
#endif

#define __DEBUGP__  
#ifdef __DEBUGP__  
#define DEBUGP(format,...) printf("File: "__FILE__", Line: %05d: "format"", __LINE__, ##__VA_ARGS__)  
#else  
#define DEBUGP(format,...)  
#endif



/**
*	@brief  数据节点结构体
*
*	数据节点结构体，数据buf和长度以及是否使用，前后数据节点都标识出来
*	
**/
typedef struct dataNode
{
	char *data_buf; ///<指定分配的空间的地址
	size_t buf_size; ///<指定分配buf空间的大小
	int flag_use;	///<标识当前buf空间有没有使用
	struct dataNode *prev; ///<上一个结点
	struct dataNode *next;///<下一个结点
}memNode, *pmemNode;


/**
*	@brief  内存分配数据结构
*
*	存储空间分配释放函数，用来找到头结点所在位置
*	
**/

typedef struct tagMEM
{
	/**
	 * man malloc
	 *@brief  空间分配函数
	 *
	 *分配sz大小的空间，返回空间首地址
	 *@param mem分配空间的地址
	 *@param size要分配空间的大小
	 *@return  成功返回分配空间的首地址(void型) ,失败返回NULL
	 */
	void *
	(*alloc)(struct tagMEM *mem, size_t sz);

	/**
	 * man free
	 * @brief 释放不用的空间
	 *  
	 *  释放ptr指定的地址的空间,将没有用的空间进行合并，标识为可重新分配
	 *@param mem用于找到要释放空间的头地址
	 *@param ptr用于找到要释放的空间的地址
	 *@return return 1代表释放成功，0代表失败
	 */
	int
	(*free)(struct tagMEM *mem, void *ptr);
	
	/**
	 * man strdup
	 *@brief   拷贝克隆字符串到新分配的空间
	 *
	 *拷贝1份str指定的字符串数据到新分配的空间中
	*@param mem要拷贝字符串到指定的字符串空间的地址
	*@param str要拷贝复制的字符串
	 *
	 *@return  成功返回拷贝复制的字符串的首地址，失败返回NULL
	 */
	//int
	//(*strdup)(struct tagMEM *mem, char *str);
	char *
	(*strdup)(struct tagMEM *mem, char *str);

}stMEM, *pstMEM;


/**
 *@brief  创建内存分配器。
 *
 * param[in] sz 预分配调度内存大小。
 *
 */
extern pstMEM
MEM_create(void *buf, size_t sz);

/**
 * @brief 释放内存分配器。
 *
 */
extern void
MEM_release(pstMEM *mem);


#if defined(__cplusplus) && __cplusplus
};
#endif
#endif // PRACTICE_MEM_H_
