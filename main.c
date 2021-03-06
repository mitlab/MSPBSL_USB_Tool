// (c)2010 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-TEST (CDC Driver)			              |
|                                                                             |
+-----------------------------------------------------------------------------*/
/*  Source: main.c, v2.0 2011/05/10        
-------------------------------------------------------------------------------+
 This firmware evaluates CDC bandwidth and latency. 
------------------------------------------------------------------------------*/
#include <MSP430.h>
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"      // Basic Type declarations
#include "USB_API/USB_Common/usb.h"        // USB-specific functions
#include "USB_config/descriptors.h"
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "usb/usbConstructs.h"

#include "main.h"
#include "initMCU.h"
#include "timer.h"

#include <intrinsics.h>
#include <string.h>

//------------------------------------------------------------------------------
VOID BlinkLed(VOID)
{
    //static BYTE nCount = 0;

    //if(nCount++ > 100)
    //{ 
    //    nCount = 0;
        TogglePin(1,0);// Toggle LED P1.0
    //}  
}

/*----------------------------------------------------------------------------+
| Main Routine                                                                |
+----------------------------------------------------------------------------*/
VOID main(VOID)
{
    Init_StartUp();			//initialize device
    ConfigUSB();			//configure USB
    Delay(3000000);                     // !!! Do not remove this delay !!!
    Init_TimerA2();

    __enable_interrupt();               // enable global interrupts
    while(1);

} //main()

//------------------------------------------------------------------------------
#pragma vector = UNMI_VECTOR
__interrupt VOID UNMI_ISR(VOID)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
    case SYSUNIV_NONE:
      __no_operation();
      break;
    case SYSUNIV_NMIIFG:
      __no_operation();
      break;
    case SYSUNIV_OFIFG:
      UCSCTL7 &= ~(DCOFFG+0+0+0); // Clear OSC flaut Flags fault flags
      SFRIFG1 &= ~OFIFG;          // Clear OFIFG fault flag
      break;
    case SYSUNIV_ACCVIFG:
      __no_operation();
      break;
    case SYSUNIV_BUSIFG:
      SYSBERRIV = 0;            // clear bus error flag
      USB_disable();            // Disable
    }
}

//------------------------------------------------------------------------------
//End of file.
//------------------------------------------------------------------------------
