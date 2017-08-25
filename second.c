#include <stdlib.h>
#include <stdio.h>

typedef struct {
 int size;
 char** listStopWords;
 
}StopWords;

enum code {OK, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERM};

int wordSize(char* file){
	int contador=0;
	char* word = (char*)malloc(sizeof(char)*20);

	FILE* pt = fopen(file,"r");
	if(pt){ 
		
		printf("abierto \n");
	}
	else{ 
		
		printf("No se pudo abrir el archivo \n");
		return 0;
	}
	
	
	while(!feof(pt)){
		contador++;
		fscanf(pt,"%s",word);	
	}
	fclose(pt);
	contador--;
	printf("entonces %d \n",contador);
	free(word);
	return contador;

}

StopWords* loadStopWords(char* pathStopWordsFile /*, code *statusCode*/){

	StopWords* words=(StopWords*)malloc(sizeof(StopWords));
	int contador=0;
	char* word = (char*)malloc(sizeof(char)*20);
	char** listWords;
	
	printf("la cantidad de stopwords es %d \n", contador);
	(*words).size=wordSize(pathStopWordsFile);
	listWords= (char**)malloc(sizeof(char*)*contador);
	
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
	printf("hola %d\n",(*words).size);
	for(i=0;i<(*words).size;i++){
		fscanf(pt,"%s", word);
		listWords[i]=word;
		printf("%s\n",word);
		
	}
	(*words).listStopWords=listWords;
	//free(listWords);
	//free(word);
	fclose(pt);
	

	return words;
	
	
	

}

int main(){
	StopWords* w = loadStopWords("stopwords.in");
	return 1;
}

	
