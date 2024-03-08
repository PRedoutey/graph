#include <line.h>
#include <iostream>

ssuds::Line::Line(std::string text, sf::Vector2f pos1, sf::Vector2f pos2)
{
	mText = text;
	mLine = sf::VertexArray(sf::LineStrip, 2);
	mLine[0].position = pos1;
	mLine[0].color = sf::Color(150, 0, 0);
	mLine[1].position = pos2;
	mLine[1].color = sf::Color(150, 0, 0);
}

ssuds::Line::~Line(){}

sf::Vector2f ssuds::Line::get_center()
{
	float x = (mLine[0].position.x + mLine[1].position.x) / 2;
	float y = (mLine[0].position.y + mLine[1].position.y) / 2;
	sf::Vector2f center = sf::Vector2f(x, y);
	return center;
}

void ssuds::Line::draw(sf::RenderWindow& win) { win.draw(mLine); }

void ssuds::Line::draw_text(sf::RenderWindow& win, sf::Font& font)
{
	sf::Text text;
	text.setFont(font);
	text.setString(mText);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color(0, 255, 0));

	sf::Vector2f cur_pos = get_center();
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(cur_pos);

	win.draw(text);
}
