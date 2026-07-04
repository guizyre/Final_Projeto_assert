/******************************************************************************/
/**
 * @file    Button.h
 * @addtogroup BUTTON
 * @brief   Cabecalho do gerenciamento do botao do usuario.
 * @author  Guilherme Gonçalves
 * @{
 ******************************************************************************/

#ifndef _BUTTON_H_
#define _BUTTON_H_

/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/
#include <stdbool.h>

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

/** @brief Processa a logica de debounce e alternancia do estado do sistema. */
void Button_ProcessDebounce(void);

/** @brief Retorna o estado atual de congelamento do sistema.
 * @retval true se o sistema estiver congelado, false caso contrario. */
bool Button_IsFrozen(void);

#endif /* _BUTTON_H_ */

/** @} DOXYGEN GROUP TAG END OF FILE */
