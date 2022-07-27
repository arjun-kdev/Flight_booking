#include <stdio.h>
#include <stdlib.h>
#include "ui_passenger.h"
#include "ui_admin.h"
#include "passenger_db.h"
#include "tickets.h"
#include "flights.h"
#include "ticket_flight_db.h"
#include "util.h"
#include "enums.h"

/**
 * @brief Method declarations.
 *
 */
void displayFlightObjectFromSourceToDest(flight, int);
void ShowAllflights();
void displayAllFlightObjects(flight *, int);
void displayFlightObject(flight, int);
void displayAllTicketObjects(ticket *, int);
void displayTicketObject(ticket, int);
void update_flight_bdb_update_intoFile(flight flightAddr, char flightId[]);
void update_flight_bdb_status(flight flightAddr, char[]);
int admin_app();
int validateStatus(char[]);
void view_seats_in_flight();
void displayAllFlightObjectsFromSourceToDest(flight *flightAddr, int flightObjectCount);

/**
 * @brief Create a Flight object
 *
 */
void createFlight()
{

	flight flightObject = {};
	printf("Enter flight ID : ");
	scanf("%s", flightObject.flightID);
	printf("\n");
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
	scanf("%d", &flightObject.total_seats);
	printf("\n");
	// printf("Enter available seats : ");
	// scanf("%d", &flightObject.seats_available);
	// printf("\n");
	char flightDepartureTime[20];
	printf("Enter time of departure in HH:MM format : ");
	scanf("%s", flightDepartureTime);
	sscanf(flightDepartureTime, "%02d:%02d",
		   &flightObject.departure_time.hour,
		   &flightObject.departure_time.minute);
	printf("\n");
	char flightArrivalTime[20];
	printf("Enter time of arrival in HH:MM format : ");
	scanf("%s", flightArrivalTime);
	sscanf(flightArrivalTime, "%02d:%02d",
		   &flightObject.arrival_time.hour,
		   &flightObject.arrival_time.minute);
	printf("\n");
	printf("Enter ticket fare : ");
	scanf("%lf", &flightObject.ticket_price);
	memset(flightObject.number_of_seats, 0, 256);
	// memset(ZEROARRAY, 0, 1024)

	for (int i = 0; i < flightObject.total_seats; i++)
	{
		flightObject.number_of_seats[i] = i + 1;
	}
	flightObject.seats_available = flightObject.total_seats;
	printf("\n");
	printf("Status (Available / Cancelled) : ");
	scanf("%s", flightObject.status);

	add_Flight_intoFile(&flightObject);

	// create file operation call comes here//
}

/**
 * @brief updating all details of a flight
 *
 */
void updateFlight()
{

	flight flightObject = {};
	char id[32];
	printf("Enter flight id to update:\n");
	scanf("%s", id);

	int found = flight_bdb_readById(&flightObject, id);

	if (found != 1)
	{
		printf("flight not found..");
		return;
	}

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
	scanf("%d", &flightObject.total_seats);
	printf("\n");
	// printf("Enter new available seats : ");
	// scanf("%d", &flightObject.seats_available);
	// printf("\n");
	char flightDepartureTime[20];
	printf("Enter updated time of departure in HH:MM format : ");
	scanf("%s", flightDepartureTime);
	sscanf(flightDepartureTime, "%02d:%02d",
		   &flightObject.departure_time.hour,
		   &flightObject.departure_time.minute);
	printf("\n");
	char flightArrivalTime[20];
	printf("Enter updated time of arrival in HH:MM format : ");
	scanf("%s", flightArrivalTime);
	sscanf(flightArrivalTime, "%02d:%02d",
		   &flightObject.arrival_time.hour,
		   &flightObject.arrival_time.minute);
	printf("\n");
	printf("Enter new ticket fare : ");
	scanf("%lf", &flightObject.ticket_price);
	memset(flightObject.number_of_seats, 0, 256);
	// memset(ZEROARRAY, 0, 1024)

	for (int i = 0; i < flightObject.total_seats; i++)
	{
		flightObject.number_of_seats[i] = i + 1;
	}
	flightObject.seats_available = flightObject.total_seats;
	printf("\n");
	printf("New Status (Available / Cancelled) : ");
	scanf("%s", flightObject.status);

	update_flight_bdb_update_intoFile(flightObject, id);

	// update file operation call comes here//
}

/**
 * @brief updating flight status
 *
 */
