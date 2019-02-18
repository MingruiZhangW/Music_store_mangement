
#include "DBfunction.h"


/*
*qstate represent the state of the query. If 0 is successful 1 is failed.
*conn is the mysql connection variable.
*row is for getting the current row of the database.
*res is for getting all the values form the database.
*/

int main()
{
	DBconnection_Init();

	AddNewItemInDatabase();
	//ShowAllItems(false);
	//FindMusic();
	//Git repo test
	std::cin.get();
	return 0;
}