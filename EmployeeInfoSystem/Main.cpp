#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
#include <algorithm>

using namespace std;

struct Employee {
    string lastName;
    string firstName;
    int age;
    string position;

    Employee(string lName = "", string fName = "", int a = 0, string pos = "")
        : lastName(lName), firstName(fName), age(a), position(pos) {
    }
};

vector<Employee> employees;
string filename;

string capitalizeFirstLetter(const string& str) {
    if (str.empty()) return str;
    string result = str;
    result[0] = toupper(result[0]);
    transform(result.begin() + 1, result.end(), result.begin() + 1, ::tolower);
    return result;
}

string formatFullName(const string& str) {
    string result = str;
    bool capitalizeNext = true;
    for (size_t i = 0; i < result.size(); ++i) {
        if (capitalizeNext && isalpha(result[i])) {
            result[i] = toupper(result[i]);
            capitalizeNext = false;
        }
        else if (isspace(result[i])) {
            capitalizeNext = true;
        }
        else {
            result[i] = tolower(result[i]);
        }
    }
    return result;
}

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void formatEmployee(Employee& emp) {
    emp.lastName = formatFullName(emp.lastName);
    emp.firstName = formatFullName(emp.firstName);
    emp.position = formatFullName(emp.position);
}

void createFile() {
    ofstream file(filename);
    if (file) {
        cout << "File '" << filename << "' has been created (*ゝω･*)\n";
        file.close();
        system(("notepad " + filename).c_str());
    }
    else {
        cout << "Failed to create file (*T^T)\n";
    }
}

void loadFromFile() {
    ifstream file(filename);
    if (!file) {
        createFile();
        return;
    }

    employees.clear();
    Employee emp;
    while (file >> emp.lastName >> emp.firstName >> emp.age >> emp.position) {
        employees.push_back(emp);
    }
    file.close();
    cout << "Data loaded from " << filename << " (*ゝω･*)" << endl;
}

void saveToFile() {
    ofstream file(filename);
    if (!file) {
        cout << "Error saving to file ( ´-ω-)\n";
        return;
    }
    for (const auto& emp : employees) {
        file << emp.lastName << " " << emp.firstName << " " << emp.age << " " << emp.position << endl;
    }
    file.close();
    cout << "Data saved to " << filename << endl;
}

void handleNotFound(bool found) {
    if (!found) {
        cout << "Employee not found ┐(￣ヘ￣）┌\n";
    }
}

void addEmployee() {
    Employee emp;
    cout << "Enter last name: ";
    cin >> emp.lastName;

    cout << "Enter first name: ";
    cin >> emp.firstName;

    cout << "Enter age: ";
    cin >> emp.age;

    cout << "Enter position: ";
    cin >> emp.position;

    formatEmployee(emp);
    employees.push_back(emp);
    cout << "Employee added ＼(^-^)／\n";
}

void editEmployee() {
    string lastName;
    cout << "Enter last name of employee to edit: ";
    cin >> lastName;
    lastName = toLowerCase(lastName);

    bool found = false;

    for (auto& emp : employees) {
        if (toLowerCase(emp.lastName) == lastName) {
            cout << "Editing " << emp.lastName << " " << emp.firstName << "...\n";
            cout << "Enter new first name: ";
            cin >> emp.firstName;

            cout << "Enter new age: ";
            cin >> emp.age;

            cout << "Enter new position: ";
            cin >> emp.position;

            formatEmployee(emp);
            found = true;
            cout << "Employee updated (>.<)\n";
            break;
        }
    }
    handleNotFound(found);
}

void deleteEmployee() {
    string lastName;
    cout << "Enter last name of employee to delete: ";
    cin >> lastName;
    lastName = toLowerCase(lastName);

    bool found = false;

    for (size_t i = 0; i < employees.size(); ++i) {
        if (toLowerCase(employees[i].lastName) == lastName) {
            employees.erase(employees.begin() + i);
            found = true;
            cout << "Employee deleted (^w^)\n";
            break;
        }
    }
    handleNotFound(found);
}

