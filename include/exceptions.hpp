#include <iostream>
#include <exception>
#include <string>

// Define a custom exception class
class ConnectionWithCommanderException : public std::runtime_error {
public:
    ConnectionWithCommanderException() : std::runtime_error("Connection lost with commander") {}
};