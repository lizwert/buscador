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
Funcion inserta una palabra en la estructura words que es pasada por referencia.

ENTRADAS: la estructura words y la palabra para ser agregada.

SALIDA: no contiene retorno, pero la palabra es insertada en words.
*/
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


/*
Funcion inserta una estructura doc_data en la estructura index que es pasada por referencia.

ENTRADAS: la estructura index y data_doc para ser agregada.

SALIDA: no contiene retorno, pero los datos de documento es insertada en index.
*/
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


/*
Funcion que crea un nuevo termino con una palabra y una estructura documento y la inserta en index pasada por referencia.

ENTRADAS: la estructura index, una palabra y una lista de documentos.

SALIDA: no contiene retorno, pero se crea un nuevo termino que es insertado en index.
*/
void insertTerm(Index* Index,char* word, document* newDoc){

	term* newTerm = (term*)malloc(sizeof(term));
	newTerm->word = word;
	newTerm->documents = newDoc;
	newTerm->nxt=NULL;
	
	if(Index->terms == NULL){
		
		Index->terms = newTerm;
		Index->size = 1;
		
		
		
	}
	else{
		
		term* aux = Index->terms;
		while(aux->nxt != NULL){
			aux = aux->nxt;
		}
		aux->nxt= newTerm;
		Index->size++;
		

	}	
}


/*
Funcion que inserta un documento en la ultima posicion de una lista de terminos

ENTRADAS: una lista de terminos y el documento a insertar.

SALIDA: no contiene retorno, pero se inserta el documento al final de la lista de terminos.
*/
void insertLastDoc(term* Term, document* Doc){
	document* aux = Term->documents;
	
	while(aux->nxt !=NULL){
		aux = aux->nxt;

	}
	aux->nxt =Doc;
}

/*
Funcion que inserta una lista de documentos en la estructura ranking. La lisda de documentos se va acumulando con
las que ya existen en la estructura Ranking.

ENTRADAS: una estructura Ranking y una lista de documentos.

SALIDA: no contiene retorno, pero se inserta la lista en la estructura.
*/

void insertAccumulatedDocList(Ranking* rk,document* current){


	if (rk->accumulated == NULL)
	{
		
		rk->accumulated = current;
		
	}
	else
	{

		document* aux = current;
		while(aux != NULL){
			
			addDocumentDatas(rk->accumulated,aux->doc,aux->frecuency);
			aux=aux->nxt;
		}
		
	}
}


/*
Funcion que crea, agrega y aumenta la frecuencia de una lista de documentos (segun corresponda).

ENTRADAS: una lista de documentos, un ID de documento y su frecuencia.

SALIDA: no contiene retorno, pero se realizan las acciones dependiendo si ya existe un documento en
la lista de documentos pasada por referencia. Si no existe, se agrega un documento al final de la lista.
*/

void addDocumentDatas(document* current,int ID,int frec){

	document* new = (document*)malloc(sizeof(document));
	new->doc=ID;
	new->frecuency=frec;
	new->nxt=NULL;
	

	if (searchDoc(current,ID)==TRUE)
	{
		
		document* temp = getdocument(current,ID);
		temp->frecuency= temp->frecuency+frec;
		
	}
	else{
	
		
		document* aux = current;


		while(aux->nxt != NULL){
				
			aux = aux->nxt;
		}
		aux->nxt=new;
			
		}


	
}


/*
Funcion que crea e inserta un nuevo resultado a la estructura Ranking.

ENTRADAS: una estructura Ranking pasada por referencia, una lista de documentos, una palabra y una frecuencia acumulada.

SALIDA: no contiene retorno, pero se agrega un nuevo resultado a la estructura Ranking.
*/
void insertRkgData(Ranking* rk, document* doc, int frec,char* word){

	result* new = (result*)malloc(sizeof(result));
	new->word = word;
	new->frec=frec;
	new->docList=doc;
	new->nxt = NULL;

	if (rk->resultList == NULL)
	{
		rk->resultList=new;
		
	}
	else{
		result* aux = rk->resultList;
		while(aux != NULL){
			aux=aux->nxt;
		}
		
		aux = new;
	}
}

/*
Funcion que crea un nuevo documento y lo inserta en la estructura index que es pasa por referencia.

ENTRADAS: una estructura Index, una palabra, un ID de documento junto con su frecuencia.

SALIDA: no contiene retorno, pero se agrega un nuevo documento a Index.
*/
void insertDataIndex(Index* index,char* word, int doc, int frecuency){
	
	if(searchTerm(word,index)==TRUE){
		
		
		term* aux = getTerm(word,index);
		
						
		document* newDoc = (document*)malloc(sizeof(document));
		newDoc->doc=doc;
		newDoc->frecuency=frecuency;
		newDoc->nxt=NULL;
					
		insertLastDoc(aux,newDoc); 

	}
	else{
		
		document* newDoc = (document*)malloc(sizeof(document));
		newDoc->doc = doc;
		newDoc->frecuency =frecuency;
		newDoc->nxt = NULL;
				
		insertTerm(index,word,newDoc);
		

	}
}

