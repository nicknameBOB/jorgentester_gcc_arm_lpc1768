#ifndef TEMP_H_
#define TEMP_H_
I2C Temp_Sensor(p28,p27); //Set Temp_Sensor as the object of one I2C
 AnalogIn TMP36(p16); //Initiates ADC and connects an object to it
 AnalogIn LM35(p17); //Initiates ADC and connects an object to it
//Send in what the vref is and the amount of readings you want averaged, and it returns the temp
float ADC_AVG_TMP36(uint32_t Amount_of_readings, uint32_t vref_mV)
{
        uint32_t analog_dump = TMP36.read_u16(); //Dumps a value
        analog_dump = 0;
        //collects X amount of readings

        for (int i = 0; i<Amount_of_readings; i++)
        {
            analog_dump = TMP36.read_u16()+analog_dump;
            wait_us(1);
        }
        
        float AVG_Analog = (float)analog_dump/(float)(Amount_of_readings); //Calulates the average
        float volt = ((float)AVG_Analog*vref_mV)/0xFFFF; //converts bits to volt
        float Temperature = (volt-500)/10; //Converts volt to temp

        return(Temperature);
}
float ADC_AVG_TEMPLM35(uint32_t Amount_of_readings, uint32_t vref_mV)
{
        uint32_t analog_dump = LM35.read_u16(); //Dumps a value
        analog_dump = 0;
        //collects X amount of readings

        for (int i = 0; i<Amount_of_readings; i++)
        {
            analog_dump = LM35.read_u16()+analog_dump;
            wait_us(1);
        }
        
        float AVG_Analog = (float)analog_dump/(float)(Amount_of_readings); //Calulates the average
        float volt = ((float)AVG_Analog*vref_mV)/0xFFFF; //converts bits to volt
        float Temperature = volt/10; //Converts volt to temp

        return(Temperature);
}
float Temp_read_LPC(uint32_t Amount_of_readings, uint32_t offset)
{    
    char buffer[2];
    uint16_t temp_dump = 0;
      Temp_Sensor.stop();
    for(int i = 0; i<Amount_of_readings; i++)
    {
       
        Temp_Sensor.write(0x90, 0x00, 1);
        Temp_Sensor.read(0x90,buffer, 2);
        uint16_t temp_data = (buffer[0]<<3) | (buffer[1]>>5);
        temp_dump += temp_data;
        
          wait_us(10);
    }   
      Temp_Sensor.stop();
    
        float temp = ((float)temp_dump/(float)(Amount_of_readings))*0.125;
       
         return(temp);
     
}
#endif