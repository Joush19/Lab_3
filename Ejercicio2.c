//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2013-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int
main(void)
{
    //volatile uint32_t ui32Loop;
    uint8_t count1 = 0;
    uint8_t c = atoi("3");
    
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
    
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    {
    }

    //
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, 0x03);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x11);
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, 0x03);
    GPIOPadConfigSet(GPIO_PORTJ_BASE, 0X03, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //
    // Loop forever.
    //
    while(1)
    {   
        if (GPIOPinRead(GPIO_PORTJ_BASE, 0x01) == 0){
            count1 = 1;
        }
        
        else if (GPIOPinRead(GPIO_PORTJ_BASE, 0x02) == 0){
            count1 = 0;
        }
        if (count1 == 0){
            GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x02);
            SysCtlDelay(5000000);
            GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x03);
            SysCtlDelay(5000000);
            GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x10);   
            SysCtlDelay(5000000);
            GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x11);   
            SysCtlDelay(5000000);
        }
        else if (count1 == 1){
            GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x11);
            GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x03);
            SysCtlDelay(5000000);
            GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x10);
            GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x03);
            SysCtlDelay(5000000);
            GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x0);
            GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x03);   
            SysCtlDelay(5000000);
            GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x02);   
            SysCtlDelay(5000000);
        }
        
        
        //
        // Turn on the LED.
        //
                
        GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x0);
        GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x0); 
        SysCtlDelay(2000000);  
        //
        // Delay for a bit.
        //
        /*for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
        {
        }
	*/
        //
        // Turn off the LED.
        //
        
        //
        // Delay for a bit.
        //
        /*for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
        {
        }*/
    }
}
