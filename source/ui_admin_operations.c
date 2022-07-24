#include <stdio.h>
#include <stdlib.h>
#include "ui_passenger.h"
#include "ui_admin.h"
#include "passenger_db.h"
#include "tickets.h"
#include "flights.h"
#include "ticket_flight_db.h"

void displayFlightObjectFromSourceToDest(flight, int);
void ShowAllflights();
void displayAllFlightObjects(flight *, int);
void displayFlightObject(flight, int);
void displayAllTicketObjects(ticket *, int);
void displayTicketObject(ticket, int);
void update_flight_bdb_update_intoFile(flight flightAddr, char flightId[]);
int admin_app();

void createFlight()
{

	flight flightObject = {};
	printf("Enter flight ID : ");
	scanf("%s", flightObject.flightID);
	printf("Enter source : ");
	scanf("%s", flightObject.source);
	printf("\n");
	printf("Enter destination : ");
	scanf("%s", flightObject.destination);
	printf("\n");
	char dateOfJourney[20];
	printf("Enter date of journey in dd-MM-yyyy format : ");
	scanf("%s", dateOfJourney);
	sscanf(dateOfJourney, "%02d-%02d-%04d",
		   &flightObject.DOJ.day,
		   &flightObject.DOJ.month,
		   &flightObject.DOJ.year);
	printf("\n");
	printf("Enter total no.of seats : ");
	scanf("%d", &flightObject.number_of_seats);
	printf("\n");
	printf("Enter available seats : ");
	scanf("%d", &flightObject.seats_available);
	printf("\n");
	char flightDepartureTime[20];
	printf("Enter time of departure in HH:MM format : ");
	scanf("%s", flightDepartureTime);
	sscanf(dateOfJourney, "%02d:%02d",
		   &flightObject.departure_time.hour,
		   &flightObject.departure_time.minute);
	printf("\n");
	char flightArrivalTime[20];
	printf("Enter time of arrival in HH:MM format : ");
	scanf("%s", flightArrivalTime);
	sscanf(dateOfJourney, "%02d:%02d",
		   &flightObject.arrival_time.hour,
		   &flightObject.arrival_time.minute);
	printf("\n");
	printf("Enter ticket fare : ");
	scanf("%lf", &flightObject.ticket_price);
	add_Flight_intoFile(&flightObject);

	// create file operation call comes here//
}
void updateFlight()
{

	flight flightObject = {};
	char id[32];
	printf("Enter flight id to update:");
	scanf("%s", id);

	flight_bdb_readById(&flightObject, id);
	printf("Enter new source : ");
	scanf("%s", flightObject.source);
	printf("\n");
	printf("Enter new destination : ");
	scanf("%s", flightObject.destination);
	printf("\n");
	char dateOfJourney[20];
	printf("Enter updated date of journey in dd-MM-yyyy format : ");
	scanf("%s", dateOfJourney);
	sscanf(dateOfJourney, "%02d-%02d-%04d",
		   &flightObject.DOJ.day,
		   &flightObject.DOJ.month,
		   &flightObject.DOJ.year);
	printf("\n");
	printf("Enter updated total no.of seats : ");
	scanf("%d", &flightObject.number_of_seats);
	printf("\n");
	printf("Enter new available seats : ");
	scanf("%d", &flightObject.seats_available);
	printf("\n");
	char flightDepartureTime[20];
	printf("Enter updated time of departure in HH:MM format : ");
	scanf("%s", flightDepartureTime);
	sscanf(dateOfJourney, "%02d:%02d",
		   &flightObject.departure_time.hour,
		   &flightObject.departure_time.minute);
	printf("\n");
	char flightArrivalTime[20];
	printf("Enter updated time of arrival in HH:MM format : ");
	scanf("%s", flightArrivalTime);
	sscanf(dateOfJourney, "%02d:%02d",
		   &flightObject.arrival_time.hour,
		   &flightObject.arrival_time.minute);
	printf("\n");
	printf("Enter new ticket fare : ");
	scanf("%lf", &flightObject.ticket_price);
	update_flight_bdb_update_intoFile(flightObject,id);

	// update file operation call comes here//
}
void ShowAllflights()
{

	flight *flightAddr = NULL;
	int noOfflightObject = 0;
	noOfflightObject = flight_bdb_count();
	 if(noOfflightObject  == -1)
    {
        printf("\n\tNo flights available..!!\n");
        return ;
    }
	flightAddr = (flight *)malloc(noOfflightObject * sizeof(flight));

	flight_bdb_readall(flightAddr, &noOfflightObject);
	displayAllFlightObjects(flightAddr, noOfflightObject);
	free(flightAddr);
	flightAddr = NULL;
}
void displayAllFlightObjects(flight *flightAddr, int objectCount)
{
	for (int i = 0; i < objectCount; i++)
	{
		displayFlightObject(flightAddr[i], i);
	}
}
void displayFlightObject(flight flightObject, int Index)
{
	printf("\n %d)\n", Index + 1);
	printf("\tFlight ID :%s", flightObject.flightID);
	printf("\n");
	printf("\tSource :%s", flightObject.source);
	printf("\n");
	printf("\tDestination :%s", flightObject.destination);
	printf("\n");
	printf("\tFly Date : ");
	printf("%02d-%02d-%04d",
		   flightObject.DOJ.day,
		   flightObject.DOJ.month,
		   flightObject.DOJ.year);
	printf("\n");
	printf("\tTotal no.of seats :%d", flightObject.number_of_seats);
	printf("\n");
	printf("\tAvailable Seats :%d", flightObject.seats_available);
	printf("\n");
	printf("\tArrival Time : ");
	printf("%02d:%02d",
		   flightObject.arrival_time.hour,
		   flightObject.arrival_time.minute);
	printf("\n");
	printf("\tDeparture Time : ");
	printf("%02d:%02d",
		   flightObject.departure_time.hour,
		   flightObject.departure_time.minute);
	printf("\n");
	printf("\tTicket price :%f", flightObject.ticket_price);
}

