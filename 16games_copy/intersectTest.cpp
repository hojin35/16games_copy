#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<time.h>

using namespace sf;
Texture t;
bool isCollided(Sprite s1, Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}
class Unit
{
public:
	Unit()
	{
		s.setPosition(50, 50);
		spriteInit();
	}
	Unit(float _x, float _y)
	{
		x = _x, y = _y;
		spriteInit();
	}
	void spriteInit()
	{
		scale = 1;
		size = 100;
		s.setPosition(x, y);
		s.setColor(Color::Green);
		
		s.setTexture(t);
	}
	void setPosition()
	{
		s.setPosition(x, y);
	}
	void setScale()
	{
		s.setScale(scale, scale);
	}
	Sprite showSprite()
	{
		return s;
	}
private:
	float x = 0, y = 0;
	int size = 0;
	float scale = 1;
	Sprite s;
	
};
int main()
{
	srand(time(NULL));

	RenderWindow app(VideoMode(500, 500), "intersectTest");
	t.loadFromFile("C:\\SFMLResource\\01 goBang\\images\\black.png");
	std::vector<Unit> unit;
	unit.push_back(Unit(rand() % 500, rand() % 500));

	while (app.isOpen())
	{
		Event e;
		if (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					unit.push_back(Unit(rand() % 500, rand() % 500));
				}
			}
		}
		app.clear(Color::White);
		for (Unit& u : unit)
		{
			app.draw(u.showSprite());
		}
		app.display();
	}
}