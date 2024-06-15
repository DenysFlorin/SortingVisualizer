//
// Created by denys on 4/6/2024.
//

#ifndef SORTINGVISUALIZER_VIEWER_H
#define SORTINGVISUALIZER_VIEWER_H
#include <deque>
#include "Data.h"
#include "SFML/Graphics.hpp"

class Viewer : public sf::Sprite {
private:
    sf::RenderTexture m_texture;
    std::vector<sf::RectangleShape> m_dr;
    std::vector<sf::Color> m_colors;

    int m_width;
    int m_height;
    float m_dx;

    std::vector<std::pair<volatile int*, uint32_t>> m_list;
    std::vector<std::deque<volatile int*>> m_values;

    Data& m_data;

    void color(int i);
public:
    Viewer(int width, int height, Data& data);
    void render();

    void color(int i, uint32_t color);
    void colorInterval(int start, int end, uint32_t color);
    void decolor(int i);
    void decolorInterval(int start, int end);
    void decolorAll();
};


#endif //SORTINGVISUALIZER_VIEWER_H
