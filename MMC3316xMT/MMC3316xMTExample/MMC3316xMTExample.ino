/**************************************************************************/
/*
        Distributed with a free-will license.
        Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
        MMC3316xMT
        This code is designed to work with the MMC3316xMT_I2CS I2C Mini Module available from ControlEverything.com.
        https://www.controleverything.com/content/Magnetic-Sensor?sku=MMC3316xMT_I2CS#tabs-0-product_tabset-2
*/
/**************************************************************************/

#include <Wire.h>
#include <MMC3316xMT.h>

MMC3316xMT mmc;

void setup(void)
{
    Serial.begin(9600);
    // The address can be changed making the option of connecting multiple devices
    mmc.getAddr_MMC3316xMT(MMC3316xMT_DEFAULT_ADDRESS_MAG);      // 0x30

    /*
    // The Magnetic Sensor Parameters can be changed using the following functions
    // Magmetometer:
    // Magnetic Sensor RESET and SET Mode, Chip Measurements in Continuous Measurement Mode
    // Enable the Continuous Measurement Mode and Initiate Measurement
    // These functions can be modified and added here so that the parameters can be altered as per requirement
    */

    mmc.begin();
    delay(1000);
}

void loop(void)
{
    byte error;
    int8_t address;

    // MMC3316xMT Magnetometer Address
    address = mmc.mmc_i2cAddress;

    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
        Serial.println("Getting Magnetic Field Data Readings from MMC3316xMT");
        Serial.println(" ");
        // Set up the sensor for Magnetometer
        mmc.setUpMagnetometer();
        delay(500);
        // Display the results for Magnetic Field Values
        mmc.Measure_Sensor();
        mmc.Measure_Magnetometer();

        // Output Data to Screen
        Serial.print("Magnetic Field in X-Axis: ");
        Serial.println(mmc.mmc_magData.X);
        Serial.print("Magnetic Field in Y-Axis: ");
        Serial.println(mmc.mmc_magData.Y);
        Serial.print("Magnetic Field in Z-Axis: ");
        Serial.println(mmc.mmc_magData.Z);
        Serial.println(" ");
        Serial.println("        ***************************        ");
        Serial.println(" ");
        delay(1000);
    }
    else
    {
        Serial.println("MMC3316xMT Disconnected!");
        Serial.println(" ");
        Serial.println("        ************        ");
        Serial.println(" ");
    }


    delay(1000);
}
