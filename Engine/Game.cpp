#include "MainWindow.h"
#include "Game.h"
#include "Box.h"
#include <random>
using namespace std;

Game::Game( MainWindow& wnd ):wnd( wnd ),	gfx( wnd ){
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xSpeed(-5, 5);
	std::uniform_int_distribution<int> ySpeed(-5, 5);
	std::uniform_int_distribution<int> bSize(20, 100);
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
	//set boxes and make them move
	for (int i = 0; i < numBoxes; ++i) {
		boxes[i].X = boxes[i].X + boxes[i].velocityX;
		boxes[i].Y = boxes[i].Y + boxes[i].velocityY;
		const int Xold = boxes[i].X;
		const int Yold = boxes[i].Y;
		//Colide check for screen
		boxes[i].X = XBound(boxes[i].X, boxes[i].Size);
		boxes[i].Y = YBound(boxes[i].Y, boxes[i].Size);
		if (boxes[i].X != Xold) boxes[i].velocityX = -boxes[i].velocityX;
		if (boxes[i].Y != Yold) boxes[i].velocityY = -boxes[i].velocityY;
		// 
		// ToDO: box overlap check for color merge before draw
	}
}

int Game::XBound(int x, int Width){
	if (x < 0) return 0;
	else if (x + Width >= gfx.ScreenWidth) return (gfx.ScreenWidth - 1) - Width;
	else return x;
}

int Game::YBound(int y, int Height){
	if (y < 0) return 0;
	else if (y + Height >= gfx.ScreenHeight) return (gfx.ScreenHeight - 1) - Height;
	else return y;
}

void Game::ComposeFrame(){
	for (int i=0; i < numBoxes; ++i) {
		gfx.DrawBox((boxes[i].X), boxes[i].Y, boxes[i].Size, boxes[i].c);
	}
}
