#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int datafield;
	struct node *next;
} node;


//Inserta al principio

node *insertar_lifo (node *l, int d){
	node *newnode;
	newnode = (node*) malloc (sizeof (node));
	newnode->datafield = d;
	newnode->next = l;
	return newnode;
	}

void showlist(node *first){
	int counter;
	counter = 0;
	while(1){
		counter++;

		if((*first).next==NULL){
			printf("%i \t %d \t %s \n",(*first).datafield,first,"last node");
			break;
		}else{
			printf("%i \t %d \t %d \n",(*first).datafield,first,(*first).next);
			first= (*first).next;
		}

		
	}

	printf("hay %i nodos en la lista.\n \n", counter);
	return;	
}

void dividirListas (node *first, node *odd, node *even, node *newfirstodd , node *newfirsteven){

	while(1){
		if((*first).next==NULL){
			//hacer ultima eleccion
			if( ( ( (*first).datafield ) % 2 ) == 0 ){
				//printf("par \n");
				even=insertar_lifo(even,(*first).datafield);
				newfirsteven=even;

					
			}else{
				//printf("impar %i \n",(*first).datafield);
				odd=insertar_lifo(odd,(*first).datafield);
				newfirstodd=odd;
			}

			break;
		}else{
			//hacer eleccion y pasar a las otras 2 listas
			if( ( ( (*first).datafield ) % 2 ) == 0 ){
				//printf("par \n");
				even=insertar_lifo(even,(*first).datafield);
				newfirsteven=even;

					
			}else{
				//printf("impar %i \n",(*first).datafield);
				odd=insertar_lifo(odd,(*first).datafield);
			}
			first= (*first).next;
		}

		
	}
	return;	
}

            

/*
1.Escriba un programa que permita insertar un nuevo elemento antes del primer nodo de una lista
lineal de enteros.

2. Escriba una función que devuelva la cantidad de elementos de una lista lineal.

3. Dada una lista encadenada, formada por números enteros, hacer un programa que la divida en
dos listas: pares e impares.
*/

int main(){
	node *first=NULL;
	node *firstOdd=NULL;
	node *firstEven=NULL;

//creo algunos nodos para probar, sino tendria que crearlos en cada ejecucion con un loop
	first= insertar_lifo(first,32);
	first= insertar_lifo(first,21);
	first= insertar_lifo(first,55);
	first= insertar_lifo(first,55);
	first= insertar_lifo(first,55);
	first= insertar_lifo(first,52);
	first= insertar_lifo(first,22);

	printf("valor \t direccion \t proxima direccion\n");
	showlist(first);	
	dividirListas(first,firstOdd,firstEven);
	return 0;
}

