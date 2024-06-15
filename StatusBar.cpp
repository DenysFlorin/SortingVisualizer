//
// Created by denys on 4/7/2024.
//

#include "StatusBar.h"
Bar::Bar(int w, int h, Data* d, Algorithm* a) {
    m_width = w;
    m_height = h;
    m_data = d;
    m_algorithm = a;

    m_texture.create(m_width, m_height);
    this->setTexture(m_texture.getTexture());

    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error loading font!";
    }

    m_text.setFont(font);
    m_text.setCharacterSize(14);
    m_description.setFont(font);
    m_description.setCharacterSize(14);
    m_description.setPosition(0, 35);
}

void Bar::render() {
    std::stringstream sstr;

    sstr << "Selected Alg: " << m_algorithm->getAlg()
         << " | Comparatii: " << m_data->m_countCompares
         << " | Interschimbari: " << m_data->m_countSwaps
         << " | Accesari: " << m_data->m_countRead
         << " | Rescrieri: " << m_data->m_countWrite << "\n"
         << "Timp: " << m_data->m_count_time.count() / 1000.f << " ms "
         << " | Data size: " << m_data->m_size
         << " | Working: " << (m_algorithm->m_running ? "Yes" : "No ")
         << " | Sorted: " << (m_algorithm->m_sorted ? "Yes" : "No ");

    m_text.setString(sstr.str());
    m_description.setString(m_algorithm->m_alg_desc);

    m_texture.clear();
    m_texture.draw(m_description);
    m_texture.draw(m_text);
    m_texture.display();
}