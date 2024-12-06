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
        cout << "��� �����������." << endl;
    }
    else {
        cout << "�� ������� ������� ����." << endl;
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
        cout << "��� ���������." << endl;
    }
    else {
        cout << "�� ������� �������� ���." << endl;
    }
}

void viewEmployees() {
    for (const auto& emp : employees) {
        cout << emp.type << " | " << emp.fullName << " | " << emp.hireDate << " | "
            << emp.position << " | ³���: " << emp.departmentID << " | �����: "
            << emp.experience << " | ������/������: " << emp.salaryOrRate
            << " | ������/˳������: " << emp.hoursOrSickDays << endl;
    }
}

void addEmployee() {
    Employee emp;
    cout << "������ ��� (Hourly/Salaried): "; cin >> emp.type;
    cin.ignore();
    cout << "������ ϲ�: "; getline(cin, emp.fullName);
    cout << "������ ���� �����: "; getline(cin, emp.hireDate);
    cout << "������ ������: "; getline(cin, emp.position);
    cout << "������ ID �����: "; cin >> emp.departmentID;
    cout << "������ ����: "; cin >> emp.experience;
    cout << "������ ������/������: "; cin >> emp.salaryOrRate;
    cout << "������ ����������� ������/�������: "; cin >> emp.hoursOrSickDays;
    employees.push_back(emp);
    cout << "���������� ������." << endl;
}

void deleteEmployee() {
    string fullName;
    cin.ignore();
    cout << "������ ϲ� ��� ���������: "; getline(cin, fullName);
    auto it = remove_if(employees.begin(), employees.end(),
        [&fullName](const Employee& emp) { return emp.fullName == fullName; });
    if (it != employees.end()) {
        employees.erase(it, employees.end());
        cout << "���������� ��������." << endl;
    }
    else {
        cout << "���������� �� ��������." << endl;
    }
}

void findEmployeeByName() {
    string fullName;
    cin.ignore();
    cout << "������ ϲ� ��� ������: "; getline(cin, fullName);
    for (const auto& emp : employees) {
        if (emp.fullName == fullName) {
            cout << "��������: " << emp.fullName << " | ������: " << emp.position << endl;
            return;
        }
    }
    cout << "���������� �� ��������." << endl;
}

void findEmployeesByPosition() {
    string position;
    cin.ignore();
    cout << "������ ������ ��� ������: "; getline(cin, position);
    for (const auto& emp : employees) {
        if (emp.position == position) {
            cout << emp.fullName << " | ³���: " << emp.departmentID << endl;
        }
    }
}
void findEmployeesByDepartment() {
    int departmentID;
    cout << "������ ID �����: ";
    cin >> departmentID;
    bool found = false;
    for (const auto& emp : employees) {
        if (emp.departmentID == departmentID) {
            cout << emp.fullName << " | ������: " << emp.position << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "���������� � ����� ���� �� ��������." << endl;
    }
}

void calculateAverageSalaryByDepartment() {
    int departmentID;
    cout << "������ ID �����: ";
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
        cout << "������� �������� � ���� " << departmentID << ": "
            << totalSalary / count << endl;
    }
    else {
        cout << "� ����� ���� ���� ����������." << endl;
    }
}

void sortEmployeesByName() {
    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.fullName < b.fullName;
        });
    cout << "���������� ����������� �� ������." << endl;
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
    cout << "���������� ����������� �� ���������." << endl;
}

void calculateSalary() {
    string fullName;
    cin.ignore();
    cout << "������ ϲ� ��� ���������� ��������: "; getline(cin, fullName);
    for (const auto& emp : employees) {
        if (emp.fullName == fullName) {
            if (emp.type == "Hourly") {
                cout << "��������: " << emp.salaryOrRate * emp.hoursOrSickDays << endl;
            }
            else {
                cout << "��������: " << emp.salaryOrRate - (emp.hoursOrSickDays * 500) << endl;
            }
            return;
        }
    }
    cout << "���������� �� ��������." << endl;
}

void updateHoursOrSickDays() {
    string fullName;
    int value;
    cin.ignore();
    cout << "������ ϲ� ��� ��������� �����: "; getline(cin, fullName);
    cout << "������ ���� �������� (������/�������): "; cin >> value;
    for (auto& emp : employees) {
        if (emp.fullName == fullName) {
            emp.hoursOrSickDays = value;
            cout << "��� ��������." << endl;
            return;
        }
    }
    cout << "���������� �� ��������." << endl;
}

void updateEmployeeInfo() {
    string fullName;
    cin.ignore();
    cout << "������ ϲ� ���������� ��� ��������� ����������: ";
    getline(cin, fullName);

    for (auto& emp : employees) {
        if (emp.fullName == fullName) {
            int choice;
            do {
                cout << "\n�� �� ������ ������?\n";
                cout << "1. ��� (Hourly/Salaried)\n";
                cout << "2. ϲ�\n";
                cout << "3. ���� �����\n";
                cout << "4. ������\n";
                cout << "5. ID �����\n";
                cout << "6. ����\n";
                cout << "7. ������/������\n";
                cout << "8. ³���������� ������/˳������\n";
                cout << "0. �����\n";
                cout << "��� ����: ";
                cin >> choice;

                cin.ignore(); // �������� ������ �����
                switch (choice) {
                case 1:
                    cout << "������ ����� ��� (Hourly/Salaried): ";
                    cin >> emp.type;
                    break;
                case 2:
                    cout << "������ ���� ϲ�: ";
                    getline(cin, emp.fullName);
                    break;
                case 3:
                    cout << "������ ���� ���� �����: ";
                    getline(cin, emp.hireDate);
                    break;
                case 4:
                    cout << "������ ���� ������: ";
                    getline(cin, emp.position);
                    break;
                case 5:
                    cout << "������ ����� ID �����: ";
                    cin >> emp.departmentID;
                    break;
                case 6:
                    cout << "������ ����� ����: ";
                    cin >> emp.experience;
                    break;
                case 7:
                    cout << "������ ���� ������/������: ";
                    cin >> emp.salaryOrRate;
                    break;
                case 8:
                    cout << "������ ��� ����������� ������/�������: ";
                    cin >> emp.hoursOrSickDays;
                    break;
                case 0:
                    cout << "��������� ���������.\n";
                    break;
                default:
                    cout << "������������ ����. ��������� ��.\n";
                }
            } while (choice != 0);

            cout << "���������� ��������.\n";
            return;
        }
    }
    cout << "���������� � ����� ϲ� �� ��������.\n";
}

void showMenu() {
    cout << R"(
1. ����������� ��� ����������
2. ������ ������ ����������
3. �������� ����������
4. ������ ���������� �� ϲ�
5. ������ ���������� �� �������
6. Գ��������� ���������� �� ������
7. ����� �������� �������� �� �����
8. ��������� ���������� �� ������
9. ��������� ���������� �� ���������
10. ������ ������ ����������
11. ����������� �������� �����
12. ������� ����������� ������/������� ��
13. ������ ���������� ��� ����������
14. �������� ��� � ����
15. ����������� ��� � �����
0. ����� � ��������
)";
    cout << "������ ��: ";
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
        case 0: cout << "�������� ���������." << endl; break;
        default: cout << "������������ ����. ��������� ��." << endl;
        }
    } while (choice != 0);
    return 0;
}