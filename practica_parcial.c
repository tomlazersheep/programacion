#include "stdlib.h"
#include "stdio.h"

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


typedef struct node{
	struct node *next;
	int data;
}node;

int main()
{
	node *first,*auxa,*auxb;
	FILE* samples;
	int temporal_int,fread_return;
	samples=fopen("muestras.dat","r");
	if (samples!=NULL)
	{

		fread_return=fread(&temporal_int,sizeof(int),1,samples);
		if (fread_return==1)
		{
			auxa=malloc(sizeof(node));
			auxa->data=temporal_int;
			first=auxa;

			while(1){

				fread_return=fread(&temporal_int,sizeof(int),1,samples);
				if (fread_return==1){
					auxb=malloc(sizeof(node));
					auxb->data=temporal_int;
					auxa->next=auxb;
					auxa=auxb;
				}else{
					auxa->next=NULL;
					fclose(samples);
					break;
				}		

			}


			//from here the list is done
			


		}else{
			printf("The file is empty or corrupted.\n");
		}

	}else{
		printf("muestras.dat not found.\n");
	}

	return 0;
}