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

struct passenger_
{
	char passengerName[128];
	char phoneNumber[16];
	char gender;
	char email[128];
	char address[256];
	DOJ_t DOJ;

  	
}__attribute__((__packed__));

typedef struct passenger_ passenger;



