#include "pch.h"
#include "threads.h"
#include "utils.h"
#include "array_utils.h"
#include "ThreadClass.h"

TEST(ThreadUtilsTest, MinMaxFunction) {
    ThreadData data;
    data.size = 5;
    data.arr = new int[data.size] { 10, 5, 7, 3, 8 };

    ThreadClass tMinMax(min_max, &data, "min_max");
    tMinMax.wait();

    EXPECT_EQ(data.min, 3);
    EXPECT_EQ(data.max, 10);
}

TEST(ThreadUtilsTest, AverageFunction) {
    ThreadData data;
    data.size = 4;
    data.arr = new int[data.size] { 2, 4, 6, 8 };

    ThreadClass tAverage(average, &data, "average");
    tAverage.wait();

    EXPECT_EQ(data.average, 5);
}

TEST(ArrayUtilsTest, ReplaceMinMaxWithAverage) {
    ThreadData data;
    data.size = 5;
    data.arr = new int[data.size] { 1, 5, 3, 9, 2 };

    ThreadClass tMinMax(min_max, &data, "min_max");
    ThreadClass tAverage(average, &data, "average");
    tMinMax.wait();
    tAverage.wait();

    replaceMinMaxWithAverage(data);

    EXPECT_EQ(data.arr[0], 4);
    EXPECT_EQ(data.arr[3], 4);
    EXPECT_EQ(data.arr[1], 5);
    EXPECT_EQ(data.arr[2], 3);
    EXPECT_EQ(data.arr[4], 2);
}

#include "pch.h"
#include "threads.h"
#include "utils.h"
#include "array_utils.h"
#include "ThreadClass.h"

TEST(ThreadUtilsTest, MinMaxFunction_Simple) {
    ThreadData data;
    data.size = 3;
    data.arr = new int[data.size] { 7, 2, 9 };

    ThreadClass tMinMax(min_max, &data, "min_max");
    tMinMax.wait();

    EXPECT_EQ(data.min, 2);
    EXPECT_EQ(data.max, 9);
}

TEST(ThreadUtilsTest, AverageFunction_Simple) {
    ThreadData data;
    data.size = 3;
    data.arr = new int[data.size] { 3, 6, 9 };

    ThreadClass tAverage(average, &data, "average");
    tAverage.wait();

    EXPECT_EQ(data.average, 6);
}

TEST(ThreadUtilsTest, MinMaxAndAverageTogether) {
    ThreadData data;
    data.size = 4;
    data.arr = new int[data.size] { 1, 4, 2, 8 };

    ThreadClass tMinMax(min_max, &data, "min_max");
    ThreadClass tAverage(average, &data, "average");
    tMinMax.wait();
    tAverage.wait();

    EXPECT_EQ(data.min, 1);
    EXPECT_EQ(data.max, 8);
    EXPECT_EQ(data.average, 3);
}

TEST(ArrayUtilsTest, ReplaceMinMaxWithAverage_Integration) {
    ThreadData data;
    data.size = 6;
    data.arr = new int[data.size] { 1, 7, 3, 9, 2, 5 };

    ThreadClass tMinMax(min_max, &data, "min_max");
    ThreadClass tAverage(average, &data, "average");
    tMinMax.wait();
    tAverage.wait();

    replaceMinMaxWithAverage(data);

    EXPECT_EQ(data.arr[0], data.average);
    EXPECT_EQ(data.arr[3], data.average);
    EXPECT_EQ(data.arr[1], 7);
    EXPECT_EQ(data.arr[2], 3);
    EXPECT_EQ(data.arr[4], 2);
    EXPECT_EQ(data.arr[5], 5);
}

TEST(ArrayUtilsTest, ReplaceMinMaxWithAverage_AllSame) {
    ThreadData data;
    data.size = 4;
    data.arr = new int[data.size] { 5, 5, 5, 5 };

    data.min = INT_MAX;
    data.max = INT_MIN;
    for (int i = 0; i < data.size; ++i) {
        if (data.arr[i] < data.min) data.min = data.arr[i];
        if (data.arr[i] > data.max) data.max = data.arr[i];
    }
    int sum = 0;
    for (int i = 0; i < data.size; ++i) sum += data.arr[i];
    data.average = sum / data.size;

    replaceMinMaxWithAverage(data);

    EXPECT_EQ(data.arr[0], 5);
    EXPECT_EQ(data.arr[1], 5);
    EXPECT_EQ(data.arr[2], 5);
    EXPECT_EQ(data.arr[3], 5);
}
