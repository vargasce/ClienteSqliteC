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
void clearTerminal();
char *insertNameDB();

int main(int argc, char **argv)
{	
	signal(SIGINT, sigintHandler);
	Create_Data_Base("business.db");
	getchar();
	return 0;
}

void sigintHandler(int signal){
	printf("\n\tSaliendo... \n\tpuede cerrar ventana!!! \n");
	exit(EXIT_FAILURE);
}

void clearTerminal() {
    if (system("clear") == -1) {
        perror("Error al limpiar la terminal");
        exit(EXIT_FAILURE);
    }
}

char *insertNameDB(){	
	
	char *buffer = (char *) malloc(20);
	char *db = ".db\0";
	
	if (buffer==NULL)return NULL;
		
	getchar();
	memset(buffer,0,20);	
	fgets(buffer,15,stdin);
	buffer[strlen(buffer) - 1] = ' ';
	strcat(buffer,db);
	
	return buffer;
}
