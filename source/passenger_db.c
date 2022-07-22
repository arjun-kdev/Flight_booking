
#include "passenger_db.h"

void add_passenger_intoFile(passenger *passengerAddr)
{
    // char fileName[45];
    // strcpy(fileName,getFilePath(PASSENGER_DB_PATH));
    char fileName[] = "passenger.dat";
    FILE *out = fopen(fileName, "ab");
    if (out == NULL)
    {
        // printf("FILE ERROR.\n");
        return;
    }

    fwrite(passengerAddr, 1, sizeof(passenger), out);

    fclose(out);
}

void passenger_bdb_readall(passenger *passengerList, int *passengerCount)
{
    int I = 0;
    passenger psngr;

    // char fileName[45];
    // strcpy(fileName,getFilePath(PASSENGER_DB_PATH));
    char fileName[] = "passenger.dat";

    FILE *in = fopen(fileName, "rb");
    if (in == NULL)
    {
        // printf("FILE ERROR.\n");
        return;
    }
    while (fread(&psngr, 1, sizeof(psngr), in))
    {
        passengerList[I] = psngr;
        I++;
    }
    *passengerCount = I;
    fclose(in);
}

int passenger_bdb_count()
{
    int countChars = 0;
    int countObjects = 0;

    // char fileName[45];
    // strcpy(fileName,getFilePath(PASSENGER_DB_PATH));
    char fileName[] = "passenger.dat";

    FILE *input = fopen(fileName, "rb");
    if (input == NULL)
    {
        printf("Does not exist ...!\n");
        return -1;
    }
    fseek(input, 0, SEEK_END);
    countChars = ftell(input);
    fclose(input);
    countObjects = countChars / (int)sizeof(passenger);
    return countObjects;
}
