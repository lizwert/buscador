#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SEPARADOR "---"
#define MAX_CHARACTER 20
#define TRUE 1
#define FALSE 0



typedef struct {
 int size;
 char** listStopWords;
 
}StopWords;

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

}Index;

enum code {OK, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERM};

//cabeceras

int documentCont(char* file);
term* getTerm(char* word, Index* InvertedIndex);
void insertLastDoc(term* Term, document* Doc);
int searchTerm(char* word, Index* invertedIndex);
void insertTerm(Index* InvertedIndex,char* word, document* newDoc);
Index* createIndex(char* pathDocumentsFile, StopWords *sw/*, code *statusCode*/);
void printInvertedIndex(Index* invertedIndex);
document* getLastDoc(term* Term);
void wordToLower(char* word);
char* cleanEspecilCharacter(char* word);
char* removeCharacter(char* word,char* character);
int serchEspecialCharacter(char* word);
int searchStopWords(char* word, StopWords* sp);

int wordSize(char* file){
	int cont=0;
	char* word = (char*)malloc(sizeof(char)*MAX_CHARACTER);

	FILE* pt = fopen(file,"r");
	if(pt){ 
		
		printf("abierto \n");
	}
	else{ 
		
		printf("No se pudo abrir el archivo \n");
		return 0;
	}
	
	
	while(!feof(pt)){
		cont++;
		fscanf(pt,"%s",word);	
	}
	fclose(pt);
	cont--;
	printf("cantidad de stopWords: %d \n",cont);
	free(word);
	return cont;

}



StopWords* loadStopWords(char* pathStopWordsFile /*, code *statusCode*/){


	StopWords* words=(StopWords*)malloc(sizeof(StopWords));
	
	
	words->size=wordSize(pathStopWordsFile);
	words->listStopWords= (char**)malloc(sizeof(char*)*words->size);

	
	
	FILE* pt = fopen(pathStopWordsFile,"r");
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

	for(i=0;i<words->size;i++){
		char* word= (char*)malloc(sizeof(char)*MAX_CHARACTER);
		fscanf(pt,"%s", word);
		words->listStopWords[i]=word;
		//free(word);
		
		printf("almacenada -----> %s\n",words->listStopWords[i]);
		
	}

	for(i=0;i<(*words).size;i++){
		printf("palabra -> %s\n",words->listStopWords[i]);
		
	}

	fclose(pt);
	return words;
}

Index* createIndex(char* pathDocumentsFile, StopWords *sw/*, code *statusCode*/){

	Index* inverted = (Index*)malloc(sizeof(Index));
	inverted->size=0;
	inverted->terms = NULL;
	//char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
	int numberDoc = 1;
	
	
	FILE* pt = fopen(pathDocumentsFile,"r");
	if(pt){ 
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
		printf("No se pudo abrir el archivo \n");
		return inverted;
	}
	
	while(!feof(pt)){
		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
		fscanf(pt,"%s",word);
		printf("leido : %s , documento N° : %d\n",word,numberDoc);
		while(serchEspecialCharacter(word)== TRUE){
			word = cleanEspecilCharacter(word);
			
		}
		wordToLower(word);
		printf("palabra sin caracteres especiales -> %s\n",word);
		if(searchStopWords(word,sw)==FALSE){
		


		}
		if(strcmp(word, SEPARADOR) == 0){
			
			numberDoc++;
			//free(word);

		}
		else{
			
			if(searchTerm(word,inverted)==TRUE){
				printf("repetido\n");
				term* aux = getTerm(word,inverted);
				document* lastDoc = getLastDoc(aux);
				printf("fallo aca\n");
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
				/*term* aux2 = getTerm(word,inverted);
				document* lastDoc2 = getLastDoc(aux);
				printf("palabra leida : %s, documento actual: %d, frecuencia de palabra: %d\n",aux2->word,lastDoc2->doc,lastDoc2->frecuency);*/
				
				

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
	printInvertedIndex(inverted);
	return inverted;
	

}

void insertTerm(Index* InvertedIndex,char* word, document* newDoc){

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

int searchTerm(char* word, Index* invertedIndex){

	
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

term* getTerm(char* word, Index* InvertedIndex){
	
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
		if(strcmp(buffer, SEPARADOR) == 0){
			printf("buffer leido : %s\n",buffer);
			cont++;
			printf("contador = %d\n",cont);
			//buffer=NULL;
		}
	}
	fclose(pt);
	return cont;

}

void printInvertedIndex(Index* invertedIndex){

	term* aux= invertedIndex->terms;
	
	while(aux->nxt != NULL){

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


	}
	return word;



}

void wordToLower(char* word){
	int i;
	printf("lower: -> %s.\n",word);
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
	int i;
	for(i=0;sp->listStopWords[i];i++){
		if(strcmp(word, sp->listStopWords[i]) == 0){

			return TRUE;
		}
	
	}
	return FALSE;


}

int main(){
	int i= documentCont("ejemplo.txt");
	StopWords* w = loadStopWords("stopwords.in");
	for(i=0;i<(*w).size;i++){
		printf("la palabra almacenada en %d es -> %s \n",i,w->listStopWords[i]);
	}*/
	//printf("resultado de documentos = %d\n",i);
	Index* hola = createIndex("ejemplo.txt", w/*, code *statusCode*/);
	
	
			
		
	return 1;
}

	
