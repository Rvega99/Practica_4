#include "lib/include.h"

int main(void)
{

    volatile uint16_t vdig[6];

    int k=0;
    Configurar_SysTick();
    Configurar_PLL();  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART1();
    
  
    char num[4];
    //printString("3");
    while(1)
    {

         ADC0->PSSI |= (1<<2)| (1<<1);  
             /* Enable SS3 conversion or start sampling data from AN0 */
         while((ADC0->RIS & (1<<2)) == 0){} ;   /* Wait untill sample conversion completed*/
         vdig[0]= ADC0->SSFIFO2& 0xFFF;
         
          /* Wait untill sample conversion completed*/
         
         vdig[1]= ADC0->SSFIFO2 &0xFFF;
         
         vdig[2]= ADC0->SSFIFO2&0xFFF;
         
         utoa(vdig[0],num,10);
         transmisor(num);
        
         utoa(vdig[1],num,10);
         transmisor(num);
         utoa(vdig[2],num,10);
         transmisor(num);
                                      /* Enable SS3 conversion or start sampling data from AN0 */
           /* Wait untill sample conversion completed*/
         
         while((ADC0->RIS & (1<<1)) == 0){} ; 
           /* Wait untill sample conversion completed*/
         vdig[3]= ADC0->SSFIFO1& 0xFFF0;
         
         
         
         
         
          
                                    /* Enable SS3 conversion or start sampling data from AN0 */
            /* Wait untill sample conversion completed*/
         vdig[4]= ADC0->SSFIFO1& 0xFF0F;
            /* Wait untill sample conversion completed*/
         
         vdig[5]= ADC0->SSFIFO1& 0xFFFF;
        
        utoa(vdig[3],num,10);
         transmisor(num);
         utoa(vdig[4],num,10);
         transmisor(num);
        
         utoa(vdig[5],num,10);
         transmisor(num); 
          ADC0->ISC = (1<<2)|(1<<1);

          /* read adc coversion result from SS3 FIFO*/
        ADC0->ISC = 8;          /* clear coversion clear flag bit*/
			/*control Green PF3->LED */
		
    }

}
