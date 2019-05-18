#include "pch.h"
#include "Game.h"
#include "Application.h"

Game::Game()
{
}


Game::~Game()
{
}


void Game::Init() {


	srand(time(NULL));

	if (!font.loadFromFile("Resources/Pokemon_Solid.ttf")) {

		// error
	}


	// create board
	boardSize = { 5 , 5 };
	board.clear();

	for (int x = 0; x < boardSize.x; x++) {

		board.push_back(std::vector<Tile>());

		for (int y = 0; y < boardSize.y; y++) {

			board.at(x).push_back(Tile());
		}
	}


	// create total arrays
	rowTotals.clear();
	for (int row = 0; row < boardSize.y; row++) {

		rowTotals.push_back(Totals());
	}

	columnTotals.clear();
	for (int column = 0; column < boardSize.x; column++) {

		columnTotals.push_back(Totals());
	}


	// initialise display variables
	tileSize = { 80.0f, 80.0f };
	tileSpacing = { 20.0f, 20.0f };

	tileColour = sf::Color(49, 150, 56);
	rowTotalColour = sf::Color(200, 196, 40);
	columnTotalColour = sf::Color(48, 155, 193);

	tileSprite = new sf::RectangleShape(tileSize);
	tileSprite->setFillColor(tileColour);


	tileText.setFont(font);
	tileText.setFillColor(sf::Color::Black);
	tileText.setCharacterSize(30);

	totalText = tileText;
	totalText.setCharacterSize(20);
	
	scoreText = tileText;
	scoreText.setCharacterSize(50);
	scoreText.setPosition(800, 50);
	scoreText.setString("0");
	scoreText.setFillColor(sf::Color::White);

	currentLevel = 1;

	levelText = scoreText;
	levelText.setPosition(800, 200);
	levelText.setString("Level " + std::to_string(currentLevel));

	StartGame();
}

void Game::CleanUp() {


	if (tileSprite) {

		delete tileSprite;
		tileSprite = nullptr;
	}
}

void Game::OnEvent(sf::Event& event) {

	if (event.type == sf::Event::MouseButtonPressed) {


		sf::Vector2i mousePos = { event.mouseButton.x, event.mouseButton.y };

		for (int x = 0; x < boardSize.x; x++) {

			for (int y = 0; y < boardSize.y; y++) {

				float xLower = 50.0f + (tileSize.x + tileSpacing.x) * (float)x;
				float xUpper = xLower + tileSize.x;
				float yLower = 50.0f + (tileSize.y + tileSpacing.y) * (float)y;
				float yUpper = yLower + tileSize.y;

				if (xLower < mousePos.x && mousePos.x < xUpper &&
					yLower < mousePos.y && mousePos.y < yUpper) {

					// do the thing

					if (event.mouseButton.button == sf::Mouse::Left) {
						ClickTile(x, y);
					}
					else if (event.mouseButton.button == sf::Mouse::Right) {
						MarkTile(x, y);
					}
					break;
				}
			}
		}
	}
}



void Game::ClickTile(int x, int y) {

	if (x < 0 || x >= boardSize.x ||
		y < 0 || y >= boardSize.y) {

		std::cout << "tryed to click tile outside board range" << std::endl;
		return;
	}


	if (!board[x][y].revealed) {

		RevealTile(x, y);
	}
}

void Game::MarkTile(int x, int y) {

	if (x < 0 || x >= boardSize.x ||
		y < 0 || y >= boardSize.y) {

		std::cout << "tryed to mark tile outside board range" << std::endl;
		return;
	}

	board[x][y].marked = !board[x][y].marked;
}

void Game::RevealTile(int x, int y) {

	if (x < 0 || x >= boardSize.x ||
		y < 0 || y >= boardSize.y) {

		std::cout << "tryed to reveal tile outside board range" << std::endl;
		return;
	}

	board[x][y].revealed = true;

	score *= board[x][y].multiplier;

	scoreText.setString(std::to_string(score));

	if (score == 0) {

		GameOver();
	}

	totalTilesRevealed++;

	if (board[x][y].multiplier > 1) {

		totalMultipliersFound++;

		if (totalMultipliersFound >= threes + twos) {

			BoardComplete();
		}
	}
}


void Game::RevealBoard() {

	for (int x = 0; x < boardSize.x; x++) {

		for (int y = 0; y < boardSize.y; y++) {

			board[x][y].revealed = true;
		}
	}
}

