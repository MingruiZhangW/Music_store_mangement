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
	std::cout << std::endl;
	std::string Category;
	getinput_str(Category);

	std::cout << "Please Entre a Type" << std::endl;
	std::cout << std::endl;
	std::string Type;
	getinput_str(Type);

	std::cout << "Please Entre a Name" << std::endl;
	std::cout << std::endl;
	std::string Name;
	getinput_str(Name);

	std::cout << "Please Entre a Artist" << std::endl;
	std::cout << std::endl;
	std::string Artist;
	getinput_str(Artist);

	std::cout << "Please Entre a Price" << std::endl;
	std::cout << std::endl;
	int Price;
	getinput_num(Price);

	std::cout << "Please Entre the Quantity" << std::endl;
	std::cout << std::endl;
	int Quantity;
	getinput_num(Quantity);

	std::string query {Insert_addNewItemInDatabase_query(Category,Type,Name,Artist,Price,Quantity,false)};
	//c_str() converts the string to constant character the mysql_query function 
	//can only deals with the constant character.
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);

	if (!qstate){std::cout << "Insert Success-------" << std::endl; std::cout << std::endl;}
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
			std::cout << std::endl;

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
			std::cout << std::endl;

		}
		else // else our extraction succeeded
		{
			// clear (up to 32767) characters out of the buffer until a '\n' character is removed
			if (stored_place < 0) {
			
				std::cout << "Input Invalid, Try again!" << std::endl;
				std::cout << std::endl;
			
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
			int Quantity,
			bool soldOrinfo
) {

	//INSERT INTO `musicinfo_tb` (`m_category`, `m_type`, `m_name`, `m_artist`, `m_price`, `m_quantity`) VALUES
	//('Popular ', 'Jazz', 'WU-TANG CLAN ¨C ¡®DON¡¯T STOP¡¯', 'WU-TANG CLAN', 10, 1)
	std::string query_re;
	if (soldOrinfo) { query_re = "INSERT INTO solditem_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES (\""; }
	else { query_re = "INSERT INTO musicinfo_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES (\""; }
	query_re += Category;
	query_re += "\"";
	query_re += ",";
	query_re += "\"";
	query_re += Type;
	query_re += "\"";
	query_re += ",";
	query_re += "\"";
	query_re += Name;
	query_re += "\"";
	query_re += ",";
	query_re += "\"";
	query_re += Artist;
	query_re += "\"";
	query_re += ",";
	query_re += std::to_string(Price);
	query_re += ",";
	query_re += std::to_string(Quantity);
	query_re += ");";

	return query_re;

}

void ShowAllItems(bool in_stock) {

	// input false will display all items even with 0 quantity

	MYSQL_ROW row;
	MYSQL_RES *res;

	std::string query{"SELECT * FROM musicinfo_tb"};
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);
	int quantit_tran;

	if (!qstate) {
	
		res = mysql_store_result(g_conn);

		if (mysql_num_rows(res) == 0) {

			std::cout << "No Item in the Store -------" << std::endl;
			std::cout << std::endl;
			return;

		}

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
	std::cout << std::endl;

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
		std::cout << std::endl;

	}

	std::cout << "Please Enter the Search Element" << std::endl;
	std::cout << std::endl;

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

		if (mysql_num_rows(res) == 0) {

			std::cout << "No Item in Found in the Store -------" << std::endl;
			std::cout << std::endl;
			return;

		}

		std::cout << std::endl;

		while (row = mysql_fetch_row(res)) {
			
			printf("Music_id: %s\n", row[0]);
			printf("Category: %s\n", row[1]);
			printf("Type: %s\n", row[2]);
			printf("Music_Name: %s\n", row[3]);
			printf("Artist: %s\n", row[4]);
			printf("Price: %s\n", row[5]);
			printf("Quantity: %s\n", row[6]);
			std::cout << std::endl;
		
		}

		std::cout << std::endl;
	}
	else { std::cout << "Query failed: Element Searched May not Exist" << std::endl; }

}

