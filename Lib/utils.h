#pragma once

#include <windows.h>
#include <iostream>

struct ThreadData {
    int* arr;
    int size, average, min, max;

public:

    ThreadData() {
        size = 0;
        average = 0;
        min = INT_MAX;
        max = INT_MIN;
    }

    friend std::istream& operator>>(std::istream&, ThreadData&);
    friend std::ostream& operator<<(std::ostream&, const ThreadData&);

    ~ThreadData();
};
