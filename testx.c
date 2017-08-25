#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define INDEX_TEXT ".I"
#define TITLE_TEXT ".T"
#define AUTHOR_TEXT ".A"
#define BIBLIOGRAFY ".B"
#define TEXT ".W"
#define MAX_CHARACTER 30
#define TRUE 1
#define FALSE 0

//estructuras esenciales 

typedef struct {
 int size;
 char** listStopWords;
 
}StopWords;

typedef struct data {
	int index;
	char** title;
	char** author;
	char** bibliografy;
	struct data* nxt;
}doc_data;

typedef struct Nodo {
 int doc;
 int frecuency;
 struct Nodo* nxt;

}document;

typedef struct Term {
 char* word;
 document* documents;
 struct Term* nxt;

}term;

typedef struct {
 int size;
 term* terms;
 int doc_size;
 doc_data* docList;

}invertedIndex;

enum code {OK, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERM};


//cabeceras

int documentCont(char* file);
term* getTerm(char* word, invertedIndex* InvertedIndex);
void insertLastDoc(term* Term, document* Doc);
int searchTerm(char* word, invertedIndex* invertedIndex);
void insertTerm(invertedIndex* InvertedIndex,char* word, document* newDoc);
invertedIndex* createIndex(char* pathDocumentsFile, StopWords *sw/*, code *statusCode*/);
void printInvertedIndex(invertedIndex* invertedIndex);
document* getLastDoc(term* Term);
void wordToLower(char* word);
char* cleanEspecilCharacter(char* word);
char* removeCharacter(char* word,char* character);
int serchEspecialCharacter(char* word);
int searchStopWords(char* word, StopWords* sp);
char* DateHour();
void saveIndex(invertedIndex* i, int* id/*, code *statusCode*/);
int numberLock(char* word,int lock);
void insertWordinList(invertedIndex* inverted, char* word, int numberDoc, StopWords* sw);
void printDocumentData(doc_data* document);
void insertDatainInverted(invertedIndex* InvertedIndex, doc_data* document);
int searchDocData(invertedIndex* InvertedIndex, doc_data* document);


/*

Esta funcion obtiene el numero de palabras de un documento el cual es pasado como parametro en "file".

Este documento es abierto y cerrado en la misma funcion por lo que no hay error si se vuelve a abrir.

SALIDA : un entero correspondiente al contados de 

*/
int wordSize(char* file){

	int cont=0; 

	char* word = (char*)malloc(sizeof(char)*MAX_CHARACTER); // reserva de memoria para almacenar una palabra.
	
	
	FILE* pt = fopen(file,"rb"); // se abre el archivo.

	//comprobacion si existe puntero al archivo.
	if(pt){ 
		
		printf("abierto \n");
	}
	else{ 
		
		printf("No se pudo abrir el archivo \n");
		return 0;
	}
	
	//ciclo para recorrer el archivo.
	while(!feof(pt)){
		fscanf(pt,"%s",word);
		cont++;
	}
	fclose(pt);
	printf("cantidad de stopWords: %d \n",cont);

	free(word);
	return cont;

}

/*

Funcion que crea una lista de palabras (stopWords) y las almacena en la estructura StopWords.

ENTRADAs: el nombre a documento a leer (pathStopWordsFile) y el statusCode el cual se encarga de entregar info del etado del programa.

SALIDA: un puntero a la estructura StopWords donde estan almacenadas las palabras. 

*/

StopWords* loadStopWords(char* pathStopWordsFile /*, code *statusCode*/){


	StopWords* words=(StopWords*)malloc(sizeof(StopWords));
	
	
	words->size=wordSize(pathStopWordsFile);
	words->listStopWords= (char**)malloc(sizeof(char*)*words->size);

	
	
	FILE* pt = fopen(pathStopWordsFile,"rb");
	if(pt){ 
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
		printf("No se pudo abrir el archivo \n");
		return words;
	}

	int i;
	//ciclo para leer las stopWords.
	for(i=0;i<words->size;i++){
		char* word= (char*)malloc(sizeof(char)*MAX_CHARACTER);
		fscanf(pt,"%s", word);
		words->listStopWords[i]=word;
		
	}

	fclose(pt);
	return words;
}
/**

Funcion que se encarga de crear un indice invertido. Este indice no contempla las palabras almacenas en la estructura StopWords.

ENTRADAS: el nombre a documento a leer (pathStopWordsFile), un puntero a la estructura StopWord y el statusCode el cual se encarga de entregar info del etado del programa.

SALIDA:  un puntero al indice invertido.

**/

