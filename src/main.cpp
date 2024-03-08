//Name: Patrick Redoutey
//Class: ETEC2101-02
//Lab: 09

#include <iostream>
#include <string>
#include <graph.h>
#include <level.h>

#define SCREENWIDTH 1250
#define SCREENHEIGHT 950

int main()
{
    // Non-graphical tests
    ssuds::Graph<std::string, float> test_graph;

    // ... adding nodes and edges to the empty graph...
    test_graph.add_node("A");
    test_graph.add_node("B");
    test_graph.add_node("D");
    test_graph.add_node("F");
    test_graph.add_node("G");
    test_graph.add_node("R");
    test_graph.add_edge("A", "B", 3.7f);
    test_graph.add_edge("F", "D", 2.1f);
    test_graph.add_edge("F", "G", 1.3f);
    test_graph.add_edge("G", "G", 0.6f);
    test_graph.add_edge("A", "F", 4.2f);         test_graph.add_edge("F", "A", 4.1f);
    test_graph.add_edge("B", "G", 5.8f);         test_graph.add_edge("G", "B", 5.5f);
    test_graph.add_edge("B", "R", 6.7f);
    test_graph.add_edge("R", "G", 9.9f);

    // ... instead of an iterator, I did this...(it's OK if your values are in a different order)
    int num_nodes = test_graph.get_num_nodes();
    for (int i = 0; i < num_nodes; i++)                                   // A           
    {                                                                     // B
        std::string n = test_graph.get_node(i);                           // D
        std::cout << n << std::endl;                                      // F  
                                                                          // G
    }                                                                     // R

    // ... testing for membership / connection ...
    std::cout << "test_graph.has_node(\"A\") = ";
    std::cout << test_graph.has_node("A") << std::endl;             // test_graph.has_node("A") = 1
    std::cout << "test_graph.has_node(\"R\") = ";
    std::cout << test_graph.has_node("R") << std::endl;             // test_graph.has_node("R") = 1
    std::cout << "test_graph.has_node(\"X\") = ";
    std::cout << test_graph.has_node("X") << std::endl;             // test_graph.has_node("X") = 0

    std::cout << "test_graph.are_connected(\"D\", \"F\") = ";
    std::cout << test_graph.are_connected("D", "F") << std::endl;   // test_graph.are_connected("D", "F") = 0
    std::cout << "test_graph.are_connected(\"F\", \"D\") = ";
    std::cout << test_graph.are_connected("F", "D") << std::endl;   // test_graph.are_connected("F", "D") = 1
    std::cout << "test_graph.are_connected(\"A\", \"X\") = ";
    std::cout << test_graph.are_connected("A", "X") << std::endl;   // test_graph.are_connected("A", "X") = 0
    std::cout << "test_graph.are_connected(\"X\", \"Y\") = ";
    std::cout << test_graph.are_connected("X", "Y") << std::endl;   // test_graph.are_connected("X", "Y") = 0

    std::cout << "test_graph.get_edge(\"A\", \"F\") = ";
    std::cout << test_graph.get_edge("A", "F") << std::endl;        // test_graph.get_edge("A", "F") = 4.2
    // These two lines, if uncommented, should raise an exception
    //std::cout << test_graph.get_edge("A", "X") << std::endl;
    //std::cout << test_graph.get_edge("X", "Y") << std::endl;


    // Removing
    test_graph.remove_edge("F", "D");
    test_graph.remove_node("R");            // Should remove any edges to / from "R"


    // An alternate way to get neighbor / edge data
    for (int i = 0; i < test_graph.get_num_neighbors("A"); i++)         // neighbor0 of "A" is B
    {                                                                   // edge0 of "A" is 3.7
        std::cout << "neighbor" << i << " of \"A\" is ";                // neighbor1 of "A" is F
        std::cout << test_graph.get_neighbor("A", i) << std::endl;      // edge1 of "A" is 4.2
        std::cout << "edge" << i << " of \"A\" is ";
        std::cout << test_graph.get_neighbor_edge("A", i) << std::endl;
    }


    // Make this produce the output below.  A few points will be for lining up the | (just
    // a semi-pointless programming challenge:-))
    test_graph.add_node("breaker");
    test_graph.add_edge("breaker", "A", 8.5f);
    test_graph.add_edge("A", "breaker", 8.4f);
    std::cout << test_graph << std::endl;
    // This "view" is called an ADJACENCY-LIST (not actually how we're implementing our graph, though)
    // A          | {B:3.7} {breaker:8.4} {F:4.2}
    // breaker    | {A:8.5}
    // B          | {G:5.8}
    // D          |
    // F          | {A:4.1} {G:1.3}
    // G          | {B:5.5} {G:0.6}



    // SFML main program could go here if you do that part...

    sf::Font font;
    if (!font.loadFromFile("../media/Merriweather-Bold.ttf"))
    {
        std::cout << "Could not load font file" << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "ETEC2101 - Lab9: Graphs");

    ssuds::Level level;
    level.load_file("../maps/map04.txt");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                else if (event.key.code == sf::Keyboard::Tab)
                    level.toggle_text();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mpos = sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
                level.check_contains(mpos);
            }
        }

        window.clear();
        level.draw(window,font);
        window.display();
    }

    return 0;
}