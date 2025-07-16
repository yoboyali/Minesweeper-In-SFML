//
// Created by Ali Hamdy on 19/05/2025.
//
#include "Game.h"
#include <time.h>
#include <iostream>
#include <sstream>     // for std::ostringstream
#include <iomanip>     // for std::setw and std::setfill
#include "Choose_Difficulty.h"
#include "YouWin_Window.h"
#include "LeaderBoard.h"
#include "SFML/Audio.hpp"
using namespace sf;
using namespace std;

//private functions
void Game::initializewindow()
{
	this->videomode.width = N * 32 + 14;
	this->videomode.height = NN * 32 + 97 + special_offset_for_easymode;
	this->app = new RenderWindow(VideoMode(this->videomode), "Minesweeper", Style::Titlebar | Style::Close);
	this->app->setFramerateLimit(60);
	this->texture = new Texture();
	this->texture->loadFromFile("images\\tiles.jpg");
	this->s.setTexture(*this->texture);
	this->border_texture = new Texture();
	this->border_texture->loadFromFile(this->border_size);
	this->border.setTexture(*this->border_texture);
	this->border.setPosition(0, special_offset_for_easymode);
	this->numbers_texture = new Texture();
	this->numbers_texture->loadFromFile("images\\numbers.png");
	this->faces_texture = new Texture();
	this->faces_texture->loadFromFile("images\\faces.png");
	this->clock_texture = new Texture;
	this->clock_texture->loadFromFile("images\\numbers.png");
	this->clock_numbers.setTexture(*this->clock_texture);
	this->button_texture = new Texture;
	this->button_texture->loadFromFile("images\\image.png");
	this->button.setTexture(*this->button_texture);
	this->Menu_ClickBuffer.loadFromFile("images\\Menu.wav");
	this->PlacingFlagBuffer.loadFromFile("images\\PlacingFlag.wav");
	this->OpeningTileBuffer.loadFromFile("images\\OpeningTile.wav");
	this->WinBuffer.loadFromFile("images\\win.wav");
	this->ResetBuffer.loadFromFile("images\\Reset.wav");
	this->reset.setBuffer(this->ResetBuffer);
	this->win.setBuffer(this->WinBuffer);
	this->PlacingFlag.setBuffer(this->PlacingFlagBuffer);
	this->MenuClick.setBuffer(this->Menu_ClickBuffer);
	this->OpeningTile.setBuffer(this->OpeningTileBuffer);
	this->OpeningTile.setVolume(25.0f);
	this->MenuClick.setVolume(25.0f);
	this->PlacingFlag.setVolume(25.0f);
	this->win.setVolume(25.0f);
	this->reset.setVolume(15.0f);

}

void Game::initializevaribales()
{
	if (!(N == 9 || N == 17 || N == 31)) {
		N = 31;
		NN = 17;
	}
	if (N == 9) {
		border_size = "images\\border8x8.png";
		special_offset_for_easymode = 35;
	}
	else if (N == 17) {
		border_size = "images\\border16x16.png";
		special_offset_for_easymode = 0;
	}
	else if (N == 31) {
		border_size = "images\\try3.png"; 
		special_offset_for_easymode = 0;
	}




	this->offsetX = (23);
	this->offsetY = (107);
	this->app = nullptr;
	this->texture = nullptr;
	this->border_texture = nullptr;
	this->numbers_texture = nullptr;
	this->clock_texture = nullptr;
	this->button_texture = nullptr;
	this->gameOver = false;
	this->gameStart = false;
	this->gameWon = true;
	this->totalBombs = 0;
	this->flagCount = 0;
	this->bombsleft = 0;
	this->timer = 0;
	this->clockRunning = false;
	this->elapsedtime = Clock();
	this->test = 0;

}

Game::Game()
{
	this->initializevaribales();
	this->initializewindow();
	this->initgrid();
}

//contructors and destructors
Game::~Game()
{
	delete this->app;
}
//accessors
const bool Game::running() const
{
	return this->app->isOpen();
}
// functions
void Game::update()
{
	Vector2i pos = Mouse::getPosition(*this->app);
	this->x = (pos.x - this->offsetX) / 32 + 1;
	this->y = (pos.y - this->offsetY - special_offset_for_easymode) / 32 + 1;
	//cout << "vertical position" << this->x << endl;
	//cout << "horizontal position" << this->y << endl;
	this->events();
}

