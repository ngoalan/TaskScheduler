#include "User.h"

template <typename T>
void uPromptUser(const string& prompt, T& input) {
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

void uPromptUserString(const string& prompt, string& input) {
    cout << prompt;
    
    getline(cin, input);
    
    return;
}

User::User() {

}

User::User(string username) {
    this->username = username;
}

void User::loadData(string filename) {
    int numTasks, numTaskLists, numTasksInList;
    string title, description, classification, dueDate;
    int id, priority, duration;
    Task* newTask = nullptr;
    TaskList* newTaskList = nullptr;

    cout << "Loading data..." << endl;

    ifstream inFile(filename);
    if (!(inFile >> numTasks)) {
        cout << "Done!" << endl;
        return;
    }
    inFile >> numTaskLists;
    inFile.ignore(1000, '\n');

    for (int i = 0; i < numTasks; i++) {
        inFile >> id;
        inFile.ignore(1000, '\n');
        getline(inFile, title);
        getline(inFile, description);
        getline(inFile, classification);
        inFile >> priority;
        inFile >> duration;
        inFile.ignore(1000, '\n');
        getline(inFile, dueDate);

        newTask = new Task(title, id);
        newTask->setDescription(description);
        newTask->setClassification(classification);
        newTask->setPriority(priority);
        newTask->setDuration(duration);
        newTask->setDueDate(dueDate);

        tasks.push_back(newTask);
    }

    for (int i = 0; i < numTaskLists; i++) {
        getline(inFile, title);
        getline(inFile, description);

        newTaskList = new TaskList(title);
        newTaskList->setDescription(description);

        inFile >> numTasksInList;
        for (int j = 0; j < numTasksInList; j++) {
            inFile >> id;
            for (int k = 0; k < numTasks; k++) {
                if (tasks[k]->getId() == id) {
                    newTaskList->addTaskToList(tasks[k]);
                    break;
                }
            }
        }

        taskLists.push_back(newTaskList);
    }

    cout << "Done!" << endl;

    return;
}


void User::createTask() {
    string taskTitle;

    uPromptUserString("Title: ", taskTitle);
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i]->getTitle() == taskTitle)
        {
            cout << "An existing task already has that title. Please try again." << endl;
            return;
        }
    }

    Task* newTask = new Task(taskTitle, tasks.size());
    string sTaskMember;
    int iTaskMember;

    uPromptUserString("Description: ", sTaskMember);
    newTask->setDescription(sTaskMember);

    uPromptUserString("Classification: ", sTaskMember);
    newTask->setClassification(sTaskMember);

    uPromptUser<int>("Priority (1 - 10, 10 being highest priority, put 0 if no priority): ", iTaskMember);
    while (iTaskMember < 0 || iTaskMember > 10)
    {
        cout << "Priority must be between 1 and 10." << endl;
        uPromptUser<int>("Priority (1 - 10, 10 being highest priority, put 0 if no priority): ", iTaskMember);
    }
    newTask->setPriority(iTaskMember);

    uPromptUser<int>("Duration (in days, put 0 if no duration): ", iTaskMember);
    while (iTaskMember < 0)
    {
        cout << "Duration must be greater or equal than 0." << endl;
        uPromptUser<int>("Duration (in days, put 0 if no duration): ", iTaskMember);
    }
    newTask->setDuration(iTaskMember);

    uPromptUserString("Due date: ", sTaskMember);
    newTask->setDueDate(sTaskMember);

    tasks.push_back(newTask);

    return;
}

void User::createTaskList() {
    string taskListTitle;
    string taskListDescription;
    
    uPromptUserString("Title: ", taskListTitle);

    TaskList* newList = new TaskList(taskListTitle);
    uPromptUserString("Description: ", taskListDescription);

    newList->setDescription(taskListDescription);
    taskLists.push_back(newList);
}


void User::displayTasks() {
    sort(tasks.begin(), tasks.end(), [](const Task* lhs, const Task* rhs )
    {
        return lhs->getPriority() < rhs->getPriority();
    });

    string temp;
    cout << endl;
    if (tasks.empty()) {
        cout << "You have no tasks." << endl;
        uPromptUserString("Press enter to continue...", temp);
        return;
    }

    cout << "******************" << endl;
    for (int i = 0; i < tasks.size(); i++)
    {
        cout << endl;
        tasks[i]->displayInfo();
        cout << "******************" << endl;
    }

    uPromptUserString("Press enter to continue...", temp);

    return;
}

