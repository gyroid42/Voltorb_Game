#pragma once

#include "Renderer.h"

class Game
{

	struct Tile {

		int multiplier;
		bool revealed;
		bool marked;

		Tile(int newMultiplier, bool newRevealed = false) {

			multiplier = newMultiplier;
			revealed = newRevealed;
			marked = false;
		}

		Tile() {

			multiplier = rand() % 4;
			revealed = false;
			marked = false;
		}
	};

	struct Totals {

		int voltorbs;
		int multipliers;
	};

public:
	Game();
	~Game();


	void Init();
	void CleanUp();

	void OnEvent(sf::Event& event);

	void Draw(Renderer& renderer);

	void StartGame();

protected:


	void BoardComplete();
	void GameOver();



	void Level1();
	void Level2();
	void Level3();
	void Level4();
	void Level5();
	void Level6();
	void Level7();


	void ClickTile(int x, int y);
	void RevealTile(int x, int y);

	void MarkTile(int x, int y);

	void RevealBoard();


	void InsertOntoBoard(int value);

	sf::Vector2i boardSize;
	std::vector< std::vector<Tile>> board;

	std::vector<Totals> rowTotals;
	std::vector<Totals> columnTotals;

	int currentLevel;
	int voltorbs;
	int threes;
	int twos;
	int totalMultipliersFound;
	int totalTilesRevealed;

	int score;

	sf::Vector2f tileSize;
	sf::Vector2f tileSpacing;
	sf::Color tileColour;
	sf::Color rowTotalColour;
	sf::Color columnTotalColour;

	sf::Font font;
	sf::Text tileText;
	sf::Text totalText;
	sf::Text scoreText;
	sf::Text levelText;

	sf::Shape* tileSprite;


	bool playing;

};

