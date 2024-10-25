#include "UART.h"

meter_attrib_t meter_attrib;

void UART_init()
{
    /*MOCKED*/
    meter_attrib.uart_type = _232;
    meter_attrib.protocol_type = ABNT;
    /*MOCKED*/
}

void UART_task(void *args)
{

}