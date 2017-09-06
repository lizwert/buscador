#include <stdio.h>
#include <stdlib.h>

typedef struct dulce
{
	char repre;
	int dureza;
	char* name;
	
}Candy;

typedef struct parmetros
{
	char dif;
	Candy* dulces;
	int* cantidad_de_dulces;
	int largo_dulces;
	
	
}Params;

typedef struct tablero
{
	Candy** matriz_dulces;
	int N;
	int M;
}Board;

int* dispenser(int N, int M, int dificultad,int largo){
	int total = N*M;

	int* cantidad = (int*)malloc(sizeof(int));

	switch(dificultad){

		case 1:
			cantidad = (int*)realloc(cantidad , sizeof(int)*5);
			cantidad[3] = (N/2) + (M/2);
			total = total - cantidad[3]-3;
			cantidad[0]= (total/3);
			cantidad[1]= (total/3);
			cantidad[2]= (total/3);
			cantidad[4]= 3;

			if ( (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]) != (N*M) )
			{
				cantidad[3] = cantidad[3] + ((N*M) - (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]) );
			}

			return cantidad;
			break;

		case 2:
			cantidad = (int*)realloc(cantidad , sizeof(int)*6);
			cantidad[4] = (N/2) + (M/2);
			total = total - cantidad[3]-2;
			cantidad[0]= (total/4);
			cantidad[1]= (total/4);
			cantidad[2]= (total/4);
			cantidad[3]= (total/4);
			cantidad[5]= 2;

			if ( (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[6]) != (N*M) )
			{
				cantidad[4] = cantidad[4] + ((N*M) - (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[5]) );
			}

			return cantidad;
			break;

		case 3:
			cantidad = (int*)realloc(cantidad , sizeof(int)*7);
			cantidad[5] = (N/2) + (M/2);
			total = total - cantidad[3]-2;
			cantidad[0]= (total/5);
			cantidad[1]= (total/5);
			cantidad[2]= (total/5);
			cantidad[3]= (total/5);
			cantidad[4]= (total/5);
			cantidad[6]= 1;

			if ( (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[6]) != (N*M) )
			{
				cantidad[5] = cantidad[5] + ((N*M) - (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[5]cantidad[6]) );
			}
			return cantidad;
			break;

		default:
			return cantidad=NULL;
			break;
	}

}
int eleccion(char dificultad){
	if (dificultad =='f')
	{
		return 5;
	}
	else if (dificultad =='m'){
		return 6;
	}
	else if (dificultad =='d'){
		return 7;
	}
	return 0;
}

Candy* bolsa(int dificultad){
	Candy* bolsa_de_dulces = (Candy*)malloc(sizeof(Candy));

	Candy fresa,limon,manzana,naranja,arandano,chocolate,especial;

	fresa.repre = 3;
	fresa.dureza = 1;
	fresa.name = "Fresa";

	limon.repre = 4;
	limon.dureza = 1;
	limon.name = "limon";

	manzana.repre = 5;
	manzana.dureza = 1;
	manzana.name = "manzana";


	naranja.repre = 6;
	naranja.dureza = 1;
	naranja.name = "naranja";


	arandano.repre = 42;
	arandano.dureza = 1;
	arandano.name = "arandano";

	chocolate.repre = 1;
	chocolate.dureza = 2;
	chocolate.name = "chocolate";

	especial.repre = 16:
	especial.dureza = 1;
	especial.name = "especial";




	switch(dificultad){
		case 1:
			bolsa_de_dulces = (Candy*)realloc(bolsa_de_dulces , sizeof(Candy)*5);
			bolsa_de_dulces[0] = fresa;
			bolsa_de_dulces[1] = limon;
			bolsa_de_dulces[2] = manzana;
			bolsa_de_dulces[3] = chocolate;
			bolsa_de_dulces[4] = especial;
			return bolsa_de_dulces;
			break;

		case 2:
			bolsa_de_dulces = (Candy*)realloc(bolsa_de_dulces , sizeof(Candy)*6);
			bolsa_de_dulces[0] = fresa;
			bolsa_de_dulces[1] = limon;
			bolsa_de_dulces[2] = manzana;
			bolsa_de_dulces[3] = naranja;
			bolsa_de_dulces[4] = chocolate;
			bolsa_de_dulces[5] = especial;
			return bolsa_de_dulces;
			break;

		case 3:
			bolsa_de_dulces =  (Candy*)realloc(bolsa_de_dulces , sizeof(Candy)*7);
			bolsa_de_dulces[0] = fresa;
			bolsa_de_dulces[1] = limon;
			bolsa_de_dulces[2] = manzana;
			bolsa_de_dulces[3] = naranja;
			bolsa_de_dulces[4] = arandano;
			bolsa_de_dulces[5] = chocolate;
			bolsa_de_dulces[6] = especial;
			return bolsa_de_dulces;
			break;

		default:
			printf("no se ingreso una dificultad valida.\n");
	        bolsa_de_dulces = NULL;
			return bolsa_de_dulces;
			break;
	}

}


Board* createBoard(int N, int M, Params params){
    int i;
	Candy** tabla = (Candy**)malloc(sizeof(Candy*)*N);
	for (i = 0; i < N; i++)
	{
		tabla[i]= (Candy*)malloc(sizeof(Candy)*M);
	}
	tabla = NULL;

	






}
void mostarMenu(){
	char dif;
	
	printf("\n\n\n\n");

	printf("************************************\n");
	printf("Bienvenido a esta mierda!\n\n\n");

	printf("Por favor Eliga una dificultad\n");
	printf("  f  =  Facil  ||  m   =  Medio   ||   d   =   Dificil\n");

	while(dif != 'f' && dif != 'm' && dif != 'd')
	{
		printf("Respuesta:  \n");
		scanf("%c", &dif);
	}

}
int main(int argc, char const *argv[])
{
	char dif;
	Candy* hola;
	hola= NULL;
	Params parametro = (Params)malloc(sizeof(Params));
	printf("\n\n\n\n");
	printf("************************************\n");
	printf("Bienvenido a esta mierda!\n\n\n");

	printf("Por favor Eliga una dificultad\n");
	printf("  f  =  Facil  ||  m   =  Medio   ||   d   =   Dificil\n");

	while(dif != 'f' && dif != 'm' && dif != 'd')
	{
		printf("Respuesta:  \n");
		scanf("%c", &dif);
	}

    hola = bolsa(dif);
		


	
	printf("hola :D\n");


	return 0;
}


