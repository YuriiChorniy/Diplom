#include "math.h"
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

void SAR_Interrupt(void);
volatile float accVoltage;

int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    init_cycfg_all();

    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    __enable_irq();
    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);

    /* retarget-io init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    Cy_TCPWM_Counter_Init(ADC_TRIG_TIMER_HW, ADC_TRIG_TIMER_NUM, &ADC_TRIG_TIMER_config);
    Cy_TCPWM_Counter_Enable(ADC_TRIG_TIMER_HW, ADC_TRIG_TIMER_NUM);
    Cy_TCPWM_TriggerStart_Single(ADC_TRIG_TIMER_HW, ADC_TRIG_TIMER_NUM);

    Cy_SysAnalog_Init(&SYS_ANALOG_config);

    /* Turn on the hardware block. */
    Cy_SysAnalog_Enable();

    /* Scenario: Configure and enable the SAR interrupt. */

    const cy_stc_sysint_t ADC_IRQ_cfg = {
            /* .intrSrc         = */ pass_interrupt_sar_IRQn,   /* Interrupt source is the SAR interrupt */
            /* .intrPriority    = */ 3UL                        /* Interrupt priority is 3 */
    };

    /* Configure the interrupt with vector at SAR_Interrupt(). */
    (void)Cy_SysInt_Init(&ADC_IRQ_cfg, SAR_Interrupt);
    /* Enable the interrupt. */
    NVIC_EnableIRQ(ADC_IRQ_cfg.intrSrc);

    Cy_SAR_Init(ADC_IN_HW, &ADC_IN_config);
    /* Turn on the SAR hardware. */
    Cy_SAR_Enable(ADC_IN_HW);
    /* Begin continuous conversions. */
    Cy_SAR_StartConvert(ADC_IN_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);

    for (;;)
    {
    	accVoltage *= ((float)1u / (float)20u); /* 1/T = 1 / 20mS  */
    	accVoltage = sqrt(accVoltage);
    	printf("%fmV    %fV\r\n", accVoltage, (accVoltage * 0.3304f));
    	Cy_SysLib_Delay(150u);
    }
}

void SAR_Interrupt(void)
{
	static uint32_t tmpVoltage = 0u;
	static uint32_t tmpResult = 0u;
	static uint32_t sampleNum = 0u;

    uint32_t intr_status = 0u;
    /* Read interrupt status register. */
    intr_status = Cy_SAR_GetInterruptStatus(SAR);

    /* Check what triggered the interrupt. */
    if ((intr_status & (uint32_t) CY_SAR_INTR_EOS) == (uint32_t) CY_SAR_INTR_EOS)
    {
    	if(sampleNum > 0u)
    	{
    		sampleNum--;
    		tmpVoltage = Cy_SAR_GetResult32(SAR, 0u);
    		tmpVoltage = Cy_SAR_CountsTo_mVolts(SAR, 0u, tmpVoltage);
    		tmpResult += ((tmpVoltage * tmpVoltage) * 1/4u /* ms */);
    	}
    	else
    	{
    		sampleNum = 80u;
    		accVoltage = (float)tmpResult;
    		tmpResult = 0u;
    	}
    }

    Cy_SAR_ClearInterrupt(SAR, intr_status);
}
/* [] END OF FILE */
