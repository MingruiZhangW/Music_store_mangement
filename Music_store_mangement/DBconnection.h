#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <mysql.h>
#include <iostream>
#include <string>
#include <stdlib.h>     /* exit, EXIT_FAILURE */

void DBconnection_Init(void);

//extern - forward declration to represent a global var is defined somewhere else
extern MYSQL *g_conn;

#endif // !DBCONNECTION_H

