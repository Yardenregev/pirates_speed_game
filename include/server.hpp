#pragma once
// #include "../include/design_patterns/dispatcher.hpp"
#include <string>
#include <map>
#include "tcp_server_broadcaster.hpp"
#include "waitable_queue.hpp"
#include "answer.hpp"

namespace pirates_speed
{


    class Server
    {
        public :

            Server(int port, const std::string & ip_address);
        public:
            std::pair<std::string,size_t> AddCaptain();
            void ShoutCommand(const std::string &command);
            void SendInventoryToCaptain(const std::string &captain_name, const std::string & inventory);
            void SendMessageToCaptain(const std::string &captain_name, const std::string &message);
            void SendMessageToAll(const std::string &message);
            void GetAnswer(std::shared_ptr<Answer> &answer);
            void EndRound();
            void QueueAnswers();
            void EndGame();
            void ClearAnswerQueue();
            void ReceiveFromAll();
            void ReceiveFromCaptain(const std::string &captain_name);
            bool IsAnswered();
        private:
            bool CheckEndRound(const std::string &answer);
            std::pair<std::string,size_t> GetCaptainDetails(int captain_socket);
            void ReadCaptainAnswers(int captain_socket);

        private:
            TCPServerBroadcaster m_tcp_dispatcher;
            std::map<std::string, int> m_captain_sockets;
            WaitableQueue<std::shared_ptr<Answer>> m_answers;
            bool m_answered;
    };
    
} // namespace pirates_speed
