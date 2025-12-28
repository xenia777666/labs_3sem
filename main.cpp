#include <iostream>
#include <vector>
#include <memory> // Для использования smart pointers

// Абстрактный базовый класс
class Uchyashchiy {
public:
    virtual void getInfo() const = 0; // Чисто виртуальная функция
    virtual ~Uchyashchiy() {} // Виртуальный деструктор
};

// Производный класс Школьник
class Shkolnik : public Uchyashchiy {
private:
    std::string name;
    int grade;

public:
    Shkolnik(const std::string& name, int grade) : name(name), grade(grade) {}

    void getInfo() const override {
        std::cout << "Школьник: " << name << ", Класс: " << grade << std::endl;
    }
};

// Производный класс Студент
class Student : public Uchyashchiy {
private:
    std::string name;
    std::string major;

public:
    Student(const std::string& name, const std::string& major) : name(name), major(major) {}

    void getInfo() const override {
        std::cout << "Студент: " << name << ", Специальность: " << major << std::endl;
    }
};

int main() {
    // Создание массива объектов базового класса
    std::vector<std::unique_ptr<Uchyashchiy>> uchashchies;

    // Заполнение массива объектами
    uchashchies.push_back(std::make_unique<Shkolnik>("Иван", 5));
    uchashchies.push_back(std::make_unique<Student>("Анна", "Экономика"));
    uchashchies.push_back(std::make_unique<Shkolnik>("Мария", 6));
    uchashchies.push_back(std::make_unique<Student>("Петр", "Физика"));

    // Показать отдельно школьников и студентов
    std::cout << "Список школьников:" << std::endl;
    for (const auto& uchashchiy : uchashchies) {
        if (dynamic_cast<Shkolnik*>(uchashchiy.get())) {
            uchashchiy->getInfo();
        }
    }

    std::cout << "\nСписок студентов:" << std::endl;
    for (const auto& uchashchiy : uchashchies) {
        if (dynamic_cast<Student*>(uchashchiy.get())) {
            uchashchiy->getInfo();
        }
    }

    return 0;
}