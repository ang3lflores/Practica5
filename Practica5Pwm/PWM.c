
#include "lib/include.h"

extern void Configurar_PWMM0G0(int cargad, int DUTY){ //M0PWM0 y M0PWM1
    SYSCTL->RCGCGPIO|=(1<<1); //PORTB PB7 PB6
    GPIOB->CR      |= (1<<7) | (1<<6);
    GPIOB->DIR     |= (1<<7) | (1<<6);
    GPIOB->DEN     |= (1<<7) | (1<<6);
    GPIOB->AFSEL   |= (1<<7) | (1<<6);
    /* Table 23-5 on page 1351. */
    GPIOB->PCTL    |= (GPIOB->PCTL & 0xF00FFFFFF) | 0x044000000;
    SYSCTL->RCGCPWM = (1<<0);       // Enable and provide a clock to PWM module 0 in Run mode.

    SYSCTL->RCC |= (1 << 20);       // RCC[20]    = 1:USEPWMDIV
    SYSCTL->RCC &= ~(0x7 << 17);    // RCC[19:17] = 000 PWMDIV
    SYSCTL->RCC |= (0x2 << 17);     // RCC[19:17] = 0x1 divider=/4
    /*
     * Value Divisor
     * 0x0 /2
     * 0x1 /4
     * 0x2 /8
     * 0x3 /16
     * 0x4 /32
     * 0x5 /64
     * 0x6 /64
     * 0x7 /64 (default)
     */

// 3. Disable PWM Generator and Setup the Timer Counting Mode
    PWM0->_0_CTL = 0x00;            // Disable PWM Generator, and set to count-down mode
    // 4. Configure LOAD (Period), CMP (Duty), GEN (PWM Mode) values
    PWM0->_0_LOAD = cargad;         // Setup the period of the PWM signal
    PWM0->_0_CMPB = DUTY;           // Setup the initial duty cycle
    PWM0->_0_CMPA = DUTY;           // Setup the initial duty cycle
    PWM0->_0_GENA = (0x02 << ACTCMPBD ) | (0x03 <<ACTLOAD); // PWM0
    PWM0->_0_GENB = (0x02 << ACTCMPAD ) | (0x03 <<ACTLOAD); // PWM1
//    PWM0->_0_INTEN = (1<<0);     //Interrupt for Counter=0
//    PWM0->INTEN = (1<<0);        //PWMINTEN = (1<<INTPWM0)
//    NVIC_SetPriority (PWM0_0_IRQn, 4);
//    NVIC_EnableIRQ (PWM0_0_IRQn);
    PWM0->_0_CTL |= 0x01,
    PWM0->ENABLE |= (1 << 1) | (1 << 0);       // Enable PWM1 y PWM0
}

