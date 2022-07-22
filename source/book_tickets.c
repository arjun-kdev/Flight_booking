#include <stdio.h>
#include "passenger_db.h"
#include "ticket_flight_db.h"
#include <stdlib.h>
#include <string.h>
//#include"util.h"
//#include"enums.h"
typedef struct _DOJ11
{
	int day;
	int year;
	int month;

} DOJ11;

// Method Declaration

void enter_name();
void find_name();
void find_room();
void checkout_guest();
void view_bookings();

// Instance Field Declaration
FILE *view;
FILE *fp;
FILE *enter;
char admin_entry[20] = {'y'};
char user_entry[20] = {'y'};

struct hotel
{
	char name[20];
	char room[20];

} h;

void passenger_details();

void passenger_details()
{
	passenger p1;
	flight flt2[1000];
	int count_1 = 0;
	int N, i;
	flight_bdb_readall(flt2, &count_1);

	printf("Enter Number of passenger:");
	scanf("%d", &N);
	// printf("enter the ticket id:");
	// scanf("%d",&p1.ticketID);

	for (i = 0; i < N; i++)
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
		printf("seats available %d\n", flt2[i].seats_available);
		// printf("select the seat no:");
		// scanf("%d",flt2[i].seats_available);
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
	scanf(dateOfJourney, "%02d-%02d-%04d", &D1.day, &D1.month, &D1.year);

	flight_count_bdb(&count, source1, dest1, dateOfJourney);
	flight *ft = (flight *)malloc(count * sizeof(flight));
	flight_bdb_readall_specific_date(ft, source1, dest1, dateOfJourney);

	flight ft1;
	int i;

	// if((strcmp(ft1.source,source1)==0)&& (strcmp(ft1.destination,dest1)==0) && (strcmp(ft1.DOJ.day,D1.day)==0)&& 		(strcmp(ft1.DOJ.month,D1.month)==0) && (strcmp(ft1.DOJ.year,D1.year)==0))
	// if((strcmp(ft1.source,source1))==0  && (strcmp(ft1.destination, dest1))==0&& (strcmp(ft1.DOJ, dateOfJourney))==0)
	if ((strcmp(ft1.source, source1) == 0) && (strcmp(ft1.destination, dest1) == 0) && (ft1.DOJ.day == D1.day) && (ft1.DOJ.month == D1.month) && (ft1.DOJ.year == D1.year))
	{

		for (int i = 0; i < count; i++)
		{
			printf("FLightId: %s\n", ft[i].flightID);
			printf("source: %s\n", ft[i].source);
			printf("Destination: %s\n", ft[i].destination);
			printf("Number of seats: %d\n", ft[i].number_of_seats);
			printf("seats available: %d\n", ft[i].seats_available);
			printf("ticket_price: %lf\n", ft[i].ticket_price);
			printf("Date of journey:"
				   "%02d-%02d-%04d",
				   ft[i].DOJ.day, ft[i].DOJ.month, ft[i].DOJ.year);
			printf("departure time:"
				   "%02d:%02d",
				   ft[i].departure_time.hour, ft[i].departure_time.minute);
		}

		printf("provide the details:");
		passenger_details();
	}

	else
	{
		printf("No flights avaliable");
	}
}

void delete_tickets()

{
	int seat_no, ticketid;
	ticket t1;
	int count = 0;
	printf("Enter the ticketID :");
	scanf("%d", &ticketid);
	printf("Enter the seatno to cancel the ticket:");
	scanf("%d", &seat_no);

	ticket_db_findticket(&t1, &count, ticketid, seat_no);

	if (t1.ticketID == ticketid && t1.seatNO == seat_no)
	{
		char ch;
		printf("Are you sure you want to delete!!! If yes press Y else N :");

		scanf("%c", &ch);
		if ('y' == ch || 'Y' == ch)
		{
			ticket_db_delete_ticket(ticketid, seat_no);
			printf("ticket is cancelled successfully.\n");
		}
	}
	else
	{
		printf("There is no ticket in this ID");
	}
}

