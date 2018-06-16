/****************************************************************************
*							UNSAM - PROGRAMACION							*
*							2018 (1er cuatrimestre)							*
*								TRABAJO FINAL								*
*	Alumno: Lovera Tomas Gonzalo   				Legajo:CYT-8308				*
*	Email: loveratomasg@gmail.com											*	
*	Profesor: David Lopez													*
*	Fecha: 16/06/2018							Fecha entrega: 23/6/2018	*
*																			*
*	GitHub ssh repository clone address:									*
*	 git@github.com:tomlazersheep/programacion.git							*
*																			*
*****************************************************************************/

//***LIBRARIES***
#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include "sys/io.h"
#include <string.h>

//******HELPER METHODS*****  
unsigned char in (unsigned char reg){
  outb (reg, 0x70);
  return inb(0x70 + 1);
  }

int canIRW(){
	int uip_flag=1;
	unsigned char aux;
	if (in(0x0D) & 0x80){ // read VRT
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

			return 1;

	}else{
		return 0;
	}
}

void finishedRW(){
	unsigned char aux;
	//set SET back to 0
	aux = in(0x0B);
	aux= aux & 0x7F; 
	outb(0x0B,0x070);
	outb(aux,0x071);
}

//******FIRST ITEM****************

void showMeRegisters(){
	unsigned char registerContent[13];
	int address= 0x00,uip_flag=1;
	unsigned char aux;
	char description[14][20]={"segundos","segundos alarma","minutos    ","minutos alarma","horas   ","horas alarma","dia semana","dia mes    ","mes     ","anio     ","Registro A","Registro B","Registro C","Registro D"};

	if (canIRW())
	{
		//get all 13 registers
		for (int i = 0; i < 13; ++i)
		{
			outb(address,0x70);
			registerContent[i]=inb(0x71);
			address++;
		}
		finishedRW();
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


//*************SECOND ITEM*****************
void alarmAt(){
	/*Utilizando el RTC programar una alarma que se active a determinada hora ingresada por teclado
(HH:MM:SS). Al activarse la alarma debe aparecer un mensaje que lo informe.*/
	int uip_flag=1;
	unsigned char hours,minutes,seconds,aux;
	
	if (canIRW()){
		//if there was a prevoius interrupt, set it to 0 by reading it
		outb(0x0C,0x70);
		inb(0x71);		//i dont really care about the bit state, im just reading it in order to reset it to 0

		printf("insertar hora deseada para la alarma:\n");
		scanf("%x:%x:%x",&hours,&minutes,&seconds);

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

		finishedRW();		
	}
	
	while(1){

		if (canIRW()){
			//read D5 bit in C register, if it is set, then a clock interruption has ocurred
			outb(0x0C,0x70);
			if(!!(inb(0x71) & 0x20)){
				printf("Ocurrio una interrupcion de reloj\n");
				finishedRW();
				return;
			}
		}
	}
	return;
}


//**************THIRD ITEM***********************
void squareWave(){
	//2Hz -> T=0.5s e.g. 2 times per second
	//SQWE in 0x0B D3 enables square wave interruption
	// last 4 bits in 0x0A define SQW frequency, for my case 2Hz i need to set them all in 1
	unsigned char aux;
	if (canIRW()){
		//set RS0 RS1 RS2 RS3 to 1 in order to get 2Hz
		aux = in(0x0A);
		aux = aux | 0x0F; //set last 4 bits to 1
		outb(0x0A,0x70);
		outb(aux,0x71);

		//set SWQE to 1 in order to enable square wave interruptions
		aux = in(0x0B);
		aux = aux | 0x08;
		outb(0x0B,0x70);
		outb(aux,0x71);		

		finishedRW();

		//now i will print a scale, it asks for at least 10 seconds and i have interruptions every 0.5s, so it must fit 20 iterations at least
		for (int i = 1; i <= 15; ++i){
			printf("....!...%02i",i );
		}	
		printf("\n");

		//0.1s de espera
		for (int i = 0; i < 150; ++i)
		{
			usleep(100000);
			fflush(stdout);
			if(canIRW()){
				/*
				outb(0x0C,0x70);
				if(!!(inb(0x71) & 0x20)){
				*/
				finishedRW();
				if (0){			//condicion de interrupcion o no?
					printf("|");
				}else{
					printf(".");
				}
			}
		}
	}
	printf("\n");
	return;
}
//***************FOURTH ITEM*********************

void lptWrite(){


	return;
}

//***************MAIN METHOD AND MENU*******************
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
				lptWrite();
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