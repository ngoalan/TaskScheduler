#ifndef USER
#define USER

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Task.h"
#include "TaskList.h"

using namespace std;

class User {
  public:
    User();
    User(string username);

    string getUsername() {return username;}

    void loadData(string filename);

    void createTask();
    void createTaskList();

    void displayTasks();
    void displayTaskTitles();
    void displayDetailsOfTask(const string& taskTitle);

    void displayTaskLists() const;
    void displayTaskList(const string& taskListTitle) const;
    void displayTasksByClassification(const string& classification) const;

    void editTask(const string& taskTitle);
    void editTaskList(const string& taskTitle);
    void addTaskToList(const string& taskListTitle, const string& taskTitle);

    void deleteTask(const string& taskTitle);
    void deleteTaskList(const string& taskListTitle);
    void removeTaskFromList(const string& taskListTitle, const string& taskTitle, bool calledFromMenu);

    void saveAndExit();
  private:
    string username;
    vector<Task*> tasks;
    vector<TaskList*> taskLists;
};

#endif