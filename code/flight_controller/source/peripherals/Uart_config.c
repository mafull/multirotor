// --- Private header ---
#define UART_PRIVATE
    #include "peripherals/Uart_private.h"
#undef UART_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const Uart_ConfigData_t Uart_configData[Uart_Instance_MAX] = 
    {
        /*
                    |Instance
                    |       | UART Init Struct
                    |       | | Baud Rate
                    |       | |       | Word Length       | Stop Bits      | Parity          | Mode           | HW Flow Control    | Oversampling         | DMA Instance RX | DMA Instance TX (MAX if unused)
        */
        [Uart1] = { USART1, { 115200, UART_WORDLENGTH_8B, UART_STOPBITS_1, UART_PARITY_NONE, UART_MODE_TX_RX, UART_HWCONTROL_NONE, UART_OVERSAMPLING_16}, Dma_Instance_MAX, Dma2_7 },
        [Uart2] = { USART2, {  38400, UART_WORDLENGTH_8B, UART_STOPBITS_1, UART_PARITY_NONE, UART_MODE_TX_RX, UART_HWCONTROL_NONE, UART_OVERSAMPLING_16}, Dma_Instance_MAX, Dma_Instance_MAX },
    };
