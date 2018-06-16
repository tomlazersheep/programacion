void squareWave(){
	//2Hz -> T=0.5s e.g. 2 times per second
	//SQWE in 0x0B D3 enables square wave interruption
	// last 4 bits in 0x0A define SQW frequency, for my case 2Hz i need to set them all in 1
	unsigned char aux;
	if (canIRW()){ // Este metodo hace todos los checkeos de VRT y bit SET=1
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

		finishedRW(); // Este metodo devuelve el bit SET a 0 despues de trabajar con los registros del clock. 

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
				outb(0x0C,0x70);			//Aca necesitaria saber como es el estado de la salida de onda cuadrada, si esta en 0 o 1
				if(!!(inb(0x71) & 0x20)){
				*/
				finishedRW();
				if (0){			//condicion de interrupcion o no? en lugar de ese cero tendria que tener algo que represente el estado de SQW
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