int accomadation_details()
{
	int a, b, c;

	// Welcome screen

	printf("\n\n\t\t*************************************************\n");
	printf("\t\t*      WELCOME TO ACCOMODATION FACILITY         *\n");
	printf("\t\t*************************************************\n\n\n");

	printf("\n\tFor ADMIN access enter --> 1 \t\t\t");
	printf("\n\tFor USER access enter --> 2 \t\t\t");
	printf("\n>> ");
	scanf("%d", &a);

	switch (a)
	{
	case 1:
	{
		char pass[10];
		char filepass[10];
		int i;

		FILE *passw;
		passw = fopen("pass.txt", "r");

		// admins password prompt
		printf("\n Hello admin!\n Please enter the password to continue --> ");

		for (i = 0; i < 6; i++)
		{
			scanf("%s", pass);
			fscanf(passw, "%s", filepass);
			if (strcmp(filepass, pass) == 0)
			{
				printf("\n\nAccess granted!\n");
				fclose(passw);
				break;
			}
			else
			{
				printf("\nIncorrect password, please try again.");
				printf("\nYou have %d trys left ", 5 - i - 1);
				printf("\n\nEnter password >> ");
			}
			if (i == 4)
			{
				fclose(passw);
				return 0;
			}
		}

		// re-entry if
		while (admin_entry[0] == 'y')
		{

			printf("\n>>>>>>>>>>>>\tTo VIEW booking requests --> 1 \t\t\t<<<<<<<<<<<<");
			printf("\n>>>>>>>>>>>>\tTo VIEW booked guests details --> 2 \t\t\t<<<<<<<<<<<<");
			printf("\n>>>>>>>>>>>>\tTo ENTER new guest --> 3 \t\t\t<<<<<<<<<<<<");
			printf("\n>>>>>>>>>>>>\tTo CHECKOUT room number of existing guest --> 4 <<<<<<<<<<<<\n");
			printf(">> ");
			scanf("%d", &b);

			switch (b)
			{
			case 1:
			{
				view_bookings();
				break;
			}
			case 2:
			{
				FILE *fpi;
				fpi = fopen("hotelnew.txt", "r");

				while (fscanf(fpi, "%s %s ", h.name, h.room) != -1)
				{

					printf("%s %s  \n", h.name, h.room);
				}
				break;
			}
			case 3:
			{
				enter_name();
				break;
			}

			case 4:
			{
				checkout_guest();
				break;
			}
			default:
			{
				printf("\n Wrong entry!");
			}
			}
			// enter again?
			printf("Would you like to continue? (y/n)\n");
			scanf("%s", admin_entry);
		}
		if (strcmp(admin_entry, "n") == 0)
		{
			printf("Exiting...\n");
			printf("\e[1;1H\e[2J");
			printf("\n >Exited<\n\n");
			// system("clear");
			return 0;
		}
		else
		{
			printf("Wrong entry!\nExiting...\n");
			return 0;
		}
		break;
	}

	case 2:
	{
		while (user_entry[0] == 'y')
		{
			printf("\nHello user and welcome to Hotel!");
			printf("\n\tTo view available rooms --> 1 \t\t\t");
			// printf("\n\tEnter number of room to be book --> 2 \t\t\t");
			printf("\n\tTo request booking of room --> 3 \t");
			printf("\n>> ");
			scanf("%d", &c);
			switch (c)
			{
			case 1:
			{
				FILE *view;
				view = fopen("rooms.txt", "r");
				printf("Available rooms are:");
				while (fscanf(view, "%s", h.room) != -1)
				{
					printf("%s ", h.room);
				}
				fclose(view);
				break;
			}
				// case 2:{

				// printf("Enter number of room to  be book: ");
				// scanf("%s",h.room);

				// break;
				// }

			case 3:
			{
				printf("Enter your name: ");
				scanf("%s", h.name);
				printf("Enter room to book: ");
				scanf("%s", h.room);

				enter = fopen("bookings.txt", "a");

				fprintf(enter, "%s %s ", h.name, h.room);
				fprintf(enter, "\n");

				printf("Succesfully requested booking\n");
				fclose(enter);
			}
			}

			printf("\nWould you like to continue? (y/n)\n");
			scanf("%s", user_entry);
		}
		if (strcmp(user_entry, "n") == 0)
		{
			printf("Exiting...\n");
			printf("\e[1;1H\e[2J");
			printf("\n >Exited<\n\n");
			// system("clear");
			return 0;
		}
		else
		{
			printf("Wrong entry!\nExiting...\n");
			return 0;
		}
		break;
	}
	}
}

