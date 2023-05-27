/*
 * ClientSlqliteinC.c
 * 
 * Copyright 2023  <kali@kali>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "ClientSlqliteinC.h"

#define ERROR -1
#define SUCCESS 1
#define SYSTEM_TABLE "system.db"
#define NAMETABLES "Tables"

int InitSystem();
char *insertString(char** original, char* insert, int pos);
int InitDataBase(char *nameDB);
int Create_DB(char *nameDB);

int Create_Data_Base(char *nameDB){
	
	InitSystem();
	InitDataBase(nameDB);
	Create_DB(nameDB);
	
	return SUCCESS;
}

int InitSystem(){
	
	sqlite3 *db;
	char *err_msg;
	
	int rc = sqlite3_open(SYSTEM_TABLE, &db);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database: %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);        
        return ERROR;
	}
	
	char *sql = "CREATE TABLE  (Id INTEGER PRIMARY KEY, Name TEXT);";
	char * sqlAdd = insertString(&sql, NAMETABLES, 13);
	
	rc = sqlite3_exec(db, sqlAdd, 0, 0, &err_msg);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Failed to create table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
	}
	
	sqlite3_close(db);
		
	return SUCCESS;
}

int InitDataBase(char *nameDB){
	
	sqlite3 *db;
	char *err_msg;
	int existNameBD = -1;
	sqlite3_stmt *res;
	
	int rc = sqlite3_open(SYSTEM_TABLE, &db);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database: %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);        
        return ERROR;
	}
	
	rc = sqlite3_prepare_v2(db, "SELECT Name FROM Tables;", -1, &res, 0);    
    
    if (rc != SQLITE_OK) {        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        sqlite3_free(res);
        return 1;
    }    
    
    rc = sqlite3_step(res);
    
    if (rc == SQLITE_ROW) {        
        char *result = (char*)sqlite3_column_text(res, 0);
        if(strcmp(result,nameDB) == 0){
			existNameBD = 1;
		}
    }
    
    sqlite3_finalize(res);
	if(existNameBD != 1){
		char *sql = "INSERT INTO (Name) VALUES ('');";
		sql = insertString(&sql, NAMETABLES, 12);
		sql = insertString(&sql, nameDB, 28 + strlen(NAMETABLES));
	
		rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
		
		if(rc != SQLITE_OK){
			printf("%s\n", sql);
			fprintf(stderr, "Failed to Insert table\n");
			fprintf(stderr, "SQL error: %s\n", err_msg);
			sqlite3_free(err_msg);
		}
		
		int last_id = sqlite3_last_insert_rowid(db);
		printf("The last Id of the inserted row is %d\n", last_id);
	}
	    
	sqlite3_close(db);
		
	return SUCCESS;
}

int Create_DB(char *nameDB){
	
	sqlite3 *db;
	
	int rc = sqlite3_open(nameDB, &db);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database: %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);        
        return ERROR;
	}
	
	sqlite3_close(db);
	
	return SUCCESS;
}

/**
 *	Tomando como inicio un puntero char, inserta un string
 *  en la posicion indicada.
 *  retorna un nuevo puntero con el string y el insert.
 **/
char *insertString(char** original, char* insert, int pos){
	
    int originalLen = strlen(*original);
    int insertLen = strlen(insert);
    int newLen = originalLen + insertLen + 1;
    int posResto = pos + insertLen;
    
    char* aux = (char*) malloc(newLen * sizeof(char));
    memset(aux,' ', newLen);
    strcpy(aux, *original);
       
    char* temp = (char*) malloc(newLen * sizeof(char));
    memset(temp,' ',newLen);
    
    strncpy(temp, aux, pos);    	
    strcpy(temp + pos, insert);        
        
    temp = (char*) realloc(temp, originalLen * sizeof(char));
    
    strcpy(temp + posResto, aux + pos);

	return temp;
}

