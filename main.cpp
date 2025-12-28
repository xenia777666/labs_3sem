//Написать функцию-шаблон, вычисляющую максимальное значение в
//массиве.

#include <iostream>
#include <stdexcept>

template <typename T>
T findMax(const T* array, int size) {
    if (size <= 0) {
        throw std::invalid_argument("Размер массива должен быть больше 0");
    }

    T maxVal = array[0];
    for (int i = 1; i < size; ++i) {
        if (array[i] > maxVal) {
            maxVal = array[i]; // Обновление максимального значения
        }
    }
    return maxVal;
}

int main() {
    int intArray[] = {1, 5, 3, 9, 2};
    double doubleArray[] = {3.1, 2.4, 8.4, 1.8};

    try {
        std::cout << "Максимальное значение в целочисленном массиве: "
                  << findMax(intArray, 5) << std::endl;

        std::cout << "Максимальное значение в массиве с плавающей точкой: "
                  << findMax(doubleArray, 4) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl; // Обработка исключений
    }

    return 0;
}