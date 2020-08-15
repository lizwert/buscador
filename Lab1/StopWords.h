StopWords* loadStopWords(char* pathStopWordsFile , Code *statusCode);
void addInListSW(StopWords* sw, char* word);
int searchStopWords(char* word, StopWords* sw);