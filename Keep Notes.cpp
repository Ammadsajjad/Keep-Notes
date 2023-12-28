#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void addTask(string*& arr, bool*& completed, int& size, const string& Task)
{
    string* newArr = new string[size + 1];
    bool* newCompletedArr = new bool[size + 1];

    for (int i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
        newCompletedArr[i] = completed[i];
    }

    newArr[size] = Task;
    newCompletedArr[size] = false;
    size++;

    delete[] arr;
    delete[] completed;

    arr = newArr;
    completed = newCompletedArr;
}

void displayTask(const string* arr, const bool* completed, int size)
{
    cout << "\t\t\t\t\t\t-------------------------------\n";
    cout << "\t\t\t\t\t\t|======== Stored Task ========|" << endl;
    cout << "\t\t\t\t\t\t-------------------------------\n";

    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << ". ";
        if (completed[i]) {
            cout << "[Completed task] ";
        }
        cout << arr[i] << endl;
    }
}

string getUserInput()
{
    string Task;
    cout << "Enter a Task: ";
    getline(cin >> ws, Task);
    return Task;
}

void removeTask(string*& arr, bool*& completed, int& size, int index)
{
    if (index >= 0 && index < size)
    {
        string* newArr = new string[size - 1];
        bool* newCompletedArr = new bool[size - 1];

        for (int i = 0, j = 0; i < size; i++)
        {
            if (i != index)
            {
                newArr[j] = arr[i];
                newCompletedArr[j] = completed[i];
                j++;
            }
        }
        size--;

        delete[] arr;
        delete[] completed;

        arr = newArr;
        completed = newCompletedArr;

        cout << "\t\t\t\t\t\t--------------------------------\n";
        cout << "\t\t\t\t\t\t|======== Task Removed ========|" << endl;
        cout << "\t\t\t\t\t\t--------------------------------\n";
    }
    else
        cout << "\nInvalid index. Please enter a valid index to remove.\n";
}

void markAsCompleted(bool*& completed, int size, int index)
{
    if (index >= 0 && index < size)
    {
        completed[index] = true;
        cout << "\nTask marked as completed.\n";
    }
    else
        cout << "Invalid index. Please enter a valid index to mark as completed.\n";
}

void saveToFile(const string* arr, const bool* completed, int size, const string& filename)
{
    ofstream file(filename);

    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            file << completed[i] << " " << arr[i] << endl;
        }

        cout << "Tasks saved to file: " << filename << endl;

        file.close();
    }
    else
    {
        cout << "Unable to open file: " << filename << endl;
    }
}

void loadFromFile(string*& arr, bool*& completed, int& size, const string& filename)
{
    ifstream file(filename);

    if (file.is_open())
    {
        string task;
        bool isCompleted;

        while (file >> isCompleted >> ws && getline(file, task))
        {
            addTask(arr, completed, size, task);
            completed[size - 1] = isCompleted;
        }

        cout << "Tasks loaded from file: " << filename << endl;

        file.close();
    }
    else
    {
        cout << "Unable to open file: " << filename << endl;
    }
}

int main()
{
    string* Tasks = nullptr;
    bool* completed = nullptr;
    int size = 0;
    int choice;

    const string filename = "tasks.txt";

    loadFromFile(Tasks, completed, size, filename);

    cout << "\t\t\t\t\t\t--------------------------------\n";
    cout << "\t\t\t\t\t\t|========= Keep Notes =========|" << endl;
    cout << "\t\t\t\t\t\t--------------------------------\n";

    do
    {
        cout << "\n1. Add a Task\n";
        cout << "2. Display Task\n";
        cout << "3. Remove a Task\n";
        cout << "4. Mark task as Task\n";
        cout << "5. Save tasks to file\n";
        cout << "6. Quit\n";
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;

        if (choice < 1 || choice > 6)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid choice. Please enter a valid option.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            string Task = getUserInput();
            addTask(Tasks, completed, size, Task);
            break;
        }
        case 2:
        {
            displayTask(Tasks, completed, size);
            break;
        }
        case 3:
        {
            displayTask(Tasks, completed, size);
            int indexToRemove;
            cout << "\nEnter the index of the Task to remove: ";
            cin >> indexToRemove;
            removeTask(Tasks, completed, size, indexToRemove - 1);
            break;
        }
        case 4:
        {
            displayTask(Tasks, completed, size);
            int indexToComplete;
            cout << "\nEnter the index of the task to mark as completed: ";
            cin >> indexToComplete;
            markAsCompleted(completed, size, indexToComplete - 1);
            break;
        }
        case 5:
        {
            saveToFile(Tasks, completed, size, filename);
            break;
        }
        case 6:
            cout << "\nExiting the program.\n";
            break;

        default:
            cout << "\nInvalid choice. Please enter a valid option.\n";
        }

    } while (choice != 6);

    delete[] Tasks;
    delete[] completed;

    return 0;
}
