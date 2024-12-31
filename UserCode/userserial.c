/*
 * userserial.c
 *
 *  Created on: Dec 25, 2024
 *      Author: Delta
 */

#include <userserial.h>

Uint16 len; // Used for checking the received data
char rdata[BUFFER_SIZE];

void UART_GPIO_init(uint32_t base)
{
    if (base == SCIA_BASE)
    {
        GPIO_setPinConfig(GPIO_43_SCIRXDA);
        GPIO_setPinConfig(GPIO_42_SCITXDA);
    }
    else if (base == SCIB_BASE)
    {
        GPIO_setPinConfig(GPIO_19_SCIRXDB);
        GPIO_setPinConfig(GPIO_18_SCITXDB);
    }
    else if (base == SCIC_BASE)
    {
        GPIO_setPinConfig(GPIO_139_SCIRXDC);
        GPIO_setPinConfig(GPIO_56_SCITXDC);
    }
}

void UART_init(uint32_t base, uint32_t baud)
{

    SCI_performSoftwareReset(base);

    SCI_setConfig(base, DEVICE_LSPCLK_FREQ, baud, (SCI_CONFIG_WLEN_8 |
    SCI_CONFIG_STOP_ONE | SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(base);
    SCI_clearInterruptStatus(base, SCI_INT_RXRDY_BRKDT);
    SCI_enableModule(base);
    SCI_performSoftwareReset(base);

    SCI_enableInterrupt(base, SCI_INT_RXRDY_BRKDT);

#ifdef AUTOBAUD
       //
       // Perform an autobaud lock.
       // SCI expects an 'a' or 'A' to lock the baud rate.
       //
       SCI_lockAutobaud(base);
   #endif
}

//This function is for sending data using SCI communication
//##########################################################
void Send_Serial(uint32_t base, const uint16_t *data, uint16_t length)
{
    SCI_writeCharArray(base, data, length);
    SCI_writeCharArray(base, (uint16_t*) "\r\n", 2);
}

//This function is for reading data using SCI communication with polling protocol
//################################################################################
int Recive_Serial(uint32_t base, uint16_t *data)
{
    uint16_t rxStatus = 0U;
    rxStatus = SCI_getRxStatus(base);
    if ((rxStatus & SCI_RXSTATUS_ERROR) != 0)
    {
        //
        //If Execution stops here there is some error
        //Analyze SCI_getRxStatus() API return value
        //
        return 0;
    }
    else
    {
        *data = SCI_readCharBlockingFIFO(base);
        return 1;
    }
}

//This function is for reading data using SCI communication with interrupt protocol
//##################################################################################
__interrupt void scicRxISR(void)
{

    rdata[len] = ScicRegs.SCIRXBUF.all;
    len++;

    if (len >= BUFFER_SIZE)
        len = 0;

    PieCtrlRegs.PIEACK.all |= 0x100;       // Issue PIE ack
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}
