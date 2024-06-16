//
// Created by denys on 4/6/2024.
//

#include <iostream>
#include <thread>
#include "../include/Data.h"

Data::Data(int size, int maxValue) {
    m_size = size;
    m_maxVal = maxValue;

    setDelay(100);
    reset_counters();

    m_items.clear();
    for(int i = 1; i <= m_size; i++){
        m_items.push_back(i * m_maxVal / m_size);
    }
}

int Data::compare(int a, int b) {

    m_countCompares++;

    int x = this->operator[](a);
    int y = this->operator[](b);

    if(x == y){
        return 0;
    }
    else if(x > y){
        return 1;
    }
    else{
        return -1;
    }
}

void Data::swap(int a, int b) {
    m_countSwaps++;

    int aux = this->operator[](a);
    this->operator()(a, this->operator[](b));
    this->operator()(b, aux);
}

void Data::reset_counters() {
    m_countSwaps = 0;
    m_countCompares = 0;
    m_countRead = 0;
    m_countWrite = 0;
    m_count_time *= 0;
}

void Data::setDelay(int delay) {
    if (delay >= 0){
        m_readDelay = delay;
        m_writeDelay = delay;
    }
}

float Data::operator[](int a) {
    if(a >= m_size){
        std::cout<< "Out of bound value selected \n";
        return -1;
    }
    m_countRead++;
    float val = m_items[a];
    std::this_thread::sleep_for(std::chrono::microseconds(m_readDelay));
    return val;
}
void Data::operator()(int a, int b) {
    if(a >= m_size){
        std::cout<<"Out of bound value selecte\n";
        return;
    }
    m_countWrite++;
    std::this_thread::sleep_for(std::chrono::microseconds(m_writeDelay));
    m_items[a] = b;
}

