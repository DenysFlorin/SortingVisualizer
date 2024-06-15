//
// Created by denys on 4/6/2024.
//

#include <random>
#include "Algorithm.h"

Algorithm::Algorithm(Data &data, Viewer &viewer) : m_data(data), m_finished_sort(false), m_last_sort(-1), m_running(false), m_sorted(true), m_view(viewer){
    setAlg(0);
    m_count = m_list.size();
}

void Algorithm::start() {
    if (m_running){
        return;
    }
    m_running = true;
    if(m_sortingThread.joinable()){
        m_sortingThread.join();
    }
    m_sortingThread = std::thread(&Algorithm::alg, this);
}

void Algorithm::stop() {
    m_running = false;
    m_sortingThread.detach();
}

void Algorithm::setAlg(int alg_number) {
    if(alg_number == -1){
        m_selected_alg = (m_selected_alg + 1) % m_count;
    }
    else if(alg_number == -2){
        m_selected_alg = (m_selected_alg + m_count - 1) % m_count;
    }
    else{
        m_selected_alg = alg_number;
    }
    if(!m_running){
        m_data.reset_counters();
        m_view.decolorAll();
    }
    //setDesc();
}

std::string Algorithm::getAlg() {
    return m_list[m_selected_alg];
}

void Algorithm::alg() {
    m_data.reset_counters();
    m_view.decolorAll();
    switch(m_selected_alg){
        case 0:
            Algorithm::check();
            break;
        case 1:
            Algorithm::shuffle();
            break;
        case 2:
            Algorithm::insertionSort();
            Algorithm::check();
            break;
        case 3:
            Algorithm::selectionSort();
            Algorithm::check();
            break;
        case 4:
            Algorithm::bubbleSort();
            Algorithm::check();
            break;
        case 5:
            Algorithm::mergeSort();
            Algorithm::check();
            break;
        case 6:
            Algorithm::quickSort();
            Algorithm::check();
            break;
        case 7:
            Algorithm::radixSort();
            Algorithm::check();
            break;
        case 8:
            Algorithm::shakerSort();
            Algorithm::check();
            break;
        case 9:
            Algorithm::shellSort();
            Algorithm::check();
            break;
    }
    m_running = false;
}

void Algorithm::check() {
    m_selected_alg = 0;
    //setDesc();
    int n = m_data.m_size - 1;
    int c;

    m_view.color(0, 0x00ff00ff);

    for(c = 0; c < n; c++){
        float val = m_data.m_items[c];
        if(val > m_data.m_items[c + 1]){
            m_view.color(c + 1, 0xff0000ff);
            break;
        }
        m_view.color(c + 1, 0x00ff00ff);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000 / n));
    }
    m_sorted = (n == c);
    if(m_sorted){
        m_view.color(n, 0x00ff00ff);
    }
}

void Algorithm::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_data.m_items.begin(), m_data.m_items.end(), std::default_random_engine(seed));
    m_sorted = false;
}
void Algorithm::insertionSort() {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    for(int i = 1, k = m_data.m_size; i < k; i++){
        m_view.color(i, 0xff0000ff);
        int curr = m_data[i];
        int j = i - 1;

        while(j >= 0 && m_data[j] > curr){
            m_data.m_countCompares++;
            m_view.color(j + 1, 0x0000ffff);
            m_data(j + 1, m_data[j]);
            m_view.decolor(j + 1);
            j--;
        }
        m_data(j + 1, curr);
        m_view.decolor(i);
    }
    m_data.m_count_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
    m_finished_sort = true;
    m_last_sort = 1;
}

void Algorithm::selectionSort() {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    int min_val_index = 0;
    int n = m_data.m_size;
    for(int i = 0; i < n; i++){
        min_val_index = i;
        for(int j = i + 1; j < n; j++){
            m_view.color(j, 0x411e59ff);
            if(m_data.compare(j, min_val_index) == -1){
                min_val_index = j;
            }
            m_view.decolor(j);
        }
        if(min_val_index != i){
            m_view.color(i, 0xff0000ff);
            m_data.swap(i, min_val_index);
            m_view.decolor(i);
        }
    }
    m_data.m_count_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
    m_finished_sort = true;
    m_last_sort = 2;
}

void Algorithm::bubbleSort() {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    int n = m_data.m_size;

    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            m_view.color(j, 0xff0000ff);
            if(m_data.compare(j, j + 1) == 1){
                m_data.swap(j, j + 1);
            }
            m_view.decolor(j);
        }
    }
    m_data.m_count_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
    m_finished_sort = true;
    m_last_sort = 2;
}

void Algorithm::mergeSort() {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    split(0, m_data.m_size - 1);
    m_data.m_count_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
    m_finished_sort = true;
    m_last_sort = 4;
}

void Algorithm::split(int left, int right){
    if(left >= right){
        return;
    }
    m_data.m_countCompares++;
    int mid = (left + right) / 2;

    split(left, mid);
    split(mid + 1, right);

    merge(left, mid, right);
}

