#include <iostream>
#include <string>
#include <windows.h>
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
    sf::RenderWindow window(sf::VideoMode(800, 600), "");
    sf::Text humText,tempText;
    sf::Font arial;
    arial.loadFromFile("ARIAL.TTF");
    humText.setFont(arial);
    tempText.setFont(arial);
    humText.setPosition(0,50);
    tempText.setPosition(0,100);
    humText.setFillColor(sf::Color::Black);
    tempText.setFillColor(sf::Color::Black);
    bool wyslano=false;
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
        try{
            json parsed_data=json::parse(data);
            std::string t=parsed_data["temp"];
            std::string h=parsed_data["hum"];
            std::string lat=parsed_data["lat"];
            std::string lon=parsed_data["lon"];
            tempText.setString("Temperatura: "+t);
            humText.setString("Wilgotnosc: "+h);
//Wysylamy maila z informacja o alarmie
            if(stoi(t)>25 && !wyslano)
            {
                std::string line="C://Users//Szko³a//Documents//GitHub//CzechoTeam//CzechoSerwer//sending.py "+lon+" "+lat;
                system(line.c_str());
                cout<<line<<endl;
                wyslano=true;
            }
        }catch(const json::parse_error& e)
        {
            std::cerr<<e.what()<<endl;
        }
        cout<<data<<endl;

        //cout<<stoi(t)<<"\t"<<h<<endl;



        window.clear(sf::Color::White);
        window.draw(tempText);
        window.draw(humText);
        window.display();
    }
    return 0;
}
