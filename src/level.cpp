#include <level.h>
#include <iostream>
#include <fstream>

void ssuds::Level::load_file(std::string fname)
{
	if(mGraph.get_num_nodes() != 0)
		return;

	std::ifstream fin(fname);
	std::string line;

	if (!fin.is_open())
	{
		std::cout << "Problem opening '" << fname << "' -- aborting load." << std::endl;
		return;
	}

	// Get the accounts
	std::string dummy_str;
	do
	{
		std::string identifier;
		fin >> identifier;

		if (identifier == "n")
		{
			std::string text;
			float x, y, radius;
			fin >> text;
			fin >> x;
			fin >> y;
			fin >> radius;
			ssuds::NamedCircle* circle = new ssuds::NamedCircle(text, x, y, radius);
			mGraph.add_node(circle);
			mList.push_back(circle);
		}

		else if (identifier == "e")
		{
			int index1, index2;
			float val;
			fin >> index1;
			fin >> index2;
			fin >> val;
			ssuds::NamedCircle* circle1 = mList[index1];
			ssuds::NamedCircle* circle2 = mList[index2];
			mGraph.add_edge(circle1, circle2, val);
		}

		std::getline(fin, dummy_str);
	} while (!fin.eof());
	fin.close();
	fin.clear();

	make_edges();
}

void ssuds::Level::make_edges()
{
	for (int i = 0; i < mGraph.get_num_nodes(); i++)
	{
		ssuds::NamedCircle* circle = mGraph.get_node(i);
		sf::Vector2f center1 = circle->get_center();
		for (int j = 0; j < mGraph.get_num_neighbors(circle); j++)
		{
			ssuds::NamedCircle* circle2 = mGraph.get_neighbor(circle, j);
			sf::Vector2f center2 = circle2->get_center();
			float val = mGraph.get_neighbor_edge(circle, j);
			ssuds::Line* line = new ssuds::Line(std::to_string(val), center1, center2);
			mEdges.push_back(line);
		}
	}
}

void ssuds::Level::toggle_text()
{
	if (showText)
		showText = false;
	else
		showText = true;
}

void ssuds::Level::check_contains(sf::Vector2f pos)
{
	for (int i = 0; i < mGraph.get_num_nodes(); i++)
		if (mGraph.get_node(i)->contains(pos))
		{
			for (int j = 0; j < mGraph.get_num_nodes(); j++)
				mGraph.get_node(j)->set_active(false);
			mGraph.get_node(i)->set_active(true);
			break;
		}
}

void ssuds::Level::draw(sf::RenderWindow& win, sf::Font& font)
{
	for (ssuds::Line* line : mEdges)
		line->draw(win);
	for (int i = 0; i < mGraph.get_num_nodes(); i++)
		win.draw(*(mGraph.get_node(i)->get_shape()));
	if (showText)
	{
		for (ssuds::Line* line : mEdges)
			line->draw_text(win, font);
		for (int i = 0; i < mGraph.get_num_nodes(); i++)
			mGraph.get_node(i)->draw_text(win, font);
	}
	
}
