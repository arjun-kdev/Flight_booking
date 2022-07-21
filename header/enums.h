enum flight_status
{
    CANCELLED1 = 0,BOARDING
};
typedef enum  flight_status flight_status;

enum ticket_status
{
    PENDING = 0,APPROVED,REJECTED,CANCELLED
};
typedef enum  ticket_status ticket_status;

enum DB_file_name
{
    FLIGHT_DB_PATH = 0,TICKET_DB_PATH ,PASSENGER_DB_PATH
};
typedef enum DB_file_name DB_FilePath;