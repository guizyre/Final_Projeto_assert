/******************************************************************************/
/**
 * @file    LedPwm.c
 * @addtogroup LED_PWM
 * @brief   Controle de intensidade dos LEDs por PWM e gerencia de estados.
 * @author  Guilherme Gonçalves
 * @details
 * \n <b>Ferramentas:</b>
 * - STM32CubeIDE, STM32CubeMX.
 *
 * \n <b>Observacoes:</b>
 * - Este modulo mantem o estado de intensidade de cada LED.
 * - Aplica o valor de entrada ao LED selecionado e preserva o estado dos demais.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "LedPwm.h"
#include "Bsp.h"

/*******************************************************************************
 * DEFINES LOCAIS
 ******************************************************************************/
#define CH_LED1           TIM_CHANNEL_1
#define CH_LED2           TIM_CHANNEL_2
#define CH_LED3           TIM_CHANNEL_3
#define PWM_MAX_PERIOD    999

/*******************************************************************************
 * VARIAVEIS LOCAIS
 ******************************************************************************/

/// Indica qual LED esta sob controle do potenciometro no momento
static ActiveLed_t currentActiveLed = LED_1;

/// Armazenam o ultimo percentual duty cycle aplicado a cada LED
static uint8_t dutyLed1 = 0;
static uint8_t dutyLed2 = 0;
static uint8_t dutyLed3 = 0;

/*******************************************************************************
 * PROTOTIPOS LOCAIS
 ******************************************************************************/

static void ApplyDutyToHardware(ActiveLed_t led, uint8_t percent);

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief  Atualiza o brilho do LED atualmente selecionado.
 * @param  percent: Intensidade desejada
 * @retval Nenhum.
 ******************************************************************************/
void LedPwm_UpdateActive(uint8_t percent) {
    // Atualiza a variavel de estado do LED ativo
    if (currentActiveLed == LED_1) dutyLed1 = percent;
    else if (currentActiveLed == LED_2) dutyLed2 = percent;
    else if (currentActiveLed == LED_3) dutyLed3 = percent;

    // Envia o comando para o hardware
    ApplyDutyToHardware(currentActiveLed, percent);
}

/******************************************************************************/
/** @brief  Altera qual LED passara a ser controlado pelo sistema.
 * @param  newLed: Identificador do novo LED a ser controlado.
 * @retval Nenhum.
 ******************************************************************************/
void LedPwm_SetSelected(ActiveLed_t newLed) {
    currentActiveLed = newLed;
}

/******************************************************************************/
/** @brief  Recupera o ultimo percentual de brilho armazenado de um LED.
 * @param  led: Identificador do LED consultado.
 * @retval Valor percentual do Duty Cycle (0 a 100%).
 ******************************************************************************/
uint8_t LedPwm_GetDuty(ActiveLed_t led) {
    if (led == LED_1) return dutyLed1;
    if (led == LED_2) return dutyLed2;
    return dutyLed3;
}

/*******************************************************************************
 * FUNCOES LOCAIS
 ******************************************************************************/

/******************************************************************************/
/** @brief  Aplica o duty cycle em escala real para os canais do Timer.
 * @param  led: O LED alvo para a modificacao de PWM.
 * @param  percent: O valor em porcentagem a ser convertido.
 * @retval Nenhum.
 * @details O hardware do STM32 atualizara apenas o canal especificado,
 * mantendo os outros canais com seus ultimos valores fisicos intactos.
 ******************************************************************************/
static void ApplyDutyToHardware(ActiveLed_t led, uint8_t percent) {
    // Converte a porcentagem de 0-100 para o range do Timer (0-999)
    uint32_t hwDuty = (percent * PWM_MAX_PERIOD) / 100;

    if (led == LED_1) {
        Bsp_Pwm_SetDuty(CH_LED1, hwDuty);
    }
    else if (led == LED_2) {
        Bsp_Pwm_SetDuty(CH_LED2, hwDuty);
    }
    else if (led == LED_3) {
        Bsp_Pwm_SetDuty(CH_LED3, hwDuty);
    }
}

/** @} DOXYGEN GROUP TAG END OF FILE */
