#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<time.h>

#define STRING(num) #num
using namespace sf;
Texture t;
int positionChange[2] = {500,-500 };
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
	Unit(float _x, float _y,Sprite target)
	{

		x = _x, y = _y;
		x += positionChange[rand() % 2];
		y += positionChange[rand() % 2];
		Vector2f targetV = target.getPosition();
		diffX = targetV.x - x;
		diffY = targetV.y - y;
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
	void moveSprite()
	{
		
		x += diffX/2000, y += diffY/2000;
		setPosition();
	}
	Sprite showSprite()
	{
		return s;
	}
private:
	float x = 0, y = 0;
	float xVector = 0, yVector = 0;
	float diffX;
	float diffY;
	int size = 0;
	float scale = 1;
	float moveVector;
	Sprite s;

};
int main()
{
	srand(time(NULL));
	int cnt = 0;
	int numOfHeart = 3;
	bool invincible = 0;
	RenderWindow app(VideoMode(500, 500), "intersectTest");
	t.loadFromFile("C:\\SFMLResource\\01 goBang\\images\\black.png");
	Texture t1;
	t1.loadFromFile("C:\\SFMLResource\\01 goBang\\images\\tablein.png");
	Sprite s1(t1);
	Texture theart1, theart2;
	theart1.loadFromFile("C:\\SFMLResource\\02 shooter\\images\\fullheart.png");
	theart2.loadFromFile("C:\\SFMLResource\\02 shooter\\images\\emptyheart.png");
	Sprite sh1(theart1), sh2(theart2);
	

	Text text;
	Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Regular);
	Color c = Color(0, 0,0);
	text.setFillColor(c);
	text.setPosition(300, 50);

	Texture tGameOver;
	tGameOver.loadFromFile("C:/SFMLResource/02 shooter/images/gameEnd.png");
	Sprite sGameOver(tGameOver);

	std::vector<Unit> unit;
	unit.push_back(Unit(rand() % 500, rand() % 500,s1));
	Clock clock,unitClock;
	float timer = 0;
	float unitTimer = 0;
	float gameTimer = 0;

	while (app.isOpen())
	{
		unitTimer += unitClock.getElapsedTime().asSeconds();
		gameTimer += unitClock.getElapsedTime().asSeconds();
		unitClock.restart();

		if (unitTimer > 2)
		{
			unit.push_back(Unit(rand() % 500, rand() % 500,s1));
			unitTimer -= 2;
		}
		if (invincible == 1)
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
			if (timer > 2)
			{
				invincible = 0;
				timer = 0;
			}
		}
		Event e;
		if (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					if (numOfHeart <= 0)
					{
						//TODO : restart;
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) s1.move(-6, 0);
			if (Keyboard::isKeyPressed(Keyboard::Right)) s1.move(6, 0);
			if (Keyboard::isKeyPressed(Keyboard::Up)) s1.move(0, -6);
			if (Keyboard::isKeyPressed(Keyboard::Down)) s1.move(0, 6);
			if (Keyboard::isKeyPressed(Keyboard::A)) s1.move(-6, 0);
			if (Keyboard::isKeyPressed(Keyboard::D)) s1.move(6, 0);
			if (Keyboard::isKeyPressed(Keyboard::W)) s1.move(0, -6);
			if (Keyboard::isKeyPressed(Keyboard::S)) s1.move(0, 6);
		}
		app.clear(Color::White);

		for (Unit& u : unit)
		{

			u.moveSprite();
			app.draw(u.showSprite());
			if (invincible == 1)
				continue;
			if (isCollided(s1, u.showSprite()) == 1)
			{
				cnt++;
				std::cout << cnt << std::endl;
				numOfHeart -= 1;
				invincible = 1;
				clock.restart();
			}

		}

		for (int i = 0; i < 3; i++)
		{
			if (numOfHeart > i)
			{
				sh1.setPosition(10 + 50 * i, 10);
				app.draw(sh1);
			}
			else
			{
				sh2.setPosition(10 + 50 * i, 10);
				app.draw(sh2);
			}
		}
		app.draw(s1);
		
		
		text.setString(std::to_string(gameTimer));
		app.draw(text);
		
		if (numOfHeart <= 0)
		{
			float endTime = gameTimer;
			text.setString(std::to_string(endTime));
			text.setFillColor(Color::White);
			text.setPosition(200, 400);
			while (1)
			{
				while (app.pollEvent(e))
				{

					if (e.type == Event::KeyPressed)
					{
						return 0;
					}
				}
				app.draw(sGameOver);
				app.draw(text);
				app.display();
			}
		}
		app.display();
	}
}