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
	delay(2000);
	printf("********************\n");
	printf("*  Menú Principal  *\n");
	printf("********************\n");
	delay(2000);
	
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
		displayMainMenu();
		displayErrorMsg();
		getMainOption();

		
	}

	return i;
}

/*int displayYesOrNo(){

}

void switchOption(int option){

	switch(option){

		case 1:
			if (sw == NULL)
			{
				
			}



	}

}
*/
int main()
{
	system("clear");
	int i;
	displayWelcome();
	displayMainMenu();
	i = getMainOption();
	return 0;
}