invertedIndex* createIndex(char* pathDocumentsFile, StopWords *sw/*, code *statusCode*/){

	//se inicial el indice invertido con valores por defecto.
	invertedIndex* inverted = (invertedIndex*)malloc(sizeof(invertedIndex));
	inverted->size=0;
	inverted->terms = NULL;
	inverted->doc_size = documentCont(pathDocumentsFile);

	//reserva de memoria para una lista de documentos.
	inverted->docList = NULL;
	

	int numberDoc;
	int lock = 0;

	FILE* pt = fopen(pathDocumentsFile,"rb");
	if(pt){ 
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
		printf("No se pudo abrir el archivo \n");
		return inverted;
	}
	//reserva de memoria para leer una palabra.
	char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
	fscanf(pt,"%s",word);

	//obtencion del lock correspondiente a la palabra leida.
	lock = numberLock(word,lock);
	
	while(!feof(pt)){

		doc_data* aux = (doc_data*)malloc(sizeof(doc_data));
		aux->title = (char**)malloc(sizeof(char*));
		aux->author = (char**)malloc(sizeof(char*));
		aux->bibliografy = (char**)malloc(sizeof(char*));
		aux->nxt=NULL;

		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);

		if(lock == 1){
			fscanf(pt,"%d\n",&numberDoc);
			fscanf(pt,"%s",word);
			printf("word leido : %s\n",word );
			lock = numberLock(word,lock);
			aux->index = numberDoc;
			//printf("numero de documento en el que se va iterando : %d ---------------------\n",aux->index);
			

		}
		int i=0;
		while(lock == 2){
		
			
			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			i++;
			//printf("fallo 1\n");
			aux->title = (char**)realloc(aux->title,sizeof(char*)*i);
			//printf("fallo 2\n");
			aux->title[i-1]=word;
			while(serchEspecialCharacter(word) == TRUE){
				word = cleanEspecilCharacter(word);
			
			}
			if(strlen(word)>1){
				insertWordinList(inverted, word, numberDoc,sw);

	
			}
		}
		i=0;
		while(lock == 3){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			i++;
			aux->author = (char**)realloc(aux->author,sizeof(char*)*i);
			aux->author[i-1]=word;
			while(serchEspecialCharacter(word) == TRUE){
				word = cleanEspecilCharacter(word);
			
			}
			if(strlen(word)>1){
				insertWordinList(inverted, word, numberDoc,sw);
	
			}
		}
		i=0;
		while(lock == 4){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			i++;
			aux->bibliografy = (char**)realloc(aux->bibliografy,sizeof(char*)*i);
			aux->bibliografy[i-1]=word;
			while(serchEspecialCharacter(word) == TRUE){
				word = cleanEspecilCharacter(word);
			
			}
			if(strlen(word)>1){
				insertWordinList(inverted, word, numberDoc,sw);
	
			}


		}
		//while(lock == 5){

		char* word2=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
		fscanf(pt,"%s",word2);
		//printf("word leido es -------------- : %s  \n",word2);
		lock = numberLock(word2,lock);
		//printf("numero de documento leido en number doc : %d\n",numberDoc );
		while(serchEspecialCharacter(word2) == TRUE){
			word2 = cleanEspecilCharacter(word2);
			
		}
		//printf("word leido es -------------- : %s  \n",word2);
		if(strlen(word2)>1){
			insertWordinList(inverted, word2, numberDoc,sw);
	
		}
		//printf("termine aca :(\n");
		//}
		aux->index = numberDoc;
		
		insertDatainInverted(inverted,aux);
		
			
			
			
			
	}
	
	printDocumentData(inverted->docList);
	//inverted->docList = first;
	//printInvertedIndex(inverted);
	return inverted;
	

}

