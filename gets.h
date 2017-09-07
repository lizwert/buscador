void getDocumentData(Index* inverted,char* pathDocumentsFile);
term* getTerm(char* word, Index* Index);
document* getLastDoc(term* Term);
doc_data* getCurrentData(Ranking* current,int id_doc);
int getDocumentAmount(document* current);
document* getdocument(document* current,int ID);