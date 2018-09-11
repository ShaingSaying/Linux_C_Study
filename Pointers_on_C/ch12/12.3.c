#include<stdlib.h>
#include<stdio.h>
#include "doubly_linked_list_node.h"
int dll_insert(node **frontp, node **rearp, int value)
{
	node **fwdp;
	node *next;
	node *newnode;
	
	fwdp=frontp;
	while((next=*fwdp)!=NULL)
	{
		if(next->value==value)
			return 0;
		if(next->value>value)
			break;
		fwdp=&next->fwd;
	}
	
	newnode=(node *)malloc(sizeof(node));
	if(newnode==NULL)
		return -1;
	newnode->value=value;

	newnode->fwd=next;
	*fwdp=newnode;
	if(fwdp!=frontp)
		if(next!=NULL)
			newnode->bwd=next->bwd;
		else
			newnode->bwd=*rearp;
	else
		newnode->bwd=NULL;
	if(next!=NULL)
		next->bwd=newnode;
	else
		*rearp=newnode;
	return 1;
}
