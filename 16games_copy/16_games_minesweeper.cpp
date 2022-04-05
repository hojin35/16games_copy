#include<SFML/Graphics.hpp>
#include<time.h>
#include<iostream>
using namespace sf;

int xArray[8] = {1,0,-1,0,1,1,-1,-1};
int yArray[8] = {0,1,0,-1,1,-1,1,-1};
int w = 32;
int grid[12][12];
int sgrid[12][12]; // for showing
bool gameOver = false;
void dfs(int x,int y)
{
	if (sgrid[x][y] != 10 || grid[x][y] == 9)
		return;
	sgrid[x][y] = grid[x][y];

	

	for (int i = 0; i < 8; i++)
	{
		if (grid[x + xArray[i]][y + yArray[i]] == 0)
		{
			dfs(x + xArray[i], y + yArray[i]);
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (grid[x + xArray[i]][y + yArray[i]] != 9)
		{
			sgrid[x + xArray[i]][y + yArray[i]] = grid[x + xArray[i]][y + yArray[i]];

		}
	}
}
void mineSweeper()
{
	int countMine = 0;
	int closeCount = 0;
	RenderWindow app(VideoMode(400, 400), "Minesweeper!");

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			grid[i][j] = 0;
			sgrid[i][j] = 0;
		}
	}

	Texture t;
	t.loadFromFile("C:/16_Games/05 Minesweeper/images/tiles.jpg");
	Sprite s(t);

	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			sgrid[i][j] = 10;
			if (rand() % 5 == 0)
			{
				countMine++;
				grid[i][j] = 9;
			}
			else grid[i][j] = 0;
		}
	}

	std::cout << "coutMine : " << countMine << "\n";
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (grid[i][j] == 9) continue;
			for (int k = 0; k < 8; k++)
			{
				if (grid[i + xArray[k]][j + yArray[k]] == 9) n++;
			}
			grid[i][j] = n;
		}
	}

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;
		Event e;
		while (app.pollEvent(e))
		{

			if (e.type == Event::Closed)
			{
				app.close();
			}
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					if (gameOver == true)
					{
						gameOver = false;
						app.close();
						mineSweeper();
						return;
					}
					else
					{
						sgrid[x][y] = grid[x][y];
						for (int i = 0; i < 8; i++)
						{
							if (grid[x + xArray[i]][y + yArray[i]] == 0)
							{
								dfs(x + xArray[i], y + yArray[i]);
							}
						}
					}
				}
				else if (e.key.code == Mouse::Right) sgrid[x][y] = 11;
			}
		}
		app.clear(Color::White);
		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				if (sgrid[x][y] == 9)
				{
					sgrid[i][j] = grid[i][j];
					gameOver = true;
				}
				if (sgrid[i][j] == 10 || sgrid[i][j] == 11)
				{
					closeCount++;
				}
				s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
				s.setPosition(i * w, j * w);
				app.draw(s);
			}
		}
		if (countMine == closeCount)
		{
			std::cout << "CLEAR" << '\n';
		}
		closeCount = 0;
		app.display();
	}
	return;
}
int main()
{
	srand(time(NULL));
	mineSweeper();
	return 0;
}
