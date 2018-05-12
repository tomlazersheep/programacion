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



node *insertar_lifo (node *l, int d)
	{
	node *nuevo;

	nuevo = (node*) malloc (sizeof (node));
	nuevo->data = d;
	nuevo->next = l;
	return nuevo;
	}	

node *deleteFirstN(node *first){
	int n,loop_flag=1;
	node *aux=first,*aux_prev;
	printf("que valor quiere eliminar?\n");
	scanf("%i",&n);

	while(loop_flag){
		if ((aux->data)==n){
			//ive found aux is the node to be deleted
			if (aux==first){
				first=aux->next;
				
			}else{
				aux_prev->next=aux->next;
			}	
			free(aux);
			loop_flag=0;
			printf("successfully deleted\n");		


		}else if (aux->next != NULL){
			aux_prev=aux;
			aux=aux->next;

		}else{

			printf("%i number not found\n", n );

		}
		
	}

	return first;
}

void showBiggerThan(node *first){
	printf("where is your minimum treshold?\n");
	int treshold,loop_flag=1,counter;
	node *aux=first;
	scanf("%i",&treshold);
	while(loop_flag){
		if (aux->next==NULL){
			loop_flag=0;
		}

		if (aux->data > treshold)
		{
			printf("%i  ",aux->data );
			counter++;
		}

		aux=aux->next;

	}
	printf("\n");
	printf("values found: %i\n",counter );
}


node *destruir (node *l) {
	node *aux;

	while (l != NULL) {
		aux = l;
		l = l->next;
		free (aux);
	}
	printf ("lista destruida\n");
	return NULL;
}

void smallerData(node *first){
	node *aux;
	int loop_flag=1,smaller;
	aux=first;
	smaller=aux->data;
	while(loop_flag){
		if (aux!=NULL){
			if (smaller > aux->data){
				smaller = aux->data;
			}
			aux=aux->next;
		}else{
			printf("End of list reached, smallest value found was %i  \n", smaller );
			return;
		}
	}
}

void showList(node *first){
	node *aux=first;
	int loop_flag=1;
	printf("value \t address \t\t next-address\n");
	while(loop_flag){
		if (aux->next!=NULL){

			printf("%i \t %p \t %p \n",aux->data, aux, aux->next );
			aux=aux->next;
		}else{
			printf("%i \t %p \t last-node \n",aux->data, aux);
			return;
		}
	}
}




int main()
{
	node *first,*auxa,*auxb;
	FILE* samples;
	int temporal_int,fread_return,user_choice,main_while_flag=1;
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
			while(main_while_flag){
				printf("Select an option\n");
				printf("1- Agregar un nuevo elemento al principio de la lista.\n");
				printf("2- Eliminar el primer elemento que coincida con un valor ingresado por teclado.\n");
				printf("3- Informar el tiempo de desintegración más bajo de la lista.\n");
				printf("4- Mostrar todos los tiempos de desintegración que son mayores a un valor ingresado por teclado e informar cuántos fueron.\n");
				printf("5- Fin del menú.\n");
				
				scanf("%i",&user_choice);
				switch(user_choice){
					case 1:
						printf("ingrese el nuevo dato al principio de la lista:\n");
						scanf("%i",&temporal_int);
						first=insertar_lifo(first,temporal_int);
						break;
					case 2:
						first=deleteFirstN(first);
						break;
					case 3:
						smallerData(first);
						break;
					case 4:
						//mostrar todos los data mayores a n
						showBiggerThan(first);

						break;
					case 5:
						first=destruir(first);
						main_while_flag=0;
						break;
					case 6:
						showList(first);
						break;
					default:
						printf("invalid option.\n");
						break;
				}


			}







		}else{
			printf("The file is empty or corrupted.\n");
		}

	}else{
		printf("muestras.dat not found.\n");
	}

	return 0;
}