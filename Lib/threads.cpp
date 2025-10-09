#include "pch.h"
#include "threads.h"
#include <iostream>

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

    std::cout << "Average = " << data->average << "\n";
    std::cout.flush();
    return 0;
}

void min_max_thread(ThreadData *data) {
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
    return;
}

void average_thread(ThreadData* data) {
    int sum = 0;

    for (int i = 0; i < data->size; i++) {
        sum += data->arr[i];
        Sleep(12);
    }

    data->average = sum / data->size;

    std::cout << "Average = " << data->average << "\n";
    std::cout.flush();
    return;
}