# include "struct_base.h"

typedef struct tickeT_t
{
	int ticketID;
	int userID;
	char flightID;
	char passengerName[32];
	int passengerCount;
	int seatNO;
}ticket;


typedef struct flighT_t
{
	int flightID[32];
	char source[64];
	char destination[64];
	DOJ_t DOJ;
	int number_of_seats;
	int seats_available;
	Time departure_time;
	Time arrival_time;
	double ticket_price;
}flight;
