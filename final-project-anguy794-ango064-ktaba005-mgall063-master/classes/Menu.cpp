#include "Menu.h"
#include <fstream>

template <typename T>
void promptUser(const string& prompt, T& input) {
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

void promptUserString(const string& prompt, string& input) {
    cout << prompt;
    
    getline(cin, input);
    
    
    return;
}

Menu::Menu() {
    user = nullptr;
}

bool Menu::displayLoginMenu(User* _user) {
    cout << "Welcome!" << endl;
    cout << "1. Enter an existing username" << endl;
    cout << "2. Create a new user" << endl;

    int choice = 0;
    promptUser<int>("Enter a choice: ", choice);
    while (choice != 1 && choice != 2)
        promptUser<int>("Enter a choice: ", choice);

    string username, currUser;
    int numUsers = 0;
    vector<string> users;

    ifstream inFile;
    inFile.open("./database/Users.txt");

    if (inFile.is_open()) {
        inFile >> numUsers;
        for (int i = 0; i < numUsers; i++) {
            inFile >> currUser;
            users.push_back(currUser);
        }
        inFile.close();
    } else {
        cout << "File not found" << endl;
        return false;
    }
    
    
    if (choice == 1) {
        promptUser("Username: ", username);
        if (find(users.begin(), users.end(), username) == users.end()) {
            cout << "User not found." << endl;
            return true;
        } else if (username == "Users") {
            cout << "Username cannot be \"Users\"" << endl;
            return true;
        } else {
            _user = new User(username);
            user = _user;
            string fileName = "./database/" + username + ".txt";
            user->loadData(fileName);
            return false;
        }
    }
    else {
        promptUserString("Enter new username: ", username);
        if (find(users.begin(), users.end(), username) != users.end()) {
            cout << "Username is already taken." << endl;
            return true;
        } else {
            string fileName = "./database/" + username + ".txt";
            ofstream outFile(fileName);
            outFile.close();
            users.push_back(username);

            fileName = "./database/Users.txt";
            outFile.open(fileName);
            if (outFile.is_open()) {
                outFile << users.size();
                for (int i = 0; i < users.size(); i++) {
                    outFile << " " << users[i];
                }
                cout << "User succesfully created." << endl;
            } else {
                cout << "User file not open" << endl;
            }
            
            return true;
        }
    }

    return false;
}

bool Menu::displayMainMenu() {
    cout << "-------Task scheduler for " << user->getUsername() << "-------" <<endl;
    cout << "1. Display all tasks" << endl;
    cout << "2. Display all task titles" << endl;
    cout << "3. Display details of a task" << endl;
    cout << "4. Display all task list titles" << endl;
    cout << "5. Display tasks by classification" << endl;
    cout << "6. Display a task list" << endl;
    cout << endl;
    cout << "7. Create a task" << endl;
    cout << "8. Create a task list" << endl;
    cout << "9. Add a task to a task list" << endl;
    cout << endl;
    cout << "10. Edit a task" << endl;
    cout << "11. Edit a task list" << endl;
    cout << endl;
    cout << "12. Remove a task from a task list" << endl;
    cout << "13. Delete a task" << endl;
    cout << "14. Delete a task list" << endl;
    cout << endl;
    cout << "15. Save and exit" << endl;
    cout << "----------------------------------";
    for (int i = 0; i < user->getUsername().length(); i++)
    {
        cout << "-";
    }
    cout << endl;
    int choice;
    promptUser<int>("Enter a choice: ", choice);
    while (choice < 0 || choice > 15)
        promptUser<int>("Enter a choice: ", choice);
    
    string taskTitle, taskListTitle, classification;
    switch(choice)
    {
        case 1:
            user->displayTasks();
            break;
        case 2:
            user->displayTaskTitles();
            break;
        case 3:
            promptUserString("Enter the title of the task list you would see the details of: ", taskTitle);
            user->displayDetailsOfTask(taskTitle);
            break;
        case 4:
            user->displayTaskLists();
            break;
        case 5:
            promptUserString("Enter classification: ", classification);
            user->displayTasksByClassification(classification);
            break;
        case 6:
            promptUserString("Enter the title of the task list you would like to display: ", taskListTitle);
            user->displayTaskList(taskListTitle);
            break;
        case 7:
            user->createTask();
            break;
        case 8:
            user->createTaskList();
            break;
        case 9:
            promptUserString("Enter the title of the task list you would like to add to: ", taskListTitle);
            promptUserString("Enter the title of the task you would like to add: ", taskTitle);
            user->addTaskToList(taskListTitle, taskTitle);
            break;
        case 10:
            promptUserString("Enter the title of the task you would like to edit: ", taskTitle);
            user->editTask(taskTitle);
            break;
        case 11:
            promptUserString("Enter the title of the task list you would like to edit: ", taskListTitle);
            user->editTaskList(taskListTitle);
            break;
        case 12:
            promptUserString("Enter the title of the task list you would like to remove from: ", taskListTitle);
            promptUserString("Enter the title of the task you would like to remove: ", taskTitle);
            user->removeTaskFromList(taskListTitle, taskTitle, true);
            break;
        case 13:
            promptUserString("Enter the title of the task you would like to delete: ", taskTitle);
            user->deleteTask(taskTitle);
            break;
        case 14:
            promptUserString("Enter the title of the task list you would like to delete: ", taskListTitle);
            user->deleteTaskList(taskListTitle);
            break;
        case 15:
            user->saveAndExit();
            return false;
        default:
            cout << "Error in switch" << endl;
            return false;
    }

    return true;
}
