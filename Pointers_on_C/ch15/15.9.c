#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE 511 
#define NAME 256  
#define BUFFERSIZE ((LINE)+(NAME)+3) /*line + filename + : + two of ' '*/

void Lookfor(char *string, char *filename, int isstdin)
{
    char buffer[BUFFERSIZE];
    FILE *file;
    char line[LINE];
    int len;
    if(isstdin == 1)
        file = stdin;
    else
        file = fopen(filename,"rb");

    while(fgets(line, LINE, file) != NULL){
        len = strlen(line);
        buffer[0] = '\0';
        if(strstr(line, string) != NULL){
            if(isstdin == 0){
                strcat(buffer, filename);
                strcat(buffer, " : ");
            }
            strcat(buffer, line);
            printf("%s",buffer);
        }
    }
    fclose(file);
}

int main(int ac, char **av)
{
    char string[LINE];
    int i;
    if(ac <= 1){
        printf("not argument!");
        return 1;
    }

    strcpy(string, av[1]);
    if(ac == 2)
        Lookfor(string, NULL, 1);
    else
        for(i = 2; i < ac; i++)
            Lookfor(string, av[i], 0);
    
    return 0;
}

#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 512

void search(char *filename, FILE *stream, char *string)
{
    char buffer[BUFFERSIZE];

    while(fgets(buffer, BUFFER_SIZE, stream) != NULL){
        if(strstr(buffer, string) != NULL){
            if(filename != NULL)
                printf("%s : ", filename);
            fputs(buffer, stdout);
        }
    }
}

int main(int ac, char **av)
{
    char *string;
    if(ac <= 1){
        printf(stderr,"Usage: fgrep string file ...\n");
        exit(EXIT_FAILURE);
    }

    string = *++av;

    if(ac <= 2)
        search(NULL, stdin, string);
    else{
        while(*++av != NULL){
            FILE *stream;
            stream = fopen(*av, "r");
            if(stream == NULL)
                perror(*av);
            else{
                search(*av, stream, string);
                fclose(stream);
            }
        }
    }
    return EXIT_SUCCESS;
}
#endif