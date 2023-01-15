#include "lib/include.h"

int main(void)
{

    volatile uint16_t vdig[7];

    
    Configurar_SysTick();
    Configurar_PLL();  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART1();
  
    char num[4];
    //printString("3");
    while(1)
    {
         ADC0->PSSI |= (1<<0)| (1<<3);       /* Enable SS3 conversion or start sampling data from AN0 */
         while((ADC0->RIS & (1<<5)) == 0){} ;   /* Wait untill sample conversion completed*/
         vdig[0]= ADC0->SSFIFO0;
         while((ADC0->RIS & (1<<5)) == 0){} ;   /* Wait untill sample conversion completed*/
         vdig[1]= ADC0->SSFIFO0;
          utoa(vdig[0],num,10);
         transmisor(num);
         utoa(vdig[1],num,10);
         transmisor(num); 

        while((ADC0->RIS & (1<<5)) == 0){} ;   /* Wait untill sample conversion completed*/
         vdig[2]= ADC0->SSFIFO0;
         while((ADC0->RIS & (1<<5)) == 0){} ;   /* Wait untill sample conversion completed*/
         vdig[3]= ADC0->SSFIFO0;
          utoa(vdig[2],num,10);
         transmisor(num);
         utoa(vdig[3],num,10);
         transmisor(num); 

         while((ADC0->RIS & (1<<5)) == 0){} ;   /* Wait untill sample conversion completed*/
         vdig[4]= ADC0->SSFIFO0;
         while((ADC0->RIS & (1<<3)) == 0){} ;   /* Wait untill sample conversion completed*/
         vdig[5]= ADC0->SSFIFO3;
         utoa(vdig[4],num,10);
         transmisor(num);
         utoa(vdig[5],num,10);
         transmisor(num); 
         
         ADC0->ISC = (1<<0)|(1<<3); 
        ADC0->ISC = 8;          /* clear coversion clear flag bit*/
			/*control Green PF3->LED */
		
    }

}
