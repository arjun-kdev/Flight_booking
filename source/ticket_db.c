#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ticket_flight_db.h"
//#include "util.h"
//#include "enums.h"



void add_tickets_intoFile(ticket *ticketAddr)
{
    //char fileName[45];
   // strcpy(fileName,getFilePath(TICKET_DB_PATH));
   char fileName[] = "ticket.dat";
    FILE* out = fopen(fileName,"ab");
    if(out == NULL){
      //  printf("FILE ERROR.\n");
        return;
    }
    
    fwrite(ticketAddr,1,sizeof(ticket),out);

    fclose(out);
}




void ticket_bdb_readall(ticket *ticketList,int *ticketCount)
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

int ticket_bdb_count()
{
    int countChars = 0;
    int countObjects = 0;

    //char fileName[45];
    //strcpy(fileName, getFilePath(FLIGHT_DB_PATH));
    char fileName[] = "ticket.dat";

    FILE *input = fopen(fileName, "rb");
    if (input == NULL)
    {
        printf("Does not exist ...!\n");
        return -1;
    }
    fseek(input, 0, SEEK_END);
    countChars = ftell(input);
    fclose(input);
    countObjects = countChars / (int)sizeof(ticket);
    return countObjects;
}


 
 
  void ticket_db_findticket( ticket* val, int* count, int ticketid, int seatno){
     
    int I=0;
  flight ft1;
  ticket tkt;
    
   // char fileName[45];
   // strcpy(fileName,getFilePath(TICKET_DB_PATH));
 char fileName[] = "ticket.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
       // printf("FILE ERROR.\n");
        return;
    }
    while(fread(&tkt,1,sizeof(ticket),in)){
        if(tkt.ticketID == ticketid && tkt.seatNO){
        	val[I] = tkt;
        	I++;
        }
        
    }
    fclose(in);
    (*count) = I; 
 }
 
 
 void ticket_db_delete_ticket(int ticketid,int seatno){
 
 

    //char fileName[45];
   // strcpy(fileName,getFilePath(TICKET_DB_PATH));
   char fileName[] = "ticket.dat";
    char tempFileName[] = "tickettemp.dat";
 ticket tkt1;
    FILE* in1 = fopen(fileName,"r");
    FILE* out1 = fopen(tempFileName,"w");
    if(in1 == NULL){
        printf("(in)FILE ERROR.\n");
        return;
    }
    if(out1 == NULL){
      //  printf("(out)FILE ERROR.\n");
        return;
    }
     while(fread(&tkt1,1,sizeof(ticket),in1)){
        if(tkt1.ticketID == ticketid && tkt1.seatNO)
       {        	
            fwrite(&tkt1,1,sizeof(ticket),out1);
       } 
    }     
    fclose(out1);
    fclose(in1); 
    remove(fileName);
    rename(tempFileName,fileName);
     
 }
 
 
 
 
