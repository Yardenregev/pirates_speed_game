#pragma once
// #include "../include/design_patterns/dispatcher.hpp"
#include <string>
#include "tcp_server_broadcaster.hpp"

namespace pirates_speed
{

    // class Commander : public Dispatcher<const std::string &>
    class Commander
    {
        public :
            // static Commander & GetInstance();
            // static Commander & GetInstance(const std::string & name, int port, const std::string & ip_address);
            Commander(const std::string & name, int port, const std::string & ip_address);
        public:
            void AddCaptain();
            void ShoutCommand(const std::string &command);
            std::string GetName() const;

        private:
            void SendMessageToLastCaptain(const std::string &command);
            char *ReciveMessageFromLastCaptain();
            TCPServerBroadcaster m_tcp_dispatcher;

            std::string m_name;
    };
    
} // namespace pirates_speed
