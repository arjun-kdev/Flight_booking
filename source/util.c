#include "util.h"


void clear_buffer()
{
   while ((getchar()) != '\n');
}
void print_line()
{
   printf("\n\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
}
char *getTicketStatus(int iStatus)
{
   if (iStatus == 0)
   {
      return "Pending";
   }
   else if (iStatus == 1)
   {
      return "Approved";
   }
   else if (iStatus == 2)
   {
      return "Rejected";
   }
   else if (iStatus == 3)
   {
      return "Cancelled";
   }
   else
   {
      return "Unknown";
   }

}
char *getFlightStatus(int iStatus)
{
   if (iStatus == 0)
   {
      return "Cancelled";
   }
   else if (iStatus == 1)
   {
      return "Boarding";
   }
   else
   {
      return "Unknown";
   }

}
char * getFilePath(int code)
{
 if (code  == 0)
   {
      return "../database/flight_db.dat";
   }
   else if (code == 1)
   {
      return "../database/ticket_db.dat";
   }
   else if (code == 2)
   {
      return "../database/passenger_db.dat";
   }
   else
   {
      return "";
   }  
 }