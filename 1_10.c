#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*Escribir una función que reciba las coordenadas cartesianas de 2 puntos en el
espacio y devuelva la distancia euclídea*/
struct punto
{
	int x;
	int y;
	int z;
};

int main(){
	struct punto p1, p2;
	printf("Ingrese las coordenadas del punto 1 separadas por espacios (x y z):\n");
	scanf("%d %d %d", &p1.x, &p1.y , &p1.z);
	printf("Ingrese las coordenadas del punto 2 separadas por espacios (x y z):\n");
	scanf("%d %d %d", &p2.x, &p2.y , &p2.z);

	float distancia = sqrt(pow(p1.x - p2.x,2)+pow(p1.y - p2.y,2)+pow(p1.z - p2.z,2) );

	printf("la distancia entre los 2 puntos es %.3f \n", distancia); 

	return 0;
}