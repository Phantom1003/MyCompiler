#ifndef TOKEN_H
#define TOKEN_H 

typedef enum tokentypes { 
	OPERATOR, DELIMITER, RESERVED, TOKEN_NAME, TOKEN_STR, TOKEN_NUM, TOKEN_CHAR
} tokenType;
typedef enum datatypes {
	DATA_NAME,
	DATA_INT,
	DATA_REAL,
	DATA_CHAR,
	DATA_STR,
} dataType;

typedef struct token {
	tokenType token_t;
	dataType data_t;
	int tokenN;
	char * name;
	union {
		char charval;
		int intval;
		double realval;
		char * strval;
	} tokenval;

} *TOKEN;
#endif

#define TOKENSIZE sizeof(struct token)