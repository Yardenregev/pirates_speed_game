#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>

namespace pirates_speed
{
class DefaultValues{
    public:
        DefaultValues() = delete;
        static const std::string& getDefaultCommanderName(){
            static const std::string defaultName = "Black Beard";
            return defaultName;
        }
        static int getDefaultPort(){
            static int defaultPort = 8080;
            return defaultPort;
        }

        static std::string getDefaultIP() {
            // List available network interfaces
            std::vector<std::string> interfaces = listNetworkInterfaces();
            if (interfaces.empty()) {
                std::cout << "No network interfaces found." << std::endl;
                return "";
            }

            // Prompt user to select an interface
            size_t choice;
            while(true)
            {
                std::cout << "Available network interfaces:" << std::endl;
                for (size_t i = 0; i < interfaces.size(); ++i) {
                    std::cout << i + 1 << ". " << interfaces[i] << std::endl;
                }

                std::cout << "Select an interface by number: ";
                std::cin >> choice;

                if (choice < 1 || choice > interfaces.size()) {
                    std::cout << "Invalid choice." << std::endl;
                }
                else
                {
                    break;
                }
            }

            std::string selectedInterface = interfaces[choice - 1];
            std::string ipAddress = getIPAddress(selectedInterface);

            if (!ipAddress.empty()) {
                std::cout << "IP address of " << selectedInterface << ": " << ipAddress << std::endl;
            } else {
                std::cout << "Could not retrieve IP address for " << selectedInterface << std::endl;
            }

            return ipAddress;
        }

private:
    // List all available network interfaces
    static std::vector<std::string> listNetworkInterfaces() {
        struct ifaddrs *ifaddr, *ifa;
        std::set<std::string> interfaces;

        if (getifaddrs(&ifaddr) == -1) {
            std::cerr << "Error getting network interfaces" << std::endl;
            return {};
        }

        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == NULL) continue;
            interfaces.insert(ifa->ifa_name);
        }

        freeifaddrs(ifaddr);
        return std::vector<std::string>(interfaces.begin(), interfaces.end());
    }

    // Get the IP address of a specific interface
    static std::string getIPAddress(const std::string& interfaceName) {
        struct ifaddrs *ifaddr, *ifa;
        std::string ipAddress;

        if (getifaddrs(&ifaddr) == -1) {
            std::cerr << "Error getting network interfaces" << std::endl;
            return "";
        }

        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == NULL) continue;

            // Check if the interface matches the desired one
            if (interfaceName == ifa->ifa_name) {
                // Check if the interface is an IPv4 address
                if (ifa->ifa_addr->sa_family == AF_INET) {
                    struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
                    char ipstr[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &(sa->sin_addr), ipstr, sizeof(ipstr));
                    ipAddress = ipstr;
                    break;
                }
            }
        }

        freeifaddrs(ifaddr);
        return ipAddress;
    }
};


} // namespace pirates_speed