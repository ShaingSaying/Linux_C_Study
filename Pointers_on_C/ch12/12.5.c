#include<stdio.h>
#include "singly_linked_list_node.h"

//删除节点的指针可以使函数和存储在链表中的类型无关，如果不知道哪个节点包含了要删除的值，我们首先必须对它进行查找
int sll_remove(struct NODE **rootp, struct NODE *node)
{
	NODE *p;
	while((p=*rootp)!=NULL)
	{
		if(p==node)
		{
			*rootp=p->link;
			free(node);
			return 1;
		}
		rootp=&p->link;
	}
	return 0;
}
