#include <stdio.h>
#include <string.h>
#include "ticket_flight_db.h"
#include "util.h"
#include "enums.h"

void add_Flight_intoFile(flight *flightAddr)
{
    char fileName[45];
    strcpy(fileName, getFilePath(FLIGHT_DB_PATH));
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

    char fileName[45];
    strcpy(fileName, getFilePath(FLIGHT_DB_PATH));

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

    char fileName[45];
    strcpy(fileName, getFilePath(FLIGHT_DB_PATH));

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
/*void flight_bdb_readById(flight *flightAddr, char flightIdAddr[])
{
    int i = 0;
    flight flight;

    char fileName[45];
    strcpy(fileName, getFilePath(FLIGHT_DB_PATH));

    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        printf("FILE ERROR.\n");
        return;
    }
    while (fread(&flight, 1, sizeof(flight), in))
    {
        if (strcmp(flight.flightID, flightIdAddr) == 0)
        {
            (*flightAddr) = flight;
            break;
        }
        i++;
    }
    fclose(in);
}*/

int flight_bdb_readBySourceDest(flight *flightAddr, char source[], char dest[])
{
    int i = 0;
    flight flightObj;
    int flightFound = 0;

    char fileName[45];
    strcpy(fileName, getFilePath(FLIGHT_DB_PATH));

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