void EditItem() {

	std::set<int> music_id_instore;
	MYSQL_ROW row;
	MYSQL_RES *res;

	std::string query{ "SELECT m_id,m_name FROM musicinfo_tb" };
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);

	if (!qstate) {

		res = mysql_store_result(g_conn);

		if (mysql_num_rows(res) == 0) {

			std::cout << "No Item in the Store -------" << std::endl;
			std::cout << std::endl;
			return;

		}

		std::cout << std::endl;
		while (row = mysql_fetch_row(res)) {
		
			int music_in_store;
			sscanf_s(row[0], "%d", &music_in_store);
			music_id_instore.emplace(music_in_store);
			std::cout << "Musicid: " << row[0] << " ------ Music_name: " << row[1] << std::endl;
			std::cout << std::endl;
		
		}
		std::cout << std::endl;

	}
	else { std::cout << "Query failed: " << mysql_error(g_conn) << std::endl; }
	
	std::cout << "Choose a Musicid to Edit-------------" << std::endl;
	std::cout << std::endl;

	int musid_to_edit;
	getinput_num(musid_to_edit);

	if (music_id_instore.find(musid_to_edit) == music_id_instore.end()) {
	
		std::cout << "Invalid Input, Exiting --------" << std::endl;
		return;
	
	}

	std::cout << "Which proprity do you want to edit for Musicid " << musid_to_edit << std::endl;
	std::cout << "1. Category" << std::endl;
	std::cout << "2. Type" << std::endl;
	std::cout << "3. Name" << std::endl;
	std::cout << "4. Artist" << std::endl;
	std::cout << "5. Price" << std::endl;
	std::cout << "6. Quantity" << std::endl;
	std::cout << std::endl;

	std::string musicPro_to_edit_str;
	int musicPro_to_edit;
	getinput_num(musicPro_to_edit);

	if (musicPro_to_edit != 1 && musicPro_to_edit != 2 && musicPro_to_edit != 3 && musicPro_to_edit != 4 && musicPro_to_edit != 5 && musicPro_to_edit != 6) {
	
		std::cout << "Invalid Input, Exiting --------" << std::endl;
		return;

	}

	switch (musicPro_to_edit)
	{
	case 1: musicPro_to_edit_str = "m_category"; break;
	case 2: musicPro_to_edit_str = "m_type"; break;
	case 3: musicPro_to_edit_str = "m_name"; break;
	case 4: musicPro_to_edit_str = "m_artist"; break;
	case 5: musicPro_to_edit_str = "m_price"; break;
	case 6: musicPro_to_edit_str = "m_quantity"; break;
		break;
	}

	std::string update_query{ "UPDATE musicinfo_tb SET " };
	update_query += musicPro_to_edit_str;
	update_query += " = ";
	int update_item_int;
	std::string update_item_str;

	std::cout << "Please Enter the Update Element" << std::endl;
	std::cout << std::endl;
	if (musid_to_edit == 5 || musid_to_edit == 6) { 

		getinput_num(update_item_int); 
		update_query += std::to_string(update_item_int);

	}
	else {

		getinput_str(update_item_str);
		update_query += "\"";
		update_query += update_item_str;
		update_query += "\"";

	}

	update_query += " WHERE m_id = ";
	update_query += std::to_string(musid_to_edit);
	//std::cout << update_query << std::endl;
	const char* q_2 = update_query.c_str();
	int qstate_2 = mysql_query(g_conn, q_2);

	if (!qstate_2) {
	
		std::cout << "Update Successed-------" << std::endl;
		std::cout << std::endl;

	}
	else { std::cout << "Query failed: " << mysql_error(g_conn) << std::endl; }
	

}

void RemoveItem() {

	std::set<int> music_id_instore;
	MYSQL_ROW row;
	MYSQL_RES *res;

	std::string query{ "SELECT m_id,m_name FROM musicinfo_tb" };
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);

	if (!qstate) {

		res = mysql_store_result(g_conn);

		if (mysql_num_rows(res) == 0) {

			std::cout << "No Item in the Store -------" << std::endl;
			std::cout << std::endl;
			return;

		}

		std::cout << std::endl;
		while (row = mysql_fetch_row(res)) {

			int music_in_store;
			sscanf_s(row[0], "%d", &music_in_store);
			music_id_instore.emplace(music_in_store);
			std::cout << "Musicid: " << row[0] << " ------ Music_name: " << row[1] << std::endl;
			std::cout << std::endl;

		}
		std::cout << std::endl;

	}
	else { std::cout << "Query failed: " << mysql_error(g_conn) << std::endl; }

	std::cout << "Choose a Musicid to Delete-------------" << std::endl;
	std::cout << std::endl;

	int musid_to_edit;
	getinput_num(musid_to_edit);

	if (music_id_instore.find(musid_to_edit) == music_id_instore.end()) {

		std::cout << "Invalid Input, Exiting --------" << std::endl;
		return;

	}

	std::string query_2{ "DELETE FROM musicinfo_tb WHERE m_id = " };
	query_2 += std::to_string(musid_to_edit);
	const char* q_2 = query_2.c_str();
	int qstate_2 = mysql_query(g_conn, q_2);

	if (!qstate_2) {

		std::cout << "Delete Successed -------" << std::endl;
		std::cout << std::endl;

	}
	else { std::cout << "Query failed: " << mysql_error(g_conn) << std::endl; }
}

