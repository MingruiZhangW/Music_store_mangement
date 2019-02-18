#include "DBfunction.h"

/*
  *`m_id` int NOT NULL auto_increment PRIMARY KEY,
  *`m_category` varchar(100) DEFAULT '0',
  *`m_type` varchar(100) DEFAULT '0',
  *`m_name` varchar(100) NOT NULL DEFAULT '0',
  *`m_artist` varchar(100) NOT NULL DEFAULT '0',
  *`m_price` INT NOT NULL DEFAULT 0,
  *`m_quantity` INT NOT NULL DEFAULT 0

*/

/*
*INSERT INTO `solditem_tb` (`m_category`, `m_type`, `m_name`, `m_artist`, `m_price`, `m_quantity`) VALUES
*('Popular ', 'Jazz', 'WU-TANG CLAN ¨C ¡®DON¡¯T STOP¡¯', 'WU-TANG CLAN', 10, 1),
*('Old', 'Pop', 'O Bondhu Lal Golapi', 'Shahabuddin', 100, 1),
*('Popular ', 'Jazz', 'WU-TANG CLAN ¨C ¡®DON¡¯T STOP¡¯', 'WU-TANG CLAN', 10, 1),
*('Old', 'Pop', 'O Bondhu Lal Golapi', 'Shahabuddin', 100, 1);
*/

void AddNewItemInDatabase() {

	//`m_category`, `m_type`, `m_name`, `m_artist`, `m_price`, `m_quantity`
	std::cout << "Please Entre a Category" << std::endl;

	std::string Category;
	getinput_str(Category);

	std::cout << "Please Entre a Type" << std::endl;
	std::string Type;
	getinput_str(Type);

	std::cout << "Please Entre a Name" << std::endl;
	std::string Name;
	getinput_str(Name);

	std::cout << "Please Entre a Artist" << std::endl;
	std::string Artist;
	getinput_str(Artist);

	std::cout << "Please Entre a Price" << std::endl;
	int Price;
	getinput_num(Price);

	std::cout << "Please Entre the Quantity" << std::endl;
	int Quantity;
	getinput_num(Quantity);

	std::string query {Insert_addNewItemInDatabase_query(Category,Type,Name,Artist,Price,Quantity)};
	//c_str() converts the string to constant character the mysql_query function 
	//can only deals with the constant character.
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);

	if (!qstate){std::cout << "Insert Success" << std::endl;}
	else{std::cout << "Query failed: " << mysql_error(g_conn) << std::endl;}


}

void getinput_str(std::string &stored_place) {

	while (true)
	{

		std::getline(std::cin, stored_place);

		if (std::cin.fail()) // has a previous extraction failed?
		{
			// yep, so let's handle the failure
			std::cin.clear(); // put us back in 'normal' operation mode
			std::cin.ignore(32767, '\n'); // and remove the bad input
			std::cout << "Input Invalid, Try again!" << std::endl;

		}
		else // else our extraction succeeded
		{

			return;
		}

	}

}

void getinput_num(int &stored_place) {

	while (true)
	{

		std::cin >> stored_place;

		if (std::cin.fail()) // has a previous extraction failed?
		{
			// yep, so let's handle the failure
			std::cin.clear(); // put us back in 'normal' operation mode
			std::cin.ignore(32767, '\n'); // and remove the bad input
			std::cout << "Input Invalid, Try again!" << std::endl;

		}
		else // else our extraction succeeded
		{
			// clear (up to 32767) characters out of the buffer until a '\n' character is removed
			if (stored_place < 0) {
			
				std::cout << "Input Invalid, Try again!" << std::endl;
			
			}
			else {
				
				std::cin.ignore(32767, '\n');
				return;

			}
		}

	}

}

