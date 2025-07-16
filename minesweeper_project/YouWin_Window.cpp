//
// Created by Ali Hamdy on 21/05/2025.
//

#include "YouWin_Window.h"
#include <iostream>
#include <fstream>
#include "Game.h"
using namespace sf;
using namespace std;
#define DELETE_KEY 8
#define EASY 9
#define MEDIUM 17
#define HARD 31
YouWin_Window::YouWin_Window() {
    initialize_variables();
    initialize_window();
    update();
    render();
}
YouWin_Window::~YouWin_Window()
{
    delete this->YouWin_window;
}

const bool YouWin_Window::displaying() const
{
    return this->YouWin_window->isOpen();
}

void YouWin_Window::initialize_variables()
{
    this->background = nullptr;
    this->YouWin_window = nullptr;
    this->Selected = true;
    this->limit = 15;

}

void YouWin_Window::initialize_window() {
    this->video = VideoMode(400, 400);
    this->YouWin_window = new RenderWindow(this->video, "You win!", Style::Titlebar | Style::Close);
    this->background = new Texture();
    this->background->loadFromFile("images\\win.png");
    this->YouWin_window->setFramerateLimit(60);
    this->background_sprite.setTexture(*this->background);
    this->background_sprite.setPosition(0, 0);
    this->font.loadFromFile("images\\minecraft.ttf");
    this->textbox.setFont(this->font);
    this->textbox.setCharacterSize(20);
    this->textbox.setFillColor(Color::Black);
    this->textbox.setPosition(60, 243);
    this->ScoreText.setFont(this->font);
    this->ScoreText.setStyle(Text::Bold);
    this->ScoreText.setCharacterSize(16);
    this->ScoreText.setFillColor(Color(255, 242, 0, 255));
    this->ScoreText.setPosition(150, 283);
    this->Menu_ClickBuffer.loadFromFile("images\\Menu.wav");
    this->MenuClick.setBuffer(this->Menu_ClickBuffer);
    this->MenuClick.setVolume(25.0f);
   
}


void YouWin_Window::render()
{
    this->YouWin_window->clear(Color::Black);
    this->YouWin_window->draw(this->background_sprite);
    this->YouWin_window->draw(textbox);
    this->YouWin_window->draw(ScoreText);
    this->YouWin_window->display();
}

void YouWin_Window::InputLogic(int CharTyped)
{
    if (CharTyped != DELETE_KEY && text.str().length() < limit && Selected) {
        text << static_cast<char>(CharTyped);
    }
    else if (CharTyped == DELETE_KEY && Selected) {
        if (text.str().length() > 0) {
            delete_char();
        }
    }
    textbox.setString(sf::String(text.str() + "|"));
}

void YouWin_Window::delete_char()
{
    string t = text.str();
    string newt = "";
    for (int i = 0; i < t.length() - 1; i++) {
        newt += t[i];
    }
    text.str("");
    text << newt;
    textbox.setString(sf::String(text.str()));
}

void YouWin_Window::setData(const std::string& score, int difficulty)
{
    this->Score = score;
    this->ScoreText.setString(Score);
    this->N = difficulty;
}

void YouWin_Window::SavetoFile(string Name)
{
    switch (N) {
    case EASY:
        diff_file = "images\\Easy.txt";
        break;
    case MEDIUM:
        diff_file = "images\\Medium.txt";
        break;
    case HARD:
        diff_file = "images\\Hard.txt";
    default:
        break;
    }

    fstream MyFile;
    MyFile.open(diff_file, ios::app);
    if (MyFile.is_open()) {
        MyFile << Name << " | " << Score << endl;
    }
    MyFile.close();
}

void YouWin_Window::Sorting()
{

    string line;
    vector<string> file_contents;
    fstream MyFile;
    MyFile.open(diff_file, ios::in);
    if (MyFile.is_open()) {
        while (getline(MyFile, line)) {
            file_contents.push_back(line);
        }
        MyFile.close();
    }
    sort(file_contents.begin(), file_contents.end(), [](const string& a, const string& b) {
        return extract_score(a) < extract_score(b);
        });

    MyFile.open(diff_file, ios::out);
    if (MyFile.is_open()) {
        for (int i = 0; i < file_contents.size(); i++) {
            MyFile << file_contents[i] << endl;


        }
        MyFile.close();

    }

}

int YouWin_Window::extract_score(const string& entry) {
    size_t pos = entry.find("|");
    if (pos != string::npos) {
        string score_str = entry.substr(pos + 1);
        stringstream ss(score_str);
        int score;
        ss >> score;
        return score;
    }
    return 0;
}



void YouWin_Window::events()
{
    while (this->YouWin_window->pollEvent(this->event)) {

        if (event.type == Event::Closed) {
            this->YouWin_window->close();
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                this->YouWin_window->close();
            }
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                Selected = false;
                SavetoFile(text.str());
                Sorting();
                this->YouWin_window->close();

            }

            if (event.text.unicode < 128) {
                InputLogic(static_cast<int>(event.text.unicode));
            }
        }
        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                if (x >= 291 && x <= 349 && y >= 282 && y <= 306) {
                    MenuClick.play();
                    Selected = false;
                    SavetoFile(text.str());
                    Sorting();
                    this->YouWin_window->close();
                }
            }
        }


    }



}

void YouWin_Window::update()
{
    Vector2i pos = Mouse::getPosition(*this->YouWin_window);
    this->x = pos.x;
    this->y = pos.y;
    // cout<<"horizontal position"<<x<<endl;
     // cout<<"vertical position"<<y<<endl;
    this->events();
}
