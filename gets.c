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

void getDocumentData(Index* inverted,char* pathDocumentsFile){

	int numberDoc,i;
	int lock = 0;


	FILE* pt = fopen(pathDocumentsFile,"rb");
	if(pt){ 
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
		printf("No se pudo abrir el archivo \n");
		
	}
	//reserva de memoria para leer una palabra.


	//obtencion del lock correspondiente a la palabra leida.

	
	while(!feof(pt)){
		doc_data* aux = (doc_data*)malloc(sizeof(doc_data));
		aux->index = 0;
		aux->title = (char**)malloc(sizeof(char*)*MAX_CHARACTER*10);
		aux->author = (char**)malloc(sizeof(char*)*MAX_CHARACTER*10);
		aux->bibliografy = (char**)malloc(sizeof(char*)*MAX_CHARACTER*10);		
		aux->nxt=NULL;

		for (i = 0; i < MAX_CHARACTER*10; i++)
		{
			aux->title[i] = "-----";
			aux->author[i] = "-----";
			aux->bibliografy[i]= "-----";
		}


		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);

		fscanf(pt,"%s",word);
		

		
		lock = numberLock(word,lock);
		

		if(lock == 1){
			
			fscanf(pt,"%d\n",&numberDoc);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);


			aux->index = numberDoc;

		}

		
		
		i=0;
		while(lock == 2){
			
			
			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);

			lock = numberLock(word,lock);
			if (strcmp(TITLE_TEXT, word) != 0 && 
				strcmp(INDEX_TEXT, word) != 0 && 
				strcmp(AUTHOR_TEXT, word) != 0 && 
				strcmp(BIBLIOGRAFY, word) != 0 &&
				strcmp(".W", word) != 0)
			{
				aux->title[i]=word;

				
				i++;
			}
			
			if(feof(pt)){
				break;
			}
			
			

		}
		i=0;
		while(lock == 3){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			
			if (strcmp(TITLE_TEXT, word) != 0 && 
				strcmp(INDEX_TEXT, word) != 0 && 
				strcmp(AUTHOR_TEXT, word) != 0 && 
				strcmp(BIBLIOGRAFY, word) != 0 &&
				strcmp(".W", word) != 0)
			{
				aux->author[i]=word;
			
				i++;
			}
			if(feof(pt)){
				break;
			}
			//insertWordsinDataDoc(aux->author,word);
			
		}
		i=0;
		while(lock == 4){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			if (strcmp(TITLE_TEXT, word) != 0 && 
				strcmp(INDEX_TEXT, word) != 0 && 
				strcmp(AUTHOR_TEXT, word) != 0 && 
				strcmp(BIBLIOGRAFY, word) != 0 &&
				strcmp(".W", word) != 0)
			{
				aux->bibliografy[i]=word;
				
				i++;
			}
			if(feof(pt)){
				break;
			}
			//insertWordsinDataDoc(aux->bibliografy,word);



		}
		if (aux->index != 0)
		{
			aux->index = numberDoc;
			printf("intetrando : %d \n",aux->index );
			insertDatainInverted(inverted,aux);
			
		}


		
		
	}
	fclose(pt);	
}

void getDocumentDataLoaded(Index* inverted,char* pathDocumentsFile){

	int numberDoc,i;
	int lock = 1;


	FILE* pt = fopen(pathDocumentsFile,"rb");
	if(pt){ 
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
		printf("No se pudo abrir el archivo \n");
		
	}
	//reserva de memoria para leer una palabra.


	//obtencion del lock correspondiente a la palabra leida.

	while(!feof(pt)){
		char buffer[100];
		fscanf(pt,"%s",buffer);
		if (strcmp(buffer,"-----")==0)
		{
			break;
		}
	}
	
	while(!feof(pt)){
		doc_data* aux = (doc_data*)malloc(sizeof(doc_data));
		aux->index = 0;
		aux->title = (char**)malloc(sizeof(char*)*MAX_CHARACTER*10);
		aux->author = (char**)malloc(sizeof(char*)*MAX_CHARACTER*10);
		aux->bibliografy = (char**)malloc(sizeof(char*)*MAX_CHARACTER*10);		
		aux->nxt=NULL;

		for (i = 0; i < MAX_CHARACTER*10; i++)
		{
			aux->title[i] = "-----";
			aux->author[i] = "-----";
			aux->bibliografy[i]= "-----";
		}


		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);

		if(lock == 1){
			
			fscanf(pt,"%d\n",&numberDoc);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);


			aux->index = numberDoc;

		}


		
		
		i=0;
		while(lock == 2){
			
			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);

			lock = numberLock(word,lock);

			if (strcmp(TITLE_TEXT, word) != 0 && 
				strcmp(INDEX_TEXT, word) != 0 && 
				strcmp(AUTHOR_TEXT, word) != 0 && 
				strcmp(BIBLIOGRAFY, word) != 0 &&
				strcmp(".W", word) != 0)
			{
				aux->title[i]=word;

				
				i++;
			}
			
			if(feof(pt)){
				break;
			}

			
			

		}
		i=0;
		while(lock == 3){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			
			if (strcmp(TITLE_TEXT, word) != 0 && 
				strcmp(INDEX_TEXT, word) != 0 && 
				strcmp(AUTHOR_TEXT, word) != 0 && 
				strcmp(BIBLIOGRAFY, word) != 0 &&
				strcmp(".W", word) != 0)
			{
				aux->author[i]=word;
			
				i++;
			}
			if(feof(pt)){
				break;
			}
			//insertWordsinDataDoc(aux->author,word);
			
		}
		i=0;
		while(lock == 4){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			if (strcmp(TITLE_TEXT, word) != 0 && 
				strcmp(INDEX_TEXT, word) != 0 && 
				strcmp(AUTHOR_TEXT, word) != 0 && 
				strcmp(BIBLIOGRAFY, word) != 0 &&
				strcmp(".W", word) != 0)
			{
				aux->bibliografy[i]=word;
				
				i++;
			}
			if(feof(pt)){
				break;
			}
			//insertWordsinDataDoc(aux->bibliografy,word);



		}
		if (aux->index != 0)
		{
			aux->index = numberDoc;

			insertDatainInverted(inverted,aux);
			
		}



	
		
	}
	fclose(pt);
	printDocumentData(inverted->docList);

}
term* getTerm(char* word, Index* Index){
	
	term* aux = Index->terms;
	
	while(aux != NULL){
		if(strcmp(word, aux->word) == 0){
			return aux;
		}
		aux = aux->nxt;

	}
	return NULL;
}
document* getLastDoc(term* Term){
	
	document* aux = Term->documents;
	if(aux == NULL){
		return aux;
	}

	while(aux->nxt != NULL){
		aux = aux->nxt;
		
	}
	return aux;
}
doc_data* getCurrentData(Ranking* current,int id_doc){

	doc_data* aux = current-> dataDoc;
	while(aux != NULL){
		if (aux->index == id_doc)
		{
			return aux;
		}
		aux=aux->nxt;
	}
	return NULL;
}
int getDocumentAmount(document* current){
	int amount=0;

	document* aux = current;
	while(aux != NULL){
		amount++;
		aux=aux->nxt;
	}
	return amount;
}
document* getdocument(document* current,int ID){

	document* aux =current;
	while(aux != NULL){
		if (aux->doc==ID)
		{
			return aux;
		}
		aux=aux->nxt;
	}
	return NULL;
}
