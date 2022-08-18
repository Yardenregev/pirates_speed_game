#include "../include/tcp_server_broadcaster.hpp"
#include <string>
#include <iostream>/*std cout cin*/

using namespace pirates_speed;

int main()
{
    TCPServerBroadcaster server("localhost", 8080, "10.10.0.151");

    server.AddClient();
    server.AddClient();

    server.SendMessageToAll("Hello World from server");
    return 0;
}
