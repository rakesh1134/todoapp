#include "Tasksdb.h"
#include <string>
#include <iostream>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/Dbo/Transaction.h>
#include "Task.h"
#include <io.h>

void Tasksdb::connect()
{
	try
	{
		auto sqlite3 = std::make_unique<Wt::Dbo::backend::Sqlite3>("tasks.db");
		session.setConnection(std::move(sqlite3));
		session.mapClass<Task>("Task");

		try
		{
			Wt::Dbo::Transaction transaction(session);
			session.createTables();
		}
		catch (std::exception& ex)
		{
			std::cerr <<"Table already exists."<<std::endl<<ex.what() << endl;
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}
}

void Tasksdb::AddTask(std::string taskDesc)
{
	Wt::Dbo::Transaction transaction(session);

	auto task = std::make_unique<Task>();
	task->desc = taskDesc;

	Wt::Dbo::ptr<Task> TaskPtr = session.add(std::move(task));
}

std::vector<std::string> Tasksdb::GetTasks()
{
	std::vector<std::string> vectasks;
	using Tasks = Wt::Dbo::collection<Wt::Dbo::ptr<Task>>;

	try
	{
		auto sqlite3 = std::make_unique<Wt::Dbo::backend::Sqlite3>("tasks.db");

		Wt::Dbo::Transaction transaction(session);

		Tasks tasks = session.find<Task>();

		vectasks.reserve(tasks.size());
		std::cerr << "----------------------------------" << std::endl;
		std::cerr << "You have " << tasks.size() << " Tasks:" << std::endl;
		
		for (const Wt::Dbo::ptr<Task>& task : tasks) {
			std::cerr <<task->desc<<std::endl;
			vectasks.push_back(task->desc);
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}
	return vectasks;
}
