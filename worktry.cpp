#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <Windows.h>

using namespace std;

const string DATA_FILE = "employees_data.txt";

struct Employee {
    string type;
    string fullName;
    string hireDate;
    string position;
    int departmentID;
    int experience;
    double salaryOrRate;
    int hoursOrSickDays;
};

vector<Employee> employees;

void loadData() {
    ifstream file(DATA_FILE);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Employee emp;
            stringstream ss(line);
            getline(ss, emp.type, ';');
            getline(ss, emp.fullName, ';');
            getline(ss, emp.hireDate, ';');
            getline(ss, emp.position, ';');
            ss >> emp.departmentID; ss.ignore();
            ss >> emp.experience; ss.ignore();
            ss >> emp.salaryOrRate; ss.ignore();
            ss >> emp.hoursOrSickDays;
            employees.push_back(emp);
        }
        file.close();
        cout << "Дані завантажено." << endl;
    }
    else {
        cout << "Не вдалося відкрити файл." << endl;
    }
}

void saveData() {
    ofstream file(DATA_FILE);
    if (file.is_open()) {
        for (const auto& emp : employees) {
            file << emp.type << ";" << emp.fullName << ";" << emp.hireDate << ";"
                << emp.position << ";" << emp.departmentID << ";" << emp.experience << ";"
                << emp.salaryOrRate << ";" << emp.hoursOrSickDays << endl;
        }
        file.close();
        cout << "Дані збережено." << endl;
    }
    else {
        cout << "Не вдалося зберегти дані." << endl;
    }
}

void viewEmployees() {
    for (const auto& emp : employees) {
        cout << emp.type << " | " << emp.fullName << " | " << emp.hireDate << " | "
            << emp.position << " | Відділ: " << emp.departmentID << " | Досвід: "
            << emp.experience << " | Оплата/Ставка: " << emp.salaryOrRate
            << " | Години/Лікарняні: " << emp.hoursOrSickDays << endl;
    }
}

void addEmployee() {
    Employee emp;
    cout << "Введіть тип (Hourly/Salaried): "; cin >> emp.type;
    cin.ignore();
    cout << "Введіть ПІБ: "; getline(cin, emp.fullName);
    cout << "Введіть дату найму: "; getline(cin, emp.hireDate);
    cout << "Введіть посаду: "; getline(cin, emp.position);
    cout << "Введіть ID відділу: "; cin >> emp.departmentID;
    cout << "Введіть стаж: "; cin >> emp.experience;
    cout << "Введіть оплату/ставку: "; cin >> emp.salaryOrRate;
    cout << "Введіть відпрацьовані години/лікарняні: "; cin >> emp.hoursOrSickDays;
    employees.push_back(emp);
    cout << "Працівника додано." << endl;
}

void deleteEmployee() {
    string fullName;
    cin.ignore();
    cout << "Введіть ПІБ для видалення: "; getline(cin, fullName);
    auto it = remove_if(employees.begin(), employees.end(),
        [&fullName](const Employee& emp) { return emp.fullName == fullName; });
    if (it != employees.end()) {
        employees.erase(it, employees.end());
        cout << "Працівника видалено." << endl;
    }
    else {
        cout << "Працівника не знайдено." << endl;
    }
}

void findEmployeeByName() {
    string fullName;
    cin.ignore();
    cout << "Введіть ПІБ для пошуку: "; getline(cin, fullName);
    for (const auto& emp : employees) {
        if (emp.fullName == fullName) {
            cout << "Знайдено: " << emp.fullName << " | Посада: " << emp.position << endl;
            return;
        }
    }
    cout << "Працівника не знайдено." << endl;
}

void findEmployeesByPosition() {
    string position;
    cin.ignore();
    cout << "Введіть посаду для пошуку: "; getline(cin, position);
    for (const auto& emp : employees) {
        if (emp.position == position) {
            cout << emp.fullName << " | Відділ: " << emp.departmentID << endl;
        }
    }
}
void findEmployeesByDepartment() {
    int departmentID;
    cout << "Введіть ID відділу: ";
    cin >> departmentID;
    bool found = false;
    for (const auto& emp : employees) {
        if (emp.departmentID == departmentID) {
            cout << emp.fullName << " | Посада: " << emp.position << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Працівників у цьому відділі не знайдено." << endl;
    }
}

void calculateAverageSalaryByDepartment() {
    int departmentID;
    cout << "Введіть ID відділу: ";
    cin >> departmentID;
    double totalSalary = 0.0;
    int count = 0;

    for (const auto& emp : employees) {
        if (emp.departmentID == departmentID) {
            double salary = (emp.type == "Hourly")
                ? emp.salaryOrRate * emp.hoursOrSickDays
                : emp.salaryOrRate - (emp.hoursOrSickDays * 500);
            totalSalary += salary;
            count++;
        }
    }

    if (count > 0) {
        cout << "Середня зарплата у відділі " << departmentID << ": "
            << totalSalary / count << endl;
    }
    else {
        cout << "У цьому відділі немає працівників." << endl;
    }
}

void sortEmployeesByName() {
    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.fullName < b.fullName;
        });
    cout << "Працівників відсортовано за іменем." << endl;
}

