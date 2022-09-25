/*
 * indicator-7seg.c
 *
 *  Created on: 6 серп. 2022 р.
 *      Author: chorn
 */
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <indicator-7seg.h>

/*******************************************************************************
* Function Name: init_7seg
*******************************************************************************/
 void init_7seg()
 {
    cy_rslt_t result;

    const cyhal_timer_cfg_t timer_7seg__cfg =
    {
        .compare_value = 0,                 /* Timer compare value, not used */
        .period = SEG_BLINK_TIMER_PERIOD,   /* Defines the timer period */
        .direction = CYHAL_TIMER_DIR_UP,    /* Timer counts up */
        .is_compare = false,                /* Don't use compare mode */
        .is_continuous = true,              /* Run timer indefinitely */
        .value = 0                          /* Initial value of counter */
    };
    result = cyhal_timer_init(&timer_7seg, NC, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }


    cyhal_timer_configure(&timer_7seg, &timer_7seg__cfg);
    cyhal_timer_set_frequency(&timer_7seg, SEG_BLINK_TIMER_CLOCK_HZ);
    cyhal_timer_register_callback(&timer_7seg, outp_value_7seg, NULL);
    cyhal_timer_enable_event(&timer_7seg, CYHAL_TIMER_IRQ_TERMINAL_COUNT, 7, true);
    cyhal_timer_start(&timer_7seg);


    result = cyhal_gpio_init(P6_0, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P6_1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P6_2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P6_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P5_0, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P5_1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P5_2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P5_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P5_4, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P5_5, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	result = cyhal_gpio_init(P5_6, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
 }


 /*******************************************************************************
 * Function Name: outp_value_7seg
 *******************************************************************************/
 void outp_value_7seg(void *callback_arg, cyhal_timer_event_t event)
 {
     (void) callback_arg;
     (void) event;

 	 switch(curSeg){
 	 case ONES:
 	 {
 		 cyhal_gpio_write(P6_0, true);
 		 cyhal_gpio_write(P6_1, false);
 		 cyhal_gpio_write(P6_2, false);
 		 cyhal_gpio_write(P6_3, false);

 		 cyhal_gpio_write(P5_0, (bool)(segCodes[0] & 0x01));
 		 cyhal_gpio_write(P5_1, (bool)(segCodes[0] & 0x02));
 		 cyhal_gpio_write(P5_2, (bool)(segCodes[0] & 0x04));
 		 cyhal_gpio_write(P5_3, (bool)(segCodes[0] & 0x08));
 		 cyhal_gpio_write(P5_4, (bool)(segCodes[0] & 0x10));
 		 cyhal_gpio_write(P5_5, (bool)(segCodes[0] & 0x20));
 		 cyhal_gpio_write(P5_6, (bool)(segCodes[0] & 0x40));

 		 curSeg = DECS;
 		 break;
 	 }
 	 case DECS:
 	 {
 		 cyhal_gpio_write(P6_0, false);
 		 cyhal_gpio_write(P6_1, true);
 		 cyhal_gpio_write(P6_2, false);
 		 cyhal_gpio_write(P6_3, false);

 		 cyhal_gpio_write(P5_0, (bool)(segCodes[1] & 0x01));
 		 cyhal_gpio_write(P5_1, (bool)(segCodes[1] & 0x02));
 		 cyhal_gpio_write(P5_2, (bool)(segCodes[1] & 0x04));
 		 cyhal_gpio_write(P5_3, (bool)(segCodes[1] & 0x08));
 		 cyhal_gpio_write(P5_4, (bool)(segCodes[1] & 0x10));
 		 cyhal_gpio_write(P5_5, (bool)(segCodes[1] & 0x20));
 		 cyhal_gpio_write(P5_6, (bool)(segCodes[1] & 0x40));

 		 curSeg = HUND;
 		 break;
 	 }
 	 case HUND:
 	 {
 		 cyhal_gpio_write(P6_0, false);
 		 cyhal_gpio_write(P6_1, false);
 		 cyhal_gpio_write(P6_2, true);
 		 cyhal_gpio_write(P6_3, false);

 		 cyhal_gpio_write(P5_0, (bool)(segCodes[2] & 0x01));
 		 cyhal_gpio_write(P5_1, (bool)(segCodes[2] & 0x02));
 		 cyhal_gpio_write(P5_2, (bool)(segCodes[2] & 0x04));
 		 cyhal_gpio_write(P5_3, (bool)(segCodes[2] & 0x08));
 		 cyhal_gpio_write(P5_4, (bool)(segCodes[2] & 0x10));
 		 cyhal_gpio_write(P5_5, (bool)(segCodes[2] & 0x20));
 		 cyhal_gpio_write(P5_6, (bool)(segCodes[2] & 0x40));

 		 curSeg = PNTR;
 		 break;
 	 }
 	 case PNTR:
 	 {
 		 cyhal_gpio_write(P6_0, false);
 		 cyhal_gpio_write(P6_1, false);
 		 cyhal_gpio_write(P6_2, false);
 		 cyhal_gpio_write(P6_3, true);

 		 cyhal_gpio_write(P5_0, (bool)(segCodes[3] & 0x01));
 		 cyhal_gpio_write(P5_1, (bool)(segCodes[3] & 0x02));
 		 cyhal_gpio_write(P5_2, (bool)(segCodes[3] & 0x04));
 		 cyhal_gpio_write(P5_3, (bool)(segCodes[3] & 0x08));
 		 cyhal_gpio_write(P5_4, (bool)(segCodes[3] & 0x10));
 		 cyhal_gpio_write(P5_5, (bool)(segCodes[3] & 0x20));
 		 cyhal_gpio_write(P5_6, (bool)(segCodes[3] & 0x40));


 		 curSeg = ONES;
 		 break;
 	 }

 	 default:
 	 {
 		 curSeg = ONES;
 		 break;
 	 }
 	 }
 }


 /*******************************************************************************
 * Function Name: set_val_7seg
 *******************************************************************************/
 void set_val_7seg(uint32 value_voltage)
 {
	 if (1 < value_voltage && value_voltage < 1000)
	 {
		 segCodes [0] = digitCodes [value_voltage/100];
		 segCodes [1] = digitCodes [(value_voltage/10)%10];
		 segCodes [2] = digitCodes [value_voltage%10];
		 segCodes[3] = 0x3Eu;
	 }
 }
