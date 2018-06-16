#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include "sys/io.h"
#include <string.h>

/*1) Mostrar el contenido de los registros 0 al 13. El contenido se debe mostrar en forma de tabla
donde cada fila corresponde a un registro y con las siguientes columnas correctamente
alineadas y en el orden en que figuran:
Valor en binario (los bits tal cual se leen)
Valor en hexadecimal (que corresponde a los bits tal cual se leyeron del RTC)
Descripción del registro (max. 20 caracteres)
Cantidad de bits en “1” que hay en el valor*/
/*typedef struct registerInfo{
	int address;
	int contentB;
	int contentH;
	char description[20];
	int bitsOn;
} registerInfo;*/

unsigned char in (unsigned char reg){
  outb (reg, 0x70);
  return inb(0x70 + 1);
  }

unsigned char giveMeBCD(unsigned char num){
   	unsigned char bcd = 0;
   	int shift = 0;


   while (num > 0) {
      bcd |= (num % 10) << (shift++ << 2);
      num /= 10;
   }
   return bcd;

}


void showMeRegisters(){
	unsigned char registerContent[13];
	int address= 0x00,uip_flag=1;
	unsigned char aux;
	char description[14][20]={"segundos","segundos alarma","minutos    ","minutos alarma","horas   ","horas alarma","dia semana","dia mes    ","mes     ","anio     ","Registro A","Registro B","Registro C","Registro D"};

	if (in(0x0D) & 0x80)//read VRT 
	{
		do{
			if (in(0x0A)&0x80){	
				nanosleep(1984000);
			}else{
				uip_flag=0;
			}	
		}while(uip_flag);

		//write 1 to SET bit on 0x0B, first bit.
		aux = in(0x0B);
		aux= aux | 0x80; 
		outb(0x0B,0x070);
		outb(aux,0x071);


		//get all 13 registers
		for (int i = 0; i < 13; ++i)
		{
			outb(address,0x70);
			registerContent[i]=inb(0x71);
			address++;
		}

		//set SET back to 0
		aux = in(0x0B);
		aux= aux & 0x7F; 
		outb(0x0B,0x070);
		outb(aux,0x071);
	}

	//now I should get all the elements to print
	printf("Address\tBinary\t\tHex\tDescription\t\tBits set\n");
	for (int j = 0; j < 13; ++j){
		printf("0x%02x\t",j );
		for (int i = 0; i < 8; i++) {
	    	printf("%d", !!((registerContent[j] << i) & 0x80));
	  	}

	  	printf("\t0x%02x",registerContent[j] );
		
		printf("\t%s",description[j] );

		int bitsOn=0;
		for (int i = 0; i < 8; i++) {
	    	if((registerContent[j] << i) & 0x80){
	    		bitsOn++;
	    	}
	  	}
	    printf("\t\t %d",bitsOn );

	  	printf("\n");
	}
	

  	return;
}

void alarmAt(){
	/*Utilizando el RTC programar una alarma que se active a determinada hora ingresada por teclado
(HH:MM:SS). Al activarse la alarma debe aparecer un mensaje que lo informe.*/
	int uip_flag=1;
	unsigned char hours,minutes,seconds,aux;
	if (in(0x0D) & 0x80)//read VRT 
	{
		do{
			if (in(0x0A)&0x80){	
				nanosleep(1984000);
			}else{
				uip_flag=0;
			}	
		}while(uip_flag);

		//write 1 to SET bit on 0x0B, first bit.
		aux = in(0x0B);
		aux = aux | 0x80; 
		outb(0x0B,0x70);
		outb(aux,0x71);

		printf("insertar hora deseada para la alarma:\n");
		scanf("%x:%x:%x",&hours,&minutes,&seconds);
		unsigned char a,b;

		for (int i = 0; i < 8; i++) {
	    	printf("%d", !!((hours << i) & 0x80));
	  	}		


		hours = giveMeBCD(hours);
	
  		minutes = giveMeBCD(minutes);
		
  		seconds = giveMeBCD(seconds);

  	//	printf("%x\n",hours );
  //	printf("%x\n",minutes );
//  	printf("%x\n",seconds );
		
		for (int i = 0; i < 8; i++) {
	    	printf("%d", !!((hours << i) & 0x80));
	  	}		


		//write all data 
		outb(0x01,0x70);
		outb(seconds,0x71);

		outb(0x03,0x70);
		outb(minutes,0x71);

		outb(0x05,0x70);
		outb(hours,0x71);


		//set AIE to 1

		aux = in(0x0B);
		aux = aux | 0x20; 
		outb(0x0B,0x70);
		outb(aux,0x71);



		//set SET back to 0

		aux = in(0x0B);
		aux= aux & 0x7F; 
		outb(0x0B,0x70);
		outb(aux,0x71);		
	}
	while(1){

		if (in(0x0D) & 0x80)//read VRT 
		{
			uip_flag=1;
			do{
				if (in(0x0A)&0x80){	
					nanosleep(1984000);
				}else{
					uip_flag=0;
				}	
			}while(uip_flag);

			//write 1 to SET bit on 0x0B, first bit.
			aux = in(0x0B);
			aux = aux | 0x80; 
			outb(0x0B,0x70);
			outb(aux,0x71);

			//read D5 bit in C register, if it is set, then a clock interruption has ocurred
			outb(0x0C,0x70);
			if(!!(inb(0x71) & 0x20)){
				printf("Ocurrio una interrupcion de reloj a las %hhu:%hhu:%hhu\n", hours, minutes , seconds);
				aux = in(0x0B);
				aux= aux & 0x7F; 
				outb(0x0B,0x70);
				outb(aux,0x71);
				return;
			}

			//set SET back to 0

			aux = in(0x0B);
			aux= aux & 0x7F; 
			outb(0x0B,0x70);
			outb(aux,0x71);		
		}
	}




	return;
}

void squareWave(){

	return;
}

void main(){
	printf("UNSAM, PROGRAMACION, TP FINAL\n");
	printf("Alumno: Lovera Tomas Gonzalo \n");
	printf("Legajo: CYT-8308\n");
	int option;

	printf("\nBienvenido al tp final. Que desea hacer?\n");
	
	if (ioperm(0x70, 2, 1)) {
	   	perror("ioperm"); 
    	exit(1);
  	}

	do{
		printf("1.Mostrar el contenido de los registros 0 al 13\n2.Utilizando el RTC programar una alarma a determinada hora\n3.Utilizando el RTC obtener un tren de pulsos de 2Hz realizando un muestreo del registro C y graficarlo en pantalla en tiempo real\n4.Enviar por el puerto paralelo el campo minutos de la hora obtenida del RTC\n");
		scanf("%d",&option);

		switch(option){
			case 1:
  				showMeRegisters();			
				break;
			case 2:
				alarmAt();
				break;
			case 3:
				squareWave();
				break;
			case 4:

				break;
			case 5:
				printf("Saliendo.\n");
				return;
				break;
			default:
				printf("No es una opcion.\n");
				continue;
				break;
		}

		//Verificar interrupciones de alarma



	}while(1);




	return;
}