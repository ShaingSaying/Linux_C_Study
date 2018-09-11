int countnode(type *p)
{
	int count=0;
	while(p!=0)
	{
		count++;
		p=p->link;
	}
	return count;
}
