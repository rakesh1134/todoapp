#include "Task.h"


Task::Task()
{
//	num = -1;
	desc = "";
	status = 0;
}
Task::Task(/*int _num,*/ std::string _taskdesc, int _status)
{
//	num = _num;
	desc = _taskdesc;
	status = _status;
}

