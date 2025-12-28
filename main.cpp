#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Базовый класс
class Learner {
public:
    virtual void showInfo() const = 0; // Чистая виртуальная функция
    virtual ~Learner() {} // Виртуальный деструктор
};

// Производный класс «Школьник»
class Schoolboy : public Learner {
private:
    string name;
    int grade;

public:
    Schoolboy(const string& name, int grade) : name(name), grade(grade) {}

    void showInfo() const override {
        cout << "Schoolboy: " << name << ", Grade: " << grade << endl;
    }
};

// Производный класс «Студент»
class Student : public Learner {
private:
    string name;
    string major;

public:
    Student(const string& name, const string& major) : name(name), major(major) {}

    void showInfo() const override {
        cout << "Student: " << name << ", Major: " << major << endl;
    }
};

int main() {
    vector<Learner*> learners; // Массив указателей на базовый класс

    // Заполнение массива объектами
    learners.push_back(new Schoolboy("Alice", 5));
    learners.push_back(new Student("Bob", "Computer Science"));
    learners.push_back(new Schoolboy("Charlie", 7));
    learners.push_back(new Student("Diana", "Mathematics"));

    cout << "Schoolboys:" << endl;
    for (const auto& learner : learners) {
        if (dynamic_cast<Schoolboy*>(learner)) { // Проверка типа
            learner->showInfo();
        }
    }

    cout << "\nStudents:" << endl;
    for (const auto& learner : learners) {
        if (dynamic_cast<Student*>(learner)) { // Проверка типа
            learner->showInfo();
        }
    }

    // Освобождение памяти
    for (const auto& learner : learners) {
        delete learner;
    }

    return 0;
}