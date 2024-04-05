#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "json.hpp"

using namespace std;
using json=nlohmann::json;
int main()
{
    sf::UdpSocket socket;
    sf::IpAddress sender;
    std::size_t recived;
    unsigned short  port=1313;
    const int dataSize=1024;
    char data[dataSize];
    if(socket.bind(1313) !=sf::Socket::Done)
    {
        std::cerr<<"Nie udalo sie polaczyc"<<std::endl;
        return -1;
    }
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::Text humText,tempText;
    sf::Font arial;
    arial.loadFromFile("ARIAL.TTF");
    humText.setFont(arial);
    tempText.setFont(arial);
    humText.setPosition(0,50);
    tempText.setPosition(0,100);
    humText.setFillColor(sf::Color::Black);
    tempText.setFillColor(sf::Color::Black);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (socket.receive(data, dataSize, recived, sender, port) != sf::Socket::Done)
        {
            continue;
        }
        json parsed_data=json::parse(data);
        std::string t=parsed_data["temp"];
        std::string h=parsed_data["hum"];
        cout<<t<<"\t"<<h<<endl;
        tempText.setString("Temperatura: "+t);
        humText.setString("Wilgotnosc: "+h);

        window.clear(sf::Color::White);
        window.draw(tempText);
        window.draw(humText);
        window.display();
    }
    return 0;
}
