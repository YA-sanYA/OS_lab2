#include <windows.h>
#include <iostream>
#include "threads.h"
#include "utils.h"
#include "array_utils.h"
#include "ThreadClass.h"

int main() {
    setlocale(LC_ALL, "Russian");

    ThreadData data;

    try {

        std::cin >> data;

        ThreadClass tMinMax(min_max, &data, "min_max");
        ThreadClass tAverage(average, &data, "average");

        tMinMax.wait();
        tAverage.wait();

        replaceMinMaxWithAverage(data);

        std::cout << data;

        return 0;
    }
    catch (const std::exception e) {
        std::cerr << "Во время работы программы возникло исключение:\n" << e.what() << "\n";

        return 1;
    }
}