void updateFlightStatus()
{

	flight flightObject = {};
	char id[32];
	printf("\n\tEnter flight id to change status:\n");
	scanf("%s", id);

	int found = flight_bdb_readById(&flightObject, id);

	if (found != 1)
	{
		printf("flight not found..");
		return;
	}
	printf("\n");
	printf("\n\tNew Status (Available / Cancelled) : ");
	scanf("%s", flightObject.status);
	int valid = 0;
	valid = validateStatus(flightObject.status);
	if (valid == 1)
	{
		update_flight_bdb_status(flightObject, id);
		printf("\n\tStatus updated to %s\n", flightObject.status);
		/*if (strcmp(flightObject.status, "Cancelled") == 0)
		{
			ChangeAllTicketsToCancelled(id);
			
		}
		*/
	}
	else
	{
		printf("\nEnter valid status..!!\n\n");
	}
}
int validateStatus(char status[])
{
	if (strcmp(status, "Available") == 0 || strcmp(status, "Cancelled") == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief View seats in a flight
 *
 */
void view_seats_in_flight()
{
	flight ft;
	char flightID[16];

	printf("\nEnter Flight id to see seating : ");
	scanf("%s", flightID);

	// flight_bdb_readByServiceId(&ft,flightID,&count);
	int found = flight_bdb_readById(&ft, flightID);

	if (found)
	{
		for (int i = 0; i < ft.total_seats; i++)
		{
			if (i % 4)
			{
				printf("%4d ", ft.number_of_seats[i]);
			}
			else
			{
				printf("\n%4d ", ft.number_of_seats[i]);
			}
		}
	}
	else
	{
		printf("\n Flight is not found....\n");
	}
}

/**
 * @brief Show all flights in all routes
 *
 */
void ShowAllflights()
{

	flight *flightAddr = NULL;
	int noOfflightObject = 0;
	noOfflightObject = flight_bdb_count();
	if (noOfflightObject == -1)
	{
		printf("\n\tNo flights available..!!\n");
		return;
	}
	flightAddr = (flight *)malloc(noOfflightObject * sizeof(flight));

	flight_bdb_readall(flightAddr, &noOfflightObject);
	displayAllFlightObjects(flightAddr, noOfflightObject);
	free(flightAddr);
	flightAddr = NULL;
}
/*
void ChangeAllTicketsToCancelled(char id[])
{
	// 1.No need to ask flight id here. This function is calling inside-
	//  updateflightstatus method when option changing to cancelled.
	// 2.Get all tickets for flight id.
	// 3.loop all tickets and update status to Cancelled.
}
*/

/*void ticket_bdb_readallByFlightId(ticket *ticketList,int *ticketCount)
  { 
   int I=0;
    ticket tkt;
    
    //char fileName[45];
    //strcpy(fileName,getFilePath(TICKET_DB_PATH));
    char fileName[] = "ticket.dat";

    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
      //  printf("FILE ERROR.\n");
        return;
    }
    while(fread(&tkt,1,sizeof(ticket),in)){
       ticketList[I] = tkt;
       I++;
    }
    *ticketCount = I;
    fclose(in);
}
*/
/**
 * @brief Part of showAllFlights method
 *
 * @param flightAddr
 * @param objectCount
 */
void displayAllFlightObjects(flight *flightAddr, int objectCount)
{
	for (int i = 0; i < objectCount; i++)
	{
		displayFlightObject(flightAddr[i], i);
	}
}

/**
 * @brief part of showAllFlights Method.
 *
 * @param flightObject
 * @param Index
 */
void displayFlightObject(flight flightObject, int Index)
{
	printf("\n\t %d)\n", Index + 1);
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
	printf("\tTotal no.of seats :%d", flightObject.total_seats);
	printf("\n");
	printf("\tAvailable Seats :%d", flightObject.seats_available);
	printf("\n");
	printf("\tDeparture Time : ");
	printf("%02d:%02d",
		   flightObject.departure_time.hour,
		   flightObject.departure_time.minute);
	printf("\n");
	printf("\tArrival Time : ");
	printf("%02d:%02d",
		   flightObject.arrival_time.hour,
		   flightObject.arrival_time.minute);
	printf("\n");
	printf("\tTicket price :%0.2f", flightObject.ticket_price);
	printf("\n");
	printf("\tFlight Status :%s", flightObject.status);
	printf("\n\n");
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
	if (noOfTicketsObject == -1)
	{
		printf("\n\tNo tickets booked\n");
		return;
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
	flight flightObj;
	int isRecordFound = 0;
	char id[32];
	printf("Enter flight id to delete:");
	scanf("%s", id);

	int found = flight_bdb_readById(&flightObj, id);

	if (found != 1)
	{
		printf("flight not found..");
		return;
	}
	char ch;
	printf("\n\tDo you want to delete flight (y/n): ");
	scanf(" %c", &ch);
	if ('y' == ch || 'Y' == ch)
	{
		flight_bdb_delete(id);
		printf("\n\tflight deleted !!\n");
		// print_line();
	}
}
void viewAccomodationDetails()
{
}
void displayAllFlightsFromSourceToDestination(char source[], char dest[])
{
	flight flights[256] = {};
	int noOfflightObject = 0;
	int flightFound = flight_bdb_readBySourceDest(flights, source, dest, &noOfflightObject);
	if (flightFound == 1)
	{
		displayAllFlightObjectsFromSourceToDest(flights, noOfflightObject);
		// print details
	}
	else
	{
		printf("\n\tNo flights found from %s to %s", source, dest);
		printf("\n\n");
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
	printf("\tTotal no.of seats :%d", flightObject.total_seats);
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
	printf("\tTicket price :%0.2f", flightObject.ticket_price);
	printf("\n");
	printf("\tFlight Status :%s", flightObject.status);
	printf("\n\n");
}

int admin_app()
{
	int menu;
	do
	{
		printf("\n\tEnter Choice : \n\n\t1=>Create flight \n\t2=>Display All flights");
		printf("\n\t3=>Update flight\n\t4=>Delete flight\n\t5=>Show seats\n\t6=>Update flight status\n\t7=>Show all tickets\n\t8=>Show Flights from a source to destination\n\t0=>exit : ");
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
			deleteFlight();
		}
		else if (menu == 5)
		{
			view_seats_in_flight();
		}

		else if (menu == 6)
		{
			updateFlightStatus();
		}
		else if (menu == 7)
		{
			viewAllTicketDetails();
		}
		else if (menu == 8)
		{
			printf("\n\n\t******Enter source and destination details *******\n\n");
			char source[40], dest[40];
			printf("\n\tsource :");
			scanf("%s", source);
			printf("\n\tdestination :");
			scanf("%s", dest);
			displayAllFlightsFromSourceToDestination(source, dest);
		}
	} while (menu == 1 || menu == 2 || menu == 3 || menu == 4 || menu == 5 || menu == 6 || menu == 7 || menu == 8);

	return EXIT_SUCCESS;
}