void User::displayTaskTitles() {
    string temp;
    sort(tasks.begin(), tasks.end(), [](const Task* lhs, const Task* rhs )
    {
        return lhs->getPriority() < rhs->getPriority();
    });

    cout << endl;
    if (tasks.empty()) {
        cout << "You have no tasks." << endl;
        uPromptUserString("Press enter to continue...", temp);
        return;
    }

    for (int i = 0; i < tasks.size(); i++)
    {
        cout << " - " << tasks[i]->getTitle() << endl;;
    }
    cout << endl;
    uPromptUserString("Press enter to continue...", temp);

    return;
}

void User::displayDetailsOfTask(const string& taskTitle) {
    string temp;
    cout << endl;
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i]->getTitle() == taskTitle)
        {
            tasks[i]->displayInfo();
            uPromptUserString("Press enter to continue...", temp);
            return;
        }
    }

    cout << "No task of the specified name was found." << endl;
    uPromptUserString("Press enter to continue...", temp);

    return;
}

void User::displayTaskLists() const {
    string temp;
    cout << endl;
    if (taskLists.empty()) {
        cout << "You have no task lists." << endl;
        uPromptUserString("Press enter to continue...", temp);
    }

    for (int i = 0; i < taskLists.size(); i++)
    {
        
        cout << " - " << taskLists[i]->getTitle() << endl;
    }
    cout << endl;
    uPromptUserString("Press enter to continue...", temp);

    return;
}

void User::displayTaskList(const string& _taskListTitle) const {
    string temp;
    cout << endl;
    if (taskLists.empty()) {
        cout << "You have no task lists." << endl;
        uPromptUserString("Press enter to continue...", temp);
        return;
    }
    for (int i = 0; i < taskLists.size(); i++)
    {
        if (taskLists[i]->getTitle() == _taskListTitle)
        {
            taskLists[i]->displayTaskTitles();
            uPromptUserString("Press enter to continue...", temp);
            return;
        }
    }

    cout << "No task list of the specified name was found." << endl;
    uPromptUserString("Press enter to continue...", temp);

    return;
}

void User::displayTasksByClassification(const string& _classification) const {
    string temp;
    if (tasks.empty()) {
        cout << "You have no tasks." << endl;
        uPromptUserString("Press enter to continue...", temp);
        return;
    }

    string lowerInputClassification = _classification;
    string lowerTaskClassification;
    bool taskWithClassFound = false;
    cout << endl;
    for (int i = 0; i < lowerInputClassification.length(); i++){
        lowerInputClassification[i] = tolower(lowerInputClassification[i]);
    }
    
    for(int i = 0; i < tasks.size(); i++){
        lowerTaskClassification = tasks[i]->getClassification();
        for (int i = 0; i < lowerTaskClassification.length(); i++){
            lowerTaskClassification[i] = tolower(lowerTaskClassification[i]);
        }

        if(lowerTaskClassification == lowerInputClassification){
            cout << " - " << tasks[i]->getTitle() << endl;
            taskWithClassFound = true;
        }
    }

    if (!taskWithClassFound) cout << "No tasks with this classification was found." << endl;
    cout << endl;
    uPromptUserString("Press enter to continue...", temp);
}

void User::editTask(const string& taskTitle) {
    cout << endl;
    string temp;
    if (tasks.empty()) {
        cout << "You have no tasks." << endl;
        uPromptUserString("Press enter to continue...", temp);
    }

    for (int i = 0; i < tasks.size(); i++) {
        if (taskTitle == tasks[i]->getTitle()) {
            tasks[i]->editTask(tasks);
            return;
        }
    }

    cout << "No task of the specified name was found." << endl;
    return;
}

void User::editTaskList(const string& taskTitle) {
    string temp;
    cout << endl;
    if (taskLists.empty()) {
        cout << "You have no task lists." << endl;
        uPromptUserString("Press enter to continue...", temp);
    }

    for (int i = 0; i < taskLists.size(); i++) {
        if (taskTitle == taskLists[i]->getTitle()) {
            taskLists[i]->editTaskList(taskLists);
            return;
        }
    }

    cout << "No task list of the specified name was found." << endl;
    return;
}

