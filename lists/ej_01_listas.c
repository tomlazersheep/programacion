/*
Ej 1 practica listas
Escriba un programa que permita insertar un nuevo elemento antes del primer nodo de una lista lineal de enteros.
Programacion UNSAM
Autor: David Lopez
Año: 2017
*/

#include<stdio.h>
#include<stdlib.h>

//Declaración de la estructura para los nodos (tipo de datos)
typedef struct nodo {
	int dato;
	struct nodo *sig;	
} nodo;

//Inserta al principio
nodo *insertar_lifo (nodo *l, int d)
	{
	nodo *nuevo;

	nuevo = (nodo*) malloc (sizeof (nodo));
	nuevo->dato = d;
	nuevo->sig = l;
	return nuevo;
	}	

//Muestra los elementos de la lista
void mostrar (nodo *l) {
	printf ("Lista");
	while (l != NULL) {
		printf (" --> %d", l->dato);
		l = l->sig;
	}
	printf ("\n");
}


//Libera toda la memoria ocupada por la lista
nodo *destruir (nodo *l) {
	nodo * aux;

	while (l != NULL) {
		aux = l;
		l = l->sig;
		free (aux);
	}
	printf ("lista destruida\n");
	return NULL;
}

//Pide entros hasta que se ingrese cero y los inserta en la lista
nodo *ingresa_usuario(nodo *lista) {
	int temp;

	printf ("Ingrese un nro entero (cero finaliza):");
	scanf ("%d", &temp);
	while (temp != 0) {
		lista = insertar_lifo (lista, temp);
		printf ("\nIngrese otro nro entero (cero finaliza):");
		scanf ("%d", &temp);
	}
	return lista;	
}

//Programa principal que hace uso de las funciones definidas arriba
int main ()
	{
	nodo *lista = NULL;

	//Inserta en la lista los valores que ingrese el usuario
	lista = ingresa_usuario (lista);
	mostrar (lista);

	//Destruir lista
	lista = destruir(lista);

	return 0;
	}
