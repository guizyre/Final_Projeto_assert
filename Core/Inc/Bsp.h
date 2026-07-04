/******************************************************************************/
/**
 * @file    Bsp.h
 * @addtogroup BSP
 * @brief   Cabecalho da camada de abstracao do hardware (Board Support Package).
 * - De maneira geral, ele só declara o que o sistema pode fazer
 *  tipo ligar o PWM ou ler o ADC, sem se importar como isso é feito fisicamente.
 * @author  Guilherme Gonçalves da Silva
 * @{
 ******************************************************************************/

#ifndef _BSP_H_
#define _BSP_H_

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

//Responsável por inicializar todos os periféricos (GPIO, ADC, PWM, UART, Timers)
void Bsp_Init(void);

//Se o botão foi pressionado
bool Bsp_IsButtonPressed(void);

//  Controles do ADC
void Bsp_Adc_Start(void);
uint32_t Bsp_Adc_GetValue(void);

//  Controles do PWM
void Bsp_Pwm_StartAll(void);
void Bsp_Pwm_SetDuty(uint32_t channel, uint32_t duty);

//  Controles da UART
void Bsp_Uart_ReceiveIT(uint8_t *pData, uint16_t size);
void Bsp_Uart_Transmit(uint8_t *pData, uint16_t size);

// Controles do Botao
bool Bsp_Button_Read(void);

// Controles dos Temporizadores
void Bsp_TimerSampling_StartIT(void);
void Bsp_TimerDebounce_StartIT(void);
void Bsp_TimerDebounce_StopIT(void);

#endif /* _BSP_H_ */

/** @} DOXYGEN GROUP TAG END OF FILE */
