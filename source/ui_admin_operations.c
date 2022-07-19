#include <stdio.h>
#include <stdlib.h>
#include "struct_base.h"
#include "ui_passenger.h"
#include "ui_admin.h"
#include "tickets.h"
#include "flights.h"
#include "struct_ticket_flight.h"

void createFlight()
{
	int count = flight_bdb_count();
	count += 1;

	flight flightObject = {};
	// flightObject.flightID = count;
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
	scanf("%d", flightObject.number_of_seats);
	printf("\n");
	printf("Enter available seats : ");
	scanf("%d", flightObject.seats_available);
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
	scanf("%lf", flightObject.number_of_seats);
	add_Flight_intoFile(flightObject);

	// create file operation call comes here//
}
void updateFlight()
{

	flight flightObject = {};
	int id;
	printf("Enter flight id to update:");
	scanf("%d", &id);

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
	scanf("%d", flightObject.number_of_seats);
	printf("\n");
	printf("Enter new available seats : ");
	scanf("%d", flightObject.seats_available);
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
	scanf("%lf", flightObject.ticket_price);
	// add_Flight_intoFile(flightObject);

	// update file operation call comes here//
}
void ShowAllflights()
{

	flight *flightAddr = NULL;
	int noOfflightObject = 0;
	noOfflightObject = scheme_bdb_count();
	flightAddr = (flight *)malloc(10 * sizeof(flight));

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
	printf("\tFlight ID :%d", flightObject.flightID);
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
	printf("\tTicket price :%d", flightObject.ticket_price);
}

void approveTicket()
{
	char ch;
	printf("\n\tSelect A :  Approve Ticket \n\tSelect C :  Reject Ticket ");
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
void verifyLogin(){

}
void viewAllTicketDetails(){

	ticket *ticketAddr = NULL;
	int noOfTicketsObject = 0;
	noOfTicketsObject = scheme_bdb_count();
	ticketAddr = (ticket *)malloc(10 * sizeof(ticket));

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
	printf("\tTicket ID :%s", ticketObject.ticketID);
	printf("\n");
	printf("\tSeat No :%s", ticketObject.seatNO);
	printf("\n");
	printf("\t No.of passengers :%d", ticketObject.passengerCount);
	printf("\n");
	printf("\tPassenger Name(s) :%d", ticketObject.passengerName);
	printf("\n");
	printf("\tUser Id :%d", ticketObject.userID);
}



void viewAllTicketByPassenger(){

	ticket *ticketAddr = NULL;
	int noOfTicketsObject = 0;
	noOfTicketsObject = scheme_bdb_count();
	ticketAddr = (ticket *)malloc(10 * sizeof(ticket));
	getIdOfloggedUser();
	ticket_bdb_readAllTicketsFromUser(ticketAddr, &noOfTicketsObject);
	displayAllTicketObjectsFromUser(ticketAddr, noOfTicketsObject);
	free(ticketAddr);
	ticketAddr = NULL;
}
void getIdOfloggedUser(){

}

void viewAllTicketDetails(){

}


void viewAllTicketDetailsFromSource(){

}


void viewAllTicketDetailsTODestination(){

}




int main()
{
	return EXIT_SUCCESS;
}