void Game::render()
{

	this->bombsleft = this->totalBombs - this->flagCount;
	bombText.setString(to_string(bombsleft));

	this->app->clear(Color(75, 75, 75, 225));
	for (int i = 1; i < N; i++)
		for (int j = 1; j < NN; j++) {
			int val = gameOver || gameWon ? Hidden_tiles[i][j] : tiles[i][j];
			s.setTextureRect(IntRect(val * 32, 0, 32, 32));
			s.setPosition((i - 1) * 32 + 24,
				(j - 1) * 32 + 107 + special_offset_for_easymode);
			this->app->draw(s);
		}
	this->app->draw(border);
	this->reset_button();
	this->counter(bombsleft, (videomode.width / 2 - 22.5f) - 92, offsetY - 77);
	this->clock((videomode.width / 2 - 22.5f) + 65, offsetY - 77);
	this->difficulty();
	//this->app->draw(button);
	this->app->display();
}

void Game::initgrid()
{
	srand(time(0));
	// Initialize grid and randomly place bombs
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < NN; j++) {
			tiles[i][j] = 10;
			if (rand() % 5 == 0) {
				Hidden_tiles[i][j] = 9; // set to bomb in the hidden grid
				this->totalBombs++;
			}
			else {
				Hidden_tiles[i][j] = 0; // otherwise set it to empty tile for now
			}
		}
	}
	for (int i = 1; i < N; i++)
		for (int j = 1; j < NN; j++) {
			int n = 0;
			if (Hidden_tiles[i][j] == 9) continue;
			if (i - 1 >= 0 && j + 1 < NN && Hidden_tiles[i - 1][j + 1] == 9) n++;
			if (j + 1 < NN && Hidden_tiles[i][j + 1] == 9) n++;
			if (i + 1 < N && j + 1 < NN && Hidden_tiles[i + 1][j + 1] == 9) n++;
			if (i + 1 < N && Hidden_tiles[i + 1][j] == 9) n++;
			if (i + 1 < N && j - 1 >= 0 && Hidden_tiles[i + 1][j - 1] == 9) n++;
			if (j - 1 >= 0 && Hidden_tiles[i][j - 1] == 9) n++;
			if (i - 1 >= 0 && Hidden_tiles[i - 1][j] == 9) n++;
			if (i - 1 >= 0 && j - 1 >= 0 && Hidden_tiles[i - 1][j - 1] == 9) n++;
			Hidden_tiles[i][j] = n;
		}
}

void Game::events()
{
	while (this->app->pollEvent(e))
	{
		switch (e.type)
		{
		case Event::Closed:
			this->app->close();
			break;

		case Event::MouseButtonPressed:

			//if (gameOver || gameWon)
			//	break;
			if (x >= N - 4 && x <= N - 1 && y >= -1 - (special_offset_for_easymode / 32 * 2) && y <= 0 - (special_offset_for_easymode / 32 * 2)) {
				MenuClick.play();
				Choose_Difficulty choose;
				while (choose.displaying()) {
					choose.update_diffWindow();
					choose.render_diffWindow();
				}
				N = choose.width;
				NN = choose.height;
				this->app->close();
				this->initializevaribales();
				this->initializewindow();
				this->initgrid();
				break;
			}
			if (x >= 1 && x <= 5 && y >= -1 - (special_offset_for_easymode / 32 * 2) && y <= 0 - (special_offset_for_easymode / 32 * 2)) {
				MenuClick.play();
				LeaderBoard Leader;
				while (Leader.running()) {
					Leader.Update();
					Leader.render();

				}
					

			}

			if (x >= 1 && x < N && y >= 1 && y < NN)
			{
				if (!clockRunning && !gameOver) {
					elapsedtime.restart();
					clockRunning = true;
					gameStart = true;
				}
				if (!gameOver && gameWon) {
					switch (e.mouseButton.button)
					{
					case Mouse::Left:

				
						if (tiles[x][y] == 10) {
							OpeningTile.play();
							if (Hidden_tiles[x][y] == 0)
								revealZeros(x, y);

							tiles[x][y] = Hidden_tiles[x][y];
							test++;
							cout << test << endl;
							
							if (Hidden_tiles[x][y] == 9) {
								gameOver = true;

							}
						}
						break;

					case Mouse::Right:
						if (tiles[x][y] == 10)
						{
							PlacingFlag.play();
							tiles[x][y] = 11;  // place flag
							this->flagCount++;
							if (flagCount == totalBombs) { CheckWinState(); }
							if (gameWon) {
								win.play();
								YouWin_Window win;
								win.setData(FinalTime, N);
								while (win.displaying()) {
									win.update();
									win.render();

								}
							}
							
						}
						else if (tiles[x][y] == 11)
						{
							PlacingFlag.play();
							tiles[x][y] = 10;  // remove flag
							this->flagCount--;
						}
						break;

					default:
						break;
					}
				}
			}
			if (x <= N / 2 + 1 && x >= N / 2 && y >= -1 && y <= 0) {
				reset.play();
				bgm.stop();
				test = 0;
				totalBombs = 0;
				bombsleft = 0;
				flagCount = 0;
				gameOver = false;
				initgrid();
				gameStart = false;
				clockRunning = false;
				gameWon = false;
				timer = 0;
				elapsedtime.restart();
				cout << "reset button clicked" << endl;
			}
			break;

		default:
			break;
		}
	}
}

