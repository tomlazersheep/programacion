/*Escribir un programa que permita modificar la hora del rtc (hh:mi:ss)*/
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "sys/io.h"
#define  P 0x70


unsigned char in (unsigned char reg){
  outb (reg, P);
  return inb(P + 1);
  }


void main()
{

	/*Things I should do:
		-Use ioperm to get root permissions for port minupulation
		-Get desired date and parse to BCD
		-Check VRT for 1
		-Check UIP for 0
		-Set SET bit to 1
		-Write hours seconds and years

		*/
	int uip_flag =1;
	unsigned char hours, minutes, seconds,aux;

	if (ioperm(P,2,1))
	{
		perror("ioperm");
		exit(1);
	}

	printf("insert desired date:\n");
	scanf("%hhu:%hhu:%hhu",&hours,&minutes,&seconds);


	if (in(0x0D) & 0x80)//read VRT 
	{
		do{
			if (in(0x0A)&0x80){	
				nanosleep(1984000);
			}else{
				uip_flag=0;
			}	
		}while(uip_flag)

		//write 1 to SET bit on 0x0B, first bit.
		aux = in(0x0B);
		aux= aux | 0x80; 
		outb(0x0B,P);
		outb(aux,++P);

		//write all data 
		outb(0x00,P);
		outb(seconds,++P);

		outb(0x02,P);
		outb(minutes,++P);

		outb(0x04,P);
		outb(hours,++P);

		//set SET back to 0

		aux = in(0x0B);
		aux= aux & 0x7F; 
		outb(0x0B,P);
		outb(aux,++P);		
	}



	return;
}