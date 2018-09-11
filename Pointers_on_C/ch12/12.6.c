#include<stdlib.h>
#include<stdio.h>
#include "doubly_linked_list_node.h"

#define FALSE 0
#define TRUE 1

int dll_remove(struct NODE *rootp, struct NODE *delete)
{
	NODE *this;
	
	for(this=rootp->fwd;this!=NULL;this=this->fwd)
		if(this==delete)
			break;

	if(this==delete)
	{
		if(this->bwd==NULL)
			rootp->fwd=this->fwd;
		else
			this->bwd->fwd=this->fwd;
		
		if(this->fwd==NULL)
			rootp->bwd=this->bwd;
		else
			this->fwd-bwd=this->bwd;

		free(this);
		return TRUE;
	}
	else
		return FALSE;
}
