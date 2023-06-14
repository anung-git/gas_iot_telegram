#include "mq2.h"


mq2::mq2(int pin)
{

    MQ2 = new MQUnifiedsensor(Board, Voltage_Resolution, ADC_Bit_Resolution, pin, Type);
    // Set math model to calculate the PPM concentration and the value of constants
    MQ2->setRegressionMethod(1); //_PPM =  a*ratio^b
    MQ2->setA(574.25);
    MQ2->setB(-2.222); // Configure the equation to to calculate LPG concentration
    /*
      Exponential regression:
      Gas    | a      | b
      H2     | 987.99 | -2.162
      LPG    | 574.25 | -2.222
      CO     | 36974  | -3.109
      Alcohol| 3616.1 | -2.675
      Propane| 658.71 | -2.168
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    MQ2->init();
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      MQ2->setRL(10);
    */
    /*****************************  MQ CAlibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
    // and on clean air (Calibration conditions), setting up R0 value.
    // We recomend executing this routine only on setup in laboratory conditions.
    // This routine does not need to be executed on each restart, you can load your R0 value from eeprom.
    // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
    // Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for (int i = 1; i <= 10; i++)
    {
        MQ2->update(); // Update data, the arduino will read the voltage from the analog pin
        calcR0 += MQ2->calibrate(RatioMQ2CleanAir);
        // Serial.print(".");
    }
    MQ2->setR0(calcR0 / 10);
    // Serial.println("  done!.");

    if (isinf(calcR0))
    {
        Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply");
        while (1)
            ;
    }
    /*****************************  MQ CAlibration ********************************************/
}

float mq2::getPpm()
{
    MQ2->update();                    // Update data, the arduino will read the voltage from the analog pin
    float result = MQ2->readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    return result;
}
mq2::~mq2()
{
}
