#include <stdio.h>
#include "passenger_db.h"
#include "ticket_flight_db.h"
#include <stdlib.h>
#include <string.h>
#include "util.h"

void flight_count_bdb(int *, char *, char *, char *);
void flight_bdb_readall_specific_date(flight *, char *, char *, char *);
void ticket_db_findticket(ticket *, char *, char *, char *);

//#include "enums.h"
typedef struct _DOJ11
{
	int day;
	int year;
	int month;

} DOJ11;

void passenger_details()
{
	passenger p1;
	int N;
	printf("Enter Number of passenger:");
	scanf("%d", &N);
	// printf("enter the ticket id:");
	// scanf("%d",&p1.ticketID);

	for (int i = 0; i < N; i++)
	{

		printf("Name:");
		scanf("%s", p1.passengerName);
		printf("PhoneNumber:");
		scanf("%s", p1.phoneNumber);
		printf("Gender:");
		scanf("%s", &p1.gender);
		printf("Email:");
		scanf("%s", p1.email);
		printf("Address:");
		scanf("%s", p1.address);
	}
	add_passenger_intoFile(&p1);
}

void book_ticket()
{
	// flight ft;
	DOJ11 D1;

	char source1[32], dest1[32];
	int count = 0;
	char dateOfJourney[16];

	printf("source place :");
	scanf("%s", source1);
	printf("Destination place:");
	scanf("%s", dest1);

	printf("Enter date of journey in dd-MM-yyyy format : ");
	scanf("%s", dateOfJourney);
	sscanf(dateOfJourney, "%02d-%02d-%04d",
		   &D1.day,
		   &D1.month,
		   &D1.year);

	flight_count_bdb(&count, source1, dest1, dateOfJourney);
	flight *ft = (flight *)malloc(count * sizeof(flight));
	flight_bdb_readall_specific_date(ft, source1, dest1, dateOfJourney);

	for (int i = 0; i < count; i++)
	{
		printf(
			"FLightId: %s\n", ft[i].flightID,
			"source: %s\n", ft[i].source,
			"Destination: %s\n", ft[i].destination,
			"Number of seats: %d\n", ft[i].number_of_seats,
			"seats available: %d\n", ft[i].seats_available,
			"ticket_price: %lf\n", ft[i].flightID,
			"Date of journey:"
			"%02d-%02d-%04d",
			ft[i].DOJ.day, ft[i].DOJ.month, ft[i].DOJ.year,
			"departure time:"
			"%02d:%02d",
			ft[i].departure_time.hour, ft[i].departure_time.minute);
	}

	printf("provide the details:");
	passenger_details();
}

void delete_tickets()

{
	int seat_no, ticketid;
	ticket *t1;
	int count = 0;
	printf("Enter the ticketID :");
	scanf("%d", &ticketid);
	printf("Enter the seatno to cancel the ticket:");
	scanf("%d", &seat_no);

	ticket_db_findticket(t1, count, ticketid, seat_no);

	char ch;
	printf("Are you sure you want to delete!!! If yes press Y else N :");
	clear_buffer();
	scanf("%c", &ch);
	if ('y' == ch || 'Y' == ch)
	{
		ticket_db_delete_ticket(ticketid, seat_no);
		printf("ticket is cancelled successfully.\n");
	}
	else
	{
		printf("Theere id no ticket in this ID");
	}
}

void view_ticket_details()
{

	ticket tkt3[1000];
	int count = 0;
	ticket_bdb_readall(tkt3, &count);

	if (count == 0)
	{
		printf("No ticket available!!!");
	}
	else
	{
		printf("\n\n\t\t\t\ttickets\n\n\n");
		printf("\ticketID\tAddharId\tPassenger name\tflightID\tpassengerCount\n\tSeatno");
		printf("------------------------------------------------------------------------------------------------------------------\n\n");
		for (int I = 0; I < count; I++)
		{
			printf("\t%d", tkt3[I].ticketID);
			printf("\t\t%s", &tkt3[I].AdharID);
			printf("\t\t%s", tkt3[I].passengerName);
			printf("\t\t%s", &tkt3[I].flightID);
			printf("\t\t%d", tkt3[I].passengerCount);
			printf("\t\t%d", tkt3[I].seatNO);
		}
	}
}

int main()
{
	int menu;

	do
	{
		printf("\n\nEnter your choice\n");
		printf("\t1-BOOK TICKETS \t2-CANCELLATION OF TICKETS\t3-VIEW TICKET DETAILS\t0-Exit\n");
		printf("Your Choice:");
		scanf("%d", &menu);
		printf("\n");
		if (1 == menu)
		{
			book_ticket();
		}
		else if (2 == menu)
		{
			delete_tickets();
		}
		else if (3 == menu)
		{
			view_ticket_details();
		}
		else
		{
			printf("Enter the Correct choice");
		}
	} while ((1 <= menu) && (menu <= 3));
	return EXIT_SUCCESS;
}
