#include <mysql.h>
#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */


//(extern) -> external linkage
MYSQL *g_conn;

void DBconnection_Init(void) {

	g_conn = mysql_init(0);

	//The value of host,The user parameter,mima,database name,port,socket,client flag

	g_conn = mysql_real_connect(g_conn, "localhost", "root", "Huang19930914", "musicstore", 3306, NULL, 0);

	if (!g_conn){
		puts("Connection to database has failed!");
		exit(EXIT_FAILURE);
	}

}