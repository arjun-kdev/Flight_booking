#include<stdio.h>
#include "passenger_db.h"

typedef struct tickeT_t
{
	int ticketID;
	//int userID;
	char passengerID[5][16];
	char flightID;
	char passengerName[5][32];
	int passengerCount;
	int seatNO[5];
}ticket;


typedef struct flighT_t
{
	char flightID[32];
	char source[64];
	char destination[64];
	DOJ_t DOJ;
	int number_of_seats;
	int seats_available;
	Time departure_time;
	Time arrival_time;
	double ticket_price;
}flight;


void add_tickets_intoFile(ticket *ticketAddr);
void ticket_bdb_readall(ticket *ticketList,int *ticketCount);
int ticket_bdb_count();
void ticket_bdb_readById(ticket* ticketAddr, int ticketIdAddr);
void ticket_db_delete(int seatNO);

void flight_bdb_readById(flight* flightAddr, char flightIdAddr[]);
int flight_bdb_count();
void flight_bdb_readall(flight *flightList,int *flightCount);
void add_Flight_intoFile(flight *flightAddr);