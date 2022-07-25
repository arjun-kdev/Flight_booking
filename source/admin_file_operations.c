#include <stdio.h>
#include <string.h>
#include "ticket_flight_db.h"
#include "util.h"

void add_Flight_intoFile(flight *flightAddr)
{
    // char fileName[45];
    // strcpy(fileName, getFilePath("flight.dat"));
    char fileName[] = "flight.dat";
    FILE *out = fopen(fileName, "ab");
    if (out == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }

    fwrite(flightAddr, 1, sizeof(flight), out);

    fclose(out);
}

void flight_bdb_readall(flight *flightList, int *flightCount)
{
    int I = 0;
    flight flightObj;

    // char fileName[45];
    // strcpy(fileName, getFilePath(FLIGHT_DB_PATH));
    char fileName[] = "flight.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&flightObj, 1, sizeof(flight), in))
    {
        flightList[I] = flightObj;
        I++;
    }
    *flightCount = I;
    fclose(in);
}
int flight_bdb_count()
{
    int countChars = 0;
    int countObjects = 0;

    // char fileName[45];
    // strcpy(fileName, getFilePath(FLIGHT_DB_PATH));
    char fileName[] = "flight.dat";

    FILE *input = fopen(fileName, "rb");
    if (input == NULL)
    {
        printf("Does not exist ...!\n");
        return -1;
    }
    fseek(input, 0, SEEK_END);
    countChars = ftell(input);
    fclose(input);
    countObjects = countChars / (int)sizeof(flight);
    return countObjects;
}

void flight_count_bdb(int *flightCount, char *srcAddr, char *destAddr, char *doj)
{
    int I = 0;
    flight flightObj;
    char db_journey_date[16];

    // char fileName[45];
    // strcpy(fileName,getFilePath(FLIGHT_DB_PATH));
    char fileName[] = "flight.dat";

    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        //  printf("FILE ERROR.\n");
        return;
    }

    while (fread(&flightObj, 1, sizeof(flight), in))
    {
        // flightList[I] = flightObj;
        sscanf(db_journey_date, "%02d-%02d-%04d", &flightObj.DOJ.day, &flightObj.DOJ.month, &flightObj.DOJ.year);
        if (!(strcmp(flightObj.source, srcAddr)) && !(strcmp(flightObj.destination, destAddr)) && !(strcmp(db_journey_date, doj)))
        {
            I++;
        }

        *flightCount = I;
        fclose(in);
    }
}

void flight_bdb_readall_specific_date(flight *flightList, char *srcAddr, char *destAddr, char *doj)
{
    int I = 0;
    flight flightObj;
    char db_journey_date;

    // char fileName[45];
    // strcpy(fileName,getFilePath(FLIGHT_DB_PATH));
    char fileName[] = "flight.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        //  printf("FILE ERROR.\n");
        return;
    }
    while (fread(&flightObj, 1, sizeof(flight), in))
    {
        sscanf(&db_journey_date, "%02d-%02d-%04d", &flightObj.DOJ.day, &flightObj.DOJ.month, &flightObj.DOJ.year);
        if (!(strcmp(flightObj.source, srcAddr)) && !(strcmp(flightObj.destination, destAddr)) && !(strcmp(&db_journey_date, doj)))
        {
            flightList[I] = flightObj;
            I++;
        }
        //*flightCount = I;
        fclose(in);
    }
}

void flight_bdb_readall12(flight *flt1, int *count1, char *flightid)
{
    int I = 0;
    flight flightObj;

    // char fileName[45];
    // strcpy(fileName,getFilePath(FLIGHT_DB_PATH));
    char fileName[] = "flight.dat";

    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        // printf("FILE ERROR.\n");
        return;
    }
    while (fread(&flightObj, 1, sizeof(flight), in))
    {
        if (!strcmp(flightObj.flightID, flightid))
        {
            (*flt1) = flightObj;
            (*count1)++;
            break;
        }
        *count1 = I;
        fclose(in);
    }
}

int flight_bdb_readById(flight *flightAddr, char flightIdAddr[])
{
    int i = 0;
    flight flight;

    int isRecordFound  = 0;
    // char fileName[45];
    // strcpy(fileName, getFilePath(FLIGHT_DB_PATH));
    char fileName[] = "flight.dat";
    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return 0;
    }
    while (fread(&flight, 1, sizeof(flight), in))
    {
        if (strcmp(flight.flightID, flightIdAddr) == 0)
        {
            (*flightAddr) = flight;
             isRecordFound = 1;
            break;
        }
        i++;
    }
    fclose(in);
    return isRecordFound;
}

int flight_bdb_readBySourceDest(flight *flightAddr, char source[], char dest[])
{
    int i = 0;
    flight flightObj;
    int flightFound = 0;

    // char fileName[45];
    // strcpy(fileName, getFilePath(FLIGHT_DB_PATH));

    char fileName[] = "flight.dat";

    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("\n\t list is empty\n");
        return -1;
    }
    while (fread(&flightObj, 1, sizeof(flight), in))
    {
        if (strcmp(flightObj.source, source) == 0)
        {
            if (strcmp(flightObj.destination, dest) == 0)
            {
                (*flightAddr) = flightObj;
                flightFound = 1;
                break;
            }
        }
        i++;
    }

    fclose(in);
    return flightFound;
}
void update_flight_bdb_update_intoFile(flight flightAddr, char flightId[])
{

    int i = 0;
    flight flight;
    // char fileName[45];
    // strcpy(fileName,getFilePath(FLIGHT_DB_PATH));
    char fileName[] = "flight.dat";
    FILE *in = fopen(fileName, "rb+");

    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }

    while (fread(&flight, 1, sizeof(flight), in))
    {
        i++;
        if (strcmp(flight.flightID, flightId) == 0)
        {
            break;
        }
    }

    if (i > 0)
    {
        fseek(in, (i - 1) * sizeof(flight), SEEK_SET);
        fwrite(&flightAddr, 1, sizeof(flight), in);
    }
    fclose(in);
}

void flight_bdb_delete(char *id)
{
    int i = 0;
    flight flight1;

    // char fileName[45];
    // strcpy(fileName,getFilePath(LOAN_DB_PATH));
    char fileName[] = "flight.dat";
    char tempFileName[] = "flightTemp_db.dat";

    FILE *in = fopen(fileName, "rb");
    FILE *out = fopen(tempFileName, "wb");

    if (in == NULL)
    {
        printf("(in)FILE ERROR.\n");
        return;
    }

    if (out == NULL)
    {
        printf("(out)FILE ERROR.\n");
        return;
    }

    while (fread(&flight1, 1, sizeof(flight), in))
    {
        i++;
        if (strcmp(flight1.flightID, id))
        {
            fwrite(&flight1, 1, sizeof(flight), out);
        }
    }

    fclose(out);
    fclose(in);

    remove(fileName);

    rename(tempFileName, fileName);
}
