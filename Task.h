#pragma once
#include <string>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WString.h>
using namespace std;

class Task
{
public:
	//int num;
	std::string desc;
	int status;
	Task();
	Task(/*int id,*/ std::string taskdesc, int status);
	template<class Action>
	void persist(Action& a)
	{
		//Wt::Dbo::field(a, num, "num");
		Wt::Dbo::field(a, desc, "desc");
		Wt::Dbo::field(a, status, "status");
	}
};

