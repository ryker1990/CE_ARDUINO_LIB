/**************************************************************************/
/*
        Distributed with a free-will license.
        Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
        TMD2771
        This code is designed to work with the TMD2771_I2CS I2C Mini Module available from ControlEverything.com.
        https://www.controleverything.com/content/Light?sku=TMD2771_I2CS#tabs-0-product_tabset-2
*/
/**************************************************************************/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

#include "TMD2771.h"

/**************************************************************************/
/*
        Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static uint8_t i2cread(void)
{
    #if ARDUINO >= 100
        return Wire.read();
    #else
        return Wire.receive();
    #endif
}

/**************************************************************************/
/*
        Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static void i2cwrite(uint8_t x)
{
    #if ARDUINO >= 100
        Wire.write((uint8_t)x);
    #else
        Wire.send(x);
    #endif
}

/**************************************************************************/
/*
        Writes 8-bits to the specified destination register
*/
/**************************************************************************/
static void writeRegister(uint8_t i2cAddress, uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(i2cAddress);
    i2cwrite((uint8_t)reg);
    i2cwrite((uint8_t)(value));
    Wire.endTransmission();
}

/**************************************************************************/
/*
        Reads 8-bits to the specified destination register
*/
/**************************************************************************/
static uint8_t readRegister(uint8_t i2cAddress, uint8_t reg)
{
    Wire.beginTransmission(i2cAddress);
    i2cwrite((uint8_t)reg);
    Wire.endTransmission();
    Wire.requestFrom(i2cAddress, (uint8_t)1);
    return (uint8_t)(i2cread());
}

/**************************************************************************/
/*
        Instantiates a new TMD2771 class with appropriate properties
*/
/**************************************************************************/
void TMD2771::getAddr_TMD2771(uint8_t i2cAddress)
{
    tmd_i2cAddress = i2cAddress;
    tmd_conversionDelay = TMD2771_CONVERSIONDELAY;
    
}

/**************************************************************************/
/*
        Sets up the Hardware
*/
/**************************************************************************/
bool TMD2771::begin()
{
    Wire.begin();
    
    uint8_t devid = readRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_ID);
    if (devid != TMD2771_ALSPROX_DEV_ID)
        return false;
    
    // Set up for Digital Ambient Light and Proximity Sensor
    setUpALSProximity();
    
    return true;
}

/**************************************************************************/
/*
        Sets the Select Command Register
*/
/**************************************************************************/
void TMD2771::setCommand(tmdCommand_t command)
{
    tmd_command = command;
}

/**************************************************************************/
/*
        Gets the Select Command Register
*/
/**************************************************************************/
tmdCommand_t TMD2771::getCommand()
{
    return tmd_command;
}

/**************************************************************************/
/*
        Sets the Proximity Interrupt Mask
*/
/**************************************************************************/
void TMD2771::setProximityInterrupt(tmdProximityInterrupt_t proximityinterrupt)
{
    tmd_proximityinterrupt = proximityinterrupt;
}

/**************************************************************************/
/*
        Gets the Proximity Interrupt Mask
*/
/**************************************************************************/
tmdProximityInterrupt_t TMD2771::getProximityInterrupt()
{
    return tmd_proximityinterrupt;
}

/**************************************************************************/
/*
        Sets the ALS Interrupt Mask
*/
/**************************************************************************/
void TMD2771::setALSInterrupt(tmdALSInterrupt_t alsinterrupt)
{
    tmd_alsinterrupt = alsinterrupt;
}

/**************************************************************************/
/*
        Gets the ALS Interrupt Mask
*/
/**************************************************************************/
tmdALSInterrupt_t TMD2771::getALSInterrupt()
{
    return tmd_alsinterrupt;
}

/**************************************************************************/
/*
        Sets the Wait Enable
*/
/**************************************************************************/
void TMD2771::setWaitEnable(tmdWaitEnable_t waitenable)
{
    tmd_waitenable = waitenable;
}

/**************************************************************************/
/*
        Gets the Wait Enable
*/
/**************************************************************************/
tmdWaitEnable_t TMD2771::getWaitEnable()
{
    return tmd_waitenable;
}

/**************************************************************************/
/*
        Sets the Proximity Enable
*/
/**************************************************************************/
void TMD2771::setProximityEnable(tmdProximityEnable_t proximityenable)
{
    tmd_proximityenable = proximityenable;
}