void CreateOrder() {

	std::map<int,std::pair<int,int>> music_id_quan_price;
	int price {0};
	MYSQL_ROW row;
	MYSQL_RES *res;

	std::string query{ "SELECT m_id,m_name,m_quantity,m_price FROM musicinfo_tb WHERE m_quantity > 0" };
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);

	if (!qstate) {

		res = mysql_store_result(g_conn);

		if (mysql_num_rows(res) == 0) {

			std::cout << "No Item in the Store -------" << std::endl;
			std::cout << std::endl;
			return;

		}

		std::cout << std::endl;
		while (row = mysql_fetch_row(res)) {

			int music_id_store, music_id_quan,music_id_price;
			sscanf_s(row[0], "%d", &music_id_store);
			sscanf_s(row[2], "%d", &music_id_quan);
			sscanf_s(row[3], "%d", &music_id_price);
			std::pair<int,int>temp_store{ std::make_pair(music_id_quan,music_id_price) };
			music_id_quan_price.emplace(music_id_store, temp_store);
			std::cout << "Musicid: " << row[0] << " -- Music_name: " << row[1] << "-- Quantity: " << row[2] << "-- Price: " << row[3] << std::endl;
			std::cout << std::endl;

		}
		std::cout << std::endl;

	}
	else { std::cout << "Query failed: " << mysql_error(g_conn) << std::endl; }

	while (true) {

		std::cout << "Please Enter the Musicid to Create Order, Zero to Exit" << std::endl;
		std::cout << std::endl;

		int music_id_buying;
		getinput_num(music_id_buying);

		if (music_id_buying == 0) { break; }
		if (music_id_quan_price.find(music_id_buying) == music_id_quan_price.end()) { std::cout << "Invalid Input, Try Again ----------" << std::endl; continue; }

		std::cout << "Please Enter the Quantity to Create Order, Zero to Exit" << std::endl;
		std::cout << std::endl;

		int music_id_quan_buying;
		getinput_num(music_id_quan_buying);

		if (music_id_quan_buying == 0) { break; }
		if (std::get<0>(music_id_quan_price[music_id_buying]) < music_id_quan_buying) { std::cout << "Invalid Input, Try Again ----------" << std::endl; continue; }


		std::get<0>(music_id_quan_price[music_id_buying]) = std::get<0>(music_id_quan_price[music_id_buying]) - music_id_quan_buying;
		price += std::get<1>(music_id_quan_price[music_id_buying]) * music_id_quan_buying;

		//Update Info Database
		MYSQL_ROW row_up_info;
		MYSQL_RES *res_up_info;

		std::string query_up_info{ "UPDATE musicinfo_tb SET m_quantity = " };

		query_up_info += std::to_string(std::get<0>(music_id_quan_price[music_id_buying]));
		query_up_info += " WHERE m_id = ";
		query_up_info += std::to_string(music_id_buying);

		const char* q_up_info = query_up_info.c_str();
		int qstate_up_info = mysql_query(g_conn, q_up_info);

		//Update Solditem database

		std::string query_up_sold{ "SELECT * FROM musicinfo_tb WHERE m_id = " };
		query_up_sold += std::to_string(music_id_buying);
		q_up_info = query_up_sold.c_str();
		qstate_up_info = mysql_query(g_conn, q_up_info);
		if (qstate_up_info) { std::cout << "Wrong Updates Check the system!!!!!!!1" << std::endl; return; }

		res_up_info = mysql_store_result(g_conn);
		int input_price { 0 };
		std::string query_up_sold_update;
		while (row_up_info = mysql_fetch_row(res_up_info)) {
				
			sscanf_s(row_up_info[5], "%d", &input_price);
			query_up_sold_update = Insert_addNewItemInDatabase_query(row_up_info[1], row_up_info[2], row_up_info[3], row_up_info[4], input_price, music_id_quan_buying, true);
				
		}

		q_up_info = query_up_sold_update.c_str();
		qstate_up_info = mysql_query(g_conn, q_up_info);
		if (qstate_up_info) { std::cout << "Wrong Updates Check the system!!!!!!!" << std::endl; return; }


		std::cout << "Another item ? ---------- 1 -> Yes, 2 -> NO" << std::endl;
		std::cout << std::endl;

		int again_int;
		getinput_num(again_int);

		if (again_int == 1) { continue; }
		break;

	}

	std::cout << "Total Price is " << price << std::endl;

}

void SoldItems() {

	MYSQL_ROW row;
	MYSQL_RES *res;

	std::string query{ "SELECT * FROM solditem_tb" };
	const char* q = query.c_str();
	int qstate = mysql_query(g_conn, q);

	if (!qstate) {

		res = mysql_store_result(g_conn);

		if (mysql_num_rows(res) == 0) {

			std::cout << "No Item in the Store -------" << std::endl;
			std::cout << std::endl;
			return;

		}

		std::cout << std::endl;
		while (row = mysql_fetch_row(res))
		{

			std::cout << std::endl;
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
	else { std::cout << "Query failed: " << mysql_error(g_conn) << std::endl; }

}