void insertDatainInverted(invertedIndex* InvertedIndex, doc_data* document){
	
	if(searchDocData(InvertedIndex , document) == FALSE){

		
		if(InvertedIndex->docList == NULL){
			
			InvertedIndex->docList = document;
			
			
		}
		else{
			doc_data* aux = InvertedIndex->docList;
			
			while(aux->nxt != NULL){
				aux = aux->nxt;
			}
			aux->nxt =  document;

		}

	}
	
}

int searchDocData(invertedIndex* InvertedIndex, doc_data* document){

	if(InvertedIndex->docList == NULL){
			
			return FALSE;
			
			
	}
	else{
		doc_data* aux = InvertedIndex->docList;
		while(aux!= NULL){

			if (aux->index == document->index)
			{
				return TRUE;
			}
			aux = aux->nxt;
		}
		return FALSE;
		
	}



}


void insertTerm(invertedIndex* InvertedIndex,char* word, document* newDoc){

	term* newTerm = (term*)malloc(sizeof(term));
	newTerm->word = word;
	newTerm->documents = newDoc;
	newTerm->nxt=NULL;
	
	if(InvertedIndex->size == 0){
		
		InvertedIndex->terms = newTerm;
		InvertedIndex->size = 1;
		
		
	}
	else{
		term* aux = InvertedIndex->terms;
		int i ;
		for (i = 0; i < InvertedIndex->size-1; i++){
			aux = aux->nxt;
		}
		aux->nxt = newTerm;
		InvertedIndex->size++;

	}

	
}

void insertWordinList(invertedIndex* inverted, char* word, int numberDoc, StopWords* sw){
		

		

		wordToLower(word);
		   
		if(searchStopWords(word,sw)==FALSE){
			
			
				
			if(searchTerm(word,inverted)==TRUE){
				//printf("repetido\n");
				term* aux = getTerm(word,inverted);
				document* lastDoc = getLastDoc(aux);
				if(aux != NULL && lastDoc->doc != numberDoc){
					//printf("repetido, en otro documento\n");
						
					document* newDoc = (document*)malloc(sizeof(document));
					newDoc->doc=numberDoc;
					newDoc->frecuency=1;
					newDoc->nxt=NULL;
					
					insertLastDoc(aux,newDoc); 

				}
				else{
					//printf("frecuencia aumentada\n");
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

int searchTerm(char* word, invertedIndex* invertedIndex){

	
	term* aux = invertedIndex->terms;
	
	while(aux != NULL){
		if(strcmp(word, aux->word) == 0){
			return TRUE;
		}
		aux = aux->nxt;

	}
	return FALSE;

}
void insertLastDoc(term* Term, document* Doc){
	document* aux = Term->documents;
	
	while(aux->nxt !=NULL){
		aux = aux->nxt;

	}
	aux->nxt =Doc;

}

term* getTerm(char* word, invertedIndex* InvertedIndex){
	
	term* aux = InvertedIndex->terms;
	
	while(aux != NULL){
		if(strcmp(word, aux->word) == 0){
			return aux;
		}
		aux = aux->nxt;

	}
	return NULL;

}

int documentCont(char* file){

	char buffer[MAX_CHARACTER];
	int cont=0;
	FILE* pt = fopen(file,"r");
	if(pt){ 
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
		printf("No se pudo abrir el archivo \n");
		return 0;
	}
	while(!feof(pt)){
		fscanf(pt,"%s" ,buffer);
		if(strcmp(buffer, INDEX_TEXT) == 0){

			cont++;
			
			//buffer=NULL;
		}
	}
	fclose(pt);
	return cont;

}

void printInvertedIndex(invertedIndex* invertedIndex){

	term* aux= invertedIndex->terms;
	
	while(aux != NULL){

		printf("termino : %s\n",aux->word);
		document* doc = aux->documents;

		while(doc != NULL){

			printf("doc : %d , frecuencia : %d\n",doc->doc,doc->frecuency);
			doc = doc->nxt;


		}
		aux = aux->nxt;
	}

}

document* getLastDoc(term* Term){
	
	document* aux = Term->documents;
	if(aux->nxt == NULL){
		return aux;
	}

	while(aux->nxt != NULL){
		aux = aux->nxt;
		
	}
	return aux;


}

void printDocumentData(doc_data* document){
	int i;	
	while(document != NULL){

		printf("el indice del documento actual es : %d \n",document->index);

		for (i = 0; document->title[i]; i++)
		{
			printf("%s ",document->title[i] );
		}
		printf("\n");
		document = document->nxt;

	}

}

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

void wordToLower(char* word){
	int i;
	//printf("lower: -> %s\n",word);
	for(i=0;word[i];i++){
		word[i]=tolower(word[i]);

	}
	
}


char* removeCharacter(char* word,char* character){
	int valor = strlen(character);
	char* new=(char*)malloc(sizeof(char)*20);
	int posicion = strlen(word) - strlen( strstr(word,character) );
 
	
	for( int a = 0; a < posicion; a++ )
		new[a] = word[a];
 
	
	for( int a = posicion; a < strlen(word); a++ )
		new[ a ] = word[a+valor]; 
 
	new[19] = '\0';
	//printf( "%s\n", new);
	return new;
}

int serchEspecialCharacter(char* word){

	int i ;

	for(i=0;word[i];i++){

		if(word[i]==','){
			word = removeCharacter(word,",");
			return TRUE;


		}
		if(word[i]=='.'){
			word = removeCharacter(word,".");
			return TRUE;

		}
		if(word[i]=='('){
			word = removeCharacter(word,"(");
			return TRUE;
		}
		if(word[i]==')'){
			word = removeCharacter(word,")");
			return TRUE;
		}


	}
	return FALSE;
}

int searchStopWords(char* word, StopWords* sp){
	int i=0;
	
	
	for(i=0;i<sp->size;i++){
		
		if(strcmp(word, sp->listStopWords[i]) == 0){
			//printf("la palabra: %s es un stopWord\n",word);
			return TRUE;
		}
	
	}
	return FALSE;


}

char* DateHour(){
	struct tm *tm;
	time_t fecha;
  	
  	char* dateAndHour = (char*)malloc(sizeof(char)*30);

  	fecha=time(NULL);
  	tm=localtime(&fecha);
  	strftime(dateAndHour, 100, "%d/%m/%Y || %H:%M", tm);
  	return dateAndHour;
	
}


void saveIndex(invertedIndex* i, int* id/*, code *statusCode*/){
	srand(time(0));
	char nombre_archivo[100];
	char* horario = DateHour();
	int j;
	(*id) = 100 + rand() % 1000;
	sprintf(nombre_archivo,"%d.id",*id);
	while(fopen(nombre_archivo,"r")!=NULL)
	{
		(*id) = 100 + rand() % 900;
		sprintf(nombre_archivo,"%d.id",*id);
		//*statusCode = DIMENSIONS_NOT_ALLOWED;

	}
	FILE* archivo = fopen(nombre_archivo,"w");

	fprintf(archivo, "indice guardado el : %s\n",horario );
	//*statusCode= OK;
	term* aux= i->terms;
	
	for(j=0;j<i->size;j++){

		fprintf(archivo,"%s ",aux->word);
		document* doc = aux->documents;

		while(doc != NULL){

			fprintf(archivo,"%d-%d ",doc->doc,doc->frecuency);
			doc = doc->nxt;


		}
		aux = aux->nxt;
		fprintf(archivo,"\n");
	}
	printf("el valor del id es %d\n",*id);
	fclose(archivo);
	

}

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
//invertedIndex* loadIndex(int id/*, code *statusCode*/)

int main(){
	int* id = (int*)malloc(sizeof(int));
	//int i= documentCont("hola.txt");
	StopWords* w = loadStopWords("StopWords.txt");
	//printf("resultado de documentos = %d\n",i);
	invertedIndex* hola = createIndex("hola.txt", w/*, code *statusCode*/);
	//saveIndex(hola, id/*, code *statusCode*/);
	
	
	
			
		
	return 1;
}

	
