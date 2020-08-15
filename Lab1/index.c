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

Funcion que se encarga de crear un indice invertido. Este indice no contempla las palabras almacenas en la estructura StopWords.

ENTRADAS: el nombre a documento a leer (pathStopWordsFile), un puntero a la estructura StopWord y el statusCode el cual se encarga de entregar info del etado del programa.

SALIDA:  un puntero al indice invertido.

*/

Index* createIndex(char* pathDocumentsFile, StopWords *sw, Code *statusCode){

	//se inicial el indice invertido con valores por defecto.
	Index* inverted = (Index*)malloc(sizeof(Index));
	inverted->size=0;
	inverted->terms = NULL;
	inverted->doc_size = documentCont(pathDocumentsFile,statusCode);

	//reserva de memoria para una lista de documentos.
	inverted->docList = NULL;

	int numberDoc;
	int lock = 0;

	FILE* pt = fopen(pathDocumentsFile,"rb");
	if(pt){ 
		*statusCode = OK;
		printf("abierto \n");
	}
	else{ 
		*statusCode = ERR_FILE_NOT_FOUND; 
		printf("No se pudo abrir el archivo \n");
		return inverted;
	}
	//reserva de memoria para leer una palabra.
	char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
	fscanf(pt,"%s",word);

	//obtencion del lock correspondiente a la palabra leida.
	lock = numberLock(word,lock);
	
	while(!feof(pt)){
		
			
	
		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);

		if(lock == 1){
			fscanf(pt,"%d\n",&numberDoc);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
		
		}

		fscanf(pt,"%s",word);
		
		lock = numberLock(word,lock);

		if (strcmp(TITLE_TEXT, word) != 0 && 
			strcmp(INDEX_TEXT, word) != 0 && 
			strcmp(AUTHOR_TEXT, word) != 0 && 
			strcmp(BIBLIOGRAFY, word) != 0 &&
			strcmp(".w", word) != 0)
		{
			while(serchEspecialCharacter(word) == TRUE){
				word = cleanEspecilCharacter(word);
			
			}
			//se agregan palabras con un size mayor a 1
			if (strlen(word)>1)
			{
				insertWordinList(inverted, word, numberDoc,sw);
			}
			
	
		}

	}
	fclose(pt);
	getDocumentData(inverted,pathDocumentsFile);
	*statusCode = OK;

	
	
	return inverted;
}

/*

Funcion que obtiene la cantidad de documentos existentes en File.

ENTRADAS: un string correspondiente al nombre del archivo (o ubucacion de este).

SALIDA:  La cantidad de documentos en File.

*/
int documentCont(char* file, Code* statusCode){

	char buffer[MAX_CHARACTER];
	int cont=0;
	FILE* pt = fopen(file,"rb");
	if(pt){ 
		*statusCode = OK;
		printf("abierto \n");
	}
	else{ 
		*statusCode = ERR_FILE_NOT_FOUND; 
		printf("No se pudo abrir el archivo \n");
		return 0;
	}
	while(!feof(pt)){
		fscanf(pt,"%s" ,buffer);
		if(strcmp(buffer, INDEX_TEXT) == 0){

			cont++;
			
			
		}
	}
	
	fclose(pt);
	return cont;
}


/*
Funcion que retorna un numero dependiendo de que palabra se ha leido (.I | .T | .A | .B | .W)

ENTRADAS: un string correspondiente a la palabra leida.

SALIDA:  un numero dependiendo del string leido(1|2|3|4|5).
*/
int numberLock(char* word,int lock){

	if(strcmp(word, INDEX_TEXT) == 0){
		lock = 1;
		return lock;	
	}
	if(strcmp(word, TITLE_TEXT) == 0){
		lock = 2;
		return lock;	
				
	}
	if(strcmp(word, AUTHOR_TEXT) == 0){
		lock = 3;			
		return lock;	
	}
	if(strcmp(word, BIBLIOGRAFY) == 0){
		lock = 4;
		return lock;		
	}
	if(strcmp(word, TEXT) == 0){
		lock = 5;
		return lock;	
			
				
	}

	return lock;
}


