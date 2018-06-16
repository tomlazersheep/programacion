/*Leer por teclado los detalles (legajo, nombre, promedio) de n estudiantes (n <
100) y almacenarlo en el archivo estudiantes.dat*/
#include "stdio.h"
#include "stdlib.h"

struct estudiante
{
	int legajo;
	char nombre[20];
	float promedio;
};

int main()
{
	struct estudiante estudiantes[100];
	int i=0,whileFlag=1;
	do
	{
		printf("ingrese el legajo del estudiante:\n");
		scanf("%d",&estudiantes[i].legajo);
		printf("ingrese el nombre del estudiante:\n");
		fgets(estudiantes[i].nombre, sizeof(estudiantes[i].nombre), stdin);
		fgets(estudiantes[i].nombre, sizeof(estudiantes[i].nombre), stdin);
		printf("ingrese el promedio del estudiante:\n");
		scanf("%f",&estudiantes[i].promedio);

		printf("desea ingresar otro estudiante? (Y/n)\n");
		int ingresarOtro = 0;
		scanf("%i",&ingresarOtro);
		if (ingresarOtro==1)
		{
			i++;
		}else if(ingresarOtro==0){
			whileFlag=0;
		}

	} while (whileFlag);


	return 0;
}