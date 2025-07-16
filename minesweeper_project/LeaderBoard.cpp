#include "LeaderBoard.h"
#include <iostream>
#include <fstream>
#define EASY 0
#define MEDIUM 1
#define HARD 2
using namespace sf;
using namespace std;

void LeaderBoard::initializevariables()
{
	this->app = nullptr;
	this->LeaderboardTexture = nullptr;
	this->ButtonsTexture = nullptr;
	this->Page = 0;
	this->N = 2;

}

void LeaderBoard::initializewindow()
{
	this->LeaderBoardWindow = VideoMode(300, 400);
	this->app = new RenderWindow(VideoMode(this->LeaderBoardWindow), "LeaderBoard", Style::Titlebar | Style::Close);
	this->LeaderboardTexture = new Texture;
	this->app->setFramerateLimit(60);
	this->LeaderboardTexture->loadFromFile("images\\LeaderBoard.png");
	this->Leaderboard.setTexture(*this->LeaderboardTexture);
	this->ButtonsTexture = new Texture;
	this->ButtonsTexture->loadFromFile("images\\leaderboardbuttons.png");
	this->Buttons.setTexture(*this->ButtonsTexture);
	this->Font.loadFromFile("images\\minecraft.ttf");
	this->Player.setFont(this->Font);
	this->Score.setFont(this->Font);
	this->PageNumber.setFont(this->Font);
	this->PageNumber.setCharacterSize(20);
	this->PageNumber.setFillColor(Color::Black);
	this->Player.setCharacterSize(20);
	this->Player.setFillColor(Color::Black);
	this->Score.setCharacterSize(20);
	this->Score.setFillColor(Color::Yellow);
	this->getfilecontents();
	this->Menu_ClickBuffer.loadFromFile("images\\Menu.wav");
	this->MenuClick.setBuffer(this->Menu_ClickBuffer);
	this->MenuClick.setVolume(25.0f);


}

const bool LeaderBoard::running() const
{
	return this->app->isOpen();
}

void LeaderBoard::Update()
{
	Vector2i pos = Mouse::getPosition(*this->app);
	this->x = pos.x;
	this->y = pos.y;
	//cout << "horizontal position" << x << endl;
	//cout<<"vertical position"<<y<<endl;
	this->Events();
}


void LeaderBoard::render()
{
	this->app->clear(Color::White);
	this->app->draw(this->Leaderboard);
	this->buttons();
	this->PrintNamesAndScores();
	this->app->display();
}

void LeaderBoard::Events()
{
	while (this->app->pollEvent(events)) {

		if (events.type == Event::Closed) {
			this->app->close();
		}
		if (events.type == Event::KeyPressed) {
			if (events.key.code == Keyboard::Escape) {
				this->app->close();
			}
		}
		if (events.type == Event::MouseButtonPressed) {
			if (events.mouseButton.button == Mouse::Left) {
				if (x >= 260 && x <= 290 && y >= 330 && y <= 355) {
					MenuClick.play();
					Page++;
					cout << "next page";
				}
				if (x >= 10 && x <= 40 && y >= 330 && y <= 355) {
					MenuClick.play();
					Page--;
					cout << "prev page";
				}
				if (x >= 82 && x <= 126 && y >= 60 && y <= 90) {
					MenuClick.play();
					Page = 0;
					N = EASY;
					file_contents.clear();
					getfilecontents();
				}
				if (x >= 127 && x <= 171 && y >= 60 && y <= 90) {
					MenuClick.play();
					Page = 0;
					N = MEDIUM;
					file_contents.clear();
					getfilecontents();
				}
				if (x >= 172 && x <= 216 && y >= 60 && y <= 90) {
					MenuClick.play();
					Page = 0;
					N = HARD;
					file_contents.clear();
					getfilecontents();
				}

			}
		}



	}



}

void LeaderBoard::buttons()
{
	Buttons.setTextureRect(IntRect(135 * N , 0, 135, 20));
	Buttons.setPosition(82, 63);
	ostringstream ss;
	ss << Page + 1;
	string i = ss.str();
	PageNumber.setString(i);
	PageNumber.setPosition(146 , 350);
	this->app->draw(this->Buttons);
	this->app->draw(this->PageNumber);


}

void LeaderBoard::getfilecontents()
{
	string diff_file , line;
	switch (N) {
	case EASY:
		diff_file = "images\\Easy.txt";
		break;
	case MEDIUM:
		diff_file = "images\\Medium.txt";
		break;
	case HARD:
		diff_file = "images\\Hard.txt";
		break;
	default:
		break;
	}
	fstream Myfile;
	Myfile.open(diff_file, ios::in);
	if (Myfile.is_open()) {
		while (getline(Myfile, line)) {
			file_contents.push_back(line);
		}
		Myfile.close();
	}
	cout << file_contents.size();

}


void LeaderBoard::PrintNamesAndScores()
{
	if (Page < 0) {
		Page = (file_contents.size() -1 ) / 5;
	}
	if (Page > (file_contents.size() -1 ) / 5) {
		Page = 0;
	}

	string line;
	int L = 0;
	int start = Page * 5;
	int end = min(start + 5, (int)file_contents.size());
	
	for (int k = start; k < end; ++k) {
		line = file_contents[k];
		size_t pos = line.find("|");
		if (pos != string::npos) {
			PlayerScore = line.substr(pos + 1);
			PlayerName = line.substr(0, pos - 1);
			Player.setString(PlayerName);
			Score.setString(PlayerScore);
			Score.setPosition(230, 95 + (51 * L));
			Player.setPosition(27 , 95 +( 51* L));
			this->app->draw(Player);
			this->app->draw(Score);
			L++;

		}
	}



}



LeaderBoard::LeaderBoard()
{
	 initializevariables();
	 initializewindow();
	 Update();
	 render();
}

LeaderBoard::~LeaderBoard()
{
	delete this->app;
}
