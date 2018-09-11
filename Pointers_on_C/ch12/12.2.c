#include "singly_linked_list_node.h"
#include <stdio.h>

struct NODE *sll_find(struct NODE *first, int desired_value)
{
	for(;first!=NULL;first=first->link)
		if(first->value==desired_value)
			return first;
	return NULL;
}
