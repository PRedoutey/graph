#pragma once
#include <named_circle.h>
#include <line.h>
#include <graph.h>
#include <array_list.h>

namespace ssuds
{
	class Level
	{
	protected:
		ssuds::Graph<ssuds::NamedCircle*,float> mGraph;
		ssuds::ArrayList<ssuds::NamedCircle*> mList;
		ssuds::ArrayList<ssuds::Line*> mEdges;
		bool showText = true;

	public:
		void load_file(std::string fname);
		void make_edges();
		void toggle_text();
		void check_contains(sf::Vector2f pos);
		void draw(sf::RenderWindow& win, sf::Font& font);
	};
}