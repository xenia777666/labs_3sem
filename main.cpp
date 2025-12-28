#include <iostream>
#include <sstream>
#include <stdexcept>


class DateFormatException : public std::runtime_error {
public:
    DateFormatException(const std::string& message)
            : std::runtime_error(message) {}
};

void validateDate(const std::string& date) {
    std::istringstream dateStream(date);
    std::string day, month, year;


    if (!std::getline(dateStream, year, '/') ||
        !std::getline(dateStream, month, '/') ||
        !std::getline(dateStream, day)) {
        throw DateFormatException("Ошибка: Неверный формат даты. Используйте формат гг/мм/дд.");
    }

    // проверка на размеры строк
    if (year.size() != 2 || month.size() != 2 || day.size() != 2) {
        throw DateFormatException("Ошибка: Неверный формат даты. Используйте формат гг/мм/дд.");
    }

    // Доп проверка: значения даты (опциональненько)
    if (std::stoi(month) < 1 || std::stoi(month) > 12 ||
        std::stoi(day) < 1 || std::stoi(day) > 31) {
        throw DateFormatException("Ошибка: Неверные значения месяца или дня.");
    }

    // все норм
    std::cout << "Дата " << date << " успешно считается." << std::endl;
}

int main() {
    std::string inputDate;

    std::cout << "Введите дату в формате гг/мм/дд: ";
    std::getline(std::cin, inputDate);

    try {
        validateDate(inputDate);
    } catch (const DateFormatException& e) {
        std::cerr << e.what() << std::endl; // Вывод сообщения об ошибке
    }

    return 0;
}