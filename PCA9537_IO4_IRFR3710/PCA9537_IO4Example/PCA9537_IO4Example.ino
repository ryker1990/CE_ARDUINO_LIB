/**************************************************************************/
/*
        Distributed with a free-will license.
        Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
        PCA9537_IO4
        This code is designed to work with the PCA9537_I2CO4_IRFR3710 I2C Mini Module available from ControlEverything.com.
        https://shop.controleverything.com/
*/
/**************************************************************************/

#include <Wire.h>
#include <PCA9537_IO4.h>

PCA9537_IO4 pca;

void setup(void)
{
    Serial.begin(9600);
    // The address can be changed making the option of connecting multiple devices
    pca.getAddr_PCA9537_IO4(PCA9537_IO4_DEFAULT_ADDRESS);           // 0x49

    pca.Reset();

    pca.begin();
    delay(500);
}

void loop(void)
{
    byte error;
    int8_t address;

    // PCA9537_IO4 Sensor Address
    address = pca.pca_i2cAddress;

    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
        Serial.println("Getting Pin State Readings from PCA9537_IO4");
        Serial.println(" ");

        // Set up for Sensor
        pca.setPinMode(PCA9537_IO4_OUTPUT_PIN2, PCA9537_IO4_MODE_OUTPUT);
        delay(1000);
        // pca.setPinMode(PCA9537_IO4_OUTPUT_PIN2, PCA9537_IO4_MODE_INPUT);
        delay(1000);

        // Output Data to Screen
        Serial.println("I/O Pin '2' State is HIGH");
        Serial.println(" ");
        Serial.println("        ***************************        ");
        Serial.println(" ");
        delay(500);
    }
    else
    {
        Serial.println("PCA9537_IO4 Disconnected!");
        Serial.println(" ");
        Serial.println("        ************        ");
        Serial.println(" ");
    }


    delay(1000);
}
