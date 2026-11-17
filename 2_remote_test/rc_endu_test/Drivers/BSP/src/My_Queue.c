#include <string.h>
#include "My_Queue.h"
#include "main.h"

/*********************************************************************
 * @brief       Queue初始化
 * @param[in]   pQueue: Queue指针
 * @param[in]   pBuff: Queue中缓存
 * @param[in]   elementBytes:Queue每个元素的字节数
 * @param[in]   depth: Queue深度
 * @return      None
 *********************************************************************/
void Queue_Init(Queue_Type *pQueue, void *pBuff, unsigned int elementBytes, unsigned int depth)
{
    // xSemaphoreTake(Queue_Binary_Handle, portMAX_DELAY);

    pQueue->Buff = pBuff;
    pQueue->ElementBytes = elementBytes;
    pQueue->Depth = depth;
    pQueue->Head = 0;
    pQueue->Tail = 0;
    pQueue->Counter = 0;

    // xSemaphoreGive(Queue_Binary_Handle);
}

/*********************************************************************
 * @brief       判断Queue是否为空
 * @param[in]   pQueue: Queue指针
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char Queue_IsEmpty(Queue_Type *pQueue)
{
    return (pQueue->Counter == 0);
}

/*********************************************************************
 * @brief       判断Queue是否已满
 * @param[in]   pQueue: Queue指针
 * @return      TRUE or FALSE
 *********************************************************************/
unsigned char Queue_IsFull(Queue_Type *pQueue)
{
    // return (pQueue->Counter * pQueue->ElementBytes == pQueue->Depth);
    return (pQueue->Counter == pQueue->Depth);
}

/*********************************************************************
 * @brief       向Queue添加一个元素
 * @param[in]   pQueue: Queue指针
 * @param[in]   pValue: 要添加的元素
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char Queue_AddOne(Queue_Type *pQueue, void *pValue)
{
    unsigned char *p;

    if (Queue_IsFull(pQueue))
    {
        return 0;
    }

    // xSemaphoreTake(Queue_Binary_Handle, portMAX_DELAY);

    p = (unsigned char *)pQueue->Buff;
    memcpy(p + pQueue->Tail, (unsigned char *)pValue, pQueue->ElementBytes);

    pQueue->Tail += pQueue->ElementBytes;
    if (pQueue->Tail >= pQueue->Depth * pQueue->ElementBytes)
    {
        pQueue->Tail = 0;
    }
    pQueue->Counter++;

    // xSemaphoreGive(Queue_Binary_Handle);
    return 1;
}

/*********************************************************************
 * @brief       向Queue添加多个元素
 * @param[in]   pQueue: Queue指针
 * @param[in]   pValues: 要添加的元素指针
 * @param[in]   bytesToAdd: 要添加元素的长度
 * @return      实际添加的元素个数
 *********************************************************************/
unsigned int Queue_Add(Queue_Type *pQueue, void *pValues, unsigned int bytesToAdd)
{
    unsigned char *p;
    unsigned int cnt = 0;

    // xSemaphoreTake(Queue_Binary_Handle, portMAX_DELAY);

    p = (unsigned char *)pValues;
    while (bytesToAdd--)
    {
        if (Queue_AddOne(pQueue, p))
        {
            p += pQueue->ElementBytes;
            cnt++;
        }
        else
        {
            break;
        }
    }

    // xSemaphoreGive(Queue_Binary_Handle);
    return cnt;
}

/*********************************************************************
 * @brief       从Queue读取一个元素
 * @param[in]   pQueue: Queue指针
 * @param[in]   pValue: 存放要读取的元素指针
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char Queue_GetOne(Queue_Type *pQueue, void *pValue)
{
    unsigned char *p;
    if (Queue_IsEmpty(pQueue))
    {
        return 0;
    }

    // xSemaphoreTake(Queue_Binary_Handle, portMAX_DELAY);

    p = (unsigned char *)pQueue->Buff;
    memcpy(pValue, p + pQueue->Head, pQueue->ElementBytes);

    pQueue->Head += pQueue->ElementBytes;
    if (pQueue->Head >= pQueue->Depth * pQueue->ElementBytes)
    {
        pQueue->Head = 0;
    }
    pQueue->Counter--;

    // xSemaphoreGive(Queue_Binary_Handle);
    return 1;
}

/*********************************************************************
 * @brief       从Queue读取多个元素
 * @param[in]   pQueue: Queue指针
 * @param[out]  pValues: 存放要读取的元素指针
 * @param[in]   bytesToRead: 要读取的元素长度
 * @return      实际读取的元素个数
 *********************************************************************/
unsigned int Queue_Get(Queue_Type *pQueue, void *pValues, unsigned int bytesToRead)
{
    unsigned int cnt = 0;
    unsigned char *p;

    // xSemaphoreTake(Queue_Binary_Handle, portMAX_DELAY);

    p = pValues;
    while (bytesToRead--)
    {
        if (Queue_GetOne(pQueue, p))
        {
            p += pQueue->ElementBytes;
            cnt++;
        }
        else
        {
            break;
        }
    }

    // xSemaphoreGive(Queue_Binary_Handle);

    return cnt;
}

/*********************************************************************
 * @brief       清空Queue
 * @param[in]   pQueue: Queue指针
 * @return      None
 *********************************************************************/
void Queue_Clear(Queue_Type *pQueue)
{
    // xSemaphoreTake(Queue_Binary_Handle, portMAX_DELAY);

    pQueue->Counter = 0;
    pQueue->Head = 0;
    pQueue->Tail = 0;

    // xSemaphoreGive(Queue_Binary_Handle);
}

/*
void TestQueue(void)
{
    int i;
    Queue_Type queue;
    Queue_Type *pQueue;
    int index;
    float fArray[10];
    float fValue;

    char cArray[10];
    char cValue;

    pQueue = &queue;

    printf("测试Queue元素为float型的数据\r\n");
    printf("初始化Queue值。\r\n");
    Queue_Init(pQueue, fArray, sizeof(float), 10);
    for (i = 0; i < 10; i++)
    {
        fValue = (100.0f + i * i);
        Queue_AddOne(pQueue, &fValue);
    }
    printf("当前元数个数：%d\r\n", pQueue->Counter);
    index = 0;
    while (Queue_GetOne(pQueue, &fValue))
    {
        index++;
        printf("第%d个元素fValue = %0.3f\r\n", index, fValue);
        if (index == 5)
        {
            printf("插入3个值。\r\n");
            fValue = 1.23f;
            Queue_AddOne(pQueue, &fValue);

            fValue = 2.34f;
            Queue_AddOne(pQueue, &fValue);

            fValue = 3.45f;
            Queue_AddOne(pQueue, &fValue);
        }
    }

    printf("\r\n\r\n");
    printf("测试Queue元素为char型的数据\r\n");
    Queue_Init(pQueue, cArray, sizeof(char), 10);
    printf("初始化Queue值。\r\n");
    Queue_Add(pQueue, "ABCDEFGHIJ", 10);
    printf("当前元数个数：%d\r\n", pQueue->Counter);
    index = 0;
    while (Queue_GetOne(pQueue, &cValue))
    {
        index++;
        printf("第%d个元素cValue = %c\r\n", index, cValue);
        if (index == 5)
        {
            printf("插入3个值。\r\n");
            cValue = 'X';
            Queue_AddOne(pQueue, &cValue);

            cValue = 'Y';
            Queue_AddOne(pQueue, &cValue);

            cValue = 'Z';
            Queue_AddOne(pQueue, &cValue);
        }
    }
}
*/
