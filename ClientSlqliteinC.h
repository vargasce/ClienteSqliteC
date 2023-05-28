
#include <sqlite3.h>

typedef struct {
	int argc;  		  //number columns
	char **argv;      //fields in the row.
	char **azColName; //column names
} Payload;

typedef struct {
	int success; // 1 success, 0 error
	Payload *payload;
	char *message;
} response_query_sqlite;

int Create_Data_Base(char *nameDB);
int ConectionDB(char *nameDB);
void CloseConection();
int ListDataBase();
void Free_Response_Query(response_query_sqlite *response);
response_query_sqlite *Select_Response();
