//#include <main.h> 
//#include <stdio.h> 


#include <16F877a.h>
#device ADC=10
#Fuses HS
#use delay(clock=10000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=pin_c7,bits=8,stop=1)
//#ZERO_RAM 



#define HX711_DO  PIN_c2 
#define HX711_CLK PIN_c3 
int1 test=0; 
unsigned int32 Count,BUFFER[11],offseeet=0,mied=0; 
unsigned int8 i=0; 
int1 flg_display=0;
unsigned int32 measurement(void); 

void main() 
{ 


while(TRUE){ 

while(i<10){ 
Count=measurement(); 
BUFFER[i]=Count; 
mied+=BUFFER[i]; 
i++; flg_display=0;
}

i=0;
//flg_display=1;
mied/=11; 

//mied=/11; 

//mied=count;

if(test==0){ 
offseeet=mied; 
test=1; 
} 
//Count=measurement();

mied-=offseeet;
mied*=0.05; 
printf("weigh=%lu",mied); 
printf("g\r\n");flg_display=0;mied=0;

 
delay_ms(100);output_toggle(pin_a1);
//printf("test_serial");
} 
} 
//******************************************** 
int32 measurement(void){ 
unsigned int32 Count; 
unsigned int8 i,A_1,A_2,A_3; 


output_bit( HX711_DO, 1); 
output_bit( HX711_CLK, 0); 
Count=0; 

while(input(HX711_DO)); 

for (i=0;i<24;i++){// gain 128 
output_bit( HX711_CLK, 1); 
delay_cycles(1);
Count=Count<<1; 
output_bit( HX711_CLK, 0);
delay_cycles(1);
if(input(HX711_DO)) Count++; 
} 
output_bit( HX711_CLK, 1); 
Count=Count^0x800000;//printf("count111 %lu ",count); 
output_bit( HX711_CLK, 0); 
//************************ 
//A_1=MAKE8(Count, 0); printf("a_1 %x ",a_1);
//A_2=MAKE8(Count, 1); printf("a_2 %x ",a_2);
//A_3=MAKE8(Count, 2); printf("a_3 %x ",a_3);
//A_2=(A_2 & 0b11111000); printf("a_2 %x ",a_2);
//Count= MAKE16(A_3, A_2); printf("count %lu",count);printf("\r\n");
//printf("count %lu",count);printf("\r\n");
return(Count); 

} 
