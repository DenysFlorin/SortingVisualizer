//
// Created by denys on 4/6/2024.
//

#include <iostream>
#include "../include/Viewer.h"

void Viewer::color(int i) {
    m_dr[i].setFillColor(sf::Color::White);
}

Viewer::Viewer(int width, int height, Data &data) :  m_width(width), m_height(height), m_data(data){
    m_dx = (float)m_width / (m_data.m_size * 1.3f);
    m_dr = std::vector<sf::RectangleShape>(m_data.m_size);
    m_colors = std::vector<sf::Color>(m_data.m_size, sf::Color::White);
    m_texture.create(m_width, m_height);
    this->setTexture(m_texture.getTexture());
}

void Viewer::render() {
    m_texture.clear();
    for(int i = 0, j = m_dr.size(); i < j; i++){
        float h = m_data.m_items[i];

        m_dr[i].setSize(sf::Vector2f(m_dx, h));
        m_dr[i].setPosition(i * m_dx, m_height - h);
        m_dr[i].setFillColor(m_colors[i]);
        m_texture.draw(m_dr[i]);
    }
    m_texture.display();
}

void Viewer::color(int i, uint32_t color) {
    if(i >= m_dr.size()){
        std::cout<<"Out of bound value selected\n";
        return;
    }
    m_colors[i] = sf::Color(color);
}

void Viewer::colorInterval(int start, int end, uint32_t color) {
    std::fill(m_colors.begin() + start, m_colors.begin() + end, sf::Color(color));
}

void Viewer::decolor(int i) {
    if (i >= m_dr.size()){
        std::cout<<"Out of bound value selected\n";
        return;
    }
    m_colors[i] = sf::Color::White;
}

void Viewer::decolorInterval(int start, int end) {
    std::fill(m_colors.begin() + start, m_colors.begin() + end, sf::Color::White);
}

void Viewer::decolorAll() {
    std::fill(m_colors.begin(), m_colors.end(), sf::Color::White);
}



