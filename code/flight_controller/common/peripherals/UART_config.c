// --- Private header ---
#define UART_PRIVATE
    #include "UART_private.h"
#undef UART_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

UART_HandleTypeDef UART_handles[UART_Instance_MAX] = 
    {
        // UART1
        {
            .instance = UART_Instance_UART1,
            .initialised = false,
            .halHandle = {
                .Instance = USART1,
                .Init =
                    {
                        .BaudRate       = UART1_BAUD_RATE,
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
            .initialised = false,
            .halHandle = {
                .Instance = USART2,
                .Init =
                    {
                        .BaudRate       = UART2_BAUD_RATE,
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
