
#include <sqlite3.h>

typedef struct {
	int argc;  		  //number columns
	char **argv;      //fields in the row.
	char **azColName; //column names
} Payload;

typedef struct {
	int success;
	Payload *payload;
	char *message;
} response_query_sqlite;

int Create_Data_Base(char *nameDB);
void CloseConection();
int ListDataBase();
response_query_sqlite *Select_Response();
