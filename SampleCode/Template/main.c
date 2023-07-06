/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#include "misc_config.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

struct flag_32bit flag_PROJ_CTL;
#define FLAG_PROJ_TIMER_PERIOD_1000MS                 	(flag_PROJ_CTL.bit0)
#define FLAG_PROJ_REVERSE1                   			(flag_PROJ_CTL.bit1)
#define FLAG_PROJ_REVERSE2                 				(flag_PROJ_CTL.bit2)
#define FLAG_PROJ_REVERSE3                              (flag_PROJ_CTL.bit3)
#define FLAG_PROJ_REVERSE4                              (flag_PROJ_CTL.bit4)
#define FLAG_PROJ_REVERSE5                              (flag_PROJ_CTL.bit5)
#define FLAG_PROJ_REVERSE6                              (flag_PROJ_CTL.bit6)
#define FLAG_PROJ_REVERSE7                              (flag_PROJ_CTL.bit7)


/*_____ D E F I N I T I O N S ______________________________________________*/

volatile unsigned int counter_systick = 0;
volatile uint32_t counter_tick = 0;

#define MULTI_WORD_PROG_LEN                             128          /* The maximum length is 128. */
#define APROM_TEST_BASE                                 0x8000

uint32_t g_au32page_buff0[FMC_FLASH_PAGE_SIZE / 4] = {0};
uint32_t g_au32page_buff1[FMC_FLASH_PAGE_SIZE / 4] = {0};
uint32_t g_au32page_buff2[FMC_FLASH_PAGE_SIZE / 4] = {0};
uint32_t g_au32page_buff3[FMC_FLASH_PAGE_SIZE / 4] = {0};
/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

unsigned int get_systick(void)
{
	return (counter_systick);
}

void set_systick(unsigned int t)
{
	counter_systick = t;
}

void systick_counter(void)
{
	counter_systick++;
}

void SysTick_Handler(void)
{

    systick_counter();

    if (get_systick() >= 0xFFFFFFFF)
    {
        set_systick(0);      
    }

    // if ((get_systick() % 1000) == 0)
    // {
       
    // }

    #if defined (ENABLE_TICK_EVENT)
    TickCheckTickEvent();
    #endif    
}

void SysTick_delay(unsigned int delay)
{  
    
    unsigned int tickstart = get_systick(); 
    unsigned int wait = delay; 

    while((get_systick() - tickstart) < wait) 
    { 
    } 

}

void SysTick_enable(unsigned int ticks_per_second)
{
    set_systick(0);
    if (SysTick_Config(SystemCoreClock / ticks_per_second))
    {
        /* Setup SysTick Timer for 1 second interrupts  */
        printf("Set system tick error!!\n");
        while (1);
    }

    #if defined (ENABLE_TICK_EVENT)
    TickInitTickEvent();
    #endif
}

uint32_t get_tick(void)
{
	return (counter_tick);
}

void set_tick(uint32_t t)
{
	counter_tick = t;
}

void tick_counter(void)
{
	counter_tick++;
    if (get_tick() >= 60000)
    {
        set_tick(0);
    }
}

// void delay_ms(uint16_t ms)
// {
// 	TIMER_Delay(TIMER0, 1000*ms);
// }


