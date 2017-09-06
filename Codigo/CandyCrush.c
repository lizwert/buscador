#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"
#include "creacion.h"
#include "menu.h"
#define TRUE 1
#define FALSE 0
#define FACIL 1
#define MEDIO 2
#define DIFICIL 3
#define PARTIDA_RAPIDA 1
#define PARTIDA_PORSONALIZADA 2






//Ejecuta el proceso de interaccion con el usuario, pide ls acciones a ejecutar.
void playOption(){
	srand(time(NULL));
	int option = pedirOpcion(1,4);
	int ID;
	Board* tablero;

	switch (option){

		case PARTIDA_RAPIDA:
			printf("********************\n");
			printf("*  Partida Rápida  *\n");
			printf("********************\n");
			mostarMenuPrimeraOpcion();
			playDificultad();
			break;

		case 2:
			printf("ingrese un ID :\n");
			scanf("%d",&ID);
			tablero = loadBoard(ID,CREATE_BOARD);
			if (tablero != NULL)
			{
				Print(tablero,CREATE_BOARD);
			}
			else{
				printf("No se encontro el ID\n");
			}

			break;

		case 3:
			
			break;

		case 4:
	
			break;

		case 5:

			break;

		case 6:
			printf("Saliendo...\n");
			return;
			break;			

	}
}

void playDificultad(){
	int dificultad = pedirOpcion(FACIL,DIFICIL);
	int N,M,eleccion,x,y,puntaje=0;
	Position Inicial,Final;
	int* ID=(int*)malloc(sizeof(int));
	int* turnos =(int*)malloc(sizeof(int));
	Params parametro;
	Board* tablero=(Board*)malloc(sizeof(Board));
	

	switch(dificultad){

		case FACIL:
			printf("Se ha seleccionado dificultad facil\n");
			(*turnos) = 25;
			N= 6+rand() % 7;
			M= 6+rand() % 7;
			parametro = generarParams(FACIL,N,M);
			tablero = createBoard(20,20, parametro,CREATE_BOARD);
			printf("N= %d, M=%d\n",N,M );
	

			break;

		case MEDIO:
			printf("Se ha seleccionado dificultad Medio\n");
			(*turnos) = 35;
			N= 13+rand() % 7;
			M= 13+rand() % 7;
			printf("N= %d, M=%d\n",N,M );
			parametro = generarParams(MEDIO,N,M);
			tablero = createBoard(20,20, parametro,CREATE_BOARD);

			break;

		case DIFICIL:
			(*turnos)=45;
			printf("Se ha seleccionado dificultad Dificil\n");
			N= 19+rand() % 7;
			M= 19+rand() % 7;
			printf("N= %d, M=%d\n",N,M );
			
			parametro = generarParams(DIFICIL,N,M);
			tablero = createBoard(20,20, parametro,CREATE_BOARD);
			break;
	}
	while(*turnos != 0){

	
		printf("tablero actualizado:\n");
		Print(tablero,CREATE_BOARD);
		printf("Juego actual     Turnos = %d     Puntaje = %d \n",*turnos, puntaje );
		playMenu();
		printf("\n");
		printf("escoja una opcion : ");
		scanf("%d",&eleccion);
		while(eleccion !=0 && (eleccion>4 || eleccion <0)){
				printf("eleccion escojida invalida\n");
				playMenu();
				printf("\n");
				printf("escoja una opcion : ");
				scanf("%d",&eleccion);
			}

			if (eleccion==1)
			{
				Print(tablero,CREATE_BOARD);
					printf("***Recuerde que para mover,las posiciones deben ser adyacentes***\n");
					printf("escoja una posicion inicial (x,y) : \n");
					printf("x= ");
					scanf("%d",&x);
					printf("y= ");
					scanf("%d",&y);
					printf("posicion inicial escogida = (%d,%d), dulce = %c\n",x,y,(*tablero).matriz_dulces[x][y].repre);
					Inicial.N=x;
					Inicial.M=y;
					Inicial.dulce=(*tablero).matriz_dulces[x][y];
					Inicial.valor=1;
				while(((x>(*tablero).fila && x<0) && (y>(*tablero).columna && y<0)) || (*tablero).matriz_dulces[x][y].repre =='C'){
					printf("No se pueden salir de los limites del tablero o mover los chocolates (C)\n");
					printf("escoja una posicion inicial (x,y) : \n");
					printf("x= ");
					scanf("%d",&x);
					printf("y= ");
					scanf("%d",&y);
					printf("posicion inicial escogida = (%d,%d), dulce = %c\n",x,y,(*tablero).matriz_dulces[x][y].repre);
					Inicial.N=x;
					Inicial.M=y;
					Inicial.dulce=(*tablero).matriz_dulces[x][y];
					Inicial.valor=1;

				}
				x=0;
				y=0;

				printf("escoja una posicion final (x,y) :\n");
				printf("x= ");
				scanf("%d",&x);
				printf("y= ");
				scanf("%d",&y);
				printf("posicion final escogida = (%d,%d), dulce = %c\n",x,y,(*tablero).matriz_dulces[x][y].repre );
				Final.N=x;
				Final.M=y;
				Final.dulce=(*tablero).matriz_dulces[x][y];
				Final.valor=1;
				while(((x>(*tablero).fila && x<0) && (y>(*tablero).columna && y<0)) || (*tablero).matriz_dulces[x][y].repre =='C'){
					printf("No se pueden salir de los limites del tablero o mover los chocolates (C)\n");
					printf("escoja una posicion final (x,y) :\n");
					printf("x= ");
					scanf("%d",&x);
					printf("y= ");
					scanf("%d",&y);
					printf("posicion final escogida = (%d,%d), dulce = %c\n",x,y,(*tablero).matriz_dulces[x][y].repre );
					Final.N=x;
					Final.M=y;
					Final.dulce=(*tablero).matriz_dulces[x][y];
					Final.valor=1;
				}
				printf("actual = (%d,%d), destino (%d,%d) \n",Inicial.N,Inicial.M,Final.N,Final.M);
				puntaje = puntaje + play(tablero,Inicial,Final,turnos,CREATE_BOARD);
				//printf("puntaje = \n");


			}
			else if(eleccion==2)
			{
				saveBoard(tablero,ID,CREATE_BOARD);
			}
			else if(eleccion == 3){
				if (checkBoard(tablero,CREATE_BOARD)==TRUE)
				{
					printf("es un tablero valido\n");
				}
				else{
					printf("no es un tablero valido\n");
					break;
				}
			}
			else if(eleccion == 4){
				printf("Saliendo...\n");
				break;

				
			}
			
		

	}
	for (x = 0; x < (*tablero).fila; x++)
	{
		for ( y = 0; y < (*tablero).columna; y++)
		{
			if ((*tablero).matriz_dulces[x][y].repre=='C' && *turnos ==0)
			{
				printf("Ha pedido!!!\n");
				printf("puntaje obtenido del juego = %d\n",puntaje);
				printf("********************\n");
				printf("*  Menú Principal  *\n");
				printf("********************\n");
				mostarMenu();
				playOption();
				
			}
		}
	}

	printf("Ha Ganado!!!\n");
	printf("puntaje obtenido del juego = %d\n",puntaje);
	printf("********************\n");
	printf("*  Menú Principal  *\n");
	printf("********************\n");
	mostarMenu();
	playOption();
	

}




