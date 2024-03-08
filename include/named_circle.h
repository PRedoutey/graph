#pragma once
#include <SFML/Graphics.hpp>

namespace ssuds
{
	class NamedCircle : public sf::CircleShape
	{
	protected:
		std::string mText;
		bool mActive;

	public:

		NamedCircle(std::string text, float x, float y, float radius);
		~NamedCircle();

		void set_active(bool boolean);
		sf::Vector2f get_center();
		sf::Shape* get_shape();
		bool contains(sf::Vector2f mpos);
		void draw_text(sf::RenderWindow& win, sf::Font& font);
	};

}