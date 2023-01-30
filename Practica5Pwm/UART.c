#include "lib/include.h"

extern void configuracionuart(int clock, int baudrate)

{
    int BRD_I;
    float BRD_F;
    int data = 0x3;


        SYSCTL->RCGCUART|= (1<<0); // habilita el Uart0 
        
        SYSCTL->RCGCGPIO|= (1<<0); // habilita el puerto A
        //                 Tx       Rx
        GPIOA->AFSEL  |= (1<<1) | (1<<0);
        GPIOA->DIR    |= (1<<1) | (0<<0);
        GPIOA->PUR    |= (0<<1) | (0<<0);
        GPIOA->PDR    |= (0<<1) | (0<<0);
        GPIOA->AMSEL  |= (0<<1) | (0<<0);
        GPIOA->DEN    |= (1<<1) | (1<<0);
        GPIOA->PCTL   &= 0xFFFFFF00;
        GPIOA->PCTL   |= 0x00000011;
        GPIOA->CR     |= 0x00000000; // lock
        /*
         * Baudrate 19200 frecuencia reloj 16 000 000
         * BRD = 16 000 000 / ( 16 * 19200 ) = 52.08333
         * UARTFBRD[DIVFRAC] = integer( 0.08333 * 64 + 0.5 ) = 6
         */
        //    int ck = 16000000;
        //    int ck = 25000000;
        BRD_I = clock/(16 * baudrate);
        BRD_F = clock/(16.0 * baudrate) - BRD_I;
        BRD_F = lround(BRD_F * 64 + 0.5);

        // Control      RXE     TXE     UARTEN
        UART0->CTL  = (0<<9) | (0<<8) | (0<<0);
        UART0->IBRD = BRD_I;      // Integer Baud-Rate Divisor
        UART0->FBRD = (int)BRD_F; // Fractional Baud-Rate Divisor
        UART0->LCRH = (data<<5) | (1<<4); //bits data & Enable FIFOs
        //The UART has two 16x8 FIFOs; one for transmit and one for receive
        UART0->CC   = 0x0; // Clock Configuration = System clock
        UART0->CTL  = (1<<9) | (1<<8) | (1<<0); //send

        

}

extern void Configurar_UART5(void)
{
    SYSCTL->RCGCUART  = (1<<5);   // Uart5Paso 1 (RCGCUART) pag.344 UART/modulo0 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<4);     // Puerto E Paso 2 (RCGCGPIO) pag.340 Enable clock port A
    //(GPIOAFSEL) pag.671 Enable alternate function

    GPIOE->AFSEL |= (1<<5) | (1<<4);
    GPIOE->DIR |= (1<<5) | (0<<4);
    //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
    GPIOE->PCTL |= (GPIOE->PCTL&0xFF00FFFF) | 0x00110000;  // (1<<5) | (1<<4);
    // GPIO Digital Enable (GPIODEN) pag.682
    GPIOE->DEN |= (1<<5) | (1<<4);//PA1 PA0
    //UART0 UART Control (UARTCTL) pag.918 DISABLE!!
    UART5->CTL |= (0<<9) | (0<<8) | (0<<0);


    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    En mi caso
    BRD = 20,000,000/ (16 * 28800) =  43.4027
    UARTFBRD[DIVFRAC] = integer(0.4027 * 64 + 0.5) = 26.278
    */
    UART5->IBRD = 43;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART5->FBRD = 26;
    //  UART Line Control (UARTLCRH) pag.916
    UART5->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART5->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART5->CTL = (1<<0) | (1<<8) | (1<<9);



}

extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART0->FR & (1<<4)) != 0 );
    v = UART0->DR & 0xFF;
    c = v;
    return c;
}
extern char readChar5(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART5->FR & (1<<4)) != 0 );
    v = UART5->DR & 0xFF;
    c = v;
    return c;
}
extern void printChar(char c)
{
    while((UART0->FR & (1<<5)) != 0 );
    UART0->DR = c;
}
extern void printChar5(char c)
{
    while((UART5->FR & (1<<5)) != 0 );
    UART5->DR = c;
}
extern void printString(char* string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}
extern void printString5(char* string)
{
    while(*string)
    {
        printChar5(*(string++));
    }
}

extern void readString(char UART0_Sring[], char delimitador)
{

   int i=0;
//   char string [20]; //= (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       (UART0_Sring[i]) = c;
       i++;
       /*if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       */

       c = readChar();
   }

   //UART7_Sring = string;
     UART0_Sring[i]= '\0';

}
extern void readString5(char UART5_Sring[], char delimitador)
{

   int i=0;
//   char string [20]; //= (char *)calloc(10,sizeof(char));
   char c = readChar5();
   while(c != delimitador)
   {
       (UART5_Sring[i]) = c;
       i++;
       /*if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       */

       c = readChar5();
   }

   //UART7_Sring = string;
     UART5_Sring[i]= '\0';

}

