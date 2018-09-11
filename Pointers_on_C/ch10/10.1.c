typedef struct _PHONE_NUMBER_
{
	short area;
	short exchange;
	short station;
}PHONE_NUMBER;

typedef struct _LONG_DISTANCE_BILL_
{
	short month;
	short day;
	short year;
	int time;
	PHONE_NUMBER called;
	PHONE_NUMBER calling;
	PHONE_NUMBER billed;
}
