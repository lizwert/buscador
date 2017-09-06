
typedef struct dulce
{
	char repre;
	int dureza;
	char* name;
	int ID;
	
}Candy;

typedef struct parmetros
{
	int dif;
	Candy* dulces;
	int* cantidad_de_dulces;
	int largo_dulces;
	
	
}Params;

typedef struct tablero
{
	Candy** matriz_dulces;
	int fila;
	int columna;
	int dificultad;
}Board;

typedef struct arreglo
{
	int N;
	int M;
	Candy dulce;
	int valor;
	
}Position;


typedef enum Code {OK, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERM, IMPOSSIBLE_VALID_BOARD, 
					MISSING_NUMBER, ADY_DOESNT_EXIST, CANT_MOVE_CANDIES, NO_ADYCANDIES,
					DIMENSIONS_NOT_ALLOWED,MISSING_SYMBOL} code;
enum {CREATE_BOARD,SAVE_BOARD,LOAD_BOARD,CHECK_BOARD,PLAY};
	