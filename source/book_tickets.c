#include<stdio.h>
#include"ui_passenger.h"
#include "db.h"
#include"struct_base.h"

#include"struct_ticket_flight.h"

void passenger_details()
{
passenger p1;

int N;
    printf("Enter Number of passenger:");
    scanf("%d",&N);
   
    for (int i =0 ;i< N;i++)
    {

printf("Name:");
scanf("%c", p1.passengerName);
printf("PhoneNumber:");
scanf("%d", p1.phoneNumber);
printf("Gender:");
scanf("%c", p1.gender);
printf("Email:");
scanf("%c", p1.email);
printf("Address:");
scanf("%c", p1.address);

flt_db_insert(&p1);
}
}


void booktickets()
{
char source1[20] dest1[20], doj[10];
//int count=0;
//
flight ft;
printf("source place :");
scanf("%s", &source1);
printf("Destination place:");
scanf("%s", &dest1);
printf("Date of Travel:");
scanf("%s", &doj);
//function name

if (ft.starting_from == source1 && ft.destination == dest1 && ft.day_of_journey == doj)
{
//function name
char ch; 
	    printf("Are you sure you want to book !!! If yes press Y else N :");
	    scanf("%c",&ch);
	    if('y' == ch || 'Y' == ch){ 
	    	passenger_details();
	    	printf("Booked successfully........\n");
	    }
    
    else
    {
    	printf("Error while Booking!!!");
    }
    }
else
{
printf("No Planes Available for the details given above");

}
}
