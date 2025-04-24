#include <SFML/Graphics.hpp>
#include<cmath>
#include <iostream>
#include <queue>
using namespace std;

vector<float> vx(360);
vector<float> vy(360);
int width = 1700, height = 800;
class izvor {
private:
	sf::Vector2f poz;
public:
	izvor(float poz_x, float poz_y)
	{
		poz = { sf::Vector2f(poz_x,poz_y) };
	}
	void pozicija(float smx, float smy)
	{
		poz = { sf::Vector2f(smx,smy) };
	}
	void crtaj(sf::RenderWindow& window, sf::Image& image)
	{
		for (int i = 0;i < 360;i++)
		{
			float x = poz.x, y = poz.y;
			sf::VertexArray linija(sf::Lines, 2);
			while (x > 0 && x < width && y>0 && y < height && image.getPixel(x, y) == sf::Color::Black)
			{
				x += vx[i];
				y += vy[i];
				
			}

			linija[0] = { poz };
			linija[1] = { sf::Vector2f(x,y) };
			window.draw(linija);
		}
	}
};


int main()
{
	for (int i = 0;i < 360;i++)
	{
		double radians = i * 3.14159265358979323846 / 180.0;
		vx[i] = cos(radians);
		vy[i] = sin(radians);
	}
	sf::RenderWindow window(sf::VideoMode(width, height), "SVETLO", sf::Style::Default);

	window.setFramerateLimit(60);
	sf::RectangleShape rec(sf::Vector2f(300, 20));
	sf::CircleShape kl(20);
	kl.setFillColor(sf::Color::White);
	kl.setPosition(1200, 100);
	rec.setFillColor(sf::Color::White);
	rec.setPosition(400, 300);
	sf::Event ev;
	sf::Mouse mouse;
	window.clear();
	window.draw(rec);
	kl.setRadius(100);
	window.draw(kl);
	sf::Texture texture;
	texture.create(width, height);
	texture.update(window);
	sf::Image image = texture.copyToImage();
	izvor mis = { 0.f,0.f };
	float smx = 0, smy = 0;
	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
				window.close();
		}
		smx = mouse.getPosition(window).x;
		smy = mouse.getPosition(window).y;
		window.clear();
		window.draw(kl);
		window.draw(rec);
		mis.pozicija(smx, smy);
		mis.crtaj(window, image);
		window.display();
	}
}