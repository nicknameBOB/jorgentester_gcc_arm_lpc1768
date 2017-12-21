uint8_t MCU_adress = 'K';
uint8_t MCU_ALL = 'Z';

// Number for for types of data
///Types to recieve
#define Number_incomming_message_type 5

#define ALARM 0
#define ERROR 1
#define TIMEDATE 2
#define STATUS 3
#define REQUEST 4

/*
const char *Incomming_message_type[Number_incomming_message_type]; 
Incomming_message_type[ALARM] =  "Alarm";
Incomming_message_type[ERROR] =  "Error";
Incomming_message_type[TIMEDATE] = "Time_and_Date";
Incomming_message_type[STATUS] = "Status";
Incomming_message_type[REQUEST] = "Request";
*/


//Data Adress starts at 10

#define MCU_ADRESS_DATA 5

#define ACC_X_DATA 10
#define ACC_Y_DATA 11
#define ACC_Z_DATA 12
#define TEMP_DATA 13
#define TIME_HOURS_DATA 14
#define TIME_MINUTS_DATA 15
#define TIME_SECONDS_DATA 16
