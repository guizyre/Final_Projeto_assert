/******************************************************************************/
/**
 * @file    Orchestrator.h
 * @addtogroup ORCHESTRATOR
 * @brief   Cabecalho do modulo principal de controle (Orquestrador).
 * @author  Guilherme Gonçalves
 * @{
 ******************************************************************************/

#ifndef _ORCHESTRATOR_H_
#define _ORCHESTRATOR_H_

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

/** @brief Inicializa os perifericos e modulos do sistema. */
void Orchestrator_Init(void);

/** @brief Loop principal de execucao que delega as tarefas de processamento. */
void Orchestrator_Run(void);

/** @brief Processa a logica do botao do usuario. */
void Orchestrator_ProcessButton(void);

/** @brief Realiza a amostragem do ADC, atualizacao do PWM e interface UART. */
void Orchestrator_ProcessSamplingAndUI(void);

/** @brief Interpreta comandos recebidos via interface serial (USART3). */
void Orchestrator_ProcessUartCommand(void);

#endif /* _ORCHESTRATOR_H_ */

/** @} DOXYGEN GROUP TAG END OF FILE */