void Game::Level1() {

	voltorbs = 6;
	threes = rand() % 3;

	switch (threes) {
	case 0:
		twos = 5;
		break;
	case 1:
		twos = 4;
		break;
	case 2:
		twos = 2;
		break;
	}
}

void Game::Level2() {

	voltorbs = 7;
	threes = rand() % 5;

	switch (threes) {
	case 0:
		twos = 6;
		break;
	case 1:
		twos = 5;
		break;
	case 2:
		twos = 3;
		break;
	case 3:
		twos = 1;
		break;
	case 4:
		twos = 0;
		break;
	}
}

void Game::Level3() {

	voltorbs = 8;
	threes = rand() % 3;

	switch (threes) {
	case 0:
		threes = 1;
		twos = 6;
		break;
	case 1:
		threes = 2;
		twos = 4;
		break;
	case 2:
		threes = 4;
		twos = 1;
		break;
	}
}

void Game::Level4() {

	voltorbs = 8;
	threes = rand() % 3;

	switch (threes) {
	case 0:
		threes = 0;
		twos = 8;
		break;
	case 1:
		threes = 3;
		twos = 3;
		break;
	case 2:
		threes = 5;
		twos = 0;
		break;
	}
}

void Game::Level5() {

	voltorbs = 10;
	threes = rand() % 4;

	switch (threes) {
	case 0:
		twos = 9;
		break;
	case 1:
		threes = 1;
		twos = 7;
		break;
	case 2:
		threes = 2;
		twos = 6;
		break;
	case 3:
		threes = 5;
		twos = 1;
		break;
	}
}

void Game::Level6() {

	voltorbs = 10;
	threes = rand() % 3;

	switch (threes) {
	case 0:
		threes = 3;
		twos = 5;
		break;
	case 1:
		threes = 4;
		twos = 3;
		break;
	case 2:
		threes = 5;
		twos = 2;
		break;
	}
}

void Game::Level7() {

	voltorbs = (rand() % 2 == 1) ? 10 : 13;

	if (voltorbs == 10) {

		threes = 3;
		twos = 6;
	}
	else if (voltorbs == 13) {

		threes = 6;
		twos = 1;
	}

}


void Game::InsertOntoBoard(int value) {

	bool locationFound = false;

	while (!locationFound) {

		int x = rand() % boardSize.x;
		int y = rand() % boardSize.y;

		if (board[x][y].multiplier == 1) {

			board[x][y].multiplier = value;
			locationFound = true;
		}
	}
}


void Game::BoardComplete() {

	playing = false;

	if (currentLevel < 7) {
		currentLevel++;
	}

	RevealBoard();

	StartGame();
}

void Game::GameOver() {

	playing = false;

	scoreText.setString("You Lose");

	RevealBoard();

	if (totalTilesRevealed <= currentLevel) {

		currentLevel = totalTilesRevealed;
	}

	StartGame();
}

void Game::StartGame() {

	totalMultipliersFound = 0;
	totalTilesRevealed = 0;
	score = 1;
	scoreText.setString("0");
	playing = true;

	levelText.setString("Level " + std::to_string(currentLevel));


	switch (currentLevel) {
	case 1:
		Level1();
		break;
	case 2:
		Level2();
		break;
	case 3:
		Level3();
		break;
	case 4:
		Level4();
		break;
	case 5:
		Level5();
		break;
	case 6:
		Level6();
		break;
	case 7:
		Level7();
		break;
	default:
		Level1();
		break;
	}

	// generate new board
	for (int x = 0; x < boardSize.x; x++) {

		for (int y = 0; y < boardSize.y; y++) {

			Tile newTile;
			newTile.multiplier = 1;
			newTile.revealed = false;

			board[x][y] = newTile;
		}
	}


	for (int i = 0; i < voltorbs; i++) {

		InsertOntoBoard(0);
	}

	for (int i = 0; i < threes; i++) {

		InsertOntoBoard(3);
	}

	for (int i = 0; i < twos; i++) {

		InsertOntoBoard(2);
	}

	// get column totals
	for (int x = 0; x < boardSize.x; x++) {

		columnTotals[x].multipliers = 0;
		columnTotals[x].voltorbs = 0;

		for (int y = 0; y < boardSize.y; y++) {

			columnTotals[x].multipliers += board[x][y].multiplier;

			if (board[x][y].multiplier == 0) {

				columnTotals[x].voltorbs++;
			}
		}
	}

	// get row totals
	for (int y = 0; y < boardSize.y; y++) {

		rowTotals[y].multipliers = 0;
		rowTotals[y].voltorbs = 0;

		for (int x = 0; x < boardSize.x; x++) {

			rowTotals[y].multipliers += board[x][y].multiplier;

			if (board[x][y].multiplier == 0) {

				rowTotals[y].voltorbs++;
			}
		}
	}



	score = 1;

}


