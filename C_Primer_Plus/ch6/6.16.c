#include<stdio.h>
#define MONEY 100
#define DANLI 0.1
#define FULI 0.05
int main()
{
	int year=1;
	float Daphne,Deirdre,li=0;
	Deirdre=MONEY;
	Daphne=MONEY;
	while(Deirdre<=Daphne)
	{
		Daphne-=li;
		li+=MONEY*DANLI;
		Daphne+=li;
		Deirdre*=(1+FULI);
		year++;
	}
	//Daphne+=MONEY;
	//Deirdre*=MONEY;
	printf("%d years Deirdre have %f and Daphne have %f money\n",year,Deirdre,Daphne);
	return 0;
}
