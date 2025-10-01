#pragma once

#include <windows.h>
#include <iostream>

struct ThreadData {
    int* arr;
    int size, average, min, max;

public:

    friend std::istream& operator>>(std::istream&, ThreadData&);
    friend std::ostream& operator<<(std::ostream&, const ThreadData&);

    ~ThreadData();
};
