#include "lib/include.h"

extern void Configura_Reg_ADC0(void)
{
    /*
    Habilitar el modulo 0 del ADC con dos canales analogicos 
    en el puerto E a una velocidad de conversion de 250ksps
    dandole la mayor prioridad al secuenciador 2 con evento
    de procesador 
    */
     //
    SYSCTL->RCGCADC = (1<< 0.
    
    
    
    
    
    
    
    
    
    
    
    0); 
    2//Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(1<<3)|(0<<2)|(1<<1)|(1<<0)|(1<<12)|(1<<8); //Abrir puertos

    //Pag 758 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    GPIOB_AHB->DIR = (0<<5);
    GPIOD_AHB->DIR = (0<<6) | (0<<5) | (0<<4);
    GPIOE_AHB->DIR = (0<<0) | (0<<5);

    //(GPIOAFSEL) pag.768 Enable alternate función para que el modulo analógico tenga control de esos pines
    GPIOB_AHB->AFSEL = (1<<5);
    GPIOD_AHB->AFSEL = (1<<6) | (1<<5) | (1<<4);
    GPIOE_AHB->AFSEL = (1<<0) | (1<<5);

    //(GPIODEN) pag.779 desabilita el modo digital
    GPIOB_AHB->DEN = (0<<5);
    GPIOD_AHB->DEN = (0<<6) | (0<<5) | (0<<4);
    GPIOE_AHB->DEN = (0<<0) | (0<<5); 

    //Pag  GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
    //----------------------------------(0x76543210)
    GPIOB_AHB->PCTL = GPIOB_AHB->PCTL & (0xFF0FFFFF);
    GPIOD_AHB->PCTL = GPIOD_AHB->PCTL & (0xF000FFFF);
    GPIOE_AHB->PCTL = GPIOE_AHB->PCTL & (0xFF0FFFF0);

    //(GPIOAMSEL) pag.786 habilitar analogico
    GPIOB_AHB->AMSEL = (1<<5);
    GPIOD_AHB->AMSEL = (1<<6) | (1<<5) | (1<<4);    //SOLO el ADC lo utiliza 
    GPIOE_AHB->AMSEL = (1<<0) | (1<<5);

    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC0->PC = 0x5;//1M samples

    //Pag 1099 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores
    ADC0->SSPRI = 0x1330;

    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0); //Asegurarse que estan apagados

    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX  = (0x0<<0)|(0x0<<12); //modo por defecto, depende del SSI

    //Pag 1129 Este registro (ADCSSMUX) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX0 = (1<<0) | (5<<4) | (7<<8) | (11<<12) | (6<<16);
    ADC0->SSMUX3 = (8<<0);
    //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
    ADC0->SSCTL0 = (1<<1) | (1<<2) | (1<<5) | (1<<6) | (1<<9) | (1<<10) | (1<<13) | (1<<14) | (1<<17) | (1<<18) ;
    ADC0->SSCTL3 = (1<<1) | (1<<2);

    /* Enable ADC Interrupt */
    ADC0->IM = (0<<2)|(0<<1); /* Unmask ADC0 sequence 2 interrupt pag 1082*/
    //NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC_EN0_R = 0x00010000;
            
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS = (1<<3) | (0<<2) | (0<<1) | (1<<0);
    
}

