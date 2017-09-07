Index* createIndex(char* pathDocumentsFile, StopWords *sw/*, code *statusCode*/);
int documentCont(char* file);
int numberLock(char* word,int lock);
int serchEspecialCharacter(char* word);
char* cleanEspecilCharacter(char* word);
char* removeCharacter(char* word,char* character);
void insertWordinList(Index* inverted, char* word, int numberDoc, StopWords* sw);
void saveIndex(Index* i, int* id/*, code *statusCode*/);
Index* loadIndex(int id/*, code *statusCode*/);