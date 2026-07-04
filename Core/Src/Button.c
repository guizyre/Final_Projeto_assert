/******************************************************************************/
/**
 * @file    Button.c
 * @addtogroup BUTTON
 * @brief   Gerenciamento do botao do usuario com logica de congelamento.
 * @author  Hillary Maximino Andrade
 * @details
 * \n <b>Ferramentas:</b>
 * - STM32CubeIDE, STM32CubeMX.
 *
 * \n <b>Observacoes:</b>
 * - Utiliza a camada BSP para leitura tratada do hardware.
 * - Implementa logica de alternancia (toggle) para o estado do sistema.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "Button.h"
#include "Bsp.h"

/*******************************************************************************
 * VARIAVEIS LOCAIS
 ******************************************************************************/

/// Estado atual do congelamento do sistema (true = congelado/OFF)
static bool isSystemFrozen = false;

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief  Processa o estado do botao para alternar o congelamento do sistema.
 * @details Verifica se o botao foi pressionado via BSP e alterna a flag de controle.
 * @retval Nenhum.
 ******************************************************************************/
void Button_ProcessDebounce(void) {
    // Usamos a funcao da BSP que ja trata o debounce de forma segura
    if (Bsp_IsButtonPressed()) {
        isSystemFrozen = !isSystemFrozen;
    }
}

/******************************************************************************/
/** @brief  Retorna o estado de congelamento atual.
 * @retval true se o sistema estiver congelado, false caso contrario.
 ******************************************************************************/
bool Button_IsFrozen(void) {
    return isSystemFrozen;
}

/** @} DOXYGEN GROUP TAG END OF FILE */
