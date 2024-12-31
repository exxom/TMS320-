/*
 * usergpio.c
 *
 *  Created on: Dec 25, 2024
 *      Author: Delta
 */
#include <usergpio.h>

void GPIO_init_Pin()
{
    EALLOW;

    //GPIO32 set output
    GPIO_setPinConfig(GPIO_32_GPIO32);
    GPIO_setPadConfig(LED_RED, GPIO_PIN_TYPE_STD);
    GPIO_writePin(LED_RED, 0);
    GPIO_setDirectionMode(LED_RED, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(LED_RED, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(LED_RED, GPIO_QUAL_SYNC);

    //GPIO2 set output
    GPIO_setPinConfig(GPIO_123_GPIO123);
    GPIO_setPadConfig(LED_GREEN, GPIO_PIN_TYPE_STD);
    GPIO_writePin(LED_GREEN, 0);
    GPIO_setDirectionMode(LED_GREEN, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(LED_GREEN, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(LED_GREEN, GPIO_QUAL_SYNC);

    EDIS;
}
