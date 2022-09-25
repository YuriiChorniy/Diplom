/*
 * indicator-7seg.h
 *
 *  Created on: 6 серп. 2022 р.
 *      Author: chorn
 */
/*******************************************************************************
* Macros
*******************************************************************************/
#define ONES (1u)
#define DECS (10u)
#define HUND (100u)
#define PNTR (0u)
#define SEG_BLINK_TIMER_CLOCK_HZ          (10000)
#define SEG_BLINK_TIMER_PERIOD            (1)


/*******************************************************************************
* Global Variables
*******************************************************************************/
static int curSeg = ONES;
static cyhal_timer_t timer_7seg;
static int segCodes [4];
static const int digitCodes [10] = {0x3F,0x06,0x5b,0x4F,0x66,0x6d,0x7D,0x07,0x7F,0x6F};

/*******************************************************************************
* Function Name: init_7seg
*******************************************************************************/
 void init_7seg();
 void outp_value_7seg(void *callback_arg, cyhal_timer_event_t event);
 void set_val_7seg(uint32 value_voltage);
