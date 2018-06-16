#include "stdio.h"
#include "stdlib.h"

/*En un laboratorio nuclear se tiene el archivo muestras.dat conformado por una cantidad
indeterminada de números enteros. Estos números están en el rango entre 102
y 107
y

representan el tiempo en segundos que tarda en desintegrarse una muestra.
No puede limitar la cantidad de números.
Se pide hacer un programa que realice las siguientes tareas:
I. Leer el archivo conformando una lista simple. Los nodos de la lista deben quedar en el
mismo orden que en el archivo del que fueron leídos.
II. Presentar un menú con las siguientes opciones:
1- Agregar un nuevo elemento al principio de la lista.
2- Eliminar el primer elemento que coincida con un valor ingresado por teclado.
3- Informar el tiempo de desintegración más bajo de la lista.
4- Mostrar todos los tiempos de desintegración que son mayores a un valor ingresado
por teclado e informar cuántos fueron.
5- Fin del menú.
Nota: Para cada opción del menú (excepto 5) se deberá usar al menos una función.*/

void main(){
	FILE *samples;
	int data,control;
	samples=fopen("muestras.dat","w");
	if (samples!=NULL)
	{
		printf("type int numbers (0 ends file writing):\n");
		while(1){
			scanf("%i",&data);
			if (data!=0)
			{
				control=fwrite(&data,sizeof(int),1,samples);
				if (control!=1){
					printf("An error ocurred during file writing. \n");
				}


			}else if (data==0)
			{
				printf("\nclosing file.\n");
				fclose(samples);
				break;
			}



		}


	}else{
		printf("erorr creaating file.\n");
	}


	return;
}