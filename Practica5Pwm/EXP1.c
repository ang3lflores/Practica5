
/////////////////////////////////////////////////////////////////////// LIBRERIAS
// #include "lib/include.h"
/////////////////////////////////////////////////////////////////////// MAIN
//int main(void){
//    ///////////////////////////////////////////////////////////// CONFIGURACION
//    Configurar_PLL(50000000);   // Se pone el reloj interno del sistema a 25 MHz
////    configuracionuart(_50MHZ, 957600);//Yo FCLK 50MHZ Baudrate 957600
////    ConfigurarGPIOF();
//    /*
//     * carga = Fclk/Fpwm = 50MHz/10kHz = 5000;
//     *
//     * con div=4 por lo tanto:
//     * carga-> carga/4 = 1250
//     *
//     * DUTY = carga*(PORCENTAJE en bajo); PORCENTAJE = 50%
//     * DUTY = 1250 * (0.5) = 625
//     */
//    int CARGA = 2500, DUTY = CARGA/2;
//    Configurar_PWMM0G1(CARGA, DUTY); // M0PWM2 y M0PWM3 | PB5 y PB4
//
//    ///////////////////////////////////////////////////////////////// LOOP
//    while(1U){
//
////        DUTY  = lround((50000) * ((100 - adc_data[0])/100.0));
////        if (DUTY == 0)
////           {
////                   DUTY = 1;
////           }
////            PWM0->_1_CMPA = (int) DUTY;
//    }
//}
