// #include "MQUnifiedsensor.h"
#ifndef mq2_h
#define mq2_h
// Include the library
#include "MQUnifiedsensor.h"
/************************Hardware Related Macros************************************/
#define Board ("Node MCU")
#define Pin (A0) // Analog input 3 of your arduino
/***********************Software Related Macros************************************/
#define Type ("MQ-2") // MQ2
#define Voltage_Resolution (6.6)
#define ADC_Bit_Resolution (10) // For arduino UNO/MEGA/NANO
#define RatioMQ2CleanAir (9.83) // RS / R0 = 9.83 ppm
class mq2
{
private:
    /*****************************Globals***********************************************/
    MQUnifiedsensor* MQ2 ;//= MQUnifiedsensor(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
    /*****************************Globals***********************************************/
    /* data */
public:
    mq2(int pin);
    ~mq2();
    float getPpm();
};

#endif