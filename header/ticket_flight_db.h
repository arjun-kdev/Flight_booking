# include "passenger_db.h"

typedef struct tickeT_t
{
	char ticketID;
	char AdharID;
	char flightID;
	char passengerName[32];
	int passengerCount;
	int seatNO;
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
 void ticket_db_findticket( ticket* val, int* count, int ticketid, int seatno);
 void ticket_db_delete_ticket(int ticketid, int seatno);
 void flight_bdb_readall12(flight *flt1,int *count1, char *flightid);
 int ticket_bdb_count();

 
void flight_bdb_readById(flight* flightAddr, char flightIdAddr[]);
int flight_bdb_count();
void flight_bdb_readall(flight *flightList,int *flightCount);
void add_Flight_intoFile(flight *flightAddr);
void flight_count_bdb(int *flightCount, char* srcAddr, char* destAddr,char* doj);
void flight_bdb_readall_specific_date(flight *flightList, char* srcAddr, char* destAddr, char* doj);
int flight_bdb_readBySourceDest(flight *flightAddr, char source[], char dest[]);



