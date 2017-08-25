#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(){
	int i;

	char a[] = "Hola-como Estas";
	int valor = strlen(a);
	printf("%d\n",valor);
	
	for(i=0; i<valor;i++){
		a[i]=tolower(a[i]);

	}
	printf("%s\n",a);
	return 0 ;




}
