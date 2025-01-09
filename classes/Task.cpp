#include "Task.h"

template <typename T>
void tPromptUser(const string& prompt, T& input) {
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

void tPromptUserString(const string& prompt, string& input) {
    cout << prompt;
    
    getline(cin, input);
    return;
}

Task::Task() {

}

Task::Task(const string& _title, const int _id) {
    title = _title;
    id = _id;
}

void Task::displayInfo() {
    cout << "Title: " << getTitle() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Classification: " << getClassification() << endl;
    cout << "Priority: " << getPriority() << endl;
    cout << "Duration: " << getDuration() << endl;
    cout << "Due date: " << getDueDate() << endl;
    cout << endl;

    return;
}


void Task::setClassification(const string& _classification){
    string lowerClassification = _classification;
    for (int i = 0; i < lowerClassification.length(); i++){
        lowerClassification[i] = tolower(lowerClassification[i]);
    }
    classification = lowerClassification;
}


void Task::editTask(const vector<Task*>& tasks) {
    string elementToChange;
    string sTaskMember;
    int iTaskMember;
    bool titleFound = false;

    do {
        cout << "\n\n\n\n\n\n" << endl;;
        titleFound = false;
        displayInfo();
        cout << endl;

        tPromptUserString("What would you like to change? (put \"*\" if you are done editing): ", elementToChange);
        for (int i = 0; i < elementToChange.length(); i++)
        {
            elementToChange[i] = tolower(elementToChange[i]);
        }
        
        if (elementToChange == "title") {   
            tPromptUserString("New title: ", sTaskMember); 
            for (int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i]->getTitle() == sTaskMember)
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
            tPromptUserString("New description: ", sTaskMember); 
            setDescription(sTaskMember);
        } else if (elementToChange == "classification") {
            tPromptUserString("New classification: ", sTaskMember); 
            setClassification(sTaskMember);
        } else if (elementToChange == "priority") {
            tPromptUser("New priority (1 - 10, 10 being highest priority, put 0 if no priority): ", iTaskMember); 
            while (iTaskMember < 0 || iTaskMember > 10)
            {
                cout << "Priority must be between 1 and 10." << endl;
                tPromptUser<int>("Priority (1 - 10, 10 being highest priority, put 0 if no priority): ", iTaskMember);
            }
            setPriority(iTaskMember);
        } else if (elementToChange == "duration") {
            tPromptUser("New duration: ", iTaskMember); 
            setDuration(iTaskMember);
        } else if (elementToChange == "due date") {
            tPromptUserString("New due date: ", sTaskMember); 
            setDueDate(sTaskMember);
        } else if (elementToChange == "*") {
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    } while (elementToChange != "*");
    
}




