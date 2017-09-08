#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
#include "gets.h"
#include "index.h"
#include "inserts.h"
#include "tools.h"
#include "StopWords.h"
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Stroing start time
    clock_t start_time = clock();
 
    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}

void displayWelcome(){

	
	printf("\n\n\n");
	printf("************************************************************************\n");
	printf("\n\n\n");
	printf("                      Bienvenido al Buscador                            \n");
	printf("\n\n\n");
	printf("************************************************************************\n");
	printf("\n\n\n");
	printf("********************\n");
	printf("*  Menú Principal  *\n");
	printf("********************\n");
	
	
}
void displayMainMenu(){

	delay(2000);
	printf("\n\n");
	printf("-Por favor seleccione una de las siguientes opciones.\n\n" );

	    	printf("	--------------------------------------------------- \n");
		printf("	|    N° opcion     |    accion                    |\n ");
		printf("	--------------------------------------------------\n");
		printf("	|		   |                              |\n");
		printf("	|	 1	   |    Cargar StopWord           |\n");
		printf("	|		   |                              |\n");
		printf("	|	 2	   |    Crear indice invertido    |\n");
		printf("	|		   |                              |\n");
		printf("	|	 3	   |    Guardar indice invertido  |\n");
		printf("	|		   |                              |\n");
		printf("	|	 4	   |    Cargar indice invertido   |\n");
		printf("	|		   |                              |\n");
		printf("	|	 5	   |    Hacer Consulta            |\n");
		printf("	|		   |                              |\n");
		printf("	|	 6	   |    Ayuda                     |\n");
		printf("	|		   |                              |\n");
		printf("	|	 7	   |    Salir                     |\n");
		printf("	|		   |                              |\n");
		printf("	---------------------------------------------------\n\n");
}
void displayErrorMsg(){
	
	printf("\n\n\n");
	printf("               !!!ERROR!!!             \n");
	printf("\n");
	printf("    Por favor escoja un opcion valida!\n");
	printf("\n\n\n");
}
int getMainOption(){
	int i = -5;
	printf("***********************************************\n");
	printf("*Opcion escogida : ");
	scanf("%d",&i);
	printf("***********************************************\n");

	if (i > 7 || i < 1 || i == -5)
	{
		while(getchar()!='\n');
		system("clear");
		displayErrorMsg();
		displayMainMenu();
		getMainOption();

		
	}

	return i;
}

int getID(){

	int i = 0;
	printf("||           Cargar indice invertido         ||\n");
	printf("***********************************************\n");
	printf("*ingrese un ID de indice : ");
	scanf("%d",&i);
	printf("***********************************************\n");

	if ( i < 1)
	{
		while(getchar()!='\n');
		system("clear");
		printf("\n\n\n");
		printf("               !!!ERROR!!!             \n");
		printf("\n");
		printf("    Por favor escoja un opcion valida!\n");
		printf("\n\n\n");
		i = getID();

		
	}
	return i;

}

int displayYesOrNo(){

	char buffer[100];
	printf("¿Esta seguro que desea continuar? Si/No = ");
	scanf("%s",buffer);

	if (strcmp(buffer,"si")==0 || strcmp(buffer,"Si")==0 || strcmp(buffer,"SI")==0 || strcmp(buffer,"sI")==0)
	{
		return 1;
	}
	else if (strcmp(buffer,"no")==0 || strcmp(buffer,"No")==0 || strcmp(buffer,"NO")==0 || strcmp(buffer,"nO")==0)
	{
		return 0;
	}
	else{
		while(getchar()!='\n');
		
		displayErrorMsg();
		return displayYesOrNo();
	}



}

void switchOption(int option,Index* index,StopWords* sw,Ranking* rk){

	switch(option){
		

		case 2:
			system("clear");
			if (sw == NULL)
			{
				printf("-----------ERROR----------\n");
				printf("no hay StopWord cargados\n");
				if ( 1 == displayYesOrNo())
				{
					
					index = createIndex("hola.txt",sw);
					printf("************************************\n");
					printf("*         Indice Cargado           *\n");
					printf("************************************\n");
				}
				else{
					break;
				}
			}

		case 3:
			index = createIndex("hola.txt",sw);
			if (index == NULL)
			{
				printf("-----------ERROR----------\n");
				printf("no hay indice invertido cargado\n");
				break;
			}
			else{
					int * ID = (int*)malloc(sizeof(int));
					
					saveIndex(index,ID);
					printf("************************************\n");
					printf("*         Indice Guardado          *\n");
					printf("************************************\n");
					printf("*            ID: %i               *\n",*ID );
					printf("************************************\n");
					break;
			}

		case 4:
			system("clear");
			int id = getID();
			index = loadIndex(id);
			break;

		





	}

}

int main()
{
	Index* index= NULL;
	StopWords* sw= NULL;
	Ranking* rk= NULL;
	system("clear");
	int i;
	displayWelcome();
	displayMainMenu();
	i = getMainOption();
	
	switchOption(i,index,sw,rk);

	return 0;
}
