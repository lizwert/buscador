
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






//Funcion booleana que busca los datos de un documentos en Index. retorna True o False
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
//Funcion booleana que busca una palabra en Index. retorna True o False
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
//Funcion que imprime los datos de un documento (ID, titulo, autor,etc)
void printDocumentData(doc_data* document){

	doc_data* docAux = document;
	int i;
	printf("***************************Inicio**************************\n\n\n");
	printf("ID del documento: %d\n\n",document->index);

		printf("Titulo :\n");
		char** aux = docAux->title;
		i=0;
		while(strcmp("-----", aux[i]) != 0)
		{
			printf("%s ",aux[i]);
			i++;
		}
		printf("\n\n");
		
		printf("Autor :\n");
		char** aux2 = docAux->author;
		i=0;
		while(strcmp("-----", aux2[i]) != 0)
		{
			printf("%s ",aux2[i]);
			i++;
		}
		printf("\n\n");
		
		printf("Bibliografia : \n");
		char** aux3 = docAux->bibliografy;
		i=0;
		while(strcmp("-----", aux3[i]) != 0)
		{
			printf("%s ",aux3[i]);
			i++;
		}
		printf("\n\n");
		
		printf("*********************************Final****************************\n\n\n");
}
//Funcion que transforma los caracteres de una palabra a minusculas
void wordToLower(char* word){
	int i;
	
	for(i=0;word[i];i++){
		word[i]=tolower(word[i]);

	}	
}
//funcion que optiene la fecha y hora del PC.
char* DateHour(){
	struct tm *tm;
	time_t fecha;
  	
  	char* dateAndHour = (char*)malloc(sizeof(char)*30);

  	fecha=time(NULL);
  	tm=localtime(&fecha);
  	strftime(dateAndHour, 100, "%d/%m/%Y || %H:%M", tm);
  	return dateAndHour;
}
//funcion que ordena los documentos de mayor a menor .
void burbbleSortDocument(document* new){

	if (new != NULL)
	{
		document *current , *next;
	     int t;
	     
	     current = new;
	     while(current->nxt != NULL)
	     {
	          next = current->nxt;
	          
	          while(next!=NULL)
	          {
	               if(current->frecuency < next->frecuency)
	               {
	                    t = next->frecuency;
	                    next->frecuency = current->frecuency;
	                    current->frecuency = t;          
	               }
	               next = next->nxt;                    
	          }    
	          current = current->nxt;
	          next = current->nxt;
	           
	     }
	}
}

//Funcion booleana que busca un documento(dado su ID) en una lista de documentos.
int searchDoc(document* current,int ID){

	document* aux =current;
	while(aux != NULL){
		if (aux->doc==ID)
		{
			return TRUE;
		}
		aux=aux->nxt;
	}
	return FALSE;
}

void printDocuments(document* current){

	document* aux = current;
	while(aux!=NULL){
		
		aux=aux->nxt;
	}
}


/*
Funcion que despliega la informacion de un documento como Titulo, autor y bibliografia.

ENTRADAS: una estructura Ranking y la cantidad de elementos a imprimir.

SALIDA: no posee un retorno, solo imprime la cantidad de datos pedidos.
*/
void displayResults(Ranking *r, int TopK/*, code *statusCode*/){
	
	int i;
	if (r->accumulated == NULL)
	{
		printf("No se han encontrado resultados para la consulta hecha\n");
	}
	else{
		if (TopK > getDocumentAmount(r->accumulated))
		{
			printf("La cantidad de respuestas pedidas es mayor a la cantidad de respuestas existentes.\n");
		}
		else{
			printf("Resultados encontrados :\n");
			document* aux = r->accumulated;
			for (i = 0; i < TopK; i++)
			{
				doc_data* current = getCurrentData(r,aux->doc);
				printDocumentData(current);
				aux=aux->nxt;
			}
		}
	}
}

/*
Funcion que crea una lista de resultados segun una consulta hecha por el usuario, los resultados son almacenados
en la estructura Ranking. Ademas se crear la estructura Ranking y retornarla con todos los valores necesarios.

ENTRADAS: una estructura Index, una lista de StopWords y una consulta hecha por el usuario.

SALIDA: retorna una estructura Ranking con toda la informacion necesaria para poder ser desplegada luego.
*/

Ranking* query(Index *i, StopWords *sw, char* text/*, code *statusCode*/){
	char new[strlen(text)];
	strcpy(new,text);
	char* buffer = NULL;
    buffer = strtok(new," ");

    Ranking* rk = (Ranking*)malloc(sizeof(Ranking));
    rk->query=NULL;
    rk->size=0;
    rk->accumulated=NULL;
    rk->resultList=NULL;
    rk->dataDoc=i->docList;


    int result_size=0;
    //result* rst = NULL;
    int frecuency;
    int j=0;
    
    rk->query= (char**)malloc(sizeof(char*)*MAX_CHARACTER);


    while( buffer != NULL ) {

    	if (searchStopWords(buffer,sw)==FALSE)
    	{
	    		
	    	
	        
	        result_size++;
	        term* aux = getTerm(buffer,i);
	        rk->query[j] = (char*)malloc(sizeof(char)*MAX_CHARACTER);
	        rk->query[j]=buffer;
	        if (aux != NULL)
	        {
	        	document* doc = aux->documents;
	        	frecuency=0;
	        	while(doc != NULL){
	        		frecuency = frecuency + doc->frecuency;
	        		doc = doc->nxt;
	        	}
	        	insertRkgData(rk,aux->documents,frecuency,buffer);
	        	printDocuments(aux->documents);
	        	insertAccumulatedDocList(rk,aux->documents);
	        	
	        	

    			

	        	j++;
	        }
	        
	     }
         buffer = strtok( NULL, " ");
         
         

    }
   
    
    rk->size=j;
    
   	burbbleSortDocument(rk->accumulated);
   	printDocuments(rk->accumulated);



    return rk;
}







	