extern void Configurar_PWMM0G1(int cargad, int DUTY){ //M0PWM2 y M0PWM3
    SYSCTL->RCGCGPIO|=(1<<1); //PORTB PB4 PB5
    GPIOB->CR      |= (1<<4) | (1<<5);
    GPIOB->DIR     |= (1<<4) | (1<<5);
    GPIOB->DEN     |= (1<<4) | (1<<5);
    GPIOB->AFSEL   |= (1<<4) | (1<<5);
    /* Table 23-5 on page 1351. */
    GPIOB->PCTL    |= (GPIOB->PCTL & 0xFF00FFFF) | 0x00440000;
    SYSCTL->RCGCPWM = (1<<0);       // Enable and provide a clock to PWM module 0 in Run mode.

    SYSCTL->RCC |= (1 << 20);       // RCC[20]    = 1:USEPWMDIV
    SYSCTL->RCC &= ~(0x7 << 17);    // RCC[19:17] = 000 PWMDIV
    SYSCTL->RCC |= (0x0 << 17);     // RCC[19:17] = 0x1 divider=/2

// 3. Disable PWM Generator and Setup the Timer Counting Mode
    PWM0->_1_CTL = 0x00;            // Disable PWM Generator, and set to count-down mode
    // 4. Configure LOAD (Period), CMP (Duty), GEN (PWM Mode) values
    PWM0->_1_LOAD = cargad;         // Setup the period of the PWM signal
    PWM0->_1_CMPB = DUTY;           // Setup the initial duty cycle
    PWM0->_1_CMPA = DUTY;           // Setup the initial duty cycle
    PWM0->_1_GENA = (0x02 << ACTCMPAD ) | (0x03 <<ACTLOAD); // PWM2
    PWM0->_1_GENB = (0x02 << ACTCMPBD ) | (0x03 <<ACTLOAD); // PWM3
    /*
     * bit 10 Action for Comparator B Down (ACTCMPBD)
     * bit 08 Action for Comparator B Up   (ACTCMPBU)
     * bit 06 Action for Comparator A Down (ACTCMPAD)
     * bit 04 Action for Comparator A Up   (ACTCMPAU)
     * bit 02 Action for Counter = LOAD    (ACTLOAD )
     * bit 00 Action for Counter = 0       (ACTZERO )
     *
     * 0x0 Do nothing.
     * 0x1 Invert pwmA.
     * 0x2 Drive pwmA Low.
     * 0x3 Drive pwmA High.
     */
//    PWM0->_1_INTEN = (1<<0);     //Interrupt for Counter=0
//    PWM0->INTEN = (1<<1);        //PWMINTEN = (1<<INTPWM1)
//    NVIC_SetPriority (PWM0_1_IRQn, 3);
//    NVIC_EnableIRQ (PWM0_1_IRQn);
    PWM0->_1_CTL |= 0x01;
    PWM0->ENABLE |= (1 << 2) | (1 << 3);       // Enable PWM2 y PWM3
}

extern void Configurar_PWMM0G2(int cargad, int DUTY){  //M0PWM4 y M0PWM5
    SYSCTL->RCGCGPIO|=(1<<4); //PORTE PE5 & E4
    GPIOE->CR      |= (1<<5) | (1<<4);
    GPIOE->DIR     |= (1<<5) | (1<<4);
    GPIOE->DEN     |= (1<<5) | (1<<4);
    GPIOE->AFSEL   |= (1<<5) | (1<<4);
    /* Table 23-5 on page 1351. */
    GPIOE->PCTL    |= (GPIOE->PCTL & 0xFFF00FFFF) | 0x00440000;
    SYSCTL->RCGCPWM =(1<<0);        // Enable and provide a clock to PWM module 0 in Run mode.

    SYSCTL->RCC |= (1 << 20);       // RCC[20]=1:USEPWMDIV
    SYSCTL->RCC &= ~(0x7 << 17);    // RCC[19:17]=000 PWMDIV
    SYSCTL->RCC |= (0x2 << 17);// RCC[19:17]=0x1 divider=/4

// 3. Disable PWM Generator and Setup the Timer Counting Mode
    PWM0->_2_CTL = 0x00;            // Disable PWM Generator, and set to count-down mode
    // 4. Configure LOAD (Period), CMP (Duty), GEN (PWM Mode) values
    PWM0->_2_LOAD = cargad;         // Setup the period of the PWM signal
    PWM0->_2_CMPB = DUTY;           // Setup the initial duty cycle // PWM3
    PWM0->_2_CMPA = DUTY;           // Setup the initial duty cycle // PWM2
    PWM0->_2_GENA = (0x02 << ACTCMPAD ) | (0x03 <<ACTLOAD); // PWM2
    PWM0->_2_GENB = (0x02 << ACTCMPBD ) | (0x03 <<ACTLOAD); // PWM3
//    PWM0->_2_INTEN = (1<<0);     //Interrupt for Counter=0
//    PWM0->INTEN = (1<<2);        //PWMINTEN = (1<<INTPWM2)
//    NVIC_SetPriority (PWM0_2_IRQn, 2);
//    NVIC_EnableIRQ (PWM0_2_IRQn);
    PWM0->_2_CTL |= 0x01;
    PWM0->ENABLE |= (1 << 4) | (1 << 5);       // Enable PWM4 PWM5
}