// method declare to enter name
void enter_name()
{

	FILE *tmp1;
	FILE *tmp2;

	printf("\nEnter guest name --> ");
	scanf("%s", h.name);
	printf("\nEnter their room number --> ");
	scanf("%s", h.room);

	// entering guests
	fp = fopen("hotelnew.txt", "a");

	if (fp == NULL)
	{
		printf("\nFile not found");
		exit(1);
	}
	else
	{
		fprintf(fp, "%s %s", h.name, h.room);
		printf("\nDone\n");
	}
	fprintf(fp, "\n");

	//
	char remove_guest[20];
	strcpy(remove_guest, h.name);
	char remove_room[20];
	strcpy(remove_room, h.room);

	// removing booking
	tmp1 = fopen("tmp1.txt", "a");
	enter = fopen("bookings.txt", "r");

	while (fscanf(enter, "%s %s ", h.name, h.room) != -1)
	{
		fgetc(enter);

		if (strcmp(h.name, remove_guest) != 0)
		{
			fprintf(tmp1, "%s %s ", h.name, h.room);
		}
	}
	fclose(enter);
	fclose(tmp1);
	remove("bookings.txt");
	rename("tmp1.txt", "bookings.txt");
	fclose(fp);

	// removing room
	tmp2 = fopen("tmp2.txt", "a");
	view = fopen("rooms.txt", "r");

	while (fscanf(view, "%s", h.room) != -1)
	{
		if (strcmp(h.room, remove_room) != 0)
		{
			fprintf(tmp2, "%s", h.room);
			fprintf(tmp2, "\n");
		}
	}
	fclose(view);
	fclose(tmp2);
	remove("rooms.txt");
	rename("tmp2.txt", "rooms.txt");

	fclose(fp);
}

// method definition for guest checkout
void checkout_guest()
{
	char buffer2[20];
	char checkout_name[20];
	char add_room[20];

	FILE *tmp;

	printf("Enter guest too checkout ");
	scanf("%s", checkout_name);

	fp = fopen("hotelnew.txt", "r");
	tmp = fopen("tmp.txt", "w");

	if (fp == NULL)
	{
		printf("File not found");
		exit(1);
	}
	else
	{
		while (fscanf(fp, "%s %s ", h.name, h.room) != -1)
		{
			fgetc(fp);

			if (strcmp(h.name, checkout_name) != 0)
			{
				fprintf(tmp, "%s %s ", h.name, h.room);
			}
			else
			{
				strcpy(add_room, h.room);
			}
		}
		printf("Room checked out!");
	}

	fclose(fp);
	fclose(tmp);
	remove("hotelnew.txt");
	rename("tmp.txt", "hotelnew.txt");

	// enter room back into available rooms list
	view = fopen("rooms.txt", "a");
	printf(" add is %s", add_room);
	fprintf(view, "%s", add_room);
	fclose(view);
}

// method defined to view bookings
void view_bookings()
{

	enter = fopen("bookings.txt", "r");

	while (fscanf(enter, "%s %s ", h.name, h.room) != -1)
	{
		printf("%s %s  \n", h.name, h.room);
	}
}

void view_ticket_details()
{
	// flight flt1[1000];
	ticket tkt3[1000];
	int count = 0, count1 = 0;
	flight flt1;
	char flightid[20];
	printf("enter the flightId:");
	scanf("%s", flightid);
	flight_bdb_readall12(&flt1, &count1, flightid);
	//  flight_bdb_readall(flt1, &count1);
	ticket_bdb_readall(tkt3, &count);

	if (count1)

	{
		printf("FLightId: %s\n", flt1.flightID);
		printf("source: %s\n", flt1.source);
		printf("Destination: %s\n", flt1.destination);
		printf("Number of seats: %d\n", flt1.number_of_seats);
		printf("seats available: %d\n", flt1.seats_available);
		printf("ticket_price: %lf\n", flt1.ticket_price);
		printf("Date of journey:"
			   "%02d-%02d-%04d",
			   flt1.DOJ.day, flt1.DOJ.month, flt1.DOJ.year);
		printf("departure time:"
			   "%02d:%02d",
			   flt1.departure_time.hour, flt1.departure_time.minute);

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
			char ch;
			printf("Need of any Accomadation!!! If yes press Y else N :");

			scanf("%c", &ch);
			if ('y' == ch || 'Y' == ch)
			{
				accomadation_details();

				printf("booked\n");
			}

			else
			{
				printf("Thank you");
			}
		}
	}
	else
	{
		printf("NO flights available");
	}
}
