#include "utils.h"

std::istream& operator>>(std::istream& in, ThreadData& data) {
    std::cout << "Введите размер массива: ";
    if (!(in >> data.size) || data.size <= 0) {
        throw std::runtime_error("Ошибка: размер массива должен быть положительным числом");
    }

    data.arr = new int[data.size];

    std::cout << "Введите " << data.size << " элементов массива:\n";
    for (int i = 0; i < data.size; i++) {
        if (!(in >> data.arr[i])) {
            throw std::runtime_error("Ошибка: элементы массива должны быть целыми числами");
        }
    }

    data.average = 0;
    data.max = INT_MIN;
    data.min = INT_MAX;
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const ThreadData& data) {
    std::cout << "Полученный массив:\n";
    for (int i = 0; i < data.size; i++) {
        std::cout << data.arr[i] << " ";
    }
    std::cout << "\n";

    return out;
}

ThreadData::~ThreadData() {
    delete[] arr;
}