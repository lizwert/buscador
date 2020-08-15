Index* createIndex(char* pathDocumentsFile, StopWords *sw, Code *statusCode);
int documentCont(char* file,Code *statusCode);
int numberLock(char* word,int lock);
int serchEspecialCharacter(char* word);
char* cleanEspecilCharacter(char* word);
char* removeCharacter(char* word,char* character);
void insertWordinList(Index* inverted, char* word, int numberDoc, StopWords* sw);
void saveIndex(Index* i, int* id, Code *statusCode);
Index* loadIndex(int id, Code *statusCode);