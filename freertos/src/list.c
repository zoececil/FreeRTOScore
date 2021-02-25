#include "stdlib.h"
#include "list.h"   

void vListInitialiseItem( ListItem_t * const pxItem )
{
     /* 初始化该节点所在链表为空 */
    pxItem->pvContainer = NULL;
}
void vListInitialise(List_t * const pxList)
{
    /*链表根节点初始化*/
    pxList->pxIndex = (ListItem_t * )&(pxList->xListEnd);
    pxList->xListEnd.xItemValue = portMAX_DELAY;
    pxList->xListEnd.pxNext = (ListItem_t * )&(pxList->xListEnd);
    pxList->xListEnd.pxPrevious = (ListItem_t * )&(pxList->xListEnd);
    pxList->uxNumberOfItems = (UBaseType_t)0U;
}
void vListInsertEnd(List_t * const pxList,ListItem_t * const pxNewListItem)
{
    /*将节点插入链表尾部*/
    ListItem_t * const pxIndex = pxList->pxIndex;

    pxNewListItem->pxNext = pxIndex;
    pxNewListItem->pxPrevious = pxIndex->pxPrevious;
    pxIndex->pxPrevious->pxNext = pxNewListItem;
    pxIndex->pxPrevious = pxNewListItem;

    pxNewListItem->pvContainer = (void * )pxList;
    (pxList->uxNumberOfItems)++; 
}
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem)
{
    /*将节点按照升序排列插入到链表*/
    ListItem_t * pxIterator;

    const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;

    if(xValueOfInsertion == portMAX_DELAY)
    {
        pxIterator = pxList->xListEnd.pxPrevious;
    }
    else
    {
        for(pxIterator = (ListItem_t * )&(pxList->xListEnd);
            pxIterator->pxNext->xItemValue <= xValueOfInsertion;
            pxIterator = pxIterator->pxNext)
            {
                /*不做任何事*/
            }
    }
    pxNewListItem->pxNext = pxIterator->pxNext;
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;
    pxNewListItem->pxPrevious = pxIterator;
    pxIterator->pxNext = pxNewListItem;

    pxNewListItem->pvContainer = (void * )pxList;
    (pxList->uxNumberOfItems)++;
}
UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove)
{
    /*将节点从链表删除*/
    List_t * const pxList = (List_t * )pxItemToRemove->pvContainer;
    pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
    pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

    if(pxList->pxIndex == pxItemToRemove)
    {
        pxList->pxIndex = pxItemToRemove->pxPrevious;
    }
    pxItemToRemove->pvContainer = NULL;
    (pxList->uxNumberOfItems)--;

    return pxList->uxNumberOfItems;
}
