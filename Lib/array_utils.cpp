#include "pch.h"
#include "array_utils.h"


void replaceMinMaxWithAverage(ThreadData& data) {
    for (int i = 0; i < data.size; i++) {
        if (data.arr[i] == data.min || data.arr[i] == data.max) {
            data.arr[i] = data.average;
        }
    }
}