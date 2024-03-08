#include <named_circle.h>
#include <iostream>

ssuds::NamedCircle::NamedCircle(std::string text, float x, float y, float radius) : sf::CircleShape(radius)
{
	get_shape()->setFillColor(sf::Color(200, 150, 0));
	get_shape()->setOutlineColor(sf::Color(150, 0, 0));
	get_shape()->setOutlineThickness((float)radius/7);
	get_shape()->setPosition(x, y);
	mText = text;
	mActive = false;
}

ssuds::NamedCircle::~NamedCircle(){}

void ssuds::NamedCircle::set_active(bool boolean)
{
	mActive = boolean;
	if (mActive)
		get_shape()->setOutlineColor(sf::Color(0, 200, 200));
	else
		get_shape()->setOutlineColor(sf::Color(150, 0, 0));
}

sf::Vector2f ssuds::NamedCircle::get_center()
{
	sf::Vector2f center = get_shape()->getPosition();
	center.x += getRadius();
	center.y += getRadius();
	return center;
}

sf::Shape* ssuds::NamedCircle::get_shape()
{
	return this;
}

bool ssuds::NamedCircle::contains(sf::Vector2f pos)
{
	sf::Vector2f center = get_center();
	float distance_sq = pow(center.x - pos.x, 2) + pow(center.y - pos.y, 2);
	if (distance_sq <= getRadius() * getRadius())
		return true;
	return false;
}

void ssuds::NamedCircle::draw_text(sf::RenderWindow& win, sf::Font& font)
{
	int radius = (int)getRadius();
	if (radius < 14)
		radius = 14;

	sf::Text text;
	text.setFont(font);
	text.setString(mText);
	text.setCharacterSize(radius);
	text.setFillColor(sf::Color(227,227,227));

	sf::Vector2f center = get_center();
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(center);

	win.draw(text);
}
