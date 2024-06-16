//
// Created by denys on 4/7/2024.
//

#ifndef SORTINGVISUALIZER_STATUSBAR_H
#define SORTINGVISUALIZER_STATUSBAR_H


#include "Data.h"
#include "Algorithm.h"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>

class Bar : public sf::Sprite {
private:
    sf::RenderTexture m_texture;

    int m_width;
    int m_height;

    Data* m_data;
    Algorithm* m_algorithm;

    sf::Text m_text;
    sf::Text m_description;
    sf::Font font;
public:
    Bar(int, int, Data*, Algorithm*);
    Bar(Bar&);

    void render();
};


#endif //SORTINGVISUALIZER_STATUSBAR_H
