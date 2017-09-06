#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "candies.h"


Candy crearBolsa(Candy dulce){
	char repre = dulce.repre;

	switch(repre){
		case 'F':
			dulce.repre = 'F';
			dulce.dureza = 1;
			dulce.ID=1;
			dulce.name = "Fresa";
			return dulce;
			break;

		case 'L':
			dulce.repre = 'L';
			dulce.dureza = 1;
			dulce.ID=2;
			dulce.name = "limon";
			return dulce;
			break;

		case 'M':
			dulce.repre = 'M';
			dulce.dureza = 1;
			dulce.ID=3;
			dulce.name = "manzana";
			return dulce;
			break;

		case 'N':
			dulce.repre = 'N';
			dulce.dureza = 1;
			dulce.ID=4;
			dulce.name = "naranja";
			return dulce;
			break;

		case 'A':
			dulce.repre = 'A';
			dulce.dureza = 1;
			dulce.ID=5;
			dulce.name = "arandano";
			return dulce;
			break;

		case 'C':
			dulce.repre = 'C';
			dulce.dureza = 2;
			dulce.ID=6;
			dulce.name = "chocolate";
			return dulce;
			break;

		case 'E':
			dulce.repre = 'E';
			dulce.dureza = 1;
			dulce.ID=7;
			dulce.name = "especial";
			return dulce;
			break;

		case 'P':
			dulce.repre = 'P';
			dulce.dureza = 1;
			dulce.ID=8;
			dulce.name = "platano";
			return dulce;
			break;

		case 'U':

			dulce.repre = 'U';
			dulce.dureza = 1;
			dulce.ID=9;
			dulce.name = "uva";
			return dulce;
			break;
			
		default:
			return dulce;
			break;

	}

}
Candy* bolsa(int dificultad){

	Candy* bolsa_de_dulces = (Candy*)malloc(sizeof(Candy));
	Candy fresa,limon,manzana,naranja,arandano,chocolate,especial,platano,uva;

	fresa.repre = 'F';
	fresa.dureza = 1;
	fresa.ID=1;
	fresa.name = "Fresa";

	limon.repre = 'L';
	limon.dureza = 1;
	limon.ID=2;
	limon.name = "limon";

	manzana.repre = 'M';
	manzana.dureza = 1;
	manzana.ID=3;
	manzana.name = "manzana";


	naranja.repre = 'N';
	naranja.dureza = 1;
	naranja.ID=4;
	naranja.name = "naranja";


	arandano.repre = 'A';
	arandano.dureza = 1;
	arandano.ID=5;
	arandano.name = "arandano";

	chocolate.repre = 'C';
	chocolate.dureza = 2;
	chocolate.ID=6;
	chocolate.name = "chocolate";

	especial.repre = 'E';
	especial.dureza = 1;
	especial.ID=7;
	especial.name = "especial";

	platano.repre = 'P';
	platano.dureza = 1;
	platano.ID=8;
	platano.name = "platano";

	uva.repre = 'U';
	uva.dureza = 1;
	uva.ID=9;
	uva.name = "uva";




	switch(dificultad){
		case 1:
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

		case 2:
			bolsa_de_dulces =  (Candy*)realloc(bolsa_de_dulces , sizeof(Candy)*8);
			bolsa_de_dulces[0] = fresa;
			bolsa_de_dulces[1] = limon;
			bolsa_de_dulces[2] = manzana;
			bolsa_de_dulces[3] = naranja;
			bolsa_de_dulces[4] = arandano;
			bolsa_de_dulces[5] = chocolate;
			bolsa_de_dulces[6] = platano;
			bolsa_de_dulces[7] = especial;
			return bolsa_de_dulces;
			break;

		case 3:
			bolsa_de_dulces =  (Candy*)realloc(bolsa_de_dulces , sizeof(Candy)*9);
			bolsa_de_dulces[0] = fresa;
			bolsa_de_dulces[1] = limon;
			bolsa_de_dulces[2] = manzana;
			bolsa_de_dulces[3] = naranja;
			bolsa_de_dulces[4] = arandano;
			bolsa_de_dulces[5] = chocolate;
			bolsa_de_dulces[6] = platano;
			bolsa_de_dulces[7] = uva;
			bolsa_de_dulces[8] = especial;
			return bolsa_de_dulces;
			break;

		default:
			printf("no se ingreso una dificultad valida.\n");
	        bolsa_de_dulces = NULL;
			return bolsa_de_dulces;
			break;
	}

}

int* dispenser(int N, int M, int dificultad,int largo){
	int total = N*M;

	int* cantidad = (int*)malloc(sizeof(int));

	switch(dificultad){

		case 1:
			cantidad = (int*)realloc(cantidad , sizeof(int)*7);
			cantidad[5] = (N/2) + (M/2);
			total = total - cantidad[5]-3;
			cantidad[0]= (total/5);
			cantidad[1]= (total/5);
			cantidad[2]= (total/5);
			cantidad[3]= (total/5);
			cantidad[4]= (total/5);
			cantidad[6]= 3;

			if ( (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[5]+cantidad[6]) != (N*M) )
			{
				cantidad[5] = cantidad[5] + ((N*M) - (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[5]+cantidad[6]) );
			}
			return cantidad;
			break;

		case 2:
			cantidad = (int*)realloc(cantidad , sizeof(int)*8);
			cantidad[5] = (N/2) + (M/2);
			total = total - cantidad[5]-2;
			cantidad[0]= (total/6);
			cantidad[1]= (total/6);
			cantidad[2]= (total/6);
			cantidad[3]= (total/6);
			cantidad[4]= (total/6);
			cantidad[6]= (total/6);
			cantidad[7]= 2;

			if ( (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[5]+cantidad[6]+cantidad[7]) != (N*M) )
			{
				cantidad[5] = cantidad[5] + ((N*M) - (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[5]+cantidad[6]+cantidad[7]) );
			}
			return cantidad;
			break;

		case 3:
			cantidad = (int*)realloc(cantidad , sizeof(int)*9);
			cantidad[5] = (N/2) + (M/2);
			total = total - cantidad[5]-2;
			cantidad[0]= (total/6);
			cantidad[1]= (total/6);
			cantidad[2]= (total/6);
			cantidad[3]= (total/6);
			cantidad[4]= (total/6);
			cantidad[6]= (total/6);
			cantidad[7]= (total/7);
			cantidad[8]= 2;

			if ( (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[5]+cantidad[6]+cantidad[7]+cantidad[8]) != (N*M) )
			{
				cantidad[5] = cantidad[5] + ((N*M) - (cantidad[3]+cantidad[0]+cantidad[1]+cantidad[2]+cantidad[4]+cantidad[5]+cantidad[6]+cantidad[7]+cantidad[8]) );
			}
			return cantidad;
			break;

		default:
			return cantidad=NULL;
			break;
	}

}