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

typedef struct nodo {
 char* word;
 struct nodo* nxt;
 
}words;

typedef struct {
 int size;
 words* listStopWords;
 
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
void addInListSW(StopWords* sw, char* word);
void insertWordsinDataDoc(words* docData,char* word);
void getDocumentData(invertedIndex* inverted,char* pathDocumentsFile);
invertedIndex* loadIndex(int id/*, code *statusCode*/);
void insertDataIndex(invertedIndex* index,char* word, int doc, int frecuency);

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
		return listSW;
	}

	
	//ciclo para leer las stopWords.
	while(!feof(pt)){
		char* word= (char*)malloc(sizeof(char)*MAX_CHARACTER);
		fscanf(pt,"%s", word);
		printf("%s \n", word);
		addInListSW(listSW,word);
		
	}
	printf("cantidad de stopWords: %d \n",listSW->size);

	fclose(pt);
	return listSW;
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
		//printf("nuevo data doc creado\n");
		/*doc_data* aux = (doc_data*)malloc(sizeof(doc_data));
			aux->title = NULL;
			aux->author = NULL;
			aux->bibliografy = NULL;
			aux->nxt=NULL;
			
	*/
		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);

		if(lock == 1){
			fscanf(pt,"%d\n",&numberDoc);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			//aux->index = numberDoc;
			
			
			//printf("numero de documento en el que se va iterando : %d ---------------------\n",aux->index);
			

		}

		/*while(lock == 2){
		
			
			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			//printf("word leido : %s\n",word );
			lock = numberLock(word,lock);
		
			insertWordsinDataDoc(aux->title,word);
			
			
	
			
			while(serchEspecialCharacter(word) == TRUE){
				
				word = cleanEspecilCharacter(word);
			
			}
			if(strlen(word)>1){
				
				insertWordinList(inverted, word, numberDoc,sw);
				

	
			}

		}

		
		while(lock == 3){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			
			insertWordsinDataDoc(aux->author,word);
			
			while(serchEspecialCharacter(word) == TRUE){
				word = cleanEspecilCharacter(word);
			
			}
			if(strlen(word)>1){
				insertWordinList(inverted, word, numberDoc,sw);
	
			}
		}
		
		while(lock == 4){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			insertWordsinDataDoc(aux->bibliografy,word);
			while(serchEspecialCharacter(word) == TRUE){
				word = cleanEspecilCharacter(word);
			
			}
			if(strlen(word)>1){
				insertWordinList(inverted, word, numberDoc,sw);
	
			}


		}
		if (aux->title != NULL || aux->author != NULL || aux->bibliografy != NULL)
		{
			insertDatainInverted(inverted,aux);
		}
		*/
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
		
		
		
		
			
			
			
			
	}
	fclose(pt);
	getDocumentData(inverted,pathDocumentsFile);
	
	//printDocumentData(inverted->docList);
	//inverted->docList = first;
	//printInvertedIndex(inverted);
	return inverted;
	

}

void insertWordsinDataDoc(words* docData,char* word){

	words* new = (words*)malloc(sizeof(words));
	new->word = word;
	new->nxt = NULL;

	
	if(docData == NULL){
			docData = new;
			
			printf("palabra agregada por primera vez : %s\n",docData->word);
	}
	else{

			words* aux = docData;
			while(aux != NULL){
				aux=aux->nxt;
			}
			
			aux = new;
			printf("palabra agregada por mas veces : %s\n",aux->word);

	}
		
			
	
	


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
void getDocumentData(invertedIndex* inverted,char* pathDocumentsFile){

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
		aux->title = (char**)malloc(sizeof(char*)*400);
		aux->author = (char**)malloc(sizeof(char*)*400);
		aux->bibliografy = (char**)malloc(sizeof(char*)*400);		
		aux->nxt=NULL;

		for (i = 0; i < 100; i++)
		{
			aux->title[i] = "-----";
			aux->author[i] = "-----";
			aux->bibliografy[i]= "-----";
		}


		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
		

		if(lock == 1){
			printf("se ha entrado al lock 1\n");
			fscanf(pt,"%d\n",&numberDoc);
			printf("-------------------------numero de numberdoc------------------------- %d\n",numberDoc );
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);


			aux->index = numberDoc;
		}
		fscanf(pt,"%s",word);
		printf("**************************palabra fuera del los hile leida : %s\n",word );
		lock = numberLock(word,lock);
		i=0;
		while(lock == 2){
		
			
			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			aux->title[i]=word;
			printf("la titulo: %s se ha agregado en el indice %d \n",aux->title[i],i );
			i++;
			if(feof(pt)){
				break;
			}
			//insertWordsinDataDoc(aux->title,word);
			

		}
		i=0;
		while(lock == 3){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			printf("palabra ultima leida : %s\n",word );
			aux->author[i]=word;
			//printf("la author : %s se ha agregado en el indice %d \n",aux->author[i],i );
			i++;
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
			aux->bibliografy[i]=word;
			printf("la biblio : %s se ha agregado en el indice %d \n",aux->bibliografy[i],i );
			i++;
			if(feof(pt)){
				break;
			}
			//insertWordsinDataDoc(aux->bibliografy,word);



		}
		if (aux->index != 0)
		{
			insertDatainInverted(inverted,aux);
			printf("se ha agregado el dada doc del documento %d al indice \n", aux->index);
		}

	
		/*char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);

		if(lock == 1){
			fscanf(pt,"%d\n",&numberDoc);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);

			aux->index = numberDoc;
			
			
			//printf("numero de documento en el que se va iterando : %d ---------------------\n",aux->index);
			

		}

		while(lock == 2){
		
			
			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			printf("word leido : %s\n",word );
			lock = numberLock(word,lock);
		
			insertWordsinDataDoc(aux->title,word);
			

		}

		
		while(lock == 3){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			
			insertWordsinDataDoc(aux->author,word);
			
		}
		
		while(lock == 4){

			char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			insertWordsinDataDoc(aux->bibliografy,word);



		}
		insertDatainInverted(inverted,aux); */
	}
	fclose(pt);
	printDocumentData(inverted->docList);
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
		printf("el size es 0\n");
		InvertedIndex->terms = newTerm;
		InvertedIndex->size = 1;
		
		
	}
	else{
		printf("el size es distinto de 0\n");
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
		printf("comparacion entre ---%s--- y ---%s---\n",word, aux->word );
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
	FILE* pt = fopen(file,"rb");
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
	printf("cerrado y funcionando \n");
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
	if(aux == NULL){
		return aux;
	}

	while(aux->nxt != NULL){
		aux = aux->nxt;
		
	}
	return aux;


}

