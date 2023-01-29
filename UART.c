#include "lib/include.h"
volatile uint16_t vdig[2];


extern void Configurar_UART1(void)
{
    SYSCTL->RCGCUART  = (1<<1);   //Paso 1 (RCGCUART) pag.344 UART/modulo0 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<1);     //Paso 2 (RCGCGPIO) pag.340 Enable clock port A
    //(GPIOAFSEL) pag.671 Enable alternate function
   
            GPIOA_AHB->AFSEL = (1<<1) | (1<<0); //GPIO Port Control (GPIOPCTL) PA1-> U1Rx PB1-> U1Tx pag.688
            GPIOA_AHB->DIR =(1<<1) | (0<<0);
            //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
            GPIOA_AHB->PCTL = (GPIOA_AHB->PCTL&0xFFFFFF00) | 0x00000011;// (1<<0) | (1<<4);//0x00000011
            // GPIO Digital Enable (GPIODEN) pag.682
            GPIOA_AHB->DEN = (1<<0) | (1<<1);//PA1 PA0 //UART0 UART Control (UARTCTL) pag.918 DISABLE!!
            GPIOA_AHB->AMSEL=0x00;
    
        UART0->CTL = (0<<9) | (0<<8) | (0<<0)| (0<<4);

    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 20,000,000 / (16 * 9600) = 130.2
    UARTFBRD[DIVFRAC] = integer(0.2 * 64 + 0.5) = 14
    */
        UART0->IBRD = 130;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
        UART0->FBRD = 14;
    //  UART Line Control (UARTLCRH) pag.916
        UART0->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
  
        UART0->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
        UART0->CTL = (1<<0) | (1<<8) | (1<<9)| (1<<4);



}
extern void trans_char(char c)
{ 
     while((UART1->FR & (1<<5))!=0);
    {
        UART0->DR=c;
    }
}

extern void transmisor(char *string)
{
while(*string)
{
trans_char(*(string++)); 
}
trans_char('\n');
}


 extern void interrupcion(void)
 {
      //UARTO->IFLS (UARTO->IFLS & 0 0x00) I 0x00; //ver pagina 9:
      UART0->IM |= (0<<4) | (1<<5); 
//para mi uart1 el num d einterrupcion es de 6   por lo que 59/4=14.75 popr lo que tioene prioridad 1  
//(4n+3)(4n+2)(4n+1)(4n) si n = numero de prioridad
//   7    6      5    4
      NVIC->IP[1] |=(NVIC->IP[1] & 0xFF00FFFF) | (0x00400000); //
      NVIC->ISER[0] =(1<<6); // interrupcion 5 (un 1 en el bit 5)59-32=27
}

extern void UARTS_ISR(void)
{ 
if(UART0->RIS & (1<<5))
 { 
 ADC0->PSSI = (1<<2) | (1<<1);
while ((ADC0->RIS & (1<<2))==0){} 
vdig[0] = ADC0->SSFIFO2 & 0XFFF; 
while((ADC0->RIS & (1<<1))==0){} 
vdig[1] = ADC0->SSFIFO1 & 0xFFF;
ADC0->ISC = (1<<2) | (1<<1); 
}
UART0->ICR = (1<<5);
}


#include "lib/include.h"

extern void Configurar_SysTick(void){
    SysTick->CTRL = (0<<0);
    SysTick->LOAD = 0xFFFFFF - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = (1<<2)|(1<<0);
}

extern void SysTick_espera(float delay){
    uint16_t i;
    for(i=0;i<(int)(delay*1);i++){
        SysTick_1ms(20000);
    }
}

extern void SysTick_1ms(uint16_t delay){
    SysTick->CTRL = (0<<0);
    SysTick->LOAD = delay - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = (1<<2)|(1<<0);
    while((SysTick->CTRL&0x10000) == 0){}
}
