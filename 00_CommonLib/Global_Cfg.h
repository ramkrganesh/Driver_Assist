#ifndef _GLOBAL_CFG_H_
#define _GLOBAL_CFG_H_

/**
 * MACROS
 */

 /**
  * @brief : The pin D2 will be used to detect INT signal from APDS9960.
  *          The pin will be configured as Input.
  */
#define CFG_NANO_HWPIN_9960INT  (2u)

 /**
 * @brief : APDS-9960 I2C device address.
 */
#define CFG_9960_I2C_ADDR   (0x39u)


/**
 * @brief : APDS9960 Power On trigger.
 */
#define CFG_9960_PON_EN     (0x01u)
#define CFG_9960_PON_DIS    (0x00u)

/**
 * @brief : Proximity Detect Enable.
 */
#define CFG_9960_PEN_EN     (0x04u)
#define CFG_9960_PEN_DIS    (0x00u)

/**
 * @brief : Proximity Interrupt Enable
 */
#define CFG_9960_PIEN_EN    (0x20u)
#define CFG_9960_PIEN_DIS   (0X00u)

/**
 * @brief : Wait Enable
 * 0x08 : Wait enabled
 * 0x00 : Wait disabled
 */
#define CFG_9960_WEN_EN     (0x08u)
#define CFG_9960_WEN_DIS    (0x00u)

/**
 * @brief : Wait time between 2 proximity detection
 * 255  = 1 * 2.78ms    = 2.78ms
 * 127  = 127 * 2.78ms  = 353.06ms
 * 0    = 256 * 2.78    = 712ms
 */
#define CFG_9960_WTIME      (254u)

/**
 * @brief : Wail Longer register.
 * Wait time will be multiplied by 12
 * 0x60 : WLONG disabled
 * 0x62 : WLONG enabled
 */
#define CFG_9960_WLONG      (0x60u)

/**
 * @brief : Proximity low threshold
 */
#define CFG_9960_PILT       (0x64u)

/**
 * @brief : Proximity high threshold
 */
#define CFG_9960_PIHT       (0xC8u)

/**
 * @brief : Proximity Interrupt Persistence. Controls rate of proximity
 *          interrupt to the host processor.
 * 0x30 : Interrupt raised after 3 out of range events
 */
#define CFG_9960_PPERS      (0x30u)

/**
 * @brief : Proximity Pulse Length. 0x40 = 8uS
 * Only the bits 7,6 are required. Others are "dont care".
 */
#define CFG_9960_PPLEN      (0x40u)

/**
 * @brief : Proximity Pulse Count.
 * Recommended value is 8pulses
 */
#define CFG_9960_PPULSE     (0x07u)

/**
 * @brief : LED Drive Strength.
 * 0x00 : 100mA
 * 0x40 : 50mA
 */
#define CFG_9960_LDRIVE     (0x00u)

/**
 * @brief : Proximity Gain Control.
 * 0x00 : 1x
 * 0x04 : 2x
 * 0x08 : 4x
 * 0x0C : 8x
 */
#define CFG_9960_PGAIN      (0x00u)

/**
 * @brief : Proximity Saturation Interrupt Enable.
 * 0x00 : Disabled
 * 0x80 : Enabled
 */
#define CFG_9960_PSIEN      (0x00u)

/**
 * @brief : Additional LDR current during proximity detection
 * 0x00 : 100%
 * 0x10 : 150%
 * 0x20 : 200%
 * 0x30 : 300%
 */
#define CFG_9960_LEDBOOST   (0x00u)

/**
 * @brief : Proximity Gain Compensation Enable (when one LED pair is disabled)
 * 0x00 : Disabled
 * 0x20 : Enabled
 */
#define CFG_9960_PCMP       (0x00u)

/**
 * @brief : Sleep After Interrupt.When enabled, the device will automatically 
 * enter low power mode when the INT pin is asserted and the state machine
 * has progressed to the SAI decision block.
 * Normal operation is resumed when INT pin is cleared over I2C.
 * 0x00 : SAI disabled
 * 0x10 : SAI enabled
 */
#define CFG_9960_SAI        (0x10u)
#endif
