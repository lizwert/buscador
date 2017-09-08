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
/*

Funcion que crea una lista de palabras (stopWords) y las almacena en la estructura StopWords.

ENTRADAs: el nombre a documento a leer (pathStopWordsFile) y el statusCode el cual se encarga de entregar info del etado del programa.

SALIDA: un puntero a la estructura StopWords donde estan almacenadas las palabras. 

*/

StopWords* loadStopWords(char* pathStopWordsFile /*, code *statusCode*/){


	StopWords* listSW=(StopWords*)malloc(sizeof(StopWords));
	
	
	listSW->size=0;
	listSW->listStopWords= NULL;

	
	
	FILE* pt = fopen(pathStopWordsFile,"rb");
	if(pt){ 
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
		printf("No se pudo abrir el archivo \n");
		return NULL;
	}

	
	//ciclo para leer las stopWords.
	while(!feof(pt)){
		char* word= (char*)malloc(sizeof(char)*MAX_CHARACTER);
		fscanf(pt,"%s", word);
		
		addInListSW(listSW,word);
		
	}

	printf("************************************\n");
	printf("*        StopWords Cargados        *\n");
	printf("************************************\n");
	printf("*            ID: %i               *\n",listSW->size);
	printf("************************************\n");
	

	fclose(pt);
	return listSW;
}
/*

Funcion que agrega o inserta una palabra a una estructura StopWord pasada por referencia.

ENTRADAS: una estructura StopWord y una palabra para ser agregada. 

SALIDA: no posee return pero la estructura StopWord es modificada por referencia.

*/

void addInListSW(StopWords* sw, char* word){

	
	words* new = (words*)malloc(sizeof(words));
	new->word =word;
	new->nxt =NULL;

	words* aux =sw->listStopWords;

	if(aux == NULL){

		sw->listStopWords = new;
		sw->size++;
	}
	else{
		

		while(aux->nxt !=NULL){
			aux = aux->nxt;

		}
		sw->size++;
		aux->nxt = new;

	}
}


/*
Funcion booleana que busca una palabra en la estructura de StopWord.

ENTRADAS: una estructura StopWord y una palabra para ser buscada.

SALIDA: un entero que representan valores booleanos TRUE(1), FALSE(0).

*/
int searchStopWords(char* word, StopWords* sw){
	if (sw != NULL)
	{
		words* aux = sw->listStopWords;
	
		while(aux !=NULL){
		
			if(strcmp(word, aux->word) == 0){
			
				return TRUE;
		}
			aux=aux->nxt;
	
		}
	}

	return FALSE;
}
