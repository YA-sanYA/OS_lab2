#include "utils.h"

std::istream& operator>>(std::istream& in, ThreadData& data) {
    std::cout << "������� ������ �������: ";
    if (!(in >> data.size) || data.size <= 0) {
        throw std::runtime_error("������: ������ ������� ������ ���� ������������� ������");
    }

    data.arr = new int[data.size];

    std::cout << "������� " << data.size << " ��������� �������:\n";
    for (int i = 0; i < data.size; i++) {
        if (!(in >> data.arr[i])) {
            throw std::runtime_error("������: �������� ������� ������ ���� ������ �������");
        }
    }

    data.average = 0;
    data.max = INT_MIN;
    data.min = INT_MAX;
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const ThreadData& data) {
    std::cout << "���������� ������:\n";
    for (int i = 0; i < data.size; i++) {
        std::cout << data.arr[i] << " ";
    }
    std::cout << "\n";

    return out;
}

ThreadData::~ThreadData() {
    delete[] arr;
}