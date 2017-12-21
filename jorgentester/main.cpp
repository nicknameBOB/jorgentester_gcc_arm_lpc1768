

#include "mbed.h"
#include "XBeeLib.h"
#if defined(ENABLE_LOGGING)
#include "DigiLoggerMbedSerial.h"
using namespace DigiLog;
#endif

#define REMOTE_NODE_ADDR64_MSB  ((uint32_t)0x0013A200)
#define REMOTE_NODE_ADDR64_LSB  ((uint32_t)0x4076A9A7)
#define REMOTE_NODE_ADDR64      UINT64(REMOTE_NODE_ADDR64_MSB, REMOTE_NODE_ADDR64_LSB)
using namespace XBeeLib;

AnalogIn Ain1(p20);              // enable analog input in p20
AnalogIn Ain2(p19);              // enable analog input in p19

float ADCdata;                   // our data for the analog to digital conversion
float values[20];                // it will store our 20 values
float avvalue;                   // it will store the averge value


Serial *log_serial;

const RemoteXBeeDM remoteDevice = RemoteXBeeDM(REMOTE_NODE_ADDR64);  

    XBeeDM xbee = XBeeDM(RADIO_TX, RADIO_RX, RADIO_RESET, NC, NC, 9600);    // DigiMesh settupp


#include "Types_of_data.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "C12832.h"
#include "TEMP.h"  //Associates the pin to the ADC and includes all the functions
#include "Communication_shell.h"



//-------------|\\    //|------//\\------||---||\\   ||-------------------------------------//
//-------------||\\  //||-----//  \\-----||---|| \\  ||-------------------------------------//
//-------------|| \\// ||----//====\\----||---||  \\ ||-------------------------------------//
//-------------||      ||---//      \\---||---||   \\||-------------------------------------//
void Doing_stuff(void)
{

      //  float temperature1 = ADC_AVG_TMP36( 50, 3300);
      //  float temperature2 = ADC_AVG_TEMPLM35( 50, 3300);
    float temperature3 =  Temp_read_LPC( 50, 0);
      // float THE_TIME = (float)hours
        //uint8_t dump = Send_to_PC(18, (float)TIME_HOURS_DATA, (float)hours, (float)TIME_MINUTS_DATA, (float)minuts, (float) TIME_SECONDS_DATA, (float)seconds.read(), (float)ACC_X_DATA,  X_integral, (float)ACC_Y_DATA,  Y_integral,  (float)ACC_Z_DATA,  Z_integral, (float)TEMP_DATA , temperature1, (float)17, temperature2, (float)18, temperature3 ); 
    uint8_t dump = Send_to_PC(8, (float)TIME_HOURS_DATA, (float)hours, (float)TIME_MINUTS_DATA, (float)minuts, (float) TIME_SECONDS_DATA, (float)seconds.read(), (float)18, temperature3 ); 
     wait(10);
   
    
    

}
int main()
{

         seconds.start(); //starts the second counter
    minut_int.attach(&time_master, 60); //Attaches the minut ticker to the time_master func
        
        RadioStatus radioStatus = xbee.init();
        MBED_ASSERT(radioStatus == Success);
    while(1){
        log_serial = new Serial(DEBUG_TX, DEBUG_RX);                            // seriel komunikasjon
        log_serial->baud(9600);                                                 // defineerer komuniksjone hastigheten
        log_serial->printf("\n\nSample application XBeeDM test settupp\n");     // printer overskrift
        log_serial->printf(XB_LIB_BANNER);                                      // printer xb stempel
        
        
        Doing_stuff();

        

        delete(log_serial);
    
   
    }
}