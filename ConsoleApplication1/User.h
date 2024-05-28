#include <iostream>
#include <cppconn/prepared_statement.h>

namespace User
{
	class User
	{
	public:
		User(std::string tableName);
		~User();
		void InsertUser(sql::Connection* connection, std::string name, int age);
		sql::ResultSet* GetUsers(sql::Connection* connection);
	private:
		std::string tableName;
		void CreateUserTable(sql::Connection* connection);
	};

	User::User(std::string tableName)
	{
		this->tableName = tableName;
	}

	User::~User()
	{
	}

	void User::CreateUserTable(sql::Connection* connection)
	{
		printf("Creating table %s\n", tableName.c_str());
		sql::Statement* stmt = connection->createStatement();
		stmt->execute("CREATE TABLE IF NOT EXISTS " + tableName + " (id serial PRIMARY KEY, name VARCHAR(50), age INTEGER);");
		std::cout << "Finished creating table" << std::endl;
		delete stmt;
		printf("Table %s created\n", tableName.c_str());
	}

	void User::InsertUser(sql::Connection* connection, std::string name, int age)
	{
		CreateUserTable(connection);
		printf("Inserting user %s\n", name.c_str());
		sql::PreparedStatement* pstmt = connection->prepareStatement("INSERT INTO " + tableName + "(name, age) VALUES(?,?)");
		pstmt->setString(1, name);
		pstmt->setInt(2, age);
		pstmt->execute();
		std::cout << "One row inserted." << std::endl;
		delete pstmt;
		printf("User %s inserted\n", name.c_str());
	}

	sql::ResultSet* User::GetUsers(sql::Connection* connection)
	{
		CreateUserTable(connection);
		printf("Getting users\n");
		sql::Statement* stmt = connection->createStatement();
		sql::ResultSet* res = stmt->executeQuery("SELECT * FROM " + tableName);
		delete stmt;
		printf("Users retrieved\n");
		return res;
	}
}
