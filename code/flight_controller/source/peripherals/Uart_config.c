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
                },
            .rxInitStruct = 
                {
                    .Alternate  = GPIO_AF7_USART1,
                    .Mode       = GPIO_MODE_AF_OD,
                    .Pin        = GPIO_PIN_10,
                    .Pull       = GPIO_NOPULL,
                    .Speed      = GPIO_SPEED_HIGH
                },
            .rxPort = GPIOA,
            .txInitStruct = 
                {
                    .Alternate  = GPIO_AF7_USART1,
                    .Mode       = GPIO_MODE_AF_OD,
                    .Pin        = GPIO_PIN_9,
                    .Pull       = GPIO_NOPULL,
                    .Speed      = GPIO_SPEED_HIGH
                },
            .txPort = GPIOA
        },
        {
            .instance = Uart2,

            .halHandle =
                {
                    .Init =
                        {
                            .BaudRate       = 38400u,
                            .HwFlowCtl      = UART_HWCONTROL_NONE,
                            .Mode           = UART_MODE_TX_RX,
                            .OverSampling   = UART_OVERSAMPLING_16,
                            .Parity         = UART_PARITY_NONE,
                            .StopBits       = UART_STOPBITS_1,
                            .WordLength     = UART_WORDLENGTH_8B
                        },
                    .Instance = USART2
                },
            .rxInitStruct = 
                {
                    .Alternate  = GPIO_AF7_USART2,
                    .Mode       = GPIO_MODE_AF_OD,
                    .Pin        = GPIO_PIN_6,
                    .Pull       = GPIO_NOPULL,
                    .Speed      = GPIO_SPEED_HIGH
                },
            .rxPort = GPIOD,
            .txInitStruct = 
                {
                    .Alternate  = GPIO_AF7_USART2,
                    .Mode       = GPIO_MODE_AF_OD,
                    .Pin        = GPIO_PIN_5,
                    .Pull       = GPIO_NOPULL,
                    .Speed      = GPIO_SPEED_HIGH
                },
            .txPort = GPIOD
        }
    };