/**************************************************************************/
/*
        Gets the Proximity Enable
*/
/**************************************************************************/
tmdProximityEnable_t TMD2771::getProximityEnable()
{
    return tmd_proximityenable;
}

/**************************************************************************/
/*
        Sets the ALS Enable
*/
/**************************************************************************/
void TMD2771::setALSEnable(tmdALSEnable_t alsenable)
{
    tmd_alsenable = alsenable;
}

/**************************************************************************/
/*
        Gets the ALS Enable
*/
/**************************************************************************/
tmdALSEnable_t TMD2771::getALSEnable()
{
    return tmd_alsenable;
}

/**************************************************************************/
/*
        Sets the Power ON
*/
/**************************************************************************/
void TMD2771::setPowerEnable(tmdPowerEnable_t powerenable)
{
    tmd_powerenable = powerenable;
}
                    
/**************************************************************************/
/*
        Gets the Power ON
*/
/**************************************************************************/
tmdPowerEnable_t TMD2771::getPowerEnable()
{
    return tmd_powerenable;
}

/**************************************************************************/
/*
        Sets to Control the Internal Integration Time of the ALS Channel 
        ADC’s in 2.72 ms Increments
*/
/**************************************************************************/
void TMD2771::setATime(tmdATime_t atime)
{
    tmd_atime = atime;
}

/**************************************************************************/
/*
        Gets to Control the Internal Integration Time of the ALS Channel 
        ADC’s in 2.72 ms Increments
*/
/**************************************************************************/
tmdATime_t TMD2771::getATime()
{
    return tmd_atime;
}

/**************************************************************************/
/*
        Sets to Control the Internal Integration Time of the Proximity
        ADC’s in 2.72 ms Increments
*/
/**************************************************************************/
void TMD2771::setPTime(tmdPTime_t ptime)
{
    tmd_ptime = ptime;
}

/**************************************************************************/
/*
        Gets to Control the Internal Integration Time of the Proximity 
        ADC’s in 2.72 ms Increments
*/
/**************************************************************************/
tmdPTime_t TMD2771::getPTime()
{
    return tmd_ptime;
}

/**************************************************************************/
/*
        Sets to Control the Wait Time is Set in 2.72 ms Increments
        Unless the WLONG Bit is Asserted in Which Case the wait Times are 12x Longer
*/
/**************************************************************************/
void TMD2771::setWTime(tmdWTime_t wtime)
{
    tmd_wtime = wtime;
}

/**************************************************************************/
/*
        Gets to Control the Wait Time is Set in 2.72 ms Increments
        Unless the WLONG Bit is Asserted in Which Case the wait Times are 12x Longer
*/
/**************************************************************************/
tmdWTime_t TMD2771::getWTime()
{
    return tmd_wtime;
}

/**************************************************************************/
/*
        Sets the Wait Long
*/
/**************************************************************************/
void TMD2771::setWaitLong(tmdWaitLong_t waitlong)
{
    tmd_waitlong = waitlong;
}

/**************************************************************************/
/*
        Gets the Wait Long
*/
/**************************************************************************/
tmdWaitLong_t TMD2771::getWaitLong()
{
    return tmd_waitlong;
}

/**************************************************************************/
/*
        Sets the Proximity LED Drive Strength
*/
/**************************************************************************/
void TMD2771::setProximityDrive(tmdProximityDrive_t proximitydrive)
{
    tmd_proximitydrive = proximitydrive;
}

/**************************************************************************/
/*
        Gets the Proximity LED Drive Strength
*/
/**************************************************************************/
tmdProximityDrive_t TMD2771::getProximityDrive()
{
    return tmd_proximitydrive;
}

/**************************************************************************/
/*
        Sets the Proximity Diode Selector
*/
/**************************************************************************/
void TMD2771::setProximityDiode(tmdProximityDiode_t proximitydiode)
{
    tmd_proximitydiode = proximitydiode;
}

/**************************************************************************/
/*
        Gets the Proximity Diode Selector
*/
/**************************************************************************/
tmdProximityDiode_t TMD2771::getProximityDiode()
{
    return tmd_proximitydiode;
}

/**************************************************************************/
/*
        Sets the ALS Gain
*/
/**************************************************************************/
void TMD2771::setALSGain(tmdALSGain_t alsgain)
{
    tmd_alsgain = alsgain;
}

/**************************************************************************/
/*
        Gets the ALS Gain
*/
/**************************************************************************/
tmdALSGain_t TMD2771::getALSGain()
{
    return tmd_alsgain;
}

