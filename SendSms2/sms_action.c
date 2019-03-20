#include "sms_action.h"

stSmsActHead *CreatSmsActHead()
{
    stSmsActHead *head;
    head = (stSmsActHead*)malloc(sizeof(stSmsActHead));
    if(NULL == head)
    {
        printf("[ERR]Line[%d]malloc failed!\n",__LINE__);
        return NULL;
    }
    head->iListLength = 0;
    head->next = NULL;
    return head;
}

int isEmpty(stSmsActHead *head)
{
    if(head->iListLength == 0)
        return EMPTY;
    return NOT;
}
int isFull(stSmsActHead *head)
{
    if(head->iListLength == head->icapacity)
        return FULL;
    return NOT;
}