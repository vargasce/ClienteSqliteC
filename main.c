/*
 * main.c
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

void sigintHandler(int signal);

int main(int argc, char **argv)
{	
	signal(SIGINT, sigintHandler);
	Create_Data_Base("identity.db");
	ListDataBase();
	response_query_sqlite *response = Select_Response();	
	
	if(response->success == 1){
		printf(" Count columns : %d\n",response->payload->argc);			
		
		for (int i = 0; i < response->payload->argc; i++) {
			printf("%s = %s\n", response->payload->azColName[i], response->payload->argv[i] ? response->payload->argv[i] : "NULL");
		}
		
	}
	
	Free_Response_Query(response);
	
	if( ConectionDB("identity.db") != 1){
		printf("Error\n");
	}
	
	CloseConection();
	
	getchar();
	return 0;
}

void sigintHandler(int signal){
	printf("\n\tSaliendo... \n\tpuede cerrar ventana!!! \n");
	exit(EXIT_FAILURE);
}


