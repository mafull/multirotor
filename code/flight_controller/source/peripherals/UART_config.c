// --- Private header ---
#define UART_PRIVATE
    #include "peripherals/Uart_private.h"
#undef UART_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

Uart_Handle_t Uart_handles[Uart_Instance_MAX] = 
    {
        {
            .instance = Uart1,

            .halHandle =
                {
                    .Init =
                        {
                            .BaudRate       = 115200u,
                            .HwFlowCtl      = UART_HWCONTROL_NONE,
                            .Mode           = UART_MODE_TX_RX,
                            .OverSampling   = UART_OVERSAMPLING_16,
                            .Parity         = UART_PARITY_NONE,
                            .StopBits       = UART_STOPBITS_1,
                            .WordLength     = UART_WORDLENGTH_8B
                        },
                    .Instance = USART1
                }
        },
        {
            .instance = Uart2,

            .halHandle =
                {
                    .Init =
                        {
                            .BaudRate       = 115200u,
                            .HwFlowCtl      = UART_HWCONTROL_NONE,
                            .Mode           = UART_MODE_TX_RX,
                            .OverSampling   = UART_OVERSAMPLING_16,
                            .Parity         = UART_PARITY_NONE,
                            .StopBits       = UART_STOPBITS_1,
                            .WordLength     = UART_WORDLENGTH_8B
                        },
                    .Instance = USART2
                }
        }
    };
