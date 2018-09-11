#include<stdlib.h>
#include<stdio.h>

typedef struct _NODE_
{
	int value;
	struct _NODE_ *link;
}Node;

Node *newnode(int value)
{
	Node *new;
	new=(Node *)malloc(sizeof(Node));
	if(new==NULL)
	{
		printf("malloc error\n");
	}
	new->value=value;
	return new
}

int main()
{
	Node *head;
	head=newnode(5);
	head->link=newnode(10);
	head->link->link=newnode(15);
	head->link->link->link=0;
	return 0;
}