/*
Funcion booleana que busca caracteres especiales en un string retornando TRUE(1), FALSE(0)

ENTRADAS: un string para ser analizado.

SALIDA: un entero que representan valores booleanos TRUE(1), FALSE(0).
*/
int serchEspecialCharacter(char* word){

	int i ;

	for(i=0;word[i];i++){

		if(word[i]==','){
			
			return TRUE;


		}
		if(word[i]=='.'){
			
			return TRUE;

		}
		if(word[i]=='('){
			
			return TRUE;
		}
		if(word[i]==')'){
			
			return TRUE;
		}
		if(word[i]==')'){
			
			return TRUE;
		}
		if(word[i]==')'){
			
			return TRUE;
		}


	}
	return FALSE;
}


/*
Funcion que limpia un palabra de los caracteres especiales.

ENTRADAS: un string para limpiado.

SALIDA: retorna la palabra ya limpiada.
*/
char* cleanEspecilCharacter(char* word){
	int i ;

	for(i=0;word[i];i++){

		if(word[i]==','){
			word = removeCharacter(word,",");
			return word;
		}
		if(word[i]=='.'){
			word = removeCharacter(word,".");
			return word;

		}
		if(word[i]=='('){
			word = removeCharacter(word,"(");
			return word;
		}
		if(word[i]==')'){
			word = removeCharacter(word,")");
			return word;
		}
		if(word[i]==':'){
			word = removeCharacter(word,":");
			return word;

		}
		if(word[i]=='/'){
			word = removeCharacter(word,"/");
			return word;

		}



	}
	return word;
}

/*
Funcion que limpia un palabra de un caracter especial

ENTRADAS: un string para limpiado y un string el cual sera borrado de la palabra.

SALIDA: retorna la palabra ya limpiada.(solo limpia el primer caracter encontrado)
*/
char* removeCharacter(char* word,char* character){
	int valor = strlen(character);
	char* new=(char*)malloc(sizeof(char)*20);
	int posicion = strlen(word) - strlen( strstr(word,character) );
 
	int a;
	for( a = 0; a < posicion; a++ ){
		new[a] = word[a];
	}
 
	
	for(a = posicion; a < strlen(word); a++ ){
		new[ a ] = word[a+valor]; 
	}
	new[a+1] = '\0';
	
	return new;
}


/*
Funcion inserta una palabra en la estructura index, segun los stopWords.

ENTRADAS: indice pasado por referencia,la palabra a agregar, numero del documento y la estructura de stopWord

SALIDA: no contiene retorno, pero la palabra es insertada en el index entregado por referencia.
*/
void insertWordinList(Index* inverted, char* word, int numberDoc, StopWords* sw){
		
		wordToLower(word);
		
		if(searchStopWords(word,sw)==FALSE){

				
			if(searchTerm(word,inverted)==TRUE){
			
				term* aux = getTerm(word,inverted);
				document* lastDoc = getLastDoc(aux);
				if(aux != NULL && lastDoc->doc != numberDoc){
					
						
					document* newDoc = (document*)malloc(sizeof(document));
					newDoc->doc=numberDoc;
					newDoc->frecuency=1;
					newDoc->nxt=NULL;
					
					insertLastDoc(aux,newDoc); 

				}
				else{
					

					lastDoc->frecuency++;
						

				}

			}
			else{
				
				document* newDoc = (document*)malloc(sizeof(document));
				newDoc->doc = numberDoc;
				newDoc->frecuency =1;
				newDoc->nxt = NULL;
				
				insertTerm(inverted,word,newDoc);

			}
			
			


		}
}