void approveTicket()
{
	char ch;
	printf("\n\tSelect A :  Approve Ticket \n\tSelect R :  Reject Ticket ");
	scanf(" %c", &ch);
	if ('a' == ch || 'A' == ch)
	{
		printf("Ticket approved..!!");
	}
	else if ('r' == ch || 'R' == ch)
	{
		printf("Ticket rejected..!!");
	}
	else
	{
		printf("Enter valid option..!!");
	}
}
/*void verifyLogin()
{
}*/
void viewAllTicketDetails()
{

	ticket *ticketAddr = NULL;
	int noOfTicketsObject = 0;
	noOfTicketsObject = ticket_bdb_count();
	 if(noOfTicketsObject  == -1)
    {
        printf("\n\tNo tickets booked\n");
        return ;
    }
	ticketAddr = (ticket *)malloc(noOfTicketsObject * sizeof(ticket));

	ticket_bdb_readall(ticketAddr, &noOfTicketsObject);
	displayAllTicketObjects(ticketAddr, noOfTicketsObject);
	free(ticketAddr);
	ticketAddr = NULL;
}
void displayAllTicketObjects(ticket *ticketAddr, int objectCount)
{
	for (int i = 0; i < objectCount; i++)
	{
		displayTicketObject(ticketAddr[i], i);
	}
}
void displayTicketObject(ticket ticketObject, int Index)
{
	printf("\n %d)\n", Index + 1);
	printf("\tFlight ID :%d", ticketObject.flightID);
	printf("\n");
	printf("\tTicket ID :%d", ticketObject.ticketID);
	printf("\n");
	printf("\tSeat No :%d", ticketObject.seatNO);
	printf("\n");
	printf("\t No.of passengers :%d", ticketObject.passengerCount);
	printf("\n");
	printf("\tPassenger Name(s) :%s", ticketObject.passengerName);
	printf("\n");
	// printf("\tUser Id :%d", ticketObject.userID);
}
void getIdOfloggedUser()
{
}

void deleteFlight()
{
}
void viewAccomodationDetails()
{
}
void displayAllFlightsFromSourceToDestination(char source[], char dest[])
{
	flight flights[256] = {};
	int flightFound = flight_bdb_readBySourceDest(flights, source, dest);
	if (flightFound == 1)
	{
		// print details
	}
}
void displayAllFlightObjectsFromSourceToDest(flight *flightAddr, int flightObjectCount)
{
	for (int i = 0; i < flightObjectCount; i++)
	{
		displayFlightObjectFromSourceToDest(flightAddr[i], i);
	}
}
void displayFlightObjectFromSourceToDest(flight flightObject, int Index)
{
	printf("\n %d)\n", Index + 1);
	printf("\tFlight ID :%s", flightObject.flightID);
	printf("\n");
	printf("\tSource :%s", flightObject.source);
	printf("\n");
	printf("\tDestination :%s", flightObject.destination);
	printf("\n");
	printf("\tFly Date : ");
	printf("%02d-%02d-%04d",
		   flightObject.DOJ.day,
		   flightObject.DOJ.month,
		   flightObject.DOJ.year);
	printf("\n");
	printf("\tTotal no.of seats :%d", flightObject.number_of_seats);
	printf("\n");
	printf("\tAvailable Seats :%d", flightObject.seats_available);
	printf("\n");
	printf("\tArrival Time : ");
	printf("%02d:%02d",
		   flightObject.arrival_time.hour,
		   flightObject.arrival_time.minute);
	printf("\n");
	printf("\tDeparture Time : ");
	printf("%02d:%02d",
		   flightObject.departure_time.hour,
		   flightObject.departure_time.minute);
	printf("\n");
	printf("\tTicket price :%lf", flightObject.ticket_price);
}

int admin_app()
{
	int menu;
	do
	{
		printf("\n\tEnter Choice : \n\n\t1=>Create flight \n\t2=>Display All flights");
		printf("\n\t3=>Update flight\n\t4=>Show all tickets\n\t5=>Show Flights from a source to destination\n\t0=>exit : ");
		scanf("%d", &menu);

		printf("\n\n\n\n");
		if (menu == 1)
		{
			createFlight();
		}
		else if (menu == 2)
		{
			ShowAllflights();
		}
		else if (menu == 3)
		{
			updateFlight();
		}
		else if (menu == 4)
		{
			viewAllTicketDetails();
		}
		else if (menu == 5)
		{
			printf("\n\n\t******Enter source and destination details *******\n\n");
			char source[40], dest[40];
			printf("\n\tsource :");
			scanf("%s", source);
			printf("\n\tdestination :");
			scanf("%s", dest);
			displayAllFlightsFromSourceToDestination(source, dest);
		}
	} while (menu == 1 || menu == 2 || menu == 3 || menu == 4 || menu == 5);

	return EXIT_SUCCESS;
}
