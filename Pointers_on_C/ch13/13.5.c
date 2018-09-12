#define TRUE 1
#define FALSE 0

#define NULL 0
#define NUL '\0'

enum{NONE,FLAG,ARG};

argtype(int ch, int control)
{
    while(*control!=NUL)
        if(ch==*control++)
            return *control=='+'?ARG:FLAG;
    return NONE;
}

char **do_args(int ac, reg char **av, char *control, void (*do_arg)
(int, char*), void(*illegal_arh)(int))
{
    char *argp;
    int ch;
    int skip_arg;

    while((argp=*++av)!=NULL && *argp=='-')
    {
        skip_arg=FALSE;
        while(!skip_arg&&(ch=*++argp)!=NUL)
        {
            switch(argtype(ch,control))
            {
                case FLAG:
                    (*do_arg)(ch, NULL);
                    break;
                case ARG:
                    if(*++argp!=NUL || (argp=*++av)!=NULL)
                    {
                        (*do_arg)(ch,argp);
                        skip_arg=TRUE;
                        break;
                    }
                    (*illegal_arh)(ch);
                    return av;
                case NONE:
                    (*illegal_arh)(ch);
                    break;
            }
        }
    }
    return av;
}