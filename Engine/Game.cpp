/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		if (!inhRight) {
			vx += 1;
			inhRight = true;
		}
	}
	else
		inhRight = false;

	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		if (!inhLeft) {
			vx -= 1;
			inhLeft = true;
		}
	}
	else
		inhLeft = false;

	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		if (!inhUp) {
			vy -= 1;
			inhUp = true;
		}
	}
	else
		inhUp = false;

	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		if (!inhDown) {
			vy += 1;
			inhDown = true;
		}
	}
	else
		inhDown = false;

	x += vx;
	y += vy;
	shapeChanged = wnd.kbd.KeyIsPressed(VK_SHIFT);
	if (x + 5 >= gfx.ScreenWidth)
	{
		x = gfx.ScreenWidth - 6;
		vx = 0;

	}
	if (y + 5 >= gfx.ScreenHeight)
	{
		y = gfx.ScreenHeight - 6;
		vy = 0;
	}
	if (x - 5 < 0)
	{
		x = 5;
		vx = 0;
	}
	if (y - 5 < 0)
	{
		y = 5;
		vy = 0;
	}
	/*if (wnd.kbd.KeyIsPressed(VK_CONTROL)) {
		normalGb += 50;
		if (normalGb > 255)
			normalGb = 0;
	}*/
	if (x > gfx.ScreenWidth / 2 - 100 && x < gfx.ScreenWidth / 2 + 100)
	{
		tempGb = normalGb;
		normalGb = stripGb;
	}
	else {
		normalGb = 255;
	}
}

void Game::drawCursor(int x,  int y, int rgb) {
	gfx.PutPixel(x + 3, y, 255, rgb, rgb);
	gfx.PutPixel(x + 4, y, 255, rgb, rgb);
	gfx.PutPixel(x + 5, y, 255, rgb, rgb);

	gfx.PutPixel(x - 3, y, 255, rgb, rgb);
	gfx.PutPixel(x - 4, y, 255, rgb, rgb);
	gfx.PutPixel(x - 5, y, 255, rgb, rgb);

	gfx.PutPixel(x, y + 3, 255, rgb, rgb);
	gfx.PutPixel(x, y + 4, 255, rgb, rgb);
	gfx.PutPixel(x, y + 5, 255, rgb, rgb);

	gfx.PutPixel(x, y - 3, 255, rgb, rgb);
	gfx.PutPixel(x, y - 4, 255, rgb, rgb);
	gfx.PutPixel(x, y - 5, 255, rgb, rgb);
}


void Game::ComposeFrame()
{
	if (shapeChanged) {
		gfx.PutPixel(x - 5, y - 5, 255, normalGb, normalGb);
		gfx.PutPixel(x - 5, y - 4, 255, normalGb, normalGb);
		gfx.PutPixel(x - 5, y - 3, 255, normalGb, normalGb);
		gfx.PutPixel(x - 4, y - 5, 255, normalGb, normalGb);
		gfx.PutPixel(x - 3, y - 5, 255, normalGb, normalGb);
		gfx.PutPixel(x - 5, y + 5, 255, normalGb, normalGb);
		gfx.PutPixel(x - 5, y + 4, 255, normalGb, normalGb);
		gfx.PutPixel(x - 5, y + 3, 255, normalGb, normalGb);
	}
	else
	{
		drawCursor(x, y, normalGb);
		drawCursor(x_fixed, y_fixed, rgb_fixed);
	}
}