void searchByLastName() {
    string lastName;
    cout << "Enter last name to search: ";
    cin >> lastName;
    lastName = toLowerCase(lastName);
    bool found = false;

    for (const auto& emp : employees) {
        if (toLowerCase(emp.lastName) == lastName) {
            cout << formatFullName(emp.lastName) << " " << formatFullName(emp.firstName)
                << ", " << emp.age << " y.o., " << formatFullName(emp.position) << endl;
            found = true;
        }
    }
    handleNotFound(found);
}

void searchByAge() {
    int age;
    cout << "Enter age to search: ";
    cin >> age;
    bool found = false;

    for (const auto& emp : employees) {
        if (emp.age == age) {
            cout << formatFullName(emp.lastName) << " " << formatFullName(emp.firstName)
                << ", " << emp.age << " y.o., " << formatFullName(emp.position) << endl;
            found = true;
        }
    }
    handleNotFound(found);
}

void searchByFirstLetter() {
    char letter;
    cout << "Enter the first letter of the last name to search: ";
    cin >> letter;

    letter = tolower(letter);

    bool found = false;

    for (const auto& emp : employees) {
        if (!emp.lastName.empty() && tolower(emp.lastName[0]) == letter) {
            cout << formatFullName(emp.lastName) << " " << formatFullName(emp.firstName)
                << ", " << emp.age << " y.o., " << formatFullName(emp.position) << endl;
            found = true;
        }
    }
    handleNotFound(found);
}

void searchByPosition() {
    string position;
    cout << "Enter position to search: ";
    cin >> position;
    position = toLowerCase(position);
    bool found = false;

    for (const auto& emp : employees) {
        if (toLowerCase(emp.position) == position) {
            cout << formatFullName(emp.lastName) << " " << formatFullName(emp.firstName)
                << ", " << emp.age << " y.o., " << formatFullName(emp.position) << endl;
            found = true;
        }
    }
    handleNotFound(found);
}

void showEmployees() {
    if (employees.empty()) {
        cout << "Employee list empty (´－ω－)人\n";
        return;
    }
    cout << "Employee list:\n";
    for (const auto& emp : employees) {
        cout << formatFullName(emp.lastName) << " " << formatFullName(emp.firstName)
            << ", " << emp.age << " y.o., " << formatFullName(emp.position) << endl;
    }
}

void openFileInNotepad() {
    system(("notepad " + filename).c_str());
}

int main() {
    cout << "Enter filename to save data (without extension .txt): ";
    cin >> filename;
    filename += ".txt";

    loadFromFile();

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "Employee\n";
        cout << "[1] add\n";
        cout << "[2] edit\n";
        cout << "[3] delete\n";
        cout << "Search\n";
        cout << "[4] by last name\n";
        cout << "[5] by age\n";
        cout << "[6] by first letter of last name\n";
        cout << "[7] by position\n";
        cout << "Other\n";
        cout << "[8] show all employees\n";
        cout << "[9] save data to file\n";
        cout << "[10] open file in Notepad\n";
        cout << "[0] exit (auto-save)\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addEmployee(); break;
        case 2: editEmployee(); break;
        case 3: deleteEmployee(); break;
        case 4: searchByLastName(); break;
        case 5: searchByAge(); break;
        case 6: searchByFirstLetter(); break;
        case 7: searchByPosition(); break;
        case 8: showEmployees(); break;
        case 9: saveToFile(); break;
        case 10: openFileInNotepad(); break;
        case 0: saveToFile(); cout << "Exiting! Sayonara (⁠=⁠^⁠･⁠ｪ⁠･⁠^⁠=⁠)\n"; break;
        default: cout << "Invalid choice ( T∀T)\n";
        }
    } while (choice != 0);

    return 0;
}
