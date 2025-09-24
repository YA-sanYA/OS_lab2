#include <windows.h>
#include <iostream>
#include "utils.h"

void SafeCloseHandle(HANDLE& h) {
    if (h) {
        CloseHandle(h);
        h = NULL;
    }
}

DWORD WINAPI min_max(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;

    for (int i = 0; i < data->size; i++) {
        int currentElement = data->arr[i];

        if (data->min > currentElement) {
            data->min = currentElement;
        }
        Sleep(7);

        if (data->max < currentElement) {
            data->max = currentElement;
        }
        Sleep(7);
    }

    std::cout << "min = " << data->min << ", max = " << data->max << "\n";
    std::cout.flush();
    return 0;
}

DWORD WINAPI average(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;

    int sum = 0;

    for (int i = 0; i < data->size; i++) {
        sum += data->arr[i];
        Sleep(12);
    }

    data->average = sum / data->size;

    std::cout << "Среднее арифметическое = " << data->average << "\n";
    std::cout.flush();
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int* array = nullptr;
    HANDLE hMin_max = NULL;
    HANDLE hAverage = NULL;

    try {

        int arraySize;
        std::cout << "Введите размер массива: ";
        if (!(std::cin >> arraySize) || arraySize <= 0) {
            throw std::runtime_error("Ошибка: размер массива должен быть положительным числом");
        }

        array = new int[arraySize];

        std::cout << "Введите " << arraySize << " элементов массива:\n";
        for (int i = 0; i < arraySize; i++) {
            if (!(std::cin >> array[i])) {
                throw std::runtime_error("Ошибка: элементы массива должны быть целыми числами");
            }
        }

        ThreadData data;
        data.arr = array;
        data.size = arraySize;
        data.average = 0;
        data.min = INT_MAX;
        data.max = INT_MIN;

        hMin_max = CreateThread(NULL, 0, min_max, &data, 0, NULL);
        if (hMin_max == NULL) {
            throw std::runtime_error("Ошибка: не удалось создать поток min_max");
        }

        hAverage = CreateThread(NULL, 0, average, &data, 0, NULL);
        if (hAverage == NULL) {
            throw std::runtime_error("Ошибка: не удалось создать поток average");
        }

        if (WaitForSingleObject(hMin_max, INFINITE) != WAIT_OBJECT_0) {
            throw std::runtime_error("Ошибка при ожидании завершения потока min_max!");
        }

        if (WaitForSingleObject(hAverage, INFINITE) != WAIT_OBJECT_0) {
            throw std::runtime_error("Ошибка при ожидании завершения потока average!");
        }

        for (int i = 0; i < data.size; i++) {
            if (data.arr[i] == data.min || data.arr[i] == data.max) {
                data.arr[i] = data.average;
            }
        }

        std::cout << "Полученный массив:\n";
        for (int i = 0; i < data.size; i++) {
            std::cout << data.arr[i] << " ";
        }
        std::cout << "\n";

        SafeCloseHandle(hMin_max);
        SafeCloseHandle(hAverage);

        delete[] array;

        return 0;
    }
    catch (const std::exception e) {
        std::cerr << "Во время работы программы возникло исключение:\n" << e.what() << "\n";

        SafeCloseHandle(hMin_max);
        SafeCloseHandle(hAverage);

        delete[] array;

        return 1;
    }
}
