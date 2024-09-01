#pragma once

#include <Wt/Dbo/Session.h>
#include <string>
#include <Wt/WString.h>


class Tasksdb
{
	std::string db = "MYSQL90";
	std::string dbuser = "rakesh";
	std::string dbpassword = "sharma";
	std::string dbhost = "localhost";
	uint32_t dbport = 3306;

	Wt::Dbo::Session session;
public:
	void connect();
	void AddTask(std::string task);
	std::vector<std::string> GetTasks();
};

