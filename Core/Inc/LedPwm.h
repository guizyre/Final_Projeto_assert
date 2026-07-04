/******************************************************************************/
/**
 * @file    LedPwm.h
 * @addtogroup LED_PWM
 * @brief   Cabecalho do controle de intensidade dos LEDs por PWM.
 * @author  Guilherme Gonçalves
 * @{
 ******************************************************************************/

#ifndef _LEDPWM_H_
#define _LEDPWM_H_

/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * TIPOS DE DADOS PUBLICOS
 ******************************************************************************/

/// Identificadores dos LEDs do sistema controlados via PWM
typedef enum {
    LED_1 = 1,
    LED_2,
    LED_3
} ActiveLed_t;

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

void LedPwm_UpdateActive(uint8_t percent);
void LedPwm_SetSelected(ActiveLed_t newLed);
uint8_t LedPwm_GetDuty(ActiveLed_t led);

#endif /* _LEDPWM_H_ */

/** @} DOXYGEN GROUP TAG END OF FILE */
