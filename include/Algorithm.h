//
// Created by denys on 4/6/2024.
//

#ifndef SORTINGVISUALIZER_ALGORITHM_H
#define SORTINGVISUALIZER_ALGORITHM_H


#include <thread>
#include "Data.h"
#include "Viewer.h"

class Algorithm {
private:
    Data& m_data;
    Viewer& m_view;
    std::thread m_sortingThread;

    int m_count;

    void alg();
    void check();
    void shuffle();
    void insertionSort();
    void selectionSort();
    void bubbleSort();
    void mergeSort(); void split(int left, int right); void merge(int left, int mid, int right);
    void quickSort(); void quick(int low, int high); int pivot(int low, int high);
    void radixSort(); void countSort(int place); int maxim();
    void shakerSort();
    void shellSort();
    const std::vector<std::string> m_list = {"Check", "Shuffle", "InsertionSort", "SelectionSort", "BubbleSort", "MergeSort", "QuickSort", "RadixSort", "ShakerSort", "ShellSort"};

public:
    bool m_running;
    bool m_sorted;
    bool m_finished_sort;
    int m_selected_alg;
    int m_last_sort;
    std::string m_alg_desc;

    Algorithm(Data& data, Viewer& viewer);
    void start();
    void stop();
    void setAlg(int alg_number);
    std::string getAlg();
};


#endif //SORTINGVISUALIZER_ALGORITHM_H