/*
Funcion guarda los datos de un index en un archivo y genera un ID que es pasado por referencia.

ENTRADAS: una estructura index, un entero pasdo por referencia para generarle un valor.

SALIDA: no contiene retorno, pero el index es guardado y el valor de ID es cambiado segun se haya generado. 
*/
void saveIndex(Index* i, int* id, Code *statusCode){
	srand(time(0));
	char nombre_archivo[100];
	char* horario = DateHour();
	int j,k;
	(*id) = 100 + rand() % 1000;
	sprintf(nombre_archivo,"%d.id",*id);
	while(fopen(nombre_archivo,"r")!=NULL)
	{
		(*id) = 100 + rand() % 900;
		sprintf(nombre_archivo,"%d.id",*id);
		

	}
	FILE* archivo = fopen(nombre_archivo,"w");

	fprintf(archivo, "indice guardado el : %s\n",horario );
	*statusCode= OK;
	term* aux= i->terms;
	fprintf(archivo, "%d\n",i->size );
	
	while(aux != NULL){

		fprintf(archivo,"%s ",aux->word);
		document* doc = aux->documents;

		while(doc != NULL){

			fprintf(archivo,"%d-%d ",doc->doc,doc->frecuency);
			doc = doc->nxt;


		}
		aux = aux->nxt;
		fprintf(archivo,"%d-%d\n",0,0);
	}
	fprintf(archivo,"-----\n");
	doc_data* aux2 = i->docList;
	while(aux2 != NULL){
		
		fprintf(archivo,".I ");
		fprintf(archivo,"%d\n",aux2->index);
		k=0;
		fprintf(archivo,".T ");
		while(strcmp("-----", aux2->title[k]) != 0){

			fprintf(archivo,"%s ",aux2->title[k]);
			k++;

		}
		fprintf(archivo,"\n");
		fprintf(archivo,".A ");
		k=0;
		while(strcmp("-----", aux2->author[k]) != 0){

			fprintf(archivo,"%s ",aux2->author[k]);
			k++;

		}
		fprintf(archivo,"\n");
		fprintf(archivo,".B ");
		k=0;
		while(strcmp("-----", aux2->bibliografy[k]) != 0){

			fprintf(archivo,"%s ",aux2->bibliografy[k]);
			k++;

		}
		fprintf(archivo,"\n");
		aux2 = aux2->nxt;


	}
	printf("el valor del id es %d\n",*id);
	fclose(archivo);
	*statusCode = OK;
}


/*
Funcion carga todos los datos necesarios para crear un Index desde una archivo que es guardado bajo un ID.

ENTRADAS: un entero ID que representa el valor con el que se guardo el index.

SALIDA: una estructura index con los datos cargados.
*/

Index* loadIndex(int id, Code *statusCode){

	Index* inverted = (Index*)malloc(sizeof(Index));
	inverted->size=0;
	inverted->terms = NULL;
	inverted->doc_size =0;

	//reserva de memoria para una lista de documentos.
	inverted->docList = NULL;
	
	int* d = (int*)malloc(sizeof(int));
	char Read[100];
	char buffer[100];
	sprintf(Read,"%d.id",id);
	FILE* pt = fopen(Read,"rb");
	if(pt){ 
		*statusCode = OK;
		printf("abierto \n");
	}
	else{ 
		*statusCode = ERR_FILE_NOT_FOUND; 
		printf("No se pudo abrir el archivo \n");
		return 0;
	}
	char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
	fscanf(pt,"%[^\n] ",buffer);
	fscanf(pt,"%d\n",&inverted->size);

	while(strcmp("-----", word) != 0){
		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
		int i,j;
		fscanf(pt,"%s",word);

		if (strcmp("-----", word) == 0)
		{
			break;
		}
		
		do{

			
			fscanf(pt,"%d-%d ",&i,&j);
			
			
			if (i !=0 && j != 0)
			{

				
				insertDataIndex(inverted,word,i,j);


				

			}
			
				
			
		}
		while(i != 0 && j !=0);
	}
	
	fclose(pt);
	getDocumentDataLoaded(inverted,Read);


	
	return inverted;
}

