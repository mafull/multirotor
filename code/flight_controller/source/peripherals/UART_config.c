// --- Private header ---
#define UART_PRIVATE
    #include "UART_private.h"
#undef UART_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

UART_Handle_t UART_handles[UART_Instance_MAX] = 
    {
        // UART1
        {
            .instance = UART_Instance_UART1,
            .halHandle = {
                .Instance = USART1,
                .Init =
                    {
                        .BaudRate       = 115200,
                        .HwFlowCtl      = UART_HWCONTROL_NONE,
                        .Mode           = UART_MODE_TX_RX,
                        .OverSampling   = UART_OVERSAMPLING_16,
                        .Parity         = UART_PARITY_NONE,
                        .StopBits       = UART_STOPBITS_1,
                        .WordLength     = UART_WORDLENGTH_8B
                    }
                }
        },

        // UART2
        {
            .instance = UART_Instance_UART2,
            .halHandle = {
                .Instance = USART2,
                .Init =
                    {
                        .BaudRate       = 115200,
                        .HwFlowCtl      = UART_HWCONTROL_NONE,
                        .Mode           = UART_MODE_TX_RX,
                        .OverSampling   = UART_OVERSAMPLING_16,
                        .Parity         = UART_PARITY_NONE,
                        .StopBits       = UART_STOPBITS_1,
                        .WordLength     = UART_WORDLENGTH_8B
                    }
                }
        }
    };
