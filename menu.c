#include <stdio.h>

void displayWelcome(){
	printf("\n\n\n");
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
	printf("-Por favor seleccione una de las siguientes opciones.\n\n\n" );

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
int getOption(){
	int i = -5;
	printf("***********************************************\n");
	printf("*Opcion escogida : ");
	scanf("%d",&i);
	printf("***********************************************\n");

	if (i > 7 || i < 1 || i == -5)
	{
		while(getchar()!='\n');
		displayErrorMsg();
		getOption();
	}

	return i;
}

int main()
{
	int i;
	displayWelcome();
	displayMainMenu();
	i = getOption();
	return 0;
}
