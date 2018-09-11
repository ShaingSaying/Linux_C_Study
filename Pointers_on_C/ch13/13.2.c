#include <stdio.h>
#include "node.h"

void sll_taversal(Node *root, void (*trav)(Node *))
{
    while(root!=NULL)
    {
        trav(root);
        root=root->link;
    }
}