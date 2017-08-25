#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
	char original[] = "como";
	char parte[] = ",";
	int valor = strlen(parte);
	char* nueva=(char*)malloc(sizeof(char)*20);
	int posicion = strlen( original ) - strlen( strstr( original, parte ) );
 
	
	for( int a = 0; a < posicion; a++ )
		nueva[ a ] = original[ a ];
 
	
	for( int a = posicion; a < strlen( original ); a++ )
		nueva[ a ] = original[ a+valor ]; 
 
	nueva[ 20 ] = '\0';
	printf( "%s\n", nueva );
	return 0;
}
