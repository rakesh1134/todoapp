#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/Dbo/Dbo.h>
#include <string>
#include "Tasksdb.h"
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);


private:
    //Wt::WLineEdit* taskDesc_;
    //Wt::WText* taskDesc_;
    Tasksdb tasksDB;
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Tasks");
    tasksDB.connect();

    Wt::WPushButton* buttonAddTask = root()->addNew<Wt::WPushButton>("Add Task");
    Wt::WLineEdit* taskDesc = root()->addNew<Wt::WLineEdit>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WBreak>();

    Wt::WPushButton* buttonShowTaks = root()->addNew<Wt::WPushButton>("Show Tasks");

    Wt::WTable* tasksTable = root()->addNew<Wt::WTable>();

    auto showtasks = [this, tasksTable] {
        tasksTable->clear();
        //tasksTable->setMargin(Wt::WLength::Auto, Wt::Side::Left | Wt::Side::Right);
        tasksTable->setHeaderCount(1);
        //tasksTable->setWidth(Wt::WLength("100%"));
        tasksTable->elementAt(0, 0)->addNew<Wt::WText>("Task #");
        std::vector<std::string> tasks = tasksDB.GetTasks();
        int num = 1;
        for (std::string s : tasks)
        {
            tasksTable->elementAt(num++, 0)->addNew<Wt::WText>(s);
        }

    };

    auto addtask = [this,taskDesc,showtasks] {
        Wt::WString strTask = taskDesc->text();
        tasksDB.AddTask(strTask.toUTF8());
        showtasks();
    };
    buttonAddTask->clicked().connect(addtask);

    
    buttonShowTaks->clicked().connect(showtasks);

}


int main(int argc, char** argv)
{

    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<HelloApplication>(env);
        });
}