void User::addTaskToList(const string& taskListTitle, const string& taskTitle) {
    string temp;
    if (taskLists.empty()) {
        cout << "You have no task lists." << endl;
        uPromptUserString("Press enter to continue...", temp);
    }

    for(int i = 0; i < taskLists.size(); i++){
        if(taskLists[i]->getTitle() == taskListTitle){
            for(int j = 0; j < tasks.size(); j++){
                if(tasks[j]->getTitle() == taskTitle){
                    taskLists[i]->addTaskToList(tasks[j]);
                    uPromptUserString("Press enter to continue...", temp);
                    return;
                }
            }
            
            cout << "No task of the specified name was found." << endl;
            uPromptUserString("Press enter to continue...", temp);
            return;
        }
    }
    
    cout << "No task list of the specified name was found." << endl;
}


void User::deleteTask(const string& taskTitle) {
    string temp;
    if (tasks.empty()) {
        cout << "You have no tasks." << endl;
        uPromptUserString("Press enter to continue...", temp);
    }
    cout << endl;
    
    Task* taskToDelete = nullptr;
    int currId;
    for(int i=0; i < tasks.size(); i++){
        if (tasks[i]->getTitle()==taskTitle){
            taskToDelete = tasks[i];
            tasks.erase(tasks.begin() + i);

            for (int i = 0; i < tasks.size(); i++) {
                currId = tasks[i]->getId();
                if (currId > taskToDelete->getId()) {
                    tasks[i]->setId(currId - 1);
                }
            }

            break;
        }
    }

    if (taskToDelete) {
        for (int i = 0; i < taskLists.size(); i++) {
            removeTaskFromList(taskLists[i]->getTitle(), taskToDelete->getTitle(), false);
        }
    } else {
        cout << "No task of the specified name was found." << endl;
        cout << endl;
        uPromptUserString("Press enter to continue...", temp);
        return;
    }
    cout << "Task succesfully deleted." << endl;
    delete taskToDelete;
    cout << endl;
    uPromptUserString("Press enter to continue...", temp);
}

void User::deleteTaskList(const string& taskListTitle) {
    TaskList* listToDelete;
    string temp;
    cout << endl;

    for(int i=0; i < taskLists.size(); i++){
        if(taskLists[i]->getTitle() == taskListTitle){
            listToDelete = taskLists[i];
            taskLists.erase(taskLists.begin() + i);
            delete listToDelete;
            cout << "Task list succesfully deleted." << endl;
            cout << endl;
            uPromptUserString("Press enter to continue...", temp);
            return;
        }
    }
    cout << "No task list of the specified name was found." << endl;
    cout << endl;
    uPromptUserString("Press enter to continue...", temp);
    
}

void User::removeTaskFromList(const string& taskListTitle, const string& taskTitle, bool calledFromMenu) {
    string temp;
    cout << endl;
    for(int i=0; i < taskLists.size(); i++){
        if(taskLists[i]->getTitle() == taskListTitle){
            bool succesfulRemoval = taskLists[i]->removeTaskFromList(taskTitle);
            
            if (calledFromMenu) {
                succesfulRemoval ? 
                cout << "Task succesfully removed from the list" << endl :
                cout << "No task of the specified name was found in the list." << endl;
                uPromptUserString("Press enter to continue...", temp);
            }
            return;
        }
    }
    cout << "No task list of the specified name was found." << endl;
    cout << endl;
    uPromptUserString("Press enter to continue...", temp);
    return;
}

void User::saveAndExit() {
    string filename = "./database/" + username + ".txt";
    int numTasks = tasks.size(), numTaskLists = taskLists.size();
    Task* task = nullptr;
    TaskList* taskList = nullptr;
    vector<int> taskIds;

    cout << "Saving data..." << endl;

    ofstream outFile(filename);
    outFile << numTasks << " " << numTaskLists << endl;

    for (int i = 0; i < numTasks; i++) {
        task = tasks[i];
        outFile << task->getId() << endl;
        outFile << task->getTitle() << endl;
        outFile << task->getDescription() << endl;
        outFile << task->getClassification() << endl;
        outFile << task->getPriority() << endl;
        outFile << task->getDuration() << endl;
        outFile << task->getDueDate() << endl;
    }

    for (int i = 0; i < numTaskLists; i++) {
        taskList = taskLists[i];
        outFile << taskList->getTitle() << endl;
        outFile << taskList->getDescription() << endl;

        taskIds = taskList->getTaskListIds();
        outFile << taskIds.size() << endl;
        for (int j = 0; j < taskIds.size(); j++) {
            outFile << taskIds[j] << " ";
        }
        outFile << endl;
    }

    cout << "Done!" << endl;

    return;
}
