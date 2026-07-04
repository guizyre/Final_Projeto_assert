/******************************************************************************/
/**
 * @file    Orchestrator.c
 * @addtogroup ORCHESTRATOR
 * @brief   Modulo principal de controle (Orquestrador) do sistema.
 * @author  Hillary Maximino Andrade
 * @details
 * \n <b>Ferramentas:</b>
 * - STM32CubeIDE, STM32CubeMX.
 *
 * \n <b>Observacoes:</b>
 * - Gerencia o fluxo principal, interrupcoes e comunicacao entre modulos.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "Orquestrador.h"
#include "main.h"
#include "Bsp.h"
#include "Sampler.h"
#include "LedPwm.h"
#include "Button.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * VARIAVEIS VOLATEIS E DE CONTROLE
 ******************************************************************************/
static volatile bool flag_Timer5ms = false;
static volatile bool flag_TimerDebounce = false;
static volatile bool flag_UartRx = false;

static uint8_t rxBuffer[5];
static uint8_t printCounter = 0;

/*******************************************************************************
 * PROTOTIPOS LOCAIS
 ******************************************************************************/
void Orchestrator_ProcessButton(void);
void Orchestrator_ProcessSamplingAndUI(void);
void Orchestrator_ProcessUartCommand(void);

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief  Inicializa os modulos e a interface UART. */
void Orchestrator_Init(void) {
    Bsp_Init();
    memset(rxBuffer, 0, 5);
    Bsp_Uart_ReceiveIT(rxBuffer, 4);
}

/******************************************************************************/
/** @brief  Loop principal que delega as tarefas do sistema. */
void Orchestrator_Run(void) {
    Orchestrator_ProcessButton();
    Orchestrator_ProcessSamplingAndUI();
    Orchestrator_ProcessUartCommand();
}

/*******************************************************************************
 * IMPLEMENTACAO DAS SUB-ROTINAS PRIVADAS
 ******************************************************************************/

void Orchestrator_ProcessButton(void) {
    if (flag_TimerDebounce) {
        flag_TimerDebounce = false;
        Button_ProcessDebounce();
    }
}

void Orchestrator_ProcessSamplingAndUI(void) {
    if (flag_Timer5ms) {
        flag_Timer5ms = false;

        // Se o sistema NÃO estiver congelado, lemos o ADC
        if (!Button_IsFrozen()) {
            Bsp_Adc_Start();
            uint32_t adcVal = Bsp_Adc_GetValue(); // Agora o adcVal existe!

            if (Sampler_AddSample(adcVal)) {
                uint8_t percent = Sampler_GetAveragePercent();
                LedPwm_UpdateActive(percent);
            }
        }

        // A impressão ocorre a cada 1s, independente se o sistema está congelado ou não
        printCounter++;
        if (printCounter >= 200) {
            printCounter = 0;
            char msg[120];
            sprintf(msg, "VALUE: %d%% || LED1: %d%% aceso || LED2: %d%% aceso || LED3: %d%% aceso || STATE: %s\r\n",
                    Sampler_GetAveragePercent(),
                    LedPwm_GetDuty(LED_1), LedPwm_GetDuty(LED_2), LedPwm_GetDuty(LED_3),
                    Button_IsFrozen() ? "OFF" : "ON");
            Bsp_Uart_Transmit((uint8_t*)msg, strlen(msg));
        }
    }
}

void Orchestrator_ProcessUartCommand(void) {
    if (flag_UartRx) {
        flag_UartRx = false;

        if (strncmp((char*)rxBuffer, "LED1", 4) == 0) LedPwm_SetSelected(LED_1);
        else if (strncmp((char*)rxBuffer, "LED2", 4) == 0) LedPwm_SetSelected(LED_2);
        else if (strncmp((char*)rxBuffer, "LED3", 4) == 0) LedPwm_SetSelected(LED_3);

        memset(rxBuffer, 0, 5);
        Bsp_Uart_ReceiveIT(rxBuffer, 4);
    }
}

/*******************************************************************************
 * CALLBACKS DE HARDWARE
 ******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        flag_Timer5ms = true;
    } else if (htim->Instance == TIM4) {
        flag_TimerDebounce = true;
        Bsp_TimerDebounce_StopIT();
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_13) {
        Bsp_TimerDebounce_StartIT();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART3) {
        flag_UartRx = true;
    }
}

/** @} DOXYGEN GROUP TAG END OF FILE */