int pedirOpcion(int valorMin, int valorMax){
	int Opcion;
	int primeraVez = TRUE;
	
	do
	{
		if(!primeraVez){
			
			printf("\n");
			printf("Opcíon invalida. Elija una opción valida!\n");
			if(valorMax == 3){
				mostarMenuPrimeraOpcion();
			}
			else if(valorMax == 4){
				mostarMenu();	
			}
			
		}
		primeraVez = FALSE;
		printf("\n");
		
		scanf("%d", &Opcion);
		
		while(getchar()!='\n'); //limpiar buffer de teclado.
		
		


	}while(Opcion < valorMin || Opcion > valorMax);
	
	return Opcion;
}

void mostarMenuPrimeraOpcion(){

	printf("Seleccione dificultad: \n");
	printf("1 = Facil \n");
	printf("2 = Medio \n");
	printf("3 = Dificil \n");

}

void mostarMenu(){
	printf("\n");
	printf("1) Jugar Partida Rápida \n");
	printf("2) Cargar Board \n");
	printf("3) Check Board\n");
	printf("4) Salir\n");

}
void playMenu(){
	printf("opciones de juego:\n");
	printf("1) Mover Dulce\n");
	printf("2) Guardar Tablero\n");
	printf("3) Check Board\n");
	printf("4) Salir\n");
}


int main(int argc, char const *argv[])
{
	printf("************************************************************************\n");
	printf("\n\n\n");
	printf("                      Bienvenido a Candy Crush                                   \n");
	printf("\n\n\n");
	printf("************************************************************************\n");
	printf("\n\n\n");
	printf("********************\n");
	printf("*  Menú Principal  *\n");
	printf("********************\n");

	mostarMenu();
	playOption();
	return 0;
}