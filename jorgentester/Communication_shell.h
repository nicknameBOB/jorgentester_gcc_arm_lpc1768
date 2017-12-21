//prototype function
void time_master(); //This function gets triggerd every minut
void Alarm_indicator(uint8_t Alert_time);
uint8_t Send_to_PC(uint8_t length, ...); 
void Get_XBEE_data(void);
float Temp_read_LPC(void);


Timeout Alarm_time; //Create an object for the timer

//Serial XBEE(p9, p10); //Using a XBEE as a serialport, rather than USB

C12832 lcd(p5, p7, p6, p8, p11);


 
 
 
 Ticker minut_int; //Interrupt vector for know when a minut has passed
 Timer seconds; //Create an object for the timer
 uint16_t minuts = 0; //Minuts that has passed. Can start with an offset
 uint32_t hours = 0; //Hours that have passed. Can start with an offset

void Alarm_timout(void)
{
            lcd.cls();
        lcd.locate(0,0);
        lcd.printf("ALARM timeout");
        wait(1);

}

void Alarm_indicator(uint8_t Alert_time)
{
    

        lcd.cls();
        lcd.locate(0,0);
        lcd.printf("ALARM!!!!! RUN!! \n");
   
       // wait(2);
        lcd.printf("WE ARE ALL GOING TO DIE! \n");
        //wait(2);
        Alarm_time.attach(&Alarm_timout, Alert_time);
}



uint8_t Send_to_PC(uint8_t length, ...) {

  uint8_t error_status = 0; //initiate Error status for error handling
  
  //checks that an even number is sent inn
  if(!(length & 0x01)){
     
     char str[128]; //String buffer
     uint8_t index = 0; //Position of data written to the string. 
     uint8_t input_position; //Position of Data
     double send_array[length]; //store the data before converting to string
     

     /* initialize valist for length number of arguments */
     va_list valist;
     va_start(valist, length);
     //Writes must have data into the string
    index += sprintf(&str[index], "%d,", MCU_ADRESS_DATA); //Insert data location for the MCU NAme
    index += sprintf(&str[index], "%d", MCU_adress); //Insert the MCU Name
    
     /* access all the input arguments assigned to valist  and puts it in the correct order*/
     for (input_position  = 0; input_position   < length; input_position++) {
        send_array[input_position] = va_arg(valist, double);
        index += sprintf(&str[index], ",%.2f", send_array[input_position]);
     }
        index += sprintf(&str[index], " \r\n");
             const TxStatus txStatus = xbee.send_data(remoteDevice, (const uint8_t *)str, index);
 if (txStatus == TxStatusSuccess)
        log_serial->printf("Vellyket data overforing\r\n");
    else
        log_serial->printf("Ikke vellyket data overforing, feilkode : %d\r\n", (int) txStatus);
        /*  clean memory reserved for valist */
      va_end(valist);
  }
  else
  {
    error_status = 1;
  }

   return error_status;
}

//This function gets triggerd every minut
void time_master()
{
    seconds.reset(); //reset the second timer
    minuts++; //increments the minut variable each minut
    if(minuts>=60) //If minut is 60 increment an hour and reset minut. 
    {
        minuts = 0;
        hours++;
    }
}