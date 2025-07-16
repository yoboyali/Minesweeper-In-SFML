//
// Created by Ali Hamdy on 21/05/2025.
//

#ifndef YOUWIN_WINDOW_H
#define YOUWIN_WINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "SFML/Audio.hpp"
#include <sstream>
using namespace sf;
using namespace std;

class YouWin_Window {
public:
    //constructors and destructors
    YouWin_Window();
    virtual ~YouWin_Window();

    // public functions
    void events();
    const bool displaying() const;
    void update();
    void render();
    void InputLogic(int CharTyped);
    void delete_char();
    void setData(const std::string& score, int difficulty);
    void SavetoFile(string Name);
    void Sorting();
    static int extract_score(const string& line);
    Event event;
    Texture* background;
    Sprite background_sprite;
    Text textbox;
    Text ScoreText;
    Font font;
    ostringstream text;
    int x, y, limit, N;
    string Score;
    string diff_file;
    bool Selected;
    SoundBuffer Menu_ClickBuffer;
    Sound MenuClick;



private:
    VideoMode video;
    RenderWindow* YouWin_window;
    void initialize_variables();
    void initialize_window();

};


#endif //YOUWIN_WINDOW_H
