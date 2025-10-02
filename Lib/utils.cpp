#include "pch.h"
#include "utils.h"

std::istream& operator>>(std::istream& in, ThreadData& data) {
    std::cout << "Enter the array size: ";
    if (!(in >> data.size) || data.size <= 0) {
        throw std::runtime_error("Error: array size must be a positive number");
    }

    data.arr = new int[data.size];

    std::cout << "Enter " << data.size << " array elements: \n";
    for (int i = 0; i < data.size; i++) {
        if (!(in >> data.arr[i])) {
            throw std::runtime_error("Error: Array elements must be integers");
        }
    }

    data.average = 0;
    data.max = INT_MIN;
    data.min = INT_MAX;
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const ThreadData& data) {
    std::cout << "The resulting array:\n";
    for (int i = 0; i < data.size; i++) {
        std::cout << data.arr[i] << " ";
    }
    std::cout << "\n";

    return out;
}

ThreadData::~ThreadData() {
    delete[] arr;
}