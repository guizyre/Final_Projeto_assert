/******************************************************************************/
/**
 * @file    Bsp.c
 * @addtogroup BSP
 * @brief   Camada de abstracao do hardware (Board Support Package).
 * @author  Seu Nome
 * @details
 * \n <b>Ferramentas:</b>
 * - STM32CubeIDE, STM32CubeMX.
 *
 * \n <b>Dependencias:</b>
 * - STM32 HAL Driver.
 *
 * \n <b>Observacoes:</b>
 * - Este arquivo e o unico que acessa diretamente as funcoes HAL_*.
 * - Toda configuracao de pinos e perifericos de baixo nivel esta aqui.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "Bsp.h"

/*******************************************************************************
 * VARIAVEIS EXTERNAS (Handles da HAL gerados pelo CubeMX)
 ******************************************************************************/
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart3;

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief  Inicializacao da BSP.
 * @details Inicia o temporizador de amostragem, ativa os canais PWM e
 * garante que todos os LEDs comecem fisicamente em 0% (apagados).
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Init(void) {
    Bsp_TimerSampling_StartIT();
    Bsp_Pwm_StartAll();

    // Garante que todos os LEDs comecem fisicamente em 0% (apagados)
    Bsp_Pwm_SetDuty(TIM_CHANNEL_1, 0);
    Bsp_Pwm_SetDuty(TIM_CHANNEL_2, 0);
    Bsp_Pwm_SetDuty(TIM_CHANNEL_3, 0);
}

/******************************************************************************/
/** @brief  Inicia a conversao do ADC.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Adc_Start(void) {
    HAL_ADC_Start(&hadc1);
}

/******************************************************************************/
/** @brief  Realiza a leitura do valor convertido pelo ADC via polling.
 * @retval Valor da conversao do ADC (0 a 4095) ou 0 em caso de falha.
 ******************************************************************************/
uint32_t Bsp_Adc_GetValue(void) {
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
        return HAL_ADC_GetValue(&hadc1);
    }
    return 0;
}

/******************************************************************************/
/** @brief  Inicia a geracao de sinal PWM em todos os canais utilizados.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Pwm_StartAll(void) {
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

/******************************************************************************/
/** @brief  Ajusta o Duty Cycle de um canal especifico do PWM.
 * @param  channel: Canal do Timer (ex: TIM_CHANNEL_1).
 * @param  duty: Valor de comparacao (Duty Cycle) a ser aplicado.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Pwm_SetDuty(uint32_t channel, uint32_t duty) {
    __HAL_TIM_SET_COMPARE(&htim3, channel, duty);
}

/******************************************************************************/
/** @brief  Inicia a recepcao de dados via UART por interrupcao.
 * @param  pData: Ponteiro para o buffer de recepcao.
 * @param  size: Quantidade de bytes a serem recebidos.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Uart_ReceiveIT(uint8_t *pData, uint16_t size) {
    HAL_UART_Receive_IT(&huart3, pData, size);
}

/******************************************************************************/
/** @brief  Transmite dados via UART de forma bloqueante (Polling).
 * @param  pData: Ponteiro para o buffer de transmissao.
 * @param  size: Quantidade de bytes a serem transmitidos.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Uart_Transmit(uint8_t *pData, uint16_t size) {
    HAL_UART_Transmit(&huart3, pData, size, 100);
}

/******************************************************************************/
/** @brief  Realiza a leitura fisica do pino do botao.
 * @retval true se o botao estiver pressionado (Nivel Baixo), false se solto.
 ******************************************************************************/
bool Bsp_Button_Read(void) {
    return (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET);
}

bool Bsp_IsButtonPressed(void) {
    // Esta função encapsula a lógica que você já tem no arquivo ou
    // chama a leitura direta se for o caso.
    // Se você não quiser mover a lógica complexa, use apenas o retorno:
    return Bsp_Button_Read();
}

/******************************************************************************/
/** @brief  Inicia o temporizador de amostragem por interrupcao (TIM2).
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_TimerSampling_StartIT(void) {
    HAL_TIM_Base_Start_IT(&htim2);
}

/******************************************************************************/
/** @brief  Zera o contador e inicia o temporizador de debounce (TIM4).
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_TimerDebounce_StartIT(void) {
    __HAL_TIM_SET_COUNTER(&htim4, 0);
    HAL_TIM_Base_Start_IT(&htim4);
}

/******************************************************************************/
/** @brief  Para o temporizador de debounce (TIM4) apos a validacao.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_TimerDebounce_StopIT(void) {
    HAL_TIM_Base_Stop_IT(&htim4);
}

/** @} DOXYGEN GROUP TAG END OF FILE */
