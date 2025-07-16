//
// Created by Ali Hamdy on 20/05/2025.
//

#include "Choose_Difficulty.h"
#include <iostream>
using namespace sf;
using namespace std;
//Constructors and Destructors
Choose_Difficulty::Choose_Difficulty()
{
    this->initvar();
    this->initwindow();
    this->update_diffWindow();
    this->render_diffWindow();
}

Choose_Difficulty::~Choose_Difficulty()
{
    delete this->difficulty_window;
}

const bool Choose_Difficulty::displaying() const
{
    return this->difficulty_window->isOpen();
}

//Functions
void Choose_Difficulty::initwindow()
{
    this->video = sf::VideoMode(400, 400);
    this->difficulty_window = new sf::RenderWindow(this->video, "Choose Difficulty", sf::Style::Titlebar | sf::Style::Close);
    this->difficulty_window->setFramerateLimit(60);
    this->background = new sf::Texture();
    this->background->loadFromFile("images\\choose.png");
    this->background_sprite.setTexture(*this->background);
    this->background_sprite.setPosition(0, 0);
    this->button_texture = new Texture;
    this->button_texture->loadFromFile("images\\diff_buttons.png");
    this->button.setTexture(*this->button_texture);
    this->Menu_ClickBuffer.loadFromFile("images\\Menu.wav");
    this->MenuClick.setBuffer(this->Menu_ClickBuffer);
    this->MenuClick.setVolume(25.0f);



}
void Choose_Difficulty::initvar()
{
    this->difficulty_window = nullptr;
    this->background = nullptr;
    this->button_texture = nullptr;
    this->width = 0;

}
void Choose_Difficulty::update_diffWindow()
{
    Vector2i pos = Mouse::getPosition(*this->difficulty_window);
    this->x = pos.x;
    this->y = pos.y;
    // cout << "vertical position" << this->x << endl;
     //cout << "horizontal position" << this->y << endl;

}
void Choose_Difficulty::render_diffWindow()
{
    this->difficulty_window->clear(Color(0, 0, 0, 255));
    this->difficulty_window->draw(this->background_sprite);
    this->buttons();
    this->difficulty_window->display();
    this->events();
}

void Choose_Difficulty::events()
{
    while (this->difficulty_window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case Event::Closed:
            this->difficulty_window->close();
            break;
        case Event::MouseButtonPressed:
            switch (this->event.mouseButton.button) {
            case Mouse::Left:
                if (this->x >= 68 && this->x <= 333 && this->y >= 32 && this->y <= 109) {
                    MenuClick.play();
                    width = 9;
                    height = 9;
                    this->difficulty_window->close();
                    cout << "easy button clicked" << endl;
                }
                if (this->x >= 68 && this->x <= 333 && this->y >= 161 && this->y <= 237) {
                    MenuClick.play();
                    width = 17;
                    height = 17;
                    this->difficulty_window->close();
                    cout << "medium button clicked" << endl;
                }
                if (this->x >= 68 && this->x <= 333 && this->y >= 291 && this->y <= 369) {
                    MenuClick.play();
                    width = 31;
                    height = 17;
                    this->difficulty_window->close();
                    cout << "hard button clicked" << endl;
                }
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}

void Choose_Difficulty::buttons()
{
    button.setTextureRect(IntRect(0, 0, 269, 78));
    button.setPosition(66, 30);
    this->difficulty_window->draw(this->button);
    button.setTextureRect(IntRect(269, 0, 269, 78));
    button.setPosition(66, 160);
    this->difficulty_window->draw(this->button);
    button.setTextureRect(IntRect(538, 0, 269, 78));
    button.setPosition(66, 291);
    this->difficulty_window->draw(this->button);


}