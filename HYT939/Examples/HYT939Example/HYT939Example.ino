/**************************************************************************/
/*
        Distributed with a free-will license.
        Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
        HYT939
        This code is designed to work with the HYT939_I2CS I2C Mini Module available from ControlEverything.com.
        https://www.controleverything.com/content/Temperature?sku=HYT939_I2CS#tabs-0-product_tabset-2
*/
/**************************************************************************/

#include <Wire.h>
#include <HYT939.h>

HYT939 hih;

void setup(void)
{
    Serial.begin(9600);

    // The address can be changed making the option of connecting multiple devices
    hih.getAddr_HYT939(HYT939_DEFAULT_ADDRESS);   // 0x28

    hih.begin();
    delay(500);
}

void loop(void)
{
    byte error;
    int8_t address;

    address = hih.hih_i2cAddress;
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
        hih.readRegister(address);
        float cTemp, fTemp, humidity;

        Serial.println("Getting Readings from HYT939");
        Serial.println(" ");
        // Read and print out the Relative Humidity, convert it to %RH
        humidity = hih.Measure_Humidity();

        // Read and print out the temperature, then convert to C and F scales
        cTemp = hih.Measure_Temperature();
        fTemp = cTemp * 1.8 + 32;

        // Output data to screen
        Serial.print("Relative Humidity Reading: ");
        Serial.print(humidity);
        Serial.println(" %RH");
        Serial.print("Temperature Reading in Celsius: ");
        Serial.print(cTemp);
        Serial.println(" C");
        Serial.print("Temperature Reading in Fahrenheit: ");
        Serial.print(fTemp);
        Serial.println(" F");
        Serial.println(" ");
        Serial.println("        ***************************        ");
        Serial.println(" ");
    }
    else
    {
        Serial.println("HYT939 Disconnected!");
        Serial.println(" ");
        Serial.println("        ************        ");
        Serial.println(" ");
    }

    delay(1000);
}
