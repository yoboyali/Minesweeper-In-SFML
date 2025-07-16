//
// Created by Ali Hamdy on 19/05/2025.
//

#ifndef GAME_H
#define GAME_H
#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "sstream"
using namespace sf;
using namespace std;

class Game
{
private:

	VideoMode videomode;
	Event e;
	Sprite s, border, numbers, faces, clock_numbers, button;
	Texture* texture;
	Texture* border_texture;
	Texture* numbers_texture;
	Texture* faces_texture;
	Texture* clock_texture;
	Texture* button_texture;
	Text bombText;
	int  tiles[31][17], Hidden_tiles[31][17], totalBombs, flagCount, bombsleft, timer, N, NN, special_offset_for_easymode;
	bool gameOver, gameStart, clockRunning, gameWon;
	string border_size;
	string FinalTime;

	// private functions 
	void initializewindow();
	void initializevaribales();

public:
	// constructors and destructors
	Game();
	virtual ~Game();
	// accessors
	const bool running() const;
	//functions 
	void update();
	void render();
	void initgrid();
	void events();
	void revealZeros(int i, int j);
	void counter(int number, float x, float y);
	void clock(float x, float y);
	void reset_button();
	void CheckWinState();
	void difficulty();
	Clock elapsedtime;
	int offsetX, offsetY;
	int x, y , test;
	RenderWindow* app;
	SoundBuffer Menu_ClickBuffer , PlacingFlagBuffer , OpeningTileBuffer , WinBuffer , ResetBuffer;
	Sound MenuClick , PlacingFlag , OpeningTile , win , reset;
	Music bgm;

};




#endif //GAME_H


