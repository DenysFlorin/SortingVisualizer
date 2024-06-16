#include <iostream>

#include "../include/Data.h"
#include "../include/Algorithm.h"
#include "../include/Viewer.h"
#include "../include/StatusBar.h"

int main(){
    sf::VideoMode def = sf::VideoMode::getDesktopMode();
    const int FPS = 60;
    const int WIDTH = def.width;
    const int HEIGHT = def.height;
    const int DATA_H = 0.05 * HEIGHT;
    const int DATA_SIZE = 200;

    sf::RenderWindow window(def, "Sorting", sf::Style::Default);
    window.setFramerateLimit(FPS);
    sf::Event event;
    Data data(DATA_SIZE, HEIGHT - DATA_H);
    Viewer viewer(WIDTH, HEIGHT - DATA_H, data);
    Algorithm algorithm(data, viewer);
    viewer.setPosition(0, 0);
    Bar bar(WIDTH, DATA_H, &data, &algorithm);
    bar.setPosition(0, HEIGHT - DATA_H);

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed){

                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        algorithm.stop();
                        window.close();
                        break;
                    case sf::Keyboard::Enter:
                        algorithm.start();
                        break;
                    case sf::Keyboard::Up:
                        algorithm.setAlg(-1);
                        break;
                    case sf::Keyboard::Down:
                        algorithm.setAlg(-2);
                        break;
                    case sf::Keyboard::C:
                        algorithm.setAlg(0);
                        break;
                    case sf::Keyboard::A:
                        algorithm.setAlg(1);
                        break;
                    case sf::Keyboard::I:
                        algorithm.setAlg(2);
                        break;
                    case sf::Keyboard::S:
                        algorithm.setAlg(3);
                        break;
                    case sf::Keyboard::D:
                        algorithm.setAlg(4);
                        break;
                    case sf::Keyboard::M:
                        algorithm.setAlg(5);
                        break;
                    case sf::Keyboard::Q:
                        algorithm.setAlg(6);
                        break;
                    case sf::Keyboard::R:
                        algorithm.setAlg(7);
                        break;
                    case sf::Keyboard::K:
                        algorithm.setAlg(8);
                        break;
                    case sf::Keyboard::J:
                        algorithm.setAlg(9);
                        break;
                }

            }
        }
        viewer.render();
        bar.render();

        window.clear();
        window.draw(viewer);
        window.draw(bar);
        window.display();
    }

    return 0;
}