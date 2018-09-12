swap(char *i, char *j, int recsize)
{
    char x;
    while(recsize-->0)
    {
        x=*i;
        *i++=*j;
        *j++=x;
    }
}

void sort(char *base, int nel, int recsize, int (*comp)(char *, char *))
{
    reg char *i;
    reg char *j;
    reg char *last;

    last = base + (nel-1)*recsize;
    for(i=base;i<last;i+=recsize)
        for(j=i+recsize;j<=last;j+=recsize)
            if(comp(i,j)>0)
                swap(i,j,recsize)
}