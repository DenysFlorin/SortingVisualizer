//
// Created by denys on 4/6/2024.
//

#ifndef SORTINGVISUALIZER_DATA_H
#define SORTINGVISUALIZER_DATA_H

#include <chrono>
#include <vector>

class Data {
public:
    int m_size;
    int m_maxVal;
    int m_readDelay;
    int m_writeDelay;
    int m_countCompares;
    int m_countSwaps;
    int m_countRead;
    int m_countWrite;
    std::chrono::microseconds m_count_time;

    std::vector<int> m_items;

    Data(int size, int maxValue);

    int compare(int a, int b);
    void swap(int a, int b);

    void reset_counters();
    void setDelay(int delay);

    void operator()(int a, int b);
    float operator[](int a);
};


#endif //SORTINGVISUALIZER_DATA_H
