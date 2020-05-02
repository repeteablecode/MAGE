#include "MainWindow.h"
#include "Game.h"
#include "Box.h"
#include <random>
#include <vector>
using namespace std;


Game::Game( MainWindow& wnd ):wnd( wnd ),	gfx( wnd ){
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xSpeed(-3, 3);
	std::uniform_int_distribution<int> ySpeed(-3, 3);
	std::uniform_int_distribution<int> bSize(10, 300);
	Color bColor[3] = { Colors::Red,Colors::Blue, Colors::Yellow };
	int iColorCount = 0;
	
	for (int i = 0; i < numBoxes; i++){

		boxes[i].Size = bSize(rng);
		int xMaxPos = (gfx.ScreenWidth - boxes[i].Size); // make box not width going past edge of screen
		std::uniform_int_distribution<int> xPos(5, xMaxPos-5); // set 5 pixel buffer for start
		boxes[i].X = xPos(rng);
		int yMaxPos = (gfx.ScreenHeight - boxes[i].Size); //same a X
		std::uniform_int_distribution<int> yPos(5, yMaxPos - 5); // same as X
		boxes[i].Y = yPos(rng);
		boxes[i].velocityX = xSpeed(rng);
		boxes[i].velocityY = ySpeed(rng);
		if (iColorCount >= 3) { iColorCount = 0; }
		boxes[i].c = bColor[iColorCount++];
	}
}

void Game::Go(){
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(){
	// get box location
	// get boxes speed
	//DRAW 30000 boxes and test x,y vs y,x

	// check box array and make sure count is same
	
	// box screen bounds check

	// box collision check for color merge
}

void Game::ComposeFrame(){
	//for each box in box[] draw box x,y,size,color
	for (int i=0; i < numBoxes; ++i) {
		gfx.DrawBox((boxes[i].X), boxes[i].Y, boxes[i].Size, boxes[i].c);
	}
	//pixel color check for overlaps here and draw or figure out in update model
}
