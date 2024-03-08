#pragma once
#include <SFML/Graphics.hpp>

namespace ssuds
{
	class Line
	{
	protected:
		std::string mText;
		sf::VertexArray mLine;

	public:

		Line(std::string text, sf::Vector2f pos1, sf::Vector2f pos2);
		~Line();

		sf::Vector2f get_center();
		void draw(sf::RenderWindow& win);
		void draw_text(sf::RenderWindow& win, sf::Font& font);
	};

}