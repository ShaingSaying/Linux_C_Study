#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0

typedef struct _WORD_{
	char *word;
	struct _WORD_ *next;
} Word;

typedef struct _LIST_{
	char letter;
	struct _LIST_ *next;
	Word *word_list;
} List;

int concordance_insert(List **listp, char *the_word)
{
	int first_char;
	List *current_list;
	Word *current_word;
	Word **wordp;
	int comparison;
	Word *new_word;
	
	first_char=*the_word;
	if(!islower(first_char))
		return FALSE;
	
	while((current_list=*listp)!=NULL && current_list->letter<first_char)
		listp=&current_list->next;

	if(current_list==NULL||current_list->letter>first_char)
	{
		List *new_list;
		new_list=(List *)malloc(sizeof(List));
		if(new_list==NULL)
			return FALSE;
		new_list->letter=first_char;
		new_list->word_list=NULL;
		new_list->next=current_list;
		*listp=new_list;
		current_list=new_list;
	}
	
	wordp=&current_list->word_list;
	while((current_word=*wordp)!=NULL)
	{
		comparison=strcmp(current_word->word,the_word);
		if(comparison>=0)
			break;
		wordp=&current_word->next;
	}

	if(current_word!=NULL&&comparison==0)
		return FALSE;

	new_word=(Word*)malloc(sizeof(Word));
	if(new_word==NULL)
		return FALSE;
	
	new_word->word=malloc(strlen(the_word)+1);
	if(new_word->word==NULL)
		return;

	strcpy(new_word->word,the_word);
	
	new_word->next=current_word;
	*wordp=new_word;
	
	return TRUE;
}
