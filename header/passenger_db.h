#pragma once

/*struct admin_
{
char adminUserId[120];
char AdminPassword[120];
int loginStatus;
}__attribute__((__packed__)); 

typedef struct admin_ admin;
*/

typedef struct _DOJ_t
{
	int day;	
	int year;
	int month;

}DOJ_t;


typedef struct Time_
{
	int hour;	
	int minute;
}Time;

struct passenger_
{
	int passengerId;
	char passengerName[128];
	char phoneNumber[16];
	char gender;
	char email[128];
	char address[256];
	DOJ_t DOJ;

  	
}__attribute__((__packed__));

typedef struct passenger_ passenger;



void add_passenger_intoFile(passenger *passengerAddr);
void passenger_bdb_readall(passenger *passengerList,int *passengerCount);
int passenger_bdb_count();
void passenger_bdb_readById(passenger* passengerAddr, int passengerIdAddr);