std::string Insert_addNewItemInDatabase_query(
			std::string Category,
			std::string Type,
			std::string Name,
			std::string Artist,
			int Price,
			int Quantity
) {

	//INSERT INTO `musicinfo_tb` (`m_category`, `m_type`, `m_name`, `m_artist`, `m_price`, `m_quantity`) VALUES
	//('Popular ', 'Jazz', 'WU-TANG CLAN ¨C ¡®DON¡¯T STOP¡¯', 'WU-TANG CLAN', 10, 1)
	std::string query_re{"INSERT INTO musicinfo_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES ('"};
	query_re += Category;
	query_re += "'";
	query_re += ",";
	query_re += "'";
	query_re += Type;
	query_re += "'";
	query_re += ",";
	query_re += "'";
	query_re += Name;
	query_re += "'";
	query_re += ",";
	query_re += "'";
	query_re += Artist;
	query_re += "'";
	query_re += ",";
	query_re += std::to_string(Price);
	query_re += ",";
	query_re += std::to_string(Quantity);
	query_re += ");";

	return query_re;

}

void ShowAllItems(bool in_stock) {

	MYSQL_ROW row;
	MYSQL_RES *res;

	std::string query{"SELECT * FROM musicinfo_tb"};
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);
	int quantit_tran;

	if (!qstate) {
	
		res = mysql_store_result(g_conn);

		std::cout << std::endl;
		while (row = mysql_fetch_row(res))
		{
			//Reads data from s and stores them according to parameter format into the locations given by the additional arguments, 
			//as if scanf was used, but reading from s instead of the standard input(stdin).
			sscanf_s(row[6], "%d", &quantit_tran);
			if (quantit_tran > 0 || !in_stock) {

				std::cout << std::endl;
				printf("Music_id: %s\n", row[0]);
				printf("Category: %s\n", row[1]);
				printf("Type: %s\n", row[2]);
				printf("Music_Name: %s\n", row[3]);
				printf("Artist: %s\n", row[4]);
				printf("Price: %s\n", row[5]);
				printf("Quantity: %s\n", row[6]);

			}

		}
		std::cout << std::endl;
	
	}
	else{ std::cout << "Query failed: " << mysql_error(g_conn) << std::endl; }

}

void ItemInStock() {

	ShowAllItems(true);

}

void FindMusic() {

	int Find_key;
	std::string key_to_query;
	std::string search_element;

	std::cout << "Please Enter the Key You Want to Search" << std::endl;
	std::cout << "1. ->->Name" << std::endl;
	std::cout << "2. ->->Type" << std::endl;
	std::cout << "3. ->->Artist" << std::endl;
	std::cout << "4. ->->Category" << std::endl;

	while (true)
	{
		Find_key = 0;
		getinput_num(Find_key);

		if (Find_key == 1 || Find_key == 2 || Find_key == 3 || Find_key == 4) {
		
			switch (Find_key)
			{

			case 1: key_to_query = "m_name"; break;
			case 2: key_to_query = "m_type"; break;
			case 3: key_to_query = "m_artist"; break;
			case 4: key_to_query = "m_category"; break;
			break;

			}
			
			break;

		}

		std::cout << "Opps, Invalid Input, Try again" << std::endl;

	}

	std::cout << "Please Enter the Search Element" << std::endl;

	getinput_str(search_element);

	MYSQL_ROW row;
	MYSQL_RES *res;

	std::string query{ "SELECT * FROM musicinfo_tb WHERE " };
	query += key_to_query;
	query += " = '";
	query += search_element;
	query += "'";
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);
	if (!qstate) {

		res = mysql_store_result(g_conn);
		std::cout << std::endl;

		while (row = mysql_fetch_row(res)) {
			
			if (row == nullptr) { std::cout << "Element Searched May not Exist"; }
			printf("Music_id: %s\n", row[0]);
			printf("Category: %s\n", row[1]);
			printf("Type: %s\n", row[2]);
			printf("Music_Name: %s\n", row[3]);
			printf("Artist: %s\n", row[4]);
			printf("Price: %s\n", row[5]);
			printf("Quantity: %s\n", row[6]);
		
		}

		std::cout << std::endl;
	}
	else { std::cout << "Query failed: Element Searched May not Exist" << std::endl; }

}