void Algorithm::merge(int left, int mid, int right) {
    m_view.color(left, 0x00ffffff);
    m_view.color(right, 0xffff00ff);
    int left_n = mid - left + 1;
    int right_n = right - mid;

    int* left_arr = new int[left_n];
    int* right_arr = new int[right_n];

    for(int i = 0; i < left_n; i++){
        m_data.m_countCompares++;
        m_view.color(left + i + 1, 0xff0000ff);
        left_arr[i] = m_data[left + i];
        m_view.decolor(left + i + 1);
    }
    for (int i = 0; i < right_n; ++i) {
        m_data.m_countCompares++;
        m_view.color(mid + 1 + i, 0xff0000ff);
        right_arr[i] = m_data[mid + 1 + i];
        m_view.decolor(mid + 1 + i);
    }
    int i = 0;
    int j = 0;
    int k = left;

    while (i < left_n && j < right_n)
    {
        m_data.m_countCompares++;
        m_view.color(k - 1, 0x0000ffff);
        if (left_arr[i] <= right_arr[j]) {
            m_data(k, left_arr[i]);
            i++;
        }
        else {
            m_data(k, right_arr[j]);
            j++;
        }
        m_view.decolor(k - 1);
        k++;
    }
    while (i < left_n) {
        m_data.m_countCompares++;
        m_view.color(k - 1, 0x0000ffff);
        m_data(k, left_arr[i]);
        i++;
        m_view.decolor(k - 1);
        k++;
    }
    while (j < right_n) {
        m_data.m_countCompares++;
        m_view.color(k - 1, 0x0000ffff);
        m_data(k, right_arr[j]);
        j++;
        m_view.decolor(k - 1);
        k++;
    }
    m_view.decolor(left);
    m_view.decolor(right);
}

void Algorithm::quickSort() {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    quick(0, m_data.m_size - 1);
    m_data.m_count_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
    m_finished_sort = true;
    m_last_sort = 5;
}
void Algorithm::quick(int low, int high) {
    int pivot_index;
    if (low >= high) return;
    pivot_index = pivot(low, high);
    m_view.color(pivot_index, 0x00ff00ff);

    quick(low, pivot_index - 1);
    quick(pivot_index + 1, high);
    m_view.decolor(pivot_index);
}
int Algorithm::pivot(int low, int high) {
    int pivot = m_data[low];
    int count = 0;
    for (int i = low + 1; i <= high; i++) {
        m_data.m_countCompares++;
        if (m_data[i] <= pivot)
            count++;
    }
    int pivotIndex = low + count;
    m_data.swap(pivotIndex, low);
    int i = low, j = high;

    while (i < pivotIndex && j > pivotIndex) {
        m_data.m_countCompares++;
        m_data.m_countCompares++;
        while (m_data[i] <= pivot) {
            m_data.m_countCompares++;
            i++;
        }
        while (m_data[j] > pivot) {
            m_data.m_countCompares++;
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            m_data.m_countCompares++;
            m_data.swap(i++, j--);
        }
    }
    return pivotIndex;
}

void Algorithm::radixSort() {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    int max_val = maxim();
    for (int p = 1; max_val / p > 0; p *= 10)
        countSort(p);
    m_data.m_count_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
    m_finished_sort = true;
    m_last_sort = 6;
}
void Algorithm::countSort(int place) {
    int s = m_data.m_size;
    float* output = new float[s];
    int count[10] = { 0 };

    for (int i = 0; i < s; ++i) {
        m_view.color(i, 0xff0000ff);
        count[(static_cast<int>(m_data[i]) / place) % 10]++;
        m_view.decolor(i);
    }

    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    for (int i = 9; i > 0; --i)
        count[i] = count[i - 1];
    count[0] = 0;

    for (int i = 0; i < s; ++i) {
        m_view.color(i, 0xff0000ff);
        float val = m_data[i];
        int digit = (static_cast<int>(val) / place) % 10;
        output[count[digit]] = val;
        count[digit]++;
        m_view.decolor(i);
    }

    for (int i = 0; i < s; ++i) {
        m_view.color(i, 0x0000ffff);
        m_data(i, output[i]);
        m_view.decolor(i);
    }
}
int Algorithm::maxim() {
    int max_i = 0;
    for (int i = 0, j = m_data.m_size; i < j; ++i) {
        m_view.color(i, 0xffff00ff);
        if (m_data.compare(i, max_i) == 1) max_i = i;
        m_view.decolor(i);
    }
    return m_data[max_i];
}
void Algorithm::shakerSort() {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    int n = m_data.m_size;
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; i++) {
            m_view.color(i, 0xff0000ff);
            if (m_data.compare(i, i + 1) == 1) {
                m_data.swap(i, i + 1);
                swapped = true;
            }
            m_view.decolor(i);
        }

        if (!swapped)
            break;
        swapped = false;

        end--;
        for (int i = end - 1; i >= start; i--) {
            m_view.color(i, 0xff0000ff);
            if (m_data.compare(i, i + 1) == 1) {
                m_data.swap(i, i + 1);
                swapped = true;
            }
            m_view.decolor(i);
        }
        start++;
    }
    m_data.m_count_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
    m_finished_sort = true;
    m_last_sort = 7;
}
void Algorithm::shellSort() {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    int n = m_data.m_size;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            m_view.color(i, 0xff0000ff);
            int temp = m_data[i];
            int j;
            for (j = i; j >= gap && m_data[j - gap] > temp; j -= gap) {
                m_data.m_countCompares++;
                m_view.color(j + 1, 0x0000ffff);
                m_data(j, m_data[j - gap]);
                m_view.decolor(j + 1);
            }
            m_data(j, temp);
            m_view.decolor(i);
        }
    }
    m_data.m_count_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
    m_finished_sort = true;
    m_last_sort = 8;
}
