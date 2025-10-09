#include <windows.h>
#include <iostream>
#include <thread>
#include "threads.h"
#include "utils.h"
#include "array_utils.h"

int main() {
    ThreadData data;

    try {

        std::cin >> data;

        std::thread tMinMax(min_max_thread, &data);
        std::thread tAverage(average_thread, &data);

        tMinMax.join();
        tAverage.join();

        replaceMinMaxWithAverage(data);

        std::cout << data;

        return 0;
    }
    catch (const std::exception e) {
        std::cerr << "An exception occurred while the program was running: \n" << e.what() << "\n";

        return 1;
    }
}
