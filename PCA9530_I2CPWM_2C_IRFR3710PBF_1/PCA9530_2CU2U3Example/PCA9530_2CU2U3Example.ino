/**************************************************************************/
/*
        Distributed with a free-will license.
        Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
        PCA9530_2CU2U3
        This code is designed to work with the PCA9530_I2CPWM_2C_IRFR3710PBF I2C Mini Module available from ControlEverything.com.
        https://shop.controleverything.com/
*/
/**************************************************************************/

#include <Wire.h>
#include <PCA9530_2CU2U3.h>

PCA9530_2CU2U3 pca;

void setup(void)
{
    Serial.begin(9600);
    // The address can be changed making the option of connecting multiple devices
    pca.getAddr_PCA9530_2CU2U3(PCA9530_2CU2U3_DEFAULT_ADDRESS);           // 0x60

    pca.setFreqPSC0(75);        // Period of Blink = 0.5 sec
    pca.setPWM0(128);           // Duty Cycle = 50
    pca.setFreqPSC1(75);        // Period of Blink = 0.5 sec
    pca.setPWM1(128);           // Duty Cycle = 50

    pca.begin();
    delay(500);
}

void loop(void)
{
    byte error;
    int8_t address;

    // PCA9530_2CU2U3 Sensor Address
    address = pca.pca_i2cAddress;

    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
        Serial.println("Getting LED State Readings from PCA9530_2CU2U3");
        Serial.println(" ");

        // Set up for Sensor for LED Selection
        // Sets the LS0 LED Select Registers, LS0-LED selector
        // setLEDSelector(uint8_t LED1, uint8_t LED0)
        pca.setLEDSelector(PCA9530_2CU2U3_REG_LS0_PWM0, PCA9530_2CU2U3_REG_LS0_PWM0);
        delay(500);

        // Output Data to Screen
        Serial.println("All LED's blinks at PWM0 Rate");
        Serial.println(" ");
        Serial.println("        ***************************        ");
        Serial.println(" ");
        delay(500);
    }
    else
    {
        Serial.println("PCA9530_2CU2U3 Disconnected!");
        Serial.println(" ");
        Serial.println("        ************        ");
        Serial.println(" ");
    }


    delay(1000);
}
