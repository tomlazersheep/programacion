#include "stdlib.h"
#include "stdio.h"

typedef struct nodo{
	struct nodo *next,*prev;
	int data;
} nodo;

typedef struct list_pointers
{
	nodo *first,*last;
}list_pointers;


/*
Escribir una función que inserte un elemento en una lista doblemente encadenada:
a. En un extremo de la lista.
b. En un lugar intermedio (por ejemplo la posición n).*/

list_pointers insertar_nodo (list_pointers pointers, int d,int n){
	nodo *aux_pointer,*prev_node;

	aux_pointer=(nodo*)malloc(sizeof(nodo));
	aux_pointer->data=d;

	if (n==0 || n==1 || pointers.first==NULL){
		aux_pointer->next = pointers.first;  //en el nuevo primer nodo el campo next apunta al viejo primer nodo 

		if (pointers.first!=NULL) //si la lista no esta vacia
		 {
		 	pointers.first->prev = aux_pointer;  //esta linea rompe todo
		 } 

		pointers.first = aux_pointer;		 //el nuevo primer nodo toma el lugar del viejo en el primer lugar de la lista
		pointers.first->prev=NULL;
	}else{
		prev_node=pointers.first;

		for (int j=0;j=(n-1) ; j++){
			prev_node =  
		}

	}
	

	return pointers;
}
















void showlist(list_pointers pointers){
	int counter=0;
	nodo *aux_pointer;
	aux_pointer=pointers.first;
	while(1){
		

		if (aux_pointer==NULL){
			printf("This list is empty.\n");
			break;
		}else if(aux_pointer->next==NULL){
			printf("%i \t %i \t %s \n",aux_pointer->data,aux_pointer,"last node");
			break;
		}else{
			printf("%i \t %i \t %i \n",aux_pointer->data,aux_pointer,aux_pointer->next);
			aux_pointer= aux_pointer->next;
		}
		counter++;
		
	}

	printf("hay %i nodos en la lista.\n \n", ++counter);
	return;	
}






int main()
{
	//variable declaration
	int command,whileflag=1,newData,newPosition;
	list_pointers list;
	list.first=NULL;
	list.last=NULL;



	//menu
	do{
		printf("Select a command:\n");
		printf("1.insert node subroutine\n");
		printf("2.print list\n");
		printf("3.delete list and exit\n");
		scanf("%i",&command);
		switch(command){
			case 1:
				printf("Data field for the new node: \n");
				scanf("%i",&newData);
				printf("Select position for new node insertion:\n");
				scanf("%i",&newPosition);
				list=insertar_nodo(list,newData,newPosition);
				//llamar a subrutina de insercion de nodo
				break;
			case 2:
				//imprimir lista
				showlist(list);

				break;
			case 3:
				//borrar_lista() y salir del while
				whileflag=0;
				printf("caso 3 correcto\n");
				break;
			default:
				printf("Invalid option. Try again.\n");

		}
	}while(whileflag);



	return 0;
}