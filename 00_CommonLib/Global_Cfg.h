#ifndef _DRIVER_ASSIST_H_
#define _DRIVER_ASSIST_H_

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

#endif
