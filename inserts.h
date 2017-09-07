void insertWordsinDataDoc(words* docData,char* word);
void insertDatainInverted(Index* Index, doc_data* document);
void insertTerm(Index* Index,char* word, document* newDoc);
void insertLastDoc(term* Term, document* Doc);
void insertAccumulatedDocList(Ranking* rk,document* current);
void addDocumentDatas(document* current,int ID,int frec);
void insertRkgData(Ranking* rk, document* doc, int frec,char* word);
void insertDataIndex(Index* index,char* word, int doc, int frecuency);