void Game::revealZeros(int i, int j)
{
	// Base case: out of bounds or already revealed
	if (i < 1 || i >= N || j < 1 || j >= N) return;
	if (tiles[i][j] != 10) return; // already revealed or flagged

	tiles[i][j] = Hidden_tiles[i][j]; // reveal this tile
	test++;
	// Only recurse if it's a 0
	if (Hidden_tiles[i][j] == 0) {
		revealZeros(i - 1, j);
		revealZeros(i + 1, j);
		revealZeros(i, j - 1);
		revealZeros(i, j + 1);
		revealZeros(i - 1, j - 1);
		revealZeros(i - 1, j + 1);
		revealZeros(i + 1, j - 1);
		revealZeros(i + 1, j + 1);
	}


}

void Game::counter(int number, float x, float y)
{
	ostringstream ss;
	if (number < 0)
		ss << "-" << setw(2) << setfill('0') << -number;
	else
		ss << setw(3) << setfill('0') << number;

	string str = ss.str();


	this->numbers.setTexture(*this->numbers_texture); // this->numbers must be a pointer to your texture

	const int digitWidth = 24;
	const int digitHeight = 46;

	for (size_t i = 0; i < str.length(); ++i)
	{
		char c = str[i];
		int index;

		if (c == '-')
			index = 0;
		else
			index = c - '0' + 1;  // '0' is at index 1

		this->numbers.setTextureRect(IntRect(index * digitWidth, 0, digitWidth, digitHeight));
		this->numbers.setPosition(x + i * digitWidth, y + special_offset_for_easymode);
		this->app->draw(this->numbers);
	}
}

void Game::clock(float x, float y)
{


	// Update current time if clock is running
	if (clockRunning && !gameOver && !gameWon) {
		timer = elapsedtime.getElapsedTime().asSeconds();
		timer = min(timer, 999); // Cap at 999
	}

	// Always display 3 digits
	ostringstream ss;
	ss << setw(3) << setfill('0') << timer;
	string displayTime = ss.str();
	FinalTime = ss.str();
	// Draw each digit
	for (int i = 0; i < 3; i++) {
		char digit = displayTime[i];
		int index = digit - '0' + 1; // Convert to texture index

		clock_numbers.setTextureRect(IntRect(index * 24, 0, 24, 46));
		clock_numbers.setPosition(x + (i * 24), y + special_offset_for_easymode);
		app->draw(clock_numbers);
	}


}

void Game::reset_button()
{
	int i;
	this->faces.setTexture(*this->faces_texture);

	switch (gameOver) {
	case true:
		i = 1;
		break;
	case false:
		i = 0;
		break;
	default:
		i = 0;
		break;
	}
	if (gameWon) { i = 2; }


	this->faces.setTextureRect(IntRect(i * 45, 0, 45, 45));
	this->faces.setPosition(videomode.width / 2 - 22.5f, offsetY - 77 + special_offset_for_easymode);
	this->app->draw(this->faces);
}

void Game::CheckWinState()
{
	int x = 0;
	for (int i = 1; i < N; i++)
		for (int j = 1; j < NN; j++) {
			if (tiles[i][j] == 11 && Hidden_tiles[i][j] == 9 || tiles[i][j] == 10 && Hidden_tiles[i][j] == 9) x++;
		}
	if (x == totalBombs) {
		gameWon = true;
	}


}

void Game::difficulty()
{
	this->button.setTextureRect(IntRect(0, 0, 125, 32));
	this->button.setPosition(offsetX + 5, offsetY - 70 - special_offset_for_easymode);
	this->app->draw(this->button);
	this->button.setTextureRect(IntRect(125, 0, 125, 32));
	this->button.setPosition(N * 32 - 137, offsetY - 70 - special_offset_for_easymode);
	this->app->draw(this->button);

}