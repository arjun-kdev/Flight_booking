#include<stdio.h>
#include "passengerdb.c"
#include "ticket_flight_db.h"
typedef struct _DOJ11
{
	int day;	
	int year;
	int month;

}DOJ11;

void passenger_details()
{
passenger p1;

int N;
    printf("Enter Number of passenger:");
    scanf("%d",&N);
   
    for (int i =0 ;i< N;i++)
    {

printf("Name:");
scanf("%c", &p1.passengerName);
printf("PhoneNumber:");
scanf("%d", &p1.phoneNumber	);
printf("Gender:");
scanf("%c", &p1.gender);
printf("Email:");
scanf("%c", &p1.email);
printf("Address:");
scanf("%c", &p1.address);

add_passenger_intoFile(&p1);
}
}


void booktickets()
{
char source1[32],dest1[32];
	int count=0;
	char dateOfJourney[16];

	printf("source place :");
	scanf("%s", &source1);
	printf("Destination place:");
	scanf("%s", &dest1);
	
	
/*("Enter date of journey in dd-MM-yyyy format : ");
    scanf("%s", dateOfJourney);
    sscanf(dateOfJourney, "%02d-%02d-%04d" ,
    	    &DOJ11.day,
           &DOJ11.month,
           &DOJ11.year);
    printf("\n");*/
//function name
	flight_count_bdb(&count, source1, dest1, dateOfJourney);
	
	flight flightList[count];

	flight_bdb_readall_specific_date(&flightList);

	for( int i = 0; i < count; i++)
	{
		printf("details", &flightList);	
	}	
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

void deletetickets()
{
int seat_no,ticketid;
ticket t1;
    printf("Enter the ticketID :");
      scanf ("%d",&ticketid);
    printf("Enter the seatno to cancel the ticket:"); 
    scanf ("%d",&seat_no);
   //finding function
    if(t1.ticketID == ticketid  && t1.seatNO == seat_no)
    {
   	 
	    char ch; 
	    printf("Are you sure you want to delete!!! If yes press Y else N :"); 
	   clear_buffer();
	    scanf("%c",&ch);
	    if('y' == ch || 'Y' == ch){ 
	    	 ticket_db_delete(seat_no);
	    	 printf("ticket is cancelled successfully.\n");
	    	
	    }
    }
    else
    {
    	printf("Item doesnot exist!!!");
    }
}	

void accomadationdetails()
{
}