/**************************************************************************/
/*
        Sets up the Digital Ambient Light and Proximity Sensor
*/
/**************************************************************************/
void TMD2771::setUpALSProximity(void)
{
    // Set Up the Configuration for the Digital Ambient Light and Proximity Sensor Enable Register
    /*
    
     // Set the Proximity Interrupt Mask
     uint8_t enable = tmd_proximityinterrupt;
    
     // Set the ALS Interrupt Mask
     enable |= tmd_alsinterrupt;
    
     // Set the Wait Enable
     enable |= tmd_waitenable;
     
     // Set the Proximity Enable
     enable |= tmd_proximityenable;
     
     // Set the ALS Enable
     enable |= tmd_alsinable;
     
     // Set the Power ON
     enable |= tmd_powerenable;
    */
    
    uint8_t enable =    TMD2771_REG_ALSPROX_ENABLE_PIEN_NOT_ASSERT      |   // Not Asserted, Did not Permits Proximity Interrupts to be Generated
                        TMD2771_REG_ALSPROX_ENABLE_AIEN_NOT_ASSERT      |   // Not Asserted, Did not Permits ALS Interrupts to be Generated
                        TMD2771_REG_ALSPROX_ENABLE_WEN_ENABLE           |   // Enables the Wait Timer
                        TMD2771_REG_ALSPROX_ENABLE_PEN_ENABLE           |   // Activates the Proximity
                        TMD2771_REG_ALSPROX_ENABLE_AEN_ENABLE           |   // Activates the ALS
                        TMD2771_REG_ALSPROX_ENABLE_PON_ENABLE;              // Activates the Internal Oscillator to Permit the Timers and ADC Channels to Operate
    
    // Write the configuration to the Digital Ambient Light and Proximity Sensor Enable Register
    writeRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_ENABLE | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR, enable);
    
    // Wait for the configuration to complete
    delay(tmd_conversionDelay);
    
    // Set Up the Configuration for the Digital Ambient Light and Proximity Sensor ATIME Register
    // Set the Internal Integration Time of the ALS Channel ADC’s in 2.72 ms Increments
    uint8_t atime = tmd_atime;
    
    // Write the configuration to the Digital Ambient Light and Proximity Sensor ATIME Register
    writeRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_ATIME | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR, atime);
    
    // Wait for the configuration to complete
    delay(tmd_conversionDelay);
    
    // Set Up the Configuration for the Digital Ambient Light and Proximity Sensor PTIME Register
    // Set the Internal Integration Time of the Proximity ADC’s in 2.72 ms Increments
    uint8_t ptime = tmd_ptime;
    
    // Write the configuration to the Digital Ambient Light and Proximity Sensor PTIME Register
    writeRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_PTIME | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR, ptime);
    
    // Wait for the configuration to complete
    delay(tmd_conversionDelay);
    
    // Set Up the Configuration for the Digital Ambient Light and Proximity Sensor WTIME Register
    // Set the Wait Time is Set in 2.72 ms Increments Unless the WLONG Bit is Asserted in Which Case the wait Times are 12x Longer
    uint8_t wtime = tmd_wtime;
    
    // Write the configuration to the Digital Ambient Light and Proximity Sensor WTIME Register
    writeRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_WTIME | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR, wtime);
    
    // Wait for the configuration to complete
    delay(tmd_conversionDelay);
    
    // Set Up the Configuration for the Digital Ambient Light and Proximity Sensor Configuration Register
    /*
     // Set the Wait Long
     uint8_t config |= tmd_waitlong;
    */
    
    uint8_t config =    TMD2771_REG_ALSPROX_CONFIG_WLONG_NOT_ASSERT;        // Not Asserted, the Wait Cycles are Not Increased by a Factor 12X from that Programmed in the WTIME Register
    
    // Write the configuration to the Digital Ambient Light and Proximity Sensor Configuration Register
    writeRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_CONFIG | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR, config);
    
    // Wait for the configuration to complete
    delay(tmd_conversionDelay);
    
    // Set Up the Configuration for the Digital Ambient Light and Proximity Sensor Control Register
    // Proximity LED Drive Strength
    uint8_t control = tmd_proximitydrive;
    
    // Proximity Diode Selector
    control |= tmd_proximitydiode;
    
    // ALS Gain
    control |= tmd_alsgain;
    
    // Write the configuration to the Digital Ambient Light and Proximity Sensor Control Register
    writeRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_CONTROL | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR, control);
    
    // Wait for the configuration to complete
    delay(tmd_conversionDelay);
}
/**************************************************************************/
/*
        Reads up the Digital Ambient Light and Proximity Sensor
*/
/**************************************************************************/
void TMD2771::Measure_Sensor(void)
{
    // Read all the Sensors
    // ALS and Proximity Data
    Measure_ALS();
    Measure_Proximity();
}

