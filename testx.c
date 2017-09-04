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

typedef struct Index{
 int size;
 term* terms;
 int doc_size;
 doc_data* docList;

}Index;

typedef struct rst{
 char* word;
 int frec;
 document* docList;
 struct rst* nxt;

}result;

typedef struct rk
{
	char** query;
	int size;
	result* resultList;
};



enum code {OK, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERM};


//cabeceras

int documentCont(char* file);
term* getTerm(char* word, Index* Index);
void insertLastDoc(term* Term, document* Doc);
int searchTerm(char* word, Index* Index);
void insertTerm(Index* Index,char* word, document* newDoc);
Index* createIndex(char* pathDocumentsFile, StopWords *sw/*, code *statusCode*/);
void printIndex(Index* Index);
document* getLastDoc(term* Term);
void wordToLower(char* word);
char* cleanEspecilCharacter(char* word);
char* removeCharacter(char* word,char* character);
int serchEspecialCharacter(char* word);
int searchStopWords(char* word, StopWords* sp);
char* DateHour();
void saveIndex(Index* i, int* id/*, code *statusCode*/);
int numberLock(char* word,int lock);
void insertWordinList(Index* inverted, char* word, int numberDoc, StopWords* sw);
void printDocumentData(doc_data* document);
void insertDatainInverted(Index* Index, doc_data* document);
int searchDocData(Index* Index, doc_data* document);
void addInListSW(StopWords* sw, char* word);
void insertWordsinDataDoc(words* docData,char* word);
void getDocumentData(Index* inverted,char* pathDocumentsFile);
Index* loadIndex(int id/*, code *statusCode*/);
void insertDataIndex(Index* index,char* word, int doc, int frecuency);
void insertRkgData(result* rk, document* doc, int frec,char* word);

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

Index* createIndex(char* pathDocumentsFile, StopWords *sw/*, code *statusCode*/){

	//se inicial el indice invertido con valores por defecto.
	Index* inverted = (Index*)malloc(sizeof(Index));
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
		
			
	
		char* word=(char*)malloc(sizeof(char*)*MAX_CHARACTER);

		if(lock == 1){
			fscanf(pt,"%d\n",&numberDoc);
			fscanf(pt,"%s",word);
			lock = numberLock(word,lock);
			//aux->index = numberDoc;
			
			
		
			

		}

		

		char* word2=(char*)malloc(sizeof(char*)*MAX_CHARACTER);
		fscanf(pt,"%s",word2);
		
		lock = numberLock(word2,lock);
		
		
		
		if (strcmp(TITLE_TEXT, word2) != 0 && 
			strcmp(INDEX_TEXT, word2) != 0 && 
			strcmp(AUTHOR_TEXT, word2) != 0 && 
			strcmp(BIBLIOGRAFY, word2) != 0 &&
			strcmp(".w", word2) != 0)
		{
			while(serchEspecialCharacter(word2) == TRUE){
				word2 = cleanEspecilCharacter(word2);
			
			}
			if (strlen(word2)>1)
			{
				insertWordinList(inverted, word2, numberDoc,sw);
			}
			
	
		}
		
		
		
		
		
			
			
			
			
	}
	fclose(pt);
	getDocumentData(inverted,pathDocumentsFile);
	
	//printDocumentData(inverted->docList);
	//inverted->docList = first;
	//printIndex(inverted);
	return inverted;
	

}

void insertWordsinDataDoc(words* docData,char* word){

	words* new = (words*)malloc(sizeof(words));
	new->word = word;
	new->nxt = NULL;

	
	if(docData == NULL){
			docData = new;
			
			
	}
	else{

			words* aux = docData;
			while(aux != NULL){
				aux=aux->nxt;
			}
			
			aux = new;
			

	}
		
			
	
	


}

void insertDatainInverted(Index* Index, doc_data* document){
	
	if(searchDocData(Index , document) == FALSE){

		
		if(Index->docList == NULL){
			
			Index->docList = document;
			
			
		}
		else{
			doc_data* aux = Index->docList;
			
			while(aux->nxt != NULL){
				aux = aux->nxt;
			}
			aux->nxt =  document;

		}

	}
	
}
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
		aux->title = (char**)malloc(sizeof(char*)*400);
		aux->author = (char**)malloc(sizeof(char*)*400);
		aux->bibliografy = (char**)malloc(sizeof(char*)*400);		
		aux->nxt=NULL;

		for (i = 0; i < 400; i++)
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
		fscanf(pt,"%s",word);
		
		lock = numberLock(word,lock);
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
			//insertWordsinDataDoc(aux->title,word);
			

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
			insertDatainInverted(inverted,aux);
			
		}

	
		
	}
	fclose(pt);
	printDocumentData(inverted->docList);
}

int searchDocData(Index* Index, doc_data* document){

	if(Index->docList == NULL){
			
			return FALSE;
			
			
	}
	else{
		doc_data* aux = Index->docList;
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


void insertTerm(Index* Index,char* word, document* newDoc){

	term* newTerm = (term*)malloc(sizeof(term));
	newTerm->word = word;
	newTerm->documents = newDoc;
	newTerm->nxt=NULL;
	
	if(Index->size == 0){
		
		Index->terms = newTerm;
		Index->size = 1;
		
		
	}
	else{
		
		term* aux = Index->terms;
		int i ;
		for (i = 0; i < Index->size-1; i++){
			aux = aux->nxt;
		}
		aux->nxt = newTerm;
		Index->size++;

	}

	
}

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

int searchTerm(char* word, Index* Index){

	
	term* aux = Index->terms;
	
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
	
	fclose(pt);
	return cont;

}

void printIndex(Index* Index){

	term* aux= Index->terms;
	
	while(aux != NULL){

		
		document* doc = aux->documents;

		while(doc != NULL){

			
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
	
	for(i=0;word[i];i++){
		word[i]=tolower(word[i]);

	}
	
}


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


void saveIndex(Index* i, int* id/*, code *statusCode*/){
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
	fprintf(archivo, "%d\n",i->size );
	
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
	

}
result* query(Index *i, StopWords *sw, char* text/*, code *statusCode*/){
	char new[strlen(text)];
	strcpy(new,text);
	char* buffer = NULL;
    buffer = strtok(new," ");

    result* rk = NULL;
    int frecuency;
    

    while( buffer != NULL ) {
        printf( "buffer : %s \n", buffer);
       
        term* aux = getTerm(buffer,i);
        if (aux != NULL)
        {
        	document* doc = aux->documents;
        	frecuency=0;
        	while(doc != NULL){
        		frecuency = frecuency + doc->frecuency;
        		doc = doc->nxt;
        	}
        	insertRkgData(rk,aux->documents,frecuency,buffer);
        	printf("se ha insertado %s, fre : %d\n",buffer,frecuency );

        	
        }
         buffer = strtok( NULL, " ");
    }
    return rk;

}

void insertRkgData(result* rk, document* doc, int frec,char* word){

	result* new = (result*)malloc(sizeof(result));
	new->word = word;
	new->frec=frec;
	new->docList=doc;
	new->nxt = NULL;

	if (rk == NULL)
	{
		rk=new;
	}
	else{
		result* aux = rk;
		while(aux != NULL){
			aux=aux->nxt;
		}
		aux = new;
	}

}

Index* loadIndex(int id/*, code *statusCode*/){

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
		/*statusCode = OK;*/
		printf("abierto \n");
	}
	else{ 
		/*statusCode = ERR_FILE_NOT_FOUND; */
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
		while(i != 0 && j !=0);
	}
	
	fclose(pt);
	getDocumentData(inverted,Read);
	saveIndex(inverted, d/*, code *statusCode*/);
	return inverted;
	


}

void insertDataIndex(Index* index,char* word, int doc, int frecuency){
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
//Index* loadIndex(int id/*, code *statusCode*/)

int main(){
	int* id = (int*)malloc(sizeof(int));
	int i= documentCont("TestCollection.txt");
	StopWords* w = loadStopWords("StopWords.txt");
	printf("resultado de documentos = %d\n",i);
	Index* hola = createIndex("TestCollection.txt", w/*, code *statusCode*/);
	saveIndex(hola, id/*, code *statusCode*/);
	//Index* new =loadIndex(370/*, code *statusCode*/);
	query(hola,w,"experimental investigation");
	
	
	//TestCollection.txt
			
		
	return 1;
}

	
