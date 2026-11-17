#ifndef __My_Queue_H_
#define __My_Queue_H_

/*********************************************************************
 * @brief       Queue队列类型定义
 *********************************************************************/
typedef struct
{
    unsigned int Depth;            // Queue深度
    volatile unsigned int Head;    // Head为起始元素
    volatile unsigned int Tail;    // Tail-1为最后一个元素
    volatile unsigned int Counter; // 元素个数
    unsigned int ElementBytes;     // 每个元素的字节数
    void *Buff;                    // 缓存区
} Queue_Type;

/*********************************************************************
 * @brief       Queue初始化
 * @param[in]   pQueue: Queue指针
 * @param[in]   pBuff: Queue中缓存
 * @param[in]   elementBytes:Queue每个元素的字节数
 * @param[in]   depth: Queue深度
 * @return      None
 *********************************************************************/
void Queue_Init(Queue_Type *pQueue, void *pBuff, unsigned int elementBytes, unsigned int depth);

/*********************************************************************
 * @brief       判断Queue是否为空
 * @param[in]   pQueue: Queue指针
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char Queue_IsEmpty(Queue_Type *pQueue);

/*********************************************************************
 * @brief       向Queue添加一个元素
 * @param[in]   pQueue: Queue指针
 * @param[in]   pValue: 要添加的元素
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char Queue_AddOne(Queue_Type *pQueue, void *pValue);

/*********************************************************************
 * @brief       向Queue添加多个元素
 * @param[in]   pQueue: Queue指针
 * @param[in]   pValues: 要添加的元素指针
 * @param[in]   bytesToAdd: 要添加元素的长度
 * @return      实际添加的元素个数
 *********************************************************************/
unsigned int Queue_Add(Queue_Type *pQueue, void *pValues, unsigned int bytesToAdd);

/*********************************************************************
 * @brief       从Queue读取一个元素
 * @param[in]   pQueue: Queue指针
 * @param[in]   pValue: 存放要读取的元素指针
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char Queue_GetOne(Queue_Type *pQueue, void *pValue);

/*********************************************************************
 * @brief       从Queue读取多个元素
 * @param[in]   pQueue: Queue指针
 * @param[out]  pValues: 存放要读取的元素指针
 * @param[in]   bytesToRead: 要读取的元素长度
 * @return      实际读取的元素个数
 *********************************************************************/
unsigned int Queue_Get(Queue_Type *pQueue, void *pValues, unsigned int bytesToRead);

/*********************************************************************
 * @brief       清空Queue
 * @param[in]   pQueue: Queue指针
 * @return      None
 *********************************************************************/
void Queue_Clear(Queue_Type *pQueue);

void Queue_Binary_Init(void);

#endif