void FMC_WRITEDATA(void)
{
    uint32_t u32addr = APROM_TEST_BASE;
    uint32_t u32maddr = 0;
    uint32_t u32LoopCnt = 0;

    SYS_UnlockReg();	
    FMC_Open();
    FMC_ENABLE_AP_UPDATE();    	

    if (FMC_Erase(u32addr) < 0)
    {
        printf("Erase error\r\n");
    }
   
    #if 1
    for (u32LoopCnt = 0; u32LoopCnt < MULTI_WORD_PROG_LEN; u32LoopCnt += 4)
    {
        g_au32page_buff0[u32LoopCnt / 4] = 0x5A5A0000 + u32LoopCnt;//
        printf("u32LoopCnt = 0x%2X(%3d,%3d) , 0x%8X\r\n",u32LoopCnt,u32LoopCnt , u32LoopCnt / 4 , g_au32page_buff0[u32LoopCnt / 4]);
        
    }

    /* execute multi-word program */
    if (FMC_Write128(u32addr + MULTI_WORD_PROG_LEN*0, g_au32page_buff0) != 0)
    {
        printf("Write128 error\r\n");
    }
    #endif

    #if 0
    for (u32LoopCnt = 0; u32LoopCnt < MULTI_WORD_PROG_LEN; u32LoopCnt += 4)
    {
        g_au32page_buff1[u32LoopCnt / 4] = 0x6A6A0000 + u32LoopCnt;//
        printf("u32LoopCnt = 0x%2X(%3d,%3d) , 0x%8X\r\n",u32LoopCnt,u32LoopCnt , u32LoopCnt / 4 , g_au32page_buff1[u32LoopCnt / 4]);
        
    }

    /* execute multi-word program */
    if (FMC_Write128(u32addr + MULTI_WORD_PROG_LEN*1, g_au32page_buff1) != 0)
    {
        printf("Write128 error\r\n");
    }
    #endif

    #if 0
    for (u32LoopCnt = 0; u32LoopCnt < MULTI_WORD_PROG_LEN; u32LoopCnt += 4)
    {
        g_au32page_buff2[u32LoopCnt / 4] = 0x7A7A0000 + u32LoopCnt;//
        printf("u32LoopCnt = 0x%2X(%3d,%3d) , 0x%8X\r\n",u32LoopCnt,u32LoopCnt , u32LoopCnt / 4 , g_au32page_buff2[u32LoopCnt / 4]);
        
    }

    /* execute multi-word program */
    if (FMC_Write128(u32addr + MULTI_WORD_PROG_LEN*2, g_au32page_buff2) != 0)
    {
        printf("Write128 error\r\n");
    }
    #endif

    #if 0
    for (u32LoopCnt = 0; u32LoopCnt < MULTI_WORD_PROG_LEN; u32LoopCnt += 4)
    {
        g_au32page_buff3[u32LoopCnt / 4] = 0x8A8A0000 + u32LoopCnt;//
        printf("u32LoopCnt = 0x%2X(%3d,%3d) , 0x%8X\r\n",u32LoopCnt,u32LoopCnt , u32LoopCnt / 4 , g_au32page_buff3[u32LoopCnt / 4]);
        
    }

    /* execute multi-word program */
    if (FMC_Write128(u32addr + MULTI_WORD_PROG_LEN*3, g_au32page_buff3) != 0)
    {
        printf("Write128 error\r\n");
    }
    #endif

    printf("write finish\r\n");

    SYS_LockReg();
}

void FMC_ENABLE(void)
{
    SYS_UnlockReg();	
    FMC_Open();
    FMC_ENABLE_AP_UPDATE();    
    SYS_LockReg();
}

void TMR1_IRQHandler(void)
{
	
    if(TIMER_GetIntFlag(TIMER1) == 1)
    {
        TIMER_ClearIntFlag(TIMER1);
		tick_counter();

		if ((get_tick() % 1000) == 0)
		{
            FLAG_PROJ_TIMER_PERIOD_1000MS = 1;//set_flag(flag_timer_period_1000ms ,ENABLE);
		}

		if ((get_tick() % 50) == 0)
		{

		}	
    }
}

void TIMER1_Init(void)
{
    TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 1000);
    TIMER_EnableInt(TIMER1);
    NVIC_EnableIRQ(TMR1_IRQn);	
    TIMER_Start(TIMER1);
}

void loop(void)
{
	static uint32_t LOG1 = 0;
	// static uint32_t LOG2 = 0;

    if ((get_systick() % 1000) == 0)
    {
        // printf("%s(systick) : %4d\r\n",__FUNCTION__,LOG2++);    
    }

    if (FLAG_PROJ_TIMER_PERIOD_1000MS)//(is_flag_set(flag_timer_period_1000ms))
    {
        FLAG_PROJ_TIMER_PERIOD_1000MS = 0;//set_flag(flag_timer_period_1000ms ,DISABLE);

        // printf("%s(timer) : %4d\r\n",__FUNCTION__,LOG1++);
        PB0 ^= 1;        
    }
}

void UARTx_Process(void)
{
	uint8_t res = 0;
	res = UART_READ(UART4);

	if (res > 0x7F)
	{
		printf("invalid command\r\n");
	}
	else
	{
		printf("press : %c\r\n" , res);
		switch(res)
		{
			case '1':
				break;

			case 'X':
			case 'x':
			case 'Z':
			case 'z':
                SYS_UnlockReg();
				// NVIC_SystemReset();	// Reset I/O and peripherals , only check BS(FMC_ISPCTL[1])
                // SYS_ResetCPU();     // Not reset I/O and peripherals
                SYS_ResetChip();    // Reset I/O and peripherals ,  BS(FMC_ISPCTL[1]) reload from CONFIG setting (CBS)	
				break;
		}
	}
}

