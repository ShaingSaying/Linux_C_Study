#include<stdio.h>
#include "singly_linked_list_node.h"

struct NODE *sll_reverse(struct NODE *current)
{
	struct NODE *previous;
	struct NODE *next;
	
	for(previous=NULL;current!=NULL;current=next)
	{
		next=current->link;
		current->link=previous;
		previous=current;
	}
	return previous;
}
