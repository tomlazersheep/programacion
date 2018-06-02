#include <stdlib.h>
#include "stdio.h"
#include "string.h"
/*Leeer un string por teclado y luego convertirlo a mayúsculas sin usar las
funciones de string.h (ayuda: piense en los códigos ASCII y el nro. 32)*/

int main()
{
	char s[20];
	printf("ingrese un string:\n");
	//scanf("%19[^/n]",s);
	fgets(s, sizeof(s),stdin);
	//printf("%s\n", s);
	for (int i = 0; i < (strlen(s)-1); ++i)
	{
		if (s[i]!=32)
		{
			s[i]-=32;
		}
	}
	//printf("%d \n",strnlen(s,20) );
	printf("%s\n", s);
	return 0;
}