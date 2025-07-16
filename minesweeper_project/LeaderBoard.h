#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "sstream"
using namespace sf;
using namespace std;

class LeaderBoard
{	private:
	//variables
	VideoMode LeaderBoardWindow;
	Event events;
	Texture* LeaderboardTexture;
	Texture* ButtonsTexture;
	Sprite Buttons;
	Sprite Leaderboard;
	int x, y ,Page, N;
	vector<string> file_contents;
	string PlayerName, PlayerScore;
	Text Player, Score , PageNumber;
	Font Font;

	void initializevariables();
	void initializewindow();
	void Events();
	void buttons();
	void getfilecontents();
	void PrintNamesAndScores();
	



public:
	//constructors and destructors
	LeaderBoard();
	virtual ~LeaderBoard();
	//accessors
	const bool running() const;
	void Update();
	void render();
	RenderWindow* app;
	SoundBuffer Menu_ClickBuffer;
	Sound MenuClick;

};

