/**************************************************************************/
/*
        Distributed with a free-will license.
        Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
        MMC3316xMT
        This code is designed to work with the MMC3316xMT_I2CS I2C Mini Module available from ControlEverything.com.
        https://www.controleverything.com/content/Magnetic-Sensor?sku=MMC3316xMT_I2CS#tabs-0-product_tabset-2
*/
/**************************************************************************/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

/**************************************************************************
    I2C ADDRESS/BITS
**************************************************************************/
    #define MMC3316xMT_DEFAULT_ADDRESS_MAG                    (0x30)

/**************************************************************************
    CONVERSION DELAY (in mS)
**************************************************************************/
    #define MMC3316xMT_CONVERSIONDELAY                          (100)

/**************************************************************************
    MAGNETOMETER REGISTERS
**************************************************************************/
    #define MMC3316xMT_REG_MAG_OUT_X_L                          (0x00)      // X-Axis Magnetic Data Loe Register
    #define MMC3316xMT_REG_MAG_OUT_X_H                          (0x01)      // X-Axis Magnetic Data High Register
    #define MMC3316xMT_REG_MAG_OUT_Y_L                          (0x02)      // Y-Axis Magnetic Data Low Register
    #define MMC3316xMT_REG_MAG_OUT_Y_H                          (0x03)      // Y-Axis Magnetic Data High Register
    #define MMC3316xMT_REG_MAG_OUT_Z_L                          (0x04)      // Z-Axis Magnetic Data Low Register
    #define MMC3316xMT_REG_MAG_OUT_Z_H                          (0x05)      // Z-Axis Magnetic Data High Register
    #define MMC3316xMT_REG_MAG_STATUS                           (0x06)      // Device Status Register
    #define MMC3316xMT_REG_MAG_CTRL_REG0                        (0x07)      // Internal Control Register 0
    #define MMC3316xMT_REG_MAG_CTRL_REG1                        (0x08)      // Internal Control Register 1
    #define MMC3316xMT_REG_MAG_PRODUCT_ID0                      (0x10)      // Magnetic Sensor Product ID 0
    #define MMC3316xMT_REG_MAG_R0                               (0x1C)      // Factory Used Register
    #define MMC3316xMT_REG_MAG_R1                               (0x1D)      // Factory Used Register
    #define MMC3316xMT_REG_MAG_R2                               (0x1E)      // Factory Used Register
    #define MMC3316xMT_REG_MAG_R3                               (0x1F)      // Factory Used Register
    #define MMC3316xMT_REG_MAG_PRODUCT_ID1                      (0x20)      // Magnetic Sensor Product ID 1

/**************************************************************************
    MAGNETOMETER INTERNAL CONTROL REGISTER 0 DESCRIPTION
**************************************************************************/
    #define MMC3316xMT_REG_MAG_CTRL_REG0_RESET_MASK             (0x40)      // Reset the Sensor by Passing a Large Current through Set/Reset Coil at a Reversed Direction
    #define MMC3316xMT_REG_MAG_CTRL_REG0_RESET_NO               (0x00)      // Don't Reset the Senor
    #define MMC3316xMT_REG_MAG_CTRL_REG0_RESET_YES              (0x40)      // Reset the Sensor

    #define MMC3316xMT_REG_MAG_CTRL_REG0_SET_MASK               (0x20)      // Set the Sensor by Passing a Large Current through Set/Reset Coil
    #define MMC3316xMT_REG_MAG_CTRL_REG0_SET_NO                 (0x00)      // Don't Set the Senor
    #define MMC3316xMT_REG_MAG_CTRL_REG0_SET_YES                (0x20)      // Set the Sensor

    #define MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_MASK           (0x0C)      // Determine How Often the Chip will Take Measurements in Continuous Measurement Mode
    #define MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_50HZ           (0x00)      // Frequency: 50Hz
    #define MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_20HZ           (0x04)      // Frequency: 20Hz
    #define MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_10HZ           (0x08)      // Frequency: 10Hz
    #define MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_1HZ            (0x0C)      // Frequency: 1Hz

    #define MMC3316xMT_REG_MAG_CTRL_REG0_CONT_MODE_MASK         (0x02)      // Enable Continuous Measurement Mode
    #define MMC3316xMT_REG_MAG_CTRL_REG0_CONT_MODE_DISABLE      (0x00)      // Disable Continuous Measurement Mode
    #define MMC3316xMT_REG_MAG_CTRL_REG0_CONT_MODE_ENABLE       (0x02)      // Enable Continuous Measurement Mode

    #define MMC3316xMT_REG_MAG_CTRL_REG0_TM_MASK                (0x01)      // Initiate Measurement
    #define MMC3316xMT_REG_MAG_CTRL_REG0_TM_NOT                 (0x00)      // Don't Initiate Measurement
    #define MMC3316xMT_REG_MAG_CTRL_REG0_TM_INITIATE            (0x01)      // Initiate Measurement


