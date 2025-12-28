#include <iostream>
#include <string>

class String {
private:
    std::string data;

public:
    String() : data("") {}

    String(const std::string& input) : data(input) {}
    String(const String& other) : data(other.data) {} //констр копирования

    String& operator++() {
        for (char& c : data) {
            if (c >= 'A' && c <= 'Z') c = (c - 'A' + 1) % 26 + 'A';  // Заглавные
            else if (c >= 'a' && c <= 'z') c = (c - 'a' + 1) % 26 + 'a';  // Строчные
        }
        return *this;
    }

    String& operator--() {
        for (char& c : data) {
            if (c >= 'A' && c <= 'Z') c = (c - 'A' + 25) % 26 + 'A';  // Заглавные ( -1 = +25 mod 26)
            else if (c >= 'a' && c <= 'z') c = (c - 'a' + 25) % 26 + 'a';  // Строчные
        }
        return *this;
    }

    // Friend-функция для вывода в поток (<<)
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
            return os << str.data;
    }

    // Friend-функция для ввода из потока (>>)
    friend std::istream& operator>>(std::istream& is, String& str) {
        return is >> str.data;
    }
};

int main() {
    String s1("Hello");
    std::cout << "Оригинал: " << s1 << std::endl;

    ++s1;  // Кодируем: Ifmmp
    std::cout << "После ++ (кодирование): " << s1 << std::endl;

    --s1;
    std::cout << "После -- (декодирование): " << s1 << std::endl;


    String s2 = s1;
    std::cout << "Копия: " << s2 << std::endl;


    std::cout << "Введите строку для кодирования: ";
    std::cin >> s2;
    ++s2;
    std::cout << "Закодированная: " << s2 << std::endl;
    --s2;
    std::cout << "Декодированная: " << s2 << std::endl;
    return 0;
}