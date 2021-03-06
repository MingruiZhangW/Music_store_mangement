#ifndef DBFUNCTION_H
#define DBFUNCTION_H

#include "DBconnection.h"

void AddNewItemInDatabase();
void getinput_str(std::string &stored_place);
void getinput_num(int &stored_place);
std::string Insert_addNewItemInDatabase_query(
	std::string Category,
	std::string Type,
	std::string Name,
	std::string Artist,
	int Price,
	int Quantity
);
void ShowAllItems(bool in_stock);
void ItemInStock();
void FindMusic();

#endif // !DBFUNCTION_H