/**************************************************************************/
/*
        Reads the Digital Ambient Light Sensor
*/
/**************************************************************************/
void TMD2771::Measure_ALS()
{
    uint8_t C0dataLo, C0dataHi, C1dataLo, C1dataHi;
    uint16_t C0Data, C1Data;
    float atime, again, CPL, Lux1, Lux2, Lux;
    
    // Counts per Lux
    CPL = 0.0;
    // The Final Lux is the Maximum of Lux1, Lux2, or 0
    Lux = 0.0;
    
    // Check the ATIME
    switch (tmd_atime)
    {
        case ATIME_2_72MS:
            atime = 2.72;
            break;
            
        case ATIME_27_2MS:
            atime = 27.2;
            break;
            
        case ATIME_101MS:
            atime = 101.0;
            break;
            
        case ATIME_174MS:
            atime = 174.0;
            break;
            
        case ATIME_696MS:
            atime = 696;
            break;
            
        default:
            break;
    }
    
    // Check the AGAIN
    switch (tmd_alsgain)
    {
        case AGAIN_1X:
            again = 1.0;
            break;
        case AGAIN_8X:
            again = 8.0;
            break;
            
        case AGAIN_16X:
            again = 16.0;
            break;
            
        case AGAIN_120X:
            again = 120.0;
            break;
            
        default:
            break;
    }
    
    // Read the Data
    // Reading the ALS CH0 Data Low Register
    C0dataLo = readRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_C0DATAL | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR);
    // Reading the ALS CH0 Data High Register
    C0dataHi = readRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_C0DATAH | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR);
    // Conversion of the result
    // 16-bit unsigned result for ALS CH0 Data of TMD2771
    C0Data = (int16_t)((C0dataHi << 8) | C0dataLo);
    
    // Reading the ALS CH1 Data Low Register
    C1dataLo = readRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_C1DATAL | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR);
    // Reading the ALS CH1 Data High Register
    C1dataHi = readRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_C1DATAH | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR);
    // Conversion of the result
    // 16-bit unsigned result for ALS CH1 Data of TMD2771
    C1Data = (int16_t)((C1dataHi << 8) | C1dataLo);
    
    /*
     CPL = (ATIME_ms × AGAINx) / (GA × 24) 
     Lux1 = (C0DATA − 2 × C1DATA) / CPL
     Lux2 = (0.6 × C0DATA − C1DATA) / CPL
     Lux = MAX(Lux1, Lux2, 0)
     For Open Air with No Aperture, GA = 1
    */
    
    CPL = (atime * again) / 24.0;
    // Fluorescent and Incandescent Light
    Lux1 = (C0Data - (2.0 * C1Data)) / CPL;
    // Dimmed Incandescent Light
    Lux2 = ((0.6 * C0Data) - (1.00 * C1Data)) / CPL;
    
    // Calculate the Final Lux
    if((Lux1 > 0) && (Lux1 > Lux2))
    {
        Lux = Lux1;
    }
    else if((Lux2 > 0) && (Lux2 > Lux1))
    {
        Lux = Lux2;
    }
    
    tmd_alsproxData.L = Lux;
}

/**************************************************************************/
/*
        Reads the Proximity Sensor
*/
/**************************************************************************/
void TMD2771::Measure_Proximity()
{
    uint8_t PdataLo, PdataHi;
    
    // Read the Data
    // Reading the Proximity Data Low Register
    PdataLo = readRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_PDATAL | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR);
    // Reading the Proximity Data High Register
    PdataHi = readRegister(tmd_i2cAddress, TMD2771_REG_ALSPROX_PDATAH | TMD2771_REG_ALSPROX_CMD_SELECT | TMD2771_REG_ALSPROX_CMD_TYPE_AUTO_INCR);
    // Conversion of the result
    // 16-bit unsigned result for Proximity Data of TMD2771
    tmd_alsproxData.P = (uint16_t)((PdataHi << 8) | PdataLo);
}
