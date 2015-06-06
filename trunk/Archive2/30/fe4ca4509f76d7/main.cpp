#ifndef GAMESTAGE_H
#define GAMESTAGE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <memory>
class GameStage
{
public:
    GameStage();

private:
  std::shared_ptr<sf::RenderWindow> _gameStage;
};

#endif // GAMESTAGE_H
//Header END


//gamestage.cpp
#include "gamestage.h"

GameStage::GameStage()
{
    _gameStage = std::make_shared<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800,800),"WindowName"));
}

