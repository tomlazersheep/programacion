#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include "sys/io.h"

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
	char[20] description;
	int bitsOn;
} registerInfo;
*/
void showMeRegisters(){
	unsigned char[13] registerContent;
	int address= 0x00;
	//check for rtc registers
	for (int i = 0; i < 13; ++i)
	{
		outb(address,0x70);
		registerContent[i]=inb(0x71);
		address++;
	}

}





void main(){
	printf("UNSAM, PROGRAMACION, TP FINAL\n");
	printf("Alumno: Lovera Tomas Gonzalo \n");
	printf("Legajo: CYT-8308\n");
	
	if (ioperm(P, 2, 1)) {
    	perror("ioperm"); 
    	exit(1);
  	}


	return;
}