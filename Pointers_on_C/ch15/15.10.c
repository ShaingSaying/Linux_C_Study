#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sum(FILE *input, FILE *output)
{
    unsigned int check = 0;
    int value;
    while((value = fgetc(input)) != EOF)
        check += value;

    fprintf(output, "%d",check);
}

int main(int ac, char **av)
{
    if(ac <= 1)
        sum(stdin, stdout);
    else if(strcmp(av[1], "-f") == 0){
        if(ac == 2){
            printf("Illegal, it is not input filename\n");
            return 1;
        }else{
            int i;
            FILE *input, *output;
            for(i = 2; i < ac; i++){
                char filename[256];
                strcpy(filename, av[i]);
                strncat(filename, ".cks", 4);
                output = fopen(filename, "w");
                input = fopen(av[i], "r");

                if(output == NULL){
                    perror("input");
                    exit(EXIT_FAILURE);
                }
                sum(input, output);
                fclose(input);
                fclose(output);
            }
        }
    }else{
        int i;
        FILE *input;
        for(i = 1; i < ac; i++){
            input = fopen(av[i], "r");
            if(input == NULL){
                perror("input");
                exit(0);
            }
            sum(input, stdout);
            fclose(input);
        }
    }
    return 0;
}