void sortEmployeesBySalary() {
    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        double salaryA = (a.type == "Hourly")
            ? a.salaryOrRate * a.hoursOrSickDays
            : a.salaryOrRate - (a.hoursOrSickDays * 500);
        double salaryB = (b.type == "Hourly")
            ? b.salaryOrRate * b.hoursOrSickDays
            : b.salaryOrRate - (b.hoursOrSickDays * 500);
        return salaryA > salaryB;
        });
    cout << "Працівників відсортовано за зарплатою." << endl;
}

void calculateSalary() {
    string fullName;
    cin.ignore();
    cout << "Введіть ПІБ для розрахунку зарплати: "; getline(cin, fullName);
    for (const auto& emp : employees) {
        if (emp.fullName == fullName) {
            if (emp.type == "Hourly") {
                cout << "Зарплата: " << emp.salaryOrRate * emp.hoursOrSickDays << endl;
            }
            else {
                cout << "Зарплата: " << emp.salaryOrRate - (emp.hoursOrSickDays * 500) << endl;
            }
            return;
        }
    }
    cout << "Працівника не знайдено." << endl;
}

void updateHoursOrSickDays() {
    string fullName;
    int value;
    cin.ignore();
    cout << "Введіть ПІБ для оновлення даних: "; getline(cin, fullName);
    cout << "Введіть нове значення (години/лікарняні): "; cin >> value;
    for (auto& emp : employees) {
        if (emp.fullName == fullName) {
            emp.hoursOrSickDays = value;
            cout << "Дані оновлено." << endl;
            return;
        }
    }
    cout << "Працівника не знайдено." << endl;
}

void updateEmployeeInfo() {
    string fullName;
    cin.ignore();
    cout << "Введіть ПІБ працівника для оновлення інформації: ";
    getline(cin, fullName);

    for (auto& emp : employees) {
        if (emp.fullName == fullName) {
            int choice;
            do {
                cout << "\nЩо ви хочете змінити?\n";
                cout << "1. Тип (Hourly/Salaried)\n";
                cout << "2. ПІБ\n";
                cout << "3. Дата найму\n";
                cout << "4. Посада\n";
                cout << "5. ID відділу\n";
                cout << "6. Стаж\n";
                cout << "7. Оплата/Ставка\n";
                cout << "8. Відпрацьовані години/Лікарняні\n";
                cout << "0. Вийти\n";
                cout << "Ваш вибір: ";
                cin >> choice;

                cin.ignore(); // Очищення потоку вводу
                switch (choice) {
                case 1:
                    cout << "Введіть новий тип (Hourly/Salaried): ";
                    cin >> emp.type;
                    break;
                case 2:
                    cout << "Введіть нове ПІБ: ";
                    getline(cin, emp.fullName);
                    break;
                case 3:
                    cout << "Введіть нову дату найму: ";
                    getline(cin, emp.hireDate);
                    break;
                case 4:
                    cout << "Введіть нову посаду: ";
                    getline(cin, emp.position);
                    break;
                case 5:
                    cout << "Введіть новий ID відділу: ";
                    cin >> emp.departmentID;
                    break;
                case 6:
                    cout << "Введіть новий стаж: ";
                    cin >> emp.experience;
                    break;
                case 7:
                    cout << "Введіть нову оплату/ставку: ";
                    cin >> emp.salaryOrRate;
                    break;
                case 8:
                    cout << "Введіть нові відпрацьовані години/лікарняні: ";
                    cin >> emp.hoursOrSickDays;
                    break;
                case 0:
                    cout << "Оновлення завершено.\n";
                    break;
                default:
                    cout << "Неправильний вибір. Спробуйте ще.\n";
                }
            } while (choice != 0);

            cout << "Інформацію оновлено.\n";
            return;
        }
    }
    cout << "Працівника з таким ПІБ не знайдено.\n";
}

void showMenu() {
    cout << R"(
1. Переглянути всіх працівників
2. Додати нового працівника
3. Видалити працівника
4. Знайти працівника за ПІБ
5. Знайти працівників за посадою
6. Фільтрувати працівників за відділом
7. Аналіз середньої зарплати по відділу
8. Сортувати працівників за іменем
9. Сортувати працівників за зарплатою
10. Змінити посаду працівника
11. Розрахувати заробітну плату
12. Оновити відпрацьовані години/лікарняні дні
13. Змінити інформацію про працівника
14. Зберегти дані у файл
15. Завантажити дані з файлу
0. Вийти з програми
)";
    cout << "Оберіть дію: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    loadData();
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
        case 1: viewEmployees(); break;
        case 2: addEmployee(); break;
        case 3: deleteEmployee(); break;
        case 4: findEmployeeByName(); break;
        case 5: findEmployeesByPosition(); break;
        case 6: findEmployeesByDepartment(); break;
        case 7: calculateAverageSalaryByDepartment(); break;
        case 8: sortEmployeesByName(); break;
        case 9: sortEmployeesBySalary(); break;
        case 11: calculateSalary(); break;
        case 12: updateHoursOrSickDays(); break;
        case 13: updateEmployeeInfo(); break;
        case 14: saveData(); break;
        case 15: loadData(); break;
        case 0: cout << "Програма завершена." << endl; break;
        default: cout << "Неправильний вибір. Спробуйте ще." << endl;
        }
    } while (choice != 0);
    return 0;
}