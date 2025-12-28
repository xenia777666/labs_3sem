#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Класс "Сотрудник"
class Employee {
private:
    string fullName;        // ФИО
    int personnelNumber;    // табельный номер
    int hoursWorked;        // количество проработанных часов за месяц
    double hourlyRate;      // почасовой тариф

public:
    // Конструктор по умолчанию
    Employee() : personnelNumber(0), hoursWorked(0), hourlyRate(0.0) {}

    // Перегрузка ввода из потока
    friend istream& operator>>(istream& in, Employee& emp);

    // Перегрузка вывода в поток
    friend ostream& operator<<(ostream& out, const Employee& emp);

    friend ifstream& operator>>(ifstream& fin, Employee& emp);

    friend ofstream& operator<<(ofstream& fout, const Employee& emp);

    // Метод для возврата ФИО сотрудников с заданным количеством часов
    static vector<string> findEmployeesByHours(const string& filename, int targetHours);
};

// Перегрузка ввода
istream& operator>>(istream& in, Employee& emp) {
    cout << "Enter Full Name: ";
    in.ignore(); // Очищаем буфер
    getline(in, emp.fullName);

    cout << "Enter Personnel Number: ";
    in >> emp.personnelNumber;

    cout << "Enter Hours Worked: ";
    in >> emp.hoursWorked;

    cout << "Enter Hourly Rate (rub): ";
    in >> emp.hourlyRate;

    return in;
}

// Перегрузка вывода
ostream& operator<<(ostream& out, const Employee& emp) {
    out << setw(30) << left << emp.fullName
        << setw(15) << emp.personnelNumber
        << setw(12) << emp.hoursWorked
        << setw(12) << fixed << setprecision(2) << emp.hourlyRate
        << setw(15) << emp.hourlyRate * emp.hoursWorked << endl;
    return out;
}

// Чтение из файла
ifstream& operator>>(ifstream& fin, Employee& emp) {
    if (!getline(fin, emp.fullName) || emp.fullName.empty()) return fin; // Чтение ФИО
    fin >> emp.personnelNumber; // Чтение табельного номера
    fin >> emp.hoursWorked; // Чтение отработанных часов
    fin >> emp.hourlyRate; // Чтение почасового тарифа
    fin.ignore(); // Игнорируем символ новой строки
    return fin;
}

// Запись в файл
ofstream& operator<<(ofstream& fout, const Employee& emp) {
    fout << emp.fullName << '\n'
         << emp.personnelNumber << '\n'
         << emp.hoursWorked << '\n'
         << emp.hourlyRate << '\n';
    return fout;
}

// Метод для возврата ФИО сотрудников с указанным количеством часов
vector<string> Employee::findEmployeesByHours(const string& filename, int targetHours) {
    vector<string> result;
    ifstream file(filename);

    if (!file) {
        cout << "Error opening file for reading!\n"; // Ошибка открытия файла для чтения
        return result;
    }

    Employee emp;
    while (file >> emp) {
        if (emp.hoursWorked == targetHours) {
            result.push_back(emp.fullName);
        }
    }

    file.close();
    return result;
}

// Основная программа
int main() {
    string filename = "employees.txt"; // Имя файла с данными сотрудников
    int choice;

    do {
        cout << "\n=== Employee Management System ===\n"; // Система управления сотрудниками
        cout << "1. Add Employees to File\n"; // Добавить сотрудников в файл
        cout << "2. Show All Employees\n"; // Показать всех сотрудников
        cout << "3. Find Employees by Hours Worked\n"; // Найти сотрудников по количеством отработанных часов
        cout << "0. Exit\n"; // Выход
        cout << "Choice: "; // Выбор
        cin >> choice;

        switch (choice) {
            case 1: {
                ofstream fout(filename, ios::app); // добавление в конец
                if (!fout) {
                    cout << "Failed to open file for writing!\n"; // Не удалось открыть файл для записи
                    break;
                }

                char cont = 'y';
                do {
                    Employee emp;
                    cin >> emp;
                    fout << emp;
                    cout << "Continue input? (y/n): "; // Продолжить ввод?
                    cin >> cont;
                } while (cont == 'y' || cont == 'Y');

                fout.close();
                break;
            }

            case 2: {
                ifstream fin(filename);
                if (!fin) {
                    cout << "File is empty or does not exist.\n"; // Файл пуст или не существует
                    break;
                }

                Employee emp;
                while (fin >> emp) {
                    cout << emp;
                }
                fin.close();
                break;
            }

            case 3: {
                int hours;
                cout << "Enter target hours worked for search: "; // Введите количество отработанных часов для поиска
                cin >> hours;

                vector<string> found = Employee::findEmployeesByHours(filename, hours);

                if (found.empty()) {
                    cout << "No employees found with " << hours << " hours worked.\n"; // Сотрудников не найдено
                } else {
                    cout << "Found employees with " << hours << " hours:\n"; // Найдены сотрудники с часами
                    for (const auto& name : found) {
                        cout << "  - " << name << endl;
                    }
                }
                break;
            }

            case 0:
                cout << "Goodbye!\n"; // До свидания
                break;

            default:
                cout << "Invalid choice!\n"; // Неверный выбор
        }
    } while (choice != 0);

    return 0;
}