void Game::Draw(Renderer& renderer) {

	
	tileSprite->setFillColor(tileColour);

	for (int x = 0; x < boardSize.x; x++) {

		for (int y = 0; y < boardSize.y; y++) {

			// get tile position
			sf::Vector2f tilePos(50.0f + (tileSize.x + tileSpacing.x) * (float)x, 50.0f + (tileSize.y + tileSpacing.y) * (float)y);

			// draw tile
			tileSprite->setPosition(tilePos);
			renderer.Draw(*tileSprite);
			
			// draw text
			if (board[x][y].revealed) {

				tileText.setString(std::to_string(board[x][y].multiplier));

				sf::FloatRect textBounds = tileText.getLocalBounds();
				tileText.setPosition(tilePos + (tileSize / 2.0f) - sf::Vector2f(textBounds.width / 2.0f, textBounds.height / 2.0f));
				renderer.Draw(tileText);
			}
			else if (board[x][y].marked) {

				tileText.setString("V");

				sf::FloatRect textBounds = tileText.getLocalBounds();
				tileText.setPosition(tilePos + (tileSize / 2.0f) - sf::Vector2f(textBounds.width / 2.0f, textBounds.height / 2.0f));
				renderer.Draw(tileText);
			}
		}
	}

	tileSprite->setFillColor(rowTotalColour);
	float row_total_x = 50.0f + (tileSize.x + tileSpacing.x) * (float)boardSize.x;

	for (int row = 0; row < boardSize.y; row++) {

		// get tile position
		sf::Vector2f tilePos(row_total_x, 50.0f + (tileSize.y + tileSpacing.y) * (float)row);

		// draw tile
		tileSprite->setPosition(tilePos);
		renderer.Draw(*tileSprite);


		// draw multiplier total

		totalText.setString(std::to_string(rowTotals[row].multipliers));

		sf::FloatRect textBounds = totalText.getLocalBounds();
		sf::Vector2f textOffset(tileSize.x * 3.0f / 4.0f, tileSize.y / 4.0f);
		totalText.setPosition(tilePos + textOffset - sf::Vector2f(textBounds.width / 2.0f, textBounds.height / 2.0f));
		renderer.Draw(totalText);


		// draw voltorb total

		totalText.setString(std::to_string(rowTotals[row].voltorbs));

		textBounds = totalText.getLocalBounds();
		textOffset = { tileSize.x * 3.0f / 4.0f, tileSize.y * 3.0f / 4.0f };
		totalText.setPosition(tilePos + textOffset - sf::Vector2f(textBounds.width / 2.0f, textBounds.height / 2.0f));
		renderer.Draw(totalText);
	}


	tileSprite->setFillColor(columnTotalColour);
	float column_total_y = 50.0f + (tileSize.y + tileSpacing.y) * (float)boardSize.y;

	for (int column = 0; column < boardSize.x; column++) {

		// get tile position
		sf::Vector2f tilePos(50.0f + (tileSize.x + tileSpacing.x) * (float)column, column_total_y);

		// draw tile
		tileSprite->setPosition(tilePos);
		renderer.Draw(*tileSprite);


		// draw multiplier total

		totalText.setString(std::to_string(columnTotals[column].multipliers));

		sf::FloatRect textBounds = totalText.getLocalBounds();
		sf::Vector2f textOffset(tileSize.x * 3.0f / 4.0f, tileSize.y / 4.0f);
		totalText.setPosition(tilePos + textOffset - sf::Vector2f(textBounds.width / 2.0f, textBounds.height / 2.0f));
		renderer.Draw(totalText);


		// draw voltorb total

		totalText.setString(std::to_string(columnTotals[column].voltorbs));

		textBounds = totalText.getLocalBounds();
		textOffset = { tileSize.x * 3.0f / 4.0f, tileSize.y * 3.0f / 4.0f };
		totalText.setPosition(tilePos + textOffset - sf::Vector2f(textBounds.width / 2.0f, textBounds.height / 2.0f));
		renderer.Draw(totalText);
	}

	renderer.Draw(scoreText);
	renderer.Draw(levelText);
}