void printDocumentData(doc_data* document){

	doc_data* docAux = document;
	int i;

	if (docAux == NULL)
	{
		printf("el documento siguiente es nulo\n");
	}
	while(docAux != NULL){

		printf("el indice del documento actual es : %d \n",docAux->index);
		char** aux = docAux->title;
		i=0;
		while(strcmp("-----", aux[i]) != 0)
		{
			printf("%s\n",aux[i]);
			i++;
		}
		docAux = docAux->nxt;

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

int searchStopWords(char* word, StopWords* sw){
	
	words* aux = sw->listStopWords;
	
	while(aux !=NULL){
		
		if(strcmp(word, aux->word) == 0){
			
			return TRUE;
		}
		aux=aux->nxt;
	
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
	int j,k;
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
		fprintf(archivo,"||\n");
		fprintf(archivo,".A ");
		k=0;
		while(strcmp("-----", aux2->author[k]) != 0){

			fprintf(archivo,"%s ",aux2->author[k]);
			k++;

		}
		fprintf(archivo,"||\n");
		fprintf(archivo,".B ");
		k=0;
		while(strcmp("-----", aux2->bibliografy[k]) != 0){

			fprintf(archivo,"%s ",aux2->bibliografy[k]);
			k++;

		}
		fprintf(archivo,"||\n");
		aux2 = aux2->nxt;


	}
	printf("el valor del id es %d\n",*id);
	fclose(archivo);
	

}

invertedIndex* loadIndex(int id/*, code *statusCode*/){

	invertedIndex* inverted = (invertedIndex*)malloc(sizeof(invertedIndex));
	inverted->size=0;
	inverted->terms = NULL;
	inverted->doc_size =0;

	//reserva de memoria para una lista de documentos.
	inverted->docList = NULL;
	
	int* d = (int*)malloc(sizeof(int));
	char Read[100];
	sprintf(Read,"%d.id",id);
	FILE* pt = fopen(Read,"rb");
	if(pt){ 
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
		printf("No se pudo abrir el archivo \n");
		return 0;
	}
	char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
	fscanf(pt,"%[^\n] ",Read);

	while(strcmp("-----", word) != 0){
		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
		int i,j;
		fscanf(pt,"%s",word);
		if (strcmp("-----", word) == 0)
		{
			break;
		}
		
		do{
			
			
				
				printf("woord leido :%s\n",word );
				fscanf(pt,"%d-%d ",&i,&j);
				printf("quede aca I = %d, J= %d\n",i,j);
				
				if (i !=0 && j != 0)
				{
					insertDataIndex(inverted,word,i,j);
					//printf("agregada a : %d-%d \n",i,j);
					
				}
				//printf("quede aca I = %d, J= %d\n",i,j);
				
			
		}
		while(i != 0 || j !=0);
		
		

	}
	
	fclose(pt);
	saveIndex(inverted, d/*, code *statusCode*/);
	return inverted;
	


}

void insertDataIndex(invertedIndex* index,char* word, int doc, int frecuency){
	printf("palagra consultada : %s\n",word);
	if(searchTerm(word,index)==TRUE){
		printf("---esta presente en el index---\n");
		term* aux = getTerm(word,index);
		//printf("repetido, en otro documento\n");
						
		document* newDoc = (document*)malloc(sizeof(document));
		newDoc->doc=doc;
		newDoc->frecuency=frecuency;
		newDoc->nxt=NULL;
					
		insertLastDoc(aux,newDoc); 

	}
	else{
		printf("---no esta presente en el index---\n");	
		document* newDoc = (document*)malloc(sizeof(document));
		newDoc->doc = doc;
		newDoc->frecuency =frecuency;
		newDoc->nxt = NULL;
				
		insertTerm(index,word,newDoc);
		printf("se ha insertado\n");

	}
	


}

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
	//int* id = (int*)malloc(sizeof(int));
	//int i= documentCont("hola.txt");
	//StopWords* w = loadStopWords("StopWords.txt");
	//printf("resultado de documentos = %d\n",i);
	//invertedIndex* hola = createIndex("hola.txt", w/*, code *statusCode*/);
	//saveIndex(hola, id/*, code *statusCode*/);
	invertedIndex* new =loadIndex(370/*, code *statusCode*/);
	
	
	
			
		
	return 1;
}

	
