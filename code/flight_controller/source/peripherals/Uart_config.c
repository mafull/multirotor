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
          |Inst.  | UART Init Struct
        */
        { USART1, { 115200, UART_WORDLENGTH_8B, UART_STOPBITS_1, UART_PARITY_NONE, UART_MODE_TX_RX, UART_HWCONTROL_NONE, UART_OVERSAMPLING_16} }, // Uart1
        { USART2, {  38400, UART_WORDLENGTH_8B, UART_STOPBITS_1, UART_PARITY_NONE, UART_MODE_TX_RX, UART_HWCONTROL_NONE, UART_OVERSAMPLING_16} }, // Uart2
    };
