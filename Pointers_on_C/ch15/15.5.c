int value,total=0;

while(fgets(buf,BUFSIZE,input)!=NULL)
{
    if(sscanf(buf,"%d",&value)==1)
        total+=value;

    fputs(buf,output);
}
fprintf(output,"%d\en",total);