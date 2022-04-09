#include<SFML/Graphics.hpp>
#include<iostream>

#define BLACKTURN 1
#define WHITETURN 2
using namespace sf;
int main()
{
	int x = 0, y = 0;
	RenderWindow app(VideoMode(420, 420), "GO");

	Texture t1, t2;
	Texture tb1, tb2;
	t1.loadFromFile("C:/SFMLResource/01 goBang/images/black.png");
	t2.loadFromFile("C:/SFMLResource/01 goBang/images/white.png");
	tb1.loadFromFile("C:/SFMLResource/01 goBang/images/tableout.png");
	tb2.loadFromFile("C:/SFMLResource/01 goBang/images/tablein.png");
	Sprite s1(t1);
	Sprite s2(t2);
	Sprite sb1(tb1);
	Sprite sb2(tb2);
	int turn = BLACKTURN;
	int lastTurn = WHITETURN;
	int grid[20][20] = { 0, };
	int gameOver = 0;
	int countGoStone = 0;
	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					x = pos.x / 20;
					y = pos.y / 20;
					// when mouse get out gomoku table
					if (x < 1 || x>19 || y < 1 || y > 19)
					{

					}
					else if (grid[x][y] == 0)
					{
						grid[x][y] = turn;
						lastTurn = turn;
						if (turn == BLACKTURN)
							turn = WHITETURN;
						else if (turn == WHITETURN)
							turn = BLACKTURN;
					}
				}
			}
		}
		if (gameOver == 1)
			std::cout << "black stone WIN"<<std::endl;
		if (gameOver == 2)
			std::cout << "white stone WIN" << std::endl;
		app.clear(Color::Color(255,167,0,255));

		// draw go stone table
		for (int i = 1; i <= 20; i++)
		{
			for (int j = 1; j <= 20; j++)
			{
				if (i == 1 || j == 1 || i == 20 || j == 20)
				{
					sb1.setPosition(i * 20 - 10, j * 20 -10);
					app.draw(sb1);
				}
				else
				{
					sb2.setPosition(i * 20 -10, j * 20 -10);
					app.draw(sb2);
				}
			}
		}

		// draw go stone
		for (int i = 1; i <= 19; i++)
		{
			for (int j = 1; j <= 19; j++)
			{
				if (grid[i][j] == 1)
				{
					s1.setPosition(i * 20, j * 20);
					app.draw(s1);
				}
				if (grid[i][j] == 2)
				{
					s2.setPosition(i * 20, j * 20);
					app.draw(s2);
				}
			}
		}
		app.display();

		// game over check
		for (int i = 1; i <= 19; i++)
		{
			if (gameOver != 0)
				break;
			for (int j = 1; j <= 19; j++)
			{
				if (gameOver != 0)
					break;
				countGoStone = 0;
				for (int k = 0; k < 5; k++)
				{
					if (grid[i + k][j] == lastTurn)
						countGoStone++;
					if (countGoStone == 5)
						gameOver = lastTurn;
				}
				countGoStone = 0;
				for (int k = 0; k < 5; k++)
				{
					if (grid[i][j+k] == lastTurn)
						countGoStone++;
					if (countGoStone == 5)
						gameOver = lastTurn;
				}
				countGoStone = 0;
				for (int k = 0; k < 5; k++)
				{
					if (grid[i + k][j+k] == lastTurn)
						countGoStone++;
					if (countGoStone == 5)
						gameOver = lastTurn;
				}
				
			}
			
		}
	}
}