typedef enum
{
    MAG_NO_RESET                    = MMC3316xMT_REG_MAG_CTRL_REG0_RESET_NO,
    MAG_RESET                       = MMC3316xMT_REG_MAG_CTRL_REG0_RESET_YES
    
} mmcMagReset_t;

typedef enum
{
    MAG_NO_SET                      = MMC3316xMT_REG_MAG_CTRL_REG0_SET_NO,
    MAG_SET                         = MMC3316xMT_REG_MAG_CTRL_REG0_SET_YES
    
} mmcMagSet_t;

typedef enum
{
    MAG_FREQUENCY_50HZ              = MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_50HZ,
    MAG_FREQUENCY_20HZ              = MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_20HZ,
    MAG_FREQUENCY_10HZ              = MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_10HZ,
    MAG_FREQUENCY_1HZ               = MMC3316xMT_REG_MAG_CTRL_REG0_CM_FREQ_1HZ
    
} mmcMagFrequency_t;

typedef enum
{
    MAG_MEASUREMENT_DISABLE         = MMC3316xMT_REG_MAG_CTRL_REG0_CONT_MODE_DISABLE,
    MAG_MEASUREMENT_ENABLE          = MMC3316xMT_REG_MAG_CTRL_REG0_CONT_MODE_ENABLE
    
} mmcMagContMode_t;

typedef enum
{
    MAG_MEASUREMENT_NOT             = MMC3316xMT_REG_MAG_CTRL_REG0_TM_NOT,
    MAG_MEASUREMENT_INITIATE        = MMC3316xMT_REG_MAG_CTRL_REG0_TM_INITIATE
    
} mmcMagMeasurement_t;

typedef struct
{
    int16_t X;
    int16_t Y;
    int16_t Z;
    
} mmcSensorData_t;


class MMC3316xMT
{
    protected:
        // Instance-specific properties
        uint8_t mmc_conversionDelay;
        mmcMagReset_t mmc_magreset;
        mmcMagSet_t mmc_magset;
        mmcMagFrequency_t mmc_magfrequency;
        mmcMagContMode_t mmc_magcontmode;
        mmcMagMeasurement_t mmc_magmeasurement;

    public:
        uint8_t mmc_i2cAddress;
        mmcSensorData_t mmc_magData;
        void getAddr_MMC3316xMT(uint8_t i2cAddress);
        bool begin(void);
        void Measure_Sensor(void);
        void setUpMagnetometer(void);
        void Measure_Magnetometer(void);
        void setMagReset(mmcMagReset_t magreset);
        mmcMagReset_t getMagReset(void);
        void setMagSet(mmcMagSet_t magrset);
        mmcMagSet_t getMagSet(void);
        void setMagFrequency(mmcMagFrequency_t magfrequency);
        mmcMagFrequency_t getMagFrequency(void);
        void setMagContMode(mmcMagContMode_t magcontmode);
        mmcMagContMode_t getMagContMode(void);
        void setMagMeasurement(mmcMagMeasurement_t magmeasurement);
        mmcMagMeasurement_t getMagMeasurement(void);
    
    private:
};
