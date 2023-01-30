
///////////////////////////////////////////////////////////////////// LIBRERIAS
#include "lib/include.h"
///////////////////////////////////////////////////////////////////// MAIN
int main(void){
    ///////////////////////////////////////////////////////////////// VALIABLES
//    char text[16] = NULL, num_char[16] = NULL;

    char  UART0_Sring [20]; //= '\0';

    char RGB_String [3];
    int RGB_int[3], x, color, i;

    ///////////////////////////////////////////////////////////// CONFIGURACION
    Configurar_PLL(_20MHZ);   // Se pone el reloj interno del sistema a 25 MHz

    /*
     * carga = Fclk/Fpwm = 20MHz/50Hz = 400,000;
     *
     * con div=8 por lo tanto:
     * carga-> carga/8 = 50,000
     *
     * DUTY = carga*(PORCENTAJE en bajo); PORCENTAJE = 50%
     * DUTY = 50,000 * (0.5) = 25,000
     */
    int CARGA = 50000, DUTY = 25000;
    Configurar_PWMM0G0(CARGA, DUTY); // M0PWM0 y M0PWM1 | PB6 y PB7    / M1PWM0 | PD0 = VERDE
    Configurar_PWMM0G1(CARGA, DUTY); // M0PWM2 | PB5 = AZUL | PB4 = ROJO
//    Configurar_PWMM0G2(CARGA, DUTY); // M0PWM3 PE4
    Configurar_ADCM0SS2();
    Configurar_SysTick(_20MHZ);
    int adc_data[3];
    int V;

    ///////////////////////////////////////////////////////////////// LOOP
    while(1U){
//255,0,78%
        //255->100%

        readADC0SS2(adc_data);
        V=5/4096.0;


        DUTY  = lround((50000) * ((100-adc_data[0])/100.0));
        if (DUTY == 0)     DUTY = 1;
        if (DUTY == 50000){
            DUTY = 49999;
        }
        PWM0->_1_CMPA = (int) DUTY; //ROJO PD0

        DUTY  = lround((50000) * ((100-adc_data[1])/100.0));
        if (DUTY == 0)
                   {
                           DUTY = 1;
                   }
        if (DUTY == 50000)    {
            DUTY = 49999;
        }
            PWM0->_0_CMPB = (int) DUTY;  //VERDE PD0

        DUTY  = lround((50000) * ((100-adc_data[2])/100.0));
        if (DUTY == 0)
                   {
                           DUTY = 1;
                   }
        if (DUTY == 50000)  {
            DUTY = 49999;
        }
            PWM0->_1_CMPB = (int) DUTY;

//            Delay_ms(300);
    }
}
