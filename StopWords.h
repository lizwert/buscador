StopWords* loadStopWords(char* pathStopWordsFile /*, code *statusCode*/);
void addInListSW(StopWords* sw, char* word);
int searchStopWords(char* word, StopWords* sw);