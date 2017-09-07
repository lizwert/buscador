
#define INDEX_TEXT ".I"
#define TITLE_TEXT ".T"
#define AUTHOR_TEXT ".A"
#define BIBLIOGRAFY ".B"
#define TEXT ".W"
#define MAX_CHARACTER 30
#define TRUE 1
#define FALSE 0


typedef enum code {OK, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERM} Code;

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

typedef struct {
	char** query;
	int size;
	document* accumulated;
	result* resultList;
	doc_data* dataDoc;
}Ranking;

