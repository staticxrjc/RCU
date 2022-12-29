#ifndef GAMEDATA_H
#define GAMEDATA_H

#pragma region GameDataImplementation
/*
class SplashState : public RCU::State {
public:
    SplashState(RCU::GameDataRef data) : _data(data) {}
    void Init() override {}
    void HandleInput() override {
        sf::Event event;
        while(this->_data->window.pollEvent(event)) {
            if(sf::Event::Closed == event.type) {
                this->_data->window.close();
            }
        }
    }
    void Update(float dt) override {
        if(this->_clock.getElapsedTime().asSeconds() > 5) {
            // Switch to main menu
            std::cout << "Go to main menu" << std::endl;
        }
    }
    void Draw(float dt) override {
        this->_data->window.clear(sf::Color::Blue);
        // this->_data->window.draw();
        this->_data->window.display();
    }
private:
    RCU::GameDataRef _data;
    sf::Clock _clock;
    sf::Sprite _background;
};

class Interstellar : public RCU::Game {
public:
    Interstellar(int width, int height, std::string title) 
        : RCU::Game(width, height, title) {}
private:
    void InitializeStates() override {
        std::cout << "Initializing" << std::endl;
        this->_data->machine.AddState(RCU::StateRef(new SplashState(this->_data)));
    }
};
*/
#pragma endregion GameDataImplementation

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "../StateMachine/StateMachine.h"
#include "../Managers/AssetManager.h"
#include "../Managers/InputManager.h"

namespace RCU {

struct GameData
{
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {
public:
    Game(int width, int height, std::string title);
    void Run();

private:
    const float dt = 1.0f / 60.0f;
    sf::Clock _clock;
    virtual void InitializeStates() = 0;

protected:
    GameDataRef _data = std::make_shared<GameData>();
};

}
#endif // GAMEDATA_H