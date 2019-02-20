
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

	std::cout << "Welcome to the Music Store Database Mangement System!" << std::endl;

	while (true) {

		std::cout << std::endl;
		std::cout << "1. Show All Items in the Store " << std::endl;
		std::cout << std::endl;
		std::cout << "2. Add New Item in Database " << std::endl;
		std::cout << std::endl;
		std::cout << "3. Items in Stock that are Available" << std::endl;
		std::cout << std::endl;
		std::cout << "4. Find Specific Music" << std::endl;
		std::cout << std::endl;
		std::cout << "5. Edit Item" << std::endl;
		std::cout << std::endl;
		std::cout << "6. Remove Item" << std::endl;
		std::cout << std::endl;
		std::cout << "7. Create An Order" << std::endl;
		std::cout << std::endl;
		std::cout << "0. Exit Program" << std::endl;
		std::cout << std::endl;

		std::cout << "Please Select One of the Options , Exit -> 0" << std::endl;

		int selection_vode;
		getinput_num(selection_vode);
		int exit;

		switch (selection_vode)
		{
		case 0: exit = 1;  break;
		case 1: ShowAllItems(false);  break;
		case 2: AddNewItemInDatabase();  break;
		case 3: ItemInStock();  break;
		case 4: FindMusic();  break;
		case 5: EditItem();  break;
		case 6: RemoveItem();  break;
		case 7: CreateOrder();  break;
		}

		if (exit == 1) { break;  }
	
	}

	return 0;
}