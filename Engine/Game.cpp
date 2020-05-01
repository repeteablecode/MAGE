#include "MainWindow.h"
#include "Game.h"
#include "Box.h"
#include <random>

Game::Game( MainWindow& wnd ):wnd( wnd ),	gfx( wnd ){
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xSpeed(-3, 3);
	std::uniform_int_distribution<int> ySpeed(-3, 3);
	std::uniform_int_distribution<int> bSize(10, 100);
	
	static constexpr int numBoxes = 3;
	for (int i = 0; i < numBoxes; i++){
		Box box;
		//Box box[3];
		//for each box process and draw in frame
		// box.c = RandomColor or something
		box.Size = bSize(rng);
		int xMaxPos = (gfx.ScreenWidth - box.Size); // make box not width going past edge of screen
		std::uniform_int_distribution<int> xPos(5, xMaxPos-5); // set 5 pixel buffer for start
		box.X = xPos(rng);
		int yMaxPos = (gfx.ScreenHeight - box.Size); //same a X
		std::uniform_int_distribution<int> yPos(5, yMaxPos - 5); // same as X
		box.Y = yPos(rng);
		box.velocityX = xSpeed(rng);
		box.velocityY = ySpeed(rng);
	}
}

void Game::Go(){
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(){
}

void Game::ComposeFrame(){
}
