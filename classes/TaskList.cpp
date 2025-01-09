#include "TaskList.h"

template <typename T>
void lPromptUser(const string& prompt, T& input) {
    cout << prompt;
    cin >> input;
    
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please try again." << endl;
        cout << prompt;
        cin >> input;
    }
    cin.ignore(1000, '\n');
    return;
}

void lPromptUserString(const string& prompt, string& input) {
    cout << prompt;
    
    getline(cin, input);
    return;
}

TaskList::TaskList() {

}

TaskList::TaskList(const string& _title) {
    title = _title;
}

void TaskList::addTaskToList(Task* task) {
    for (int i = 0; i < tasks.size(); i++) {
        if (task->getTitle() == tasks[i]->getTitle()) {
            cout << "This task is already in the list." << endl;
            return;
        }
    }

    tasks.push_back(task);
    cout << "Task succesfully added to the list." << endl;
}

void TaskList::displayTaskTitles() {
    for (int i = 0; i < tasks.size(); i++)
    {
        cout << " - " << tasks[i]->getTitle() << endl;
    }
    
    char choice;
    cout << "Would you like to view the details of each task? (Y or N): ";
    cin >> choice;

    while (choice != 'Y' && choice != 'N')
    {   
        cout << "Please enter Y or N: ";
        cin >> choice;
    }

    cin.ignore(1000, '\n');
    cout << endl;
    if (choice == 'Y') displayAllTasks();

    return;
}

void TaskList::displayAllTasks() {
    if (tasks.empty()) {
        cout << "This list contains no tasks." << endl;
    }
    cout << "******************" << endl;
    for (int i = 0; i < tasks.size(); i++)
    {
        tasks[i]->displayInfo();
        cout << "******************" << endl;
    }
}

void TaskList::editTaskList(const vector<TaskList*>& taskLists){
    string elementToChange;
    string sTaskMember;
    bool titleFound = false;

    do {
        cout << "\n\n\n\n\n\n" << endl;;
        titleFound = false;
        cout << "Title: " << getTitle() << endl;
        cout << "Description: " << getDescription() << endl;
        cout << endl;

        lPromptUserString("What would you like to change? (put \"*\" if you are done editing): ", elementToChange);
        for (int i = 0; i < elementToChange.length(); i++)
        {
            elementToChange[i] = tolower(elementToChange[i]);
        }
        
        if (elementToChange == "title") {   
            lPromptUserString("New title: ", sTaskMember); 
            for (int i = 0; i < taskLists.size(); i++)
            {
                if (taskLists[i]->getTitle() == sTaskMember)
                {
                    cout << "Title not succesfully edited. An existing task already has that title." << endl;
                    titleFound = true;
                    break;
                }
            }

            if (!titleFound) {
                setTitle(sTaskMember);
            }

        } else if (elementToChange == "description") {
            lPromptUserString("New description: ", sTaskMember); 
            setDescription(sTaskMember);
        } else if (elementToChange == "*") {
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    } while (elementToChange != "*");
}


bool TaskList::removeTaskFromList(const string& taskTitle) {
    for(int i=0; i< tasks.size(); i++){
        if(tasks[i]->getTitle() == taskTitle){
            tasks.erase(tasks.begin()+i);
            return true;
        }
    }
    return false;
}

bool TaskList::taskInList(const Task* task) const {
    return find(tasks.begin(), tasks.end(), task) != tasks.end();
}
