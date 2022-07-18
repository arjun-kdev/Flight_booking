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

    flight flightObject = {};
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

    //create file operation call comes here//
}
void updateFlight(){

 flight flightObject = {};

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
    scanf("%lf", flightObject.number_of_seats);
    add_Flight_intoFile(flightObject);


    
    //update file operation call comes here//
}

int main()
{
    return EXIT_SUCCESS;
}
