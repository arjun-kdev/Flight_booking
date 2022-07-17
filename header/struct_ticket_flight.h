

typedef struct tickeT_t
{
	int 	ticketID;
	int 	userID;
	char 	flightID;
	char 	passengerName[32];
	int 	passengerCount;
	int 	seatNO;
}ticket;


typedef struct flighT_t
{
	char 	flightID[32];
	char 	starting_from[64];
	char 	destination[64];
    char 	day_of_journey[16];
    int  	number_of_seats[256];
    int  	seats_available;
    char 	departure_time[16];
    char 	arraival_time[16];
    double 	ticket_price;
}flight;