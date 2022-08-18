#pragma once
// #include "../include/design_patterns/dispatcher.hpp"
#include <string>
#include "tcp_server_broadcaster.hpp"
#include "waitable_queue.hpp"

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
            void HandleAnswers();
        private:
            void ReciveAnswers();
            TCPServerBroadcaster m_tcp_dispatcher;

            std::string m_name;
            WaitableQueue<const std::string &> answers;
            bool m_answered;
    };
    
} // namespace pirates_speed