void UART4_IRQHandler(void)
{
    if(UART_GET_INT_FLAG(UART4, UART_INTSTS_RDAINT_Msk | UART_INTSTS_RXTOINT_Msk))     /* UART receive data available flag */
    {
        while(UART_GET_RX_EMPTY(UART4) == 0)
        {
			UARTx_Process();
        }
    }

    if(UART4->FIFOSTS & (UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk | UART_FIFOSTS_RXOVIF_Msk))
    {
        UART_ClearIntFlag(UART4, (UART_INTSTS_RLSINT_Msk| UART_INTSTS_BUFERRINT_Msk));
    }	
}

void UART4_Init(void)
{
    SYS_ResetModule(UART4_RST);

    /* Configure UART4 and set UART4 baud rate */
    UART_Open(UART4, 115200);
    UART_EnableInt(UART4, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk);
    NVIC_EnableIRQ(UART4_IRQn);
	
	#if (_debug_log_UART_ == 1)	//debug
	printf("\r\nCLK_GetCPUFreq : %8d\r\n",CLK_GetCPUFreq());
	printf("CLK_GetHCLKFreq : %8d\r\n",CLK_GetHCLKFreq());
	printf("CLK_GetHXTFreq : %8d\r\n",CLK_GetHXTFreq());
	printf("CLK_GetLXTFreq : %8d\r\n",CLK_GetLXTFreq());	
	printf("CLK_GetPCLK0Freq : %8d\r\n",CLK_GetPCLK0Freq());
	printf("CLK_GetPCLK1Freq : %8d\r\n",CLK_GetPCLK1Freq());	
	#endif	

    #if 0
    printf("FLAG_PROJ_TIMER_PERIOD_1000MS : 0x%2X\r\n",FLAG_PROJ_TIMER_PERIOD_1000MS);
    printf("FLAG_PROJ_REVERSE1 : 0x%2X\r\n",FLAG_PROJ_REVERSE1);
    printf("FLAG_PROJ_REVERSE2 : 0x%2X\r\n",FLAG_PROJ_REVERSE2);
    printf("FLAG_PROJ_REVERSE3 : 0x%2X\r\n",FLAG_PROJ_REVERSE3);
    printf("FLAG_PROJ_REVERSE4 : 0x%2X\r\n",FLAG_PROJ_REVERSE4);
    printf("FLAG_PROJ_REVERSE5 : 0x%2X\r\n",FLAG_PROJ_REVERSE5);
    printf("FLAG_PROJ_REVERSE6 : 0x%2X\r\n",FLAG_PROJ_REVERSE6);
    printf("FLAG_PROJ_REVERSE7 : 0x%2X\r\n",FLAG_PROJ_REVERSE7);
    #endif

}

void GPIO_Init (void)
{
    SYS->GPB_MFPL = (SYS->GPB_MFPL & ~(SYS_GPB_MFPL_PB0MFP_Msk)) | (SYS_GPB_MFPL_PB0MFP_GPIO);

    GPIO_SetMode(PB, BIT0, GPIO_MODE_OUTPUT);

}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);
    
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

//    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);
//    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

//    CLK_EnableXtalRC(CLK_PWRCTL_LIRCEN_Msk);
//    CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk);	

//    CLK_EnableXtalRC(CLK_PWRCTL_LXTEN_Msk);
//    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);	

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    CLK_EnableModuleClock(GPB_MODULE);

    CLK_EnableModuleClock(TMR1_MODULE);
  	CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HIRC, 0);

    /* Debug UART clock setting */
    UartDebugCLK();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    UartDebugMFP();


    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Lock protected registers */
    SYS_LockReg();
}

/*
 * This is a template project for M251 series MCU. Users could based on this project to create their
 * own application without worry about the IAR/Keil project settings.
 *
 * This template application uses external crystal as HCLK source and configures UART4 to print out
 * "Hello World", users may need to do extra system configuration based on their system design.
 */

int main()
{
    SYS_Init();

	GPIO_Init();
	UART4_Init();
	TIMER1_Init();

    SysTick_enable(1000);
    #if defined (ENABLE_TICK_EVENT)
    TickSetTickEvent(1000, TickCallback_processA);  // 1000 ms
    TickSetTickEvent(5000, TickCallback_processB);  // 5000 ms
    #endif

    FMC_ENABLE();
    FMC_WRITEDATA();

    /* Got no where to go, just loop forever */
    while(1)
    {
        loop();

    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
