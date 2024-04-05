#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

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
    while(true)
    {
        if (socket.receive(data, dataSize, recived, sender, port) != sf::Socket::Done)
        {
            continue;
        }
        cout<<data<<endl;
    }
    return 0;
}
