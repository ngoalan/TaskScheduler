#ifndef TASK
#define TASK
#include <string>
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;


class Task {
  public:
    Task();
    Task(const string&, const int);
    void displayInfo();
    void editTask(const vector<Task*>& tasks);

    void setId(int _id) {id = _id;}
    void setTitle(const string& _title) {title = _title;}
    void setDescription(const string& _description) {description = _description;}
    void setClassification(const string& _classification);
    void setPriority(int _priority) {priority = _priority;}
    void setDuration(int _duration) {duration = _duration;}
    void setDueDate(const string& _dueDate) {dueDate = _dueDate;}

    int getId() const {return id;}
    string getTitle() const {return title;}
    string getDescription() const {return description;}
    string getClassification() const {return classification;}
    int getPriority() const {return priority;}
    int getDuration() const {return duration;}
    string getDueDate() const {return dueDate;}

  private:
    int id;
    string title;
    string description;
    string classification;
    int priority;
    int duration;
    string dueDate;
};

#endif