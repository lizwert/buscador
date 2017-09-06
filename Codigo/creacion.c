#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "candies.h"
#include "creacion.h"
#define CHOCOLATE 6
#define TRUE 1
#define FALSE 0


void Print(Board* b,code *statusCode){

	int i, j;
	printf("");
	for (i = 0; i < (*b).columna; i++)
	{
		printf("%d ",i);
	}
	printf("\n");

	for ( i = 0; i < (*b).fila; i++)
	{
		//printf("%d ",i);
		for (j = 0; j < (*b).columna; j++)
		{
			printf("%c ",(*b).matriz_dulces[i][j].repre);
		}
		printf("%d ",i);
		printf("\n");
		
	}
	//*statusCode = OK;

}



Board* createBoard(int N, int M, Params params,code *statusCode){
	/*if(N>26 || M>26 || N<0 || M<0 ){
		*statusCode = DIMENSIONS_NOT_ALLOWED;
	}*/
	printf("1\n");
	int i,j,indice;
	Board* pun_tabla = (Board*)malloc(sizeof(Board));
	Candy** tablero = (Candy**)malloc(sizeof(Candy*)*N);
	for ( i = 0; i < N; i++)
	{
		tablero[i]= (Candy*)malloc(sizeof(Candy)*M);
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			
			indice = rand() % params.largo_dulces;
			tablero[i][j]= params.dulces[indice];


			if (i>=2)
			{
				if (params.dulces[indice].ID != CHOCOLATE)
				{
					while(tablero[i][j].ID == tablero[i-2][j].ID || params.cantidad_de_dulces[indice] == 0){
					indice = rand() % (params.largo_dulces);
					tablero[i][j]= params.dulces[indice];
					}
				}

			}
			if (j>=2)
			{
				if (params.dulces[indice].ID != CHOCOLATE)
				{
						
					
					while(tablero[i][j].ID == tablero[i][j-2].ID || params.cantidad_de_dulces[indice] == 0){
						indice = rand() % (params.largo_dulces);
						tablero[i][j]= params.dulces[indice];
					}
				}
			}
			params.cantidad_de_dulces[indice] = params.cantidad_de_dulces[indice]-1;

			
		}
	}

	//*statusCode = OK;
	printf("2\n");
	(*pun_tabla).matriz_dulces = tablero;
	(*pun_tabla).fila= N;
	(*pun_tabla).columna= M;
	(*pun_tabla).dificultad = params.dif;


	return pun_tabla;

}
char* DateHour(){
	struct tm *tm;
	time_t fecha;
  	
  	char* fechayhora = (char*)malloc(sizeof(char)*100);

  	fecha=time(NULL);
  	tm=localtime(&fecha);
  	strftime(fechayhora, 100, "%d/%m/%Y || %H:%M", tm);
  	return fechayhora;
	
}

void saveBoard(Board *b, int *id ,code *statusCode){
	srand(time(0));
	char nombre_archivo[100];
	char* horario = (char*)malloc(sizeof(char)*100);
	int i,j;
	(*id) = 100 + rand() % 1000;
	sprintf(nombre_archivo,"%d.id",*id);
	while(fopen(nombre_archivo,"r")!=NULL)
	{
		(*id) = 100 + rand() % 1000;
		sprintf(nombre_archivo,"%d.id",*id);
		//*statusCode = DIMENSIONS_NOT_ALLOWED;

	}
	FILE* archivo = fopen(nombre_archivo,"w");
	horario = DateHour();

	fprintf(archivo, "Board guardado en : %s\n",horario );
	fprintf(archivo, "%d\n",(*b).dificultad );
	fprintf(archivo, "%d %d\n",(*b).fila,(*b).columna );


		for ( i = 0; i < (*b).fila; i++)
		{
			for ( j = 0; j < (*b).columna; j++)
			{
				fprintf(archivo, "%c",(*b).matriz_dulces[i][j].repre);
			}
			fprintf(archivo, "\n");
		}
	//*statusCode= OK;
	printf("el valor del id es %d\n",*id);
	fclose(archivo);
	

}
int checkBoard(Board *b, code *statusCode){
	int i,j;
	for (i = 0; i < (*b).fila; i++)
	{
		for ( j = 0; j < (*b).columna; j++)
		{
			if (sizeof((*b).matriz_dulces[i][j].repre)!=sizeof(char))
			{
				printf("los componentes sin inbalidos\n");
			//*statusCode = MISSING_SYMBOL;
				return FALSE;

			}

		}
	}

	if ((*b).fila > 25 || (*b).columna >25 || (*b).fila < 6 || (*b).columna < 6)
	{
		printf("limites inbalidos\n");
	//*statusCode = DIMENSIONS_NOT_ALLOWED;
		return FALSE;
	}
 	//*statusCode = OK;
	return TRUE;


}


Board* loadBoard(int id,code *statusCode){
	int i,j;
	Board* tablero =(Board*)malloc(sizeof(Board));
	char nombre_archivo[100], basura[100];
	sprintf(nombre_archivo,"%d.id",id);
	FILE* archivo = fopen(nombre_archivo,"r");
	if (archivo != NULL)
	{
		fscanf(archivo," %[^\n]",basura);
		fscanf(archivo,"%d",&(*tablero).dificultad);
		
		fscanf(archivo,"%d %d", &(*tablero).fila , &(*tablero).columna);

		


	    Candy** matriz=(Candy**)malloc(sizeof(Candy*)*(*tablero).fila);
	    for (i = 0; i < (*tablero).fila; i++)
	    {
	    	matriz[i]=(Candy*)malloc(sizeof(Candy)*(*tablero).columna);
	    }

	    for ( i = 0; i < (*tablero).fila; i++)
	    {
	    	for ( j = 0; j < (*tablero).columna ; j++)
	    	{
	    		fscanf(archivo," %c",&matriz[i][j].repre);
	    		matriz[i][j] = crearBolsa(matriz[i][j]);
	    		
	    	}
	    }

	    (*tablero).matriz_dulces = matriz;
	    fclose(archivo);
	}
	else{
		printf("no existe el archivo\n");
		//*statusCode = ERR_FILE_NOT_FOUND;
		return NULL;
	}

	//*statusCode = OK;
    return tablero;
}


int play(Board *b, Position pOri, Position pDes, int *turnos, code *statusCode){
	
	int i=0,k,j,c,largo_bolsa,indice,puntaje=0;
	
	

	if ((*b).dificultad == 1)
	{
		largo_bolsa=7;
	}
	if ((*b).dificultad == 2)
	{
		largo_bolsa=8;
	}
	if ((*b).dificultad == 3)
	{
		largo_bolsa=9;
	}
	else{
		//*statusCode = MISSING_NUMBER;
	}

	Candy aux,nuevo;
	Candy* bolsa_dulce= bolsa((*b).dificultad);
	Position* arreglo;
	(*turnos)--;
	if (adyacente(pOri,pDes)==TRUE)
	{
		
		aux = (*b).matriz_dulces[pOri.N][pOri.M];
		(*b).matriz_dulces[pOri.N][pOri.M] = (*b).matriz_dulces[pDes.N][pDes.M];
		(*b).matriz_dulces[pDes.N][pDes.M]= aux;
		arreglo = checkCandies(b,statusCode);
		
		if ((*b).matriz_dulces[pDes.N][pDes.M].repre=='E')
		{
			for (c = 0; c <(*b).fila ; c++)
			{
				(*b).matriz_dulces[c][pDes.M].dureza=0;
				puntaje++;
			}
		}
		if ((*b).matriz_dulces[pOri.N][pOri.M].repre=='E')
		{
			for ( c = 0; c < (*b).columna; c++)
			{
				(*b).matriz_dulces[pOri.N][c].dureza=0;
				puntaje++;
			}
		}


		for ( k = 0; k < (*b).fila; k++)
			{
				
				for (j = 0; j < (*b).columna; j++)
				{
					
					if((*b).matriz_dulces[k][j].dureza == 0){
						
						indice = rand() % largo_bolsa;
						nuevo = bolsa_dulce[indice];
						if (indice > (*b).fila ||indice > (*b).columna )
						{
							//*statusCode = DIMENSIONS_NOT_ALLOWED;
						}
						while(nuevo.repre == 'C'){
							indice = rand() % largo_bolsa;
							nuevo = bolsa_dulce[indice];

						}
						(*b).matriz_dulces[k][j] = nuevo;



					}
				}
			}
			arreglo = checkCandies(b,statusCode);

		while(arreglo[i].valor != 0){
			
			

			if ((*b).matriz_dulces[arreglo[i].N+1][arreglo[i].M].repre == 'C')
			{
				((*b).matriz_dulces[arreglo[i].N+1][arreglo[i].M].dureza)--;
				puntaje++;	
			}if (arreglo[i].N != 0)
			{
				if ((*b).matriz_dulces[arreglo[i].N-1][arreglo[i].M].repre == 'C')
				{
				((*b).matriz_dulces[arreglo[i].N-1][arreglo[i].M].dureza)--;
				puntaje++;
				}

			}

			if ((*b).matriz_dulces[arreglo[i].N][arreglo[i].M+1].repre == 'C')
			{
				((*b).matriz_dulces[arreglo[i].N][arreglo[i].M+1].dureza)--;
				puntaje++;
			}
			if (arreglo[i].M !=0)
			{
				if ((*b).matriz_dulces[arreglo[i].N][arreglo[i].M-1].repre == 'C')
				{
				((*b).matriz_dulces[arreglo[i].N][arreglo[i].M-1].dureza)--;
				puntaje++;
				}
			}


			((*b).matriz_dulces[arreglo[i].N][arreglo[i].M].dureza)--;

			i++;


			

			for ( k = 0; k < (*b).fila; k++)
			{
				
				for (j = 0; j < (*b).columna; j++)
				{
					
					if((*b).matriz_dulces[k][j].dureza == 0){
						
						indice = rand() % largo_bolsa;
						nuevo = bolsa_dulce[indice];
						while(nuevo.repre == 'C'){
							indice = rand() % largo_bolsa;
							nuevo = bolsa_dulce[indice];

						}
						(*b).matriz_dulces[k][j] = nuevo;



					}
				}
			}
			

		}

	}
	else{
		printf("Elemento no adyacente.\n");
		//*statusCode = NO_ADYCANDIES;

	}
	//*statusCode = OK;
	return puntaje;
	



}

Position *checkCandies(Board * b, code *statusCode){
	int i,j,contador,contador2,x,k,largo=0;
	
	
	Position* arreglo =(Position*)malloc(sizeof(Position)*(*b).fila*(*b).columna);
	Position pocision;
	
	for ( i = 0; i < (*b).fila*(*b).columna; i++)
	{
		arreglo[i].valor=0;
	}

	for ( i = 0; i < (*b).fila; i++)
	{
		for (j = 0; j < (*b).columna; j++)
		{
			
			
			x=j;
			contador =1;
			
			if(x<=j && x>0){
				
				while( x>0 && (*b).matriz_dulces[i][x].repre==(*b).matriz_dulces[i][x-1].repre )
				{
					if ((*b).matriz_dulces[i][x].repre != 'C')
					{
					
					
					contador++;
					
					
					}
					x--;

				}
			}
				
			if (contador >=3)
			{
				for (k = 0; k < contador; k++)
				{
					pocision.dulce = (*b).matriz_dulces[i][j-k];
					pocision.N=i;
					pocision.M=j-k;
					pocision.valor=1;
					
					if (esta_posicion(arreglo,largo, pocision)== FALSE)
					{
						
						arreglo[largo]=pocision;
					    largo++;	
					}
					
					
				}
			}



			
			x=i;
			contador2 =1;
			if(x<=i && x > 0){
				
				while(x>0 && (*b).matriz_dulces[x][j].repre == (*b).matriz_dulces[x-1][j].repre)
				{
					if ((*b).matriz_dulces[x][j].repre != 'C')
					{
					
						
						
						
						contador2++;
						
						
					}

					x--;
				}
			}
			
			if (contador2 >=3)
			{
				for (k = 0; k < contador2; k++)
				{

					pocision.dulce = (*b).matriz_dulces[i-k][j];
					pocision.N=i-k;
					pocision.M=j;
					pocision.valor=1;

					if (esta_posicion(arreglo,largo, pocision)== FALSE)
					{
						arreglo[largo]=pocision;
						largo++;
					}


				}
			}



			

		}
	}
	
	return arreglo;
}


void imprimir_areglo_igual(Position* arreglo){
	int i =0;
	
	while(arreglo[i].valor != 0){
		
		i++;
	}
	
}

int esta_posicion(Position* arreglo,int largo, Position actual){
	int i=0;
	
	while(i< largo){
		
		if (arreglo[i].N == actual.N && arreglo[i].M==actual.M)
		{
			
			return TRUE;
		}
		i++;

	}
	return FALSE;

}

int adyacente(Position actual, Position destino){
	
	if (actual.N+1 == destino.N && actual.M== destino.M)
	{
		return TRUE;
	}
	if (actual.N-1 == destino.N && actual.M == destino.M)
	{
		return TRUE;
	}
	if (actual.N == destino.N && actual.M+1 == destino.M)
	{
		return TRUE;
	}
	if (actual.N == destino.N && actual.M-1 == destino.M)
	{
		return TRUE;
	}

	return FALSE;

}

Params generarParams(int dificultad,int N,int M){

	Params Parametro;
	Parametro.dif=dificultad;
	if (dificultad == 1)
	{
		Parametro.largo_dulces=7;
	}
	if (dificultad == 2)
	{
		Parametro.largo_dulces=8;
	}
	if (dificultad==3)
	{
		Parametro.largo_dulces=9;
	}
	Parametro.dulces= (Candy*)malloc(sizeof(Candy)*Parametro.largo_dulces);
	Parametro.dulces=bolsa(dificultad);
	Parametro.cantidad_de_dulces =(int*)malloc(sizeof(int)*Parametro.largo_dulces);
	Parametro.cantidad_de_dulces= dispenser(N,M,dificultad,Parametro.largo_dulces);
	return Parametro;
}


