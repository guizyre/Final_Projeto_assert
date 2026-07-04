/******************************************************************************/
/**
 * @file    Sampler.h
 * @addtogroup SAMPLER
 * @brief   Cabecalho do modulo de aquisicao e filtragem de sinais.
 * @author  Hillary Maximino Andrade
 * @{
 ******************************************************************************/

#ifndef _SAMPLER_H_
#define _SAMPLER_H_

/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * DEFINES PUBLICOS
 ******************************************************************************/

/// Quantidade de amostras para o calculo da media movel
#define SAMPLER_MAX_SAMPLES    100

/// Resolucao maxima do ADC (12 bits = 4095)
#define ADC_MAX_RESOLUTION     4095

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

/** @brief Adiciona uma nova amostra do ADC ao filtro.
 * @param adcValue: Valor bruto lido do ADC.
 * @retval true se a media foi recalculada, false caso contrario. */
bool Sampler_AddSample(uint32_t adcValue);

/** @brief Retorna a ultima media calculada em porcentagem.
 * @retval Valor percentual (0 a 100%). */
uint8_t Sampler_GetAveragePercent(void);

#endif /* _SAMPLER_H_ */

/** @} DOXYGEN GROUP TAG END OF FILE */
