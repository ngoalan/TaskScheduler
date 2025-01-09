#ifndef TASKLIST
#define TASKLIST

#include "Task.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class TaskList {
  public:
    TaskList();
    TaskList(const string& title);
    void addTaskToList(Task* task);
    void displayTaskTitles();
    void displayAllTasks();
    void editTaskList(const vector<TaskList*>& taskLists);
    bool removeTaskFromList(const string& taskTitle);

    void setTitle(const string& _title) {title = _title;}
    void setDescription(const string& _description) {description = _description;}

    string getTitle() const {return title;}
    string getDescription() const {return description;}
    vector<int> getTaskListIds() const {
        vector<int> taskIds;
        for (int i = 0; i < tasks.size(); i++) {
            taskIds.push_back(tasks[i]->getId());
        }
        return taskIds;
    }

    bool taskInList(const Task* task) const;

  private:
    string title;
    string description;
    vector<Task*> tasks;
};

#endif