//
// Created by Ali Hamdy on 20/05/2025.
//

#ifndef CHOOSE_DIFFICULTY_H
#define CHOOSE_DIFFICULTY_H
#include "Game.h"
using namespace sf;

class Choose_Difficulty {



public:
    Choose_Difficulty();
    virtual ~Choose_Difficulty();
    const bool displaying() const;
    Event event;
    Texture* background;
    Texture* button_texture;
    Sprite background_sprite;
    Sprite button;
    int x, y, width, height;
    void initwindow();
    void initvar();
    void update_diffWindow();
    void render_diffWindow();
    void events();
    void buttons();
    SoundBuffer Menu_ClickBuffer;
    Sound MenuClick;

private:
    VideoMode video;
    RenderWindow* difficulty_window;

};



#endif //CHOOSE_DIFFICULTY_H
