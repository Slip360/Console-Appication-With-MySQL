#include <stdlib.h>
#include <iostream>
#include <string>

#include "mysql_connection.h"
#include <cppconn/driver.h>

#include "User.h"

//for demonstration only. never save your password in the code!
const std::string server = "tcp://127.0.0.1:3306";
const std::string username = "root";
const std::string password = "root";
const std::string schema = "project";

int ShowMenu()
{
	int value = 0;
	printf("1. Insert user\n");
	printf("2. View users\n");
	printf("3. Exit\n");
	printf("Select an option: ");
	scanf_s("%d", &value);
	system("cls || clear");
	return value;
}

void OptionCreateUser(std::string &name, int &age)
{
	std::cout << "Enter user name:" << std::endl;
	std::cin >> name;
	std::cout << "Enter user age:" << std::endl;
	std::cin >> age;
}

int main()
{
	setlocale(LC_ALL, "Spanish");
	sql::Driver* driver = get_driver_instance();
	sql::Connection* connection = driver->connect(server, username, password);
	connection->setSchema(schema);
	User::User user("users");

	while (true)
	{
		int result = ShowMenu();
		if (result == 1)
		{
			std::string name;
			int age;
			OptionCreateUser(name, age);
			user.InsertUser(connection, name, age);
			system("cls || clear");
		}
		else if (result == 2)
		{
			sql::ResultSet* result = user.GetUsers(connection);
			while(result->next())
			{
				std::cout << "Name: " << result->getString("name") << " Age: " << result->getInt("age") << std::endl;
			}
			system("pause");
			system("cls || clear");
		}
		else
		{
			printf("Invalid option\n");
			printf("Exiting\n");
			break;
		}
	}

	system("pause");
	delete connection;
	return 0;
}
