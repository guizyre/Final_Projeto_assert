/******************************************************************************/
/**
 * @file    Sampler.c
 * @addtogroup SAMPLER
 * @brief   Modulo de aquisicao e filtragem de sinais analogicos.
 * @author  Hillary Maximino Andrade
 * @details
 * \n <b>Ferramentas:</b>
 * - STM32CubeIDE, STM32CubeMX.
 *
 * \n <b>Observacoes:</b>
 * - Realiza media aritmetica de N amostras para atenuar ruidos.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "Sampler.h"

/*******************************************************************************
 * VARIAVEIS LOCAIS
 ******************************************************************************/

/// Acumulador da soma das amostras
static uint32_t sampleSum = 0;

/// Contador de amostras coletadas
static uint16_t sampleCount = 0;

/// Ultima media convertida para porcentagem (0-100%)
static uint8_t lastAveragePercent = 0;

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief  Adiciona uma nova amostra do ADC e processa a media quando necessario.
 * @param  adcValue: Valor bruto lido do ADC.
 * @retval true se uma nova media foi calculada, false caso contrario.
 ******************************************************************************/
bool Sampler_AddSample(uint32_t adcValue) {
    sampleSum += adcValue;
    sampleCount++;

    if (sampleCount >= SAMPLER_MAX_SAMPLES) {
        // Calcula a media aritmetica
        uint32_t average = sampleSum / SAMPLER_MAX_SAMPLES;

        // Converte para escala de 0 a 100%
        uint32_t rawPercent = (average * 100) / ADC_MAX_RESOLUTION;
        lastAveragePercent = (uint8_t)(rawPercent > 100 ? 100 : rawPercent);

        // Reseta o filtro para a proxima janela
        sampleSum = 0;
        sampleCount = 0;
        return true;
    }
    return false;
}

/******************************************************************************/
/** @brief  Retorna o valor da ultima media calculada em porcentagem.
 * @retval Valor percentual (0 a 100%).
 ******************************************************************************/
uint8_t Sampler_GetAveragePercent(void) {
    return lastAveragePercent;
}

/** @} DOXYGEN GROUP TAG END OF FILE */
