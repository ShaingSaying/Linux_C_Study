void print_ledger(int arg)
{
#ifdef OPTION_LONG
    #define OK 1
    print_ledger_long(arg);
#endif

#ifdef OPTION_DETAILED
    #define OK 1
    print_ledger_detailed(arg);
#endif

#ifndef OK 
    print_ledger_default(arg);
#endif
}