
#include <sqlite3.h>

typedef struct {
	int success;
	sqlite3_stmt *payload;
	char *menssage;
} response_query_sqlite;

int Create_Data_Base(char *nameDB);
void CloseConection();
response_query_sqlite select_request(char *body);
