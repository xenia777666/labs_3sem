#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <windows.h>

// Шаблонный контейнерчик для двумер массива
template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Matrix() : rows(0), cols(0) {}
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<T>(c)) {}

    T& at(size_t row, size_t col) {
        if (row >= rows || col >= cols)
            throw std::out_of_range("Индекс вне диапазона");
        return data[row][col];
    }

    const T& at(size_t row, size_t col) const {
        if (row >= rows || col >= cols)
            throw std::out_of_range("Индекс вне диапазона");
        return data[row][col];
    }

    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Доступ к строке для сортировочки
    std::vector<T>& getRow(size_t i) {
        if (i >= rows)
            throw std::out_of_range("Строка вне диапазона");
        return data[i];
    }

    const std::vector<T>& getRow(size_t i) const {
        if (i >= rows)
            throw std::out_of_range("Строка вне диапазона");
        return data[i];
    }

    // Линейный итератор по элементу обход (по строкам)
    class Iterator {
    private:
        Matrix* matrix;
        size_t row, col;
    public:
        Iterator(Matrix* m, size_t r = 0, size_t c = 0) : matrix(m), row(r), col(c) {}

        T& operator*() { return matrix->at(row, col); }
        const T& operator*() const { return matrix->at(row, col); }

        Iterator& operator++() {
            ++col;
            if (col >= matrix->getCols()) { col = 0; ++row; }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return row != other.row || col != other.col;
        }
    };

    Iterator begin() { return Iterator(this, 0, 0); }
    Iterator end() { return Iterator(this, rows, 0); }

    // Удобный вывод матрицы
    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << getRow(i)[j] << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

// Класс алгоритмов: поиск и сортировка
template <typename T>
class Algorithm {
public:
    // Поиск элемента (линейный)
    static typename Matrix<T>::Iterator find(Matrix<T>& m, const T& value) {
        for (auto it = m.begin(); it != m.end(); ++it) {
            if (*it == value) return it;
        }
        return m.end();
    }

    // Полная сортировка всех элементов
    static void sort(Matrix<T>& m) {
        std::vector<T> temp;
        temp.reserve(m.getRows() * m.getCols());
        for (auto it = m.begin(); it != m.end(); ++it)
            temp.push_back(*it);
        std::sort(temp.begin(), temp.end());
        auto tempIt = temp.begin();
        for (auto it = m.begin(); it != m.end(); ++it, ++tempIt)
            *it = *tempIt;
    }

    // Сортировка по строкам
    static void sortRows(Matrix<T>& m) {
        for (size_t i = 0; i < m.getRows(); ++i) {
            std::sort(m.getRow(i).begin(), m.getRow(i).end());
        }
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);  // Фикс вывода кириллицы

    Matrix<int> mat(3, 4);

    // Заполнение матрицы
    int val = 10;
    for (auto it = mat.begin(); it != mat.end(); ++it) {
        *it = val--;
    }

    std::cout << "Исходная матрица:\n";
    mat.print();

    // Поиск
    auto found = Algorithm<int>::find(mat, 5);
    if (found != mat.end())
        std::cout << "Элемент 5 найден!\n";
    else
        std::cout << "Элемент 5 не найден.\n";

    // Сортировка по строкам
    Algorithm<int>::sortRows(mat);
    std::cout << "После сортировки по строкам:\n";
    mat.print();

    // Полная сортировка
    Algorithm<int>::sort(mat);
    std::cout << "После полной сортировки:\n";
    mat.print();

    // Демонстрация исключения
    try {
        mat.at(10, 0) = 999;
    } catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }

    return 0;
}