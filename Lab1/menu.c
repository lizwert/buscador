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



void getQuery(char* word){
	


	printf("\n");
	printf("* Haga su consulta : ");
	

	while(getchar()!='\n');
	scanf("%[^\n]",word);
 
	
	
	
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Stroing start time
    clock_t start_time = clock();
 
    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}

int getAnswersAmount(){

	printf("\n\n\n");
	printf("||           hacer consulta         ||\n");
	printf("\n");
	int i = 0;

	printf("* Cantidad de respestas pedidas :  ");
	while(getchar()!='\n');
	scanf("%d",&i);
	if (i<1)

	{
		system("@cls||clear");
		printf("\n\n\n");
		printf("               !!!ERROR!!!             \n");
		printf("\n");
		printf("   La Cantidad escogida no es correcta \n");
		printf("\n\n\n");
		return getAnswersAmount();
	}
	return i;
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
		printf("	|	 6	   |    Salir                     |\n");
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
		system("@cls||clear");
		displayErrorMsg();
		displayMainMenu();
		return getMainOption();

		
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
		system("@cls||clear");
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

	if (strcmp(buffer,"si")==0 || strcmp(buffer,"Si")==0 || strcmp(buffer,"SI")==0 || strcmp(buffer,"sI")==0 || strcmp(buffer,"s")==0)
	{
		return 1;
	}
	else if (strcmp(buffer,"no")==0 || strcmp(buffer,"No")==0 || strcmp(buffer,"NO")==0 || strcmp(buffer,"nO")==0 || strcmp(buffer,"n")==0)
	{
		return 0;
	}
	else{
		while(getchar()!='\n');
		
		displayErrorMsg();
		return displayYesOrNo();
	}



}

void getDirectory(char* word){

	printf("\n");
	printf("* Ruta o nombre del archivo a leer : ");
	

	while(getchar()!='\n');
	scanf("%[^\n]",word);

}

void switchOption(int option,menu* Mn){

	char* buffer=(char*)malloc(sizeof(char)*MAX_CHARACTER*10);
	switch(option){



		case 1:
			
			system("@cls||clear");
			printf("*******Cargar StopWords*******\n\n");
			printf("*Ingrese nombre del documento o ubicacion del mismo: " );
			scanf("%s",buffer);
			Mn->sw=loadStopWords(buffer,Mn->code);


			printf("\n\n");

			printf("volviando el menu principal....\n");
			break;

		

		case 2:
			system("@cls||clear");
			char* wordIndex = (char*)malloc(sizeof(char)*MAX_CHARACTER*10);
			if (Mn->sw == NULL)
			{
				printf("-----------ERROR----------\n");
				printf("no hay StopWord cargados\n");
				if ( 1 == displayYesOrNo())
				{
					getDirectory(wordIndex);
					Mn->i = createIndex(wordIndex,Mn->sw,Mn->code);
					printf("************************************\n");
					printf("*         Indice Cargado           *\n");
					printf("************************************\n");

					printf("\n\n");

					printf("volviando el menu principal....\n");
					break;
				}
				else{
					break;
				}
			}
			else{
				getDirectory(wordIndex);
				Mn->i = createIndex(wordIndex,Mn->sw,Mn->code);
				printf("************************************\n");
				printf("*         Indice Cargado           *\n");
				printf("************************************\n");

				printf("\n\n");

				printf("volviando el menu principal....\n");
				break;
			}

		case 3:
			
			if (Mn->i == NULL)
			{
				printf("-----------ERROR----------\n");
				printf("no hay indice invertido cargado\n");
				break;
			}
			else{
					int * ID = (int*)malloc(sizeof(int));
					
					saveIndex(Mn->i,ID,Mn->code);
					printf("************************************\n");
					printf("*         Indice Guardado          *\n");
					printf("************************************\n");
					printf("*            ID: %i               *\n",*ID );
					printf("************************************\n");

					printf("\n\n");

					printf("volviando el menu principal....\n");
					break;
			}

		case 4:
			system("@cls||clear");
			int id = getID();
			Mn->i = loadIndex(id,Mn->code);
			//system("@cls||clear");
			if (Mn->i != NULL)
			{
					printf("************************************\n");
					printf("*         Indice Cargado           *\n");
					printf("************************************\n");
					printf("\n\n");

					printf("volviando el menu principal....\n");

			}else{
				printf("No se ha podido cargar el Indice \n");
				printf("\n\n");

				printf("volviando el menu principal....\n");
			}

			break;

		case 5:
			if (Mn->i == NULL)
			{
				printf("-----------ERROR----------\n");
				printf("no hay indice invertido cargado\n");

				printf("\n\n");

				printf("volviando el menu principal....\n");
				break;
			}
			else{
					int amount = getAnswersAmount();
					printf("**********************************************\n");
					printf("cantidad de respuestas pedidas : %d \n",amount);
					printf("**********************************************\n");
					getQuery(Mn->Query);
					Mn->rk=query(Mn->i,Mn->sw,Mn->Query,Mn->code);
					//system("@cls||clear");
					printf("**********************************************\n");
					printf("pregunta realizada : %s. \n",Mn->Query);
					printf("**********************************************\n");
					displayResults(Mn->rk,amount,Mn->code);
					break;
			}

		case 6:
			break;


		





	}

}


menu* menuInit(){
	menu* mn = (menu*)malloc(sizeof(menu));
	mn->i=NULL;
	mn->sw=NULL;
	mn->rk=NULL;
	mn->Query=(char*)malloc(sizeof(char)*MAX_CHARACTER*10);
	mn->code = (Code*)malloc(sizeof(Code));
	return mn;
}

int main()
{

	menu* mn = menuInit();
	system("@cls||clear");
	int i;
	displayWelcome();
	while(i != 6){

		displayMainMenu();
		i = getMainOption();
		
		switchOption(i,mn);

	}
	return 0;
}
