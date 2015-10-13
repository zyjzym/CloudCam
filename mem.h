/**
 * �����ڴ��������ϰ��
 * ���һ���ڴ����ģ�飬����ϵͳmalloc��free��strdup�����ƵĽӿڡ�\n
 * �ڴ�����������ڴ�̶��ڴ����һ���ڴ�ռ��ڣ�\n
 * ����һ���ڴ���������Թ㷺��Ӧ�õ���Ŀ�У�����Ƶ��ʹ��ϵͳ��malloc��free�ӿڣ�\n
 * ʹϵͳ����Ƶ����ҳ�л����Ӷ���Ч�������Ч�ʡ�
 *
 */

/**
@file   mem.h
@brief �ڴ������ģ��ͷ�ļ���


��Ҫʵ���ڿ��ٵľ�̬����ռ��ڽ����ڴ�ķ��䣬�ͷź����ݿ������ܣ�����ʵ�ֱ�׼���е�malloc
free��strdup�����Ĺ���

@author  zhouyj
@version V1.1 \n
			1.�Ż�����\n
			2.����Ҫ������ڴ�ռ��������һ������ռ䣬�����ڴ���Ƭ�Ĳ���\n

			
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
*	@brief  ���ݽڵ�ṹ��
*
*	���ݽڵ�ṹ�壬����buf�ͳ����Լ��Ƿ�ʹ�ã�ǰ�����ݽڵ㶼��ʶ����
*	
**/
typedef struct dataNode
{
	char *data_buf; ///<ָ������Ŀռ�ĵ�ַ
	size_t buf_size; ///<ָ������buf�ռ�Ĵ�С
	int flag_use;	///<��ʶ��ǰbuf�ռ���û��ʹ��
	struct dataNode *prev; ///<��һ�����
	struct dataNode *next;///<��һ�����
}memNode, *pmemNode;


/**
*	@brief  �ڴ�������ݽṹ
*
*	�洢�ռ�����ͷź����������ҵ�ͷ�������λ��
*	
**/

typedef struct tagMEM
{
	/**
	 * man malloc
	 *@brief  �ռ���亯��
	 *
	 *����sz��С�Ŀռ䣬���ؿռ��׵�ַ
	 *@param mem����ռ�ĵ�ַ
	 *@param sizeҪ����ռ�Ĵ�С
	 *@return  �ɹ����ط���ռ���׵�ַ(void��) ,ʧ�ܷ���NULL
	 */
	void *
	(*alloc)(struct tagMEM *mem, size_t sz);

	/**
	 * man free
	 * @brief �ͷŲ��õĿռ�
	 *  
	 *  �ͷ�ptrָ���ĵ�ַ�Ŀռ�,��û���õĿռ���кϲ�����ʶΪ�����·���
	 *@param mem�����ҵ�Ҫ�ͷſռ��ͷ��ַ
	 *@param ptr�����ҵ�Ҫ�ͷŵĿռ�ĵ�ַ
	 *@return return 1�����ͷųɹ���0����ʧ��
	 */
	int
	(*free)(struct tagMEM *mem, void *ptr);
	
	/**
	 * man strdup
	 *@brief   ������¡�ַ������·���Ŀռ�
	 *
	 *����1��strָ�����ַ������ݵ��·���Ŀռ���
	*@param memҪ�����ַ�����ָ�����ַ����ռ�ĵ�ַ
	*@param strҪ�������Ƶ��ַ���
	 *
	 *@return  �ɹ����ؿ������Ƶ��ַ������׵�ַ��ʧ�ܷ���NULL
	 */
	//int
	//(*strdup)(struct tagMEM *mem, char *str);
	char *
	(*strdup)(struct tagMEM *mem, char *str);

}stMEM, *pstMEM;


/**
 *@brief  �����ڴ��������
 *
 * param[in] sz Ԥ��������ڴ��С��
 *
 */
extern pstMEM
MEM_create(void *buf, size_t sz);

/**
 * @brief �ͷ��ڴ��������
 *
 */
extern void
MEM_release(pstMEM *mem);


#if defined(__cplusplus) && __cplusplus
};
#endif
#endif // PRACTICE_MEM_H_
