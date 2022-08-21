#include "../include/server.hpp"
#include "../include/design_patterns/singleton.hpp"
#include <iostream>/*std cout cin*/


namespace pirates_speed
{

    
    void Server::ShoutCommand(const std::string &command)
    {
        m_tcp_dispatcher.SendMessageToAll(command);
    }

    Server::Server(int port, const std::string & ip_address)
        : m_tcp_dispatcher(port, ip_address),
          m_captain_sockets(),
          m_answers(),
          m_thread_pool(),
          m_answered(false)
    {
    }

    std::pair<std::string,size_t> Server::AddCaptain()
    {
        std::cout << "Waiting for captain to join the game..." << std::endl;
        int captain_socket = m_tcp_dispatcher.AddClient();
        std::cout << "Captain joined the game" << std::endl;
        auto captain_details = GetCaptainDetails(captain_socket);
        m_captain_sockets[captain_details.first] = captain_socket;
        std::cout << "Captain " << captain_details.first << " joined the game" << std::endl;
        return captain_details;
    }

    std::pair<std::string,size_t> Server::GetCaptainDetails(int captain_socket)
    {
        std::string user_details = m_tcp_dispatcher.ReceiveMessageFromClient(captain_socket);
        std::string captain_name = user_details.substr(0, user_details.find("-"));
        std::string num_of_pirates = user_details.substr(user_details.find("-") + 1);
        return std::make_pair(captain_name, std::stoi(num_of_pirates));
    }

    bool Server::CheckEndRound(const std::string &answer)
    {
        return answer == "end_round";
    }
    

    void Server::ReadCaptainAnswers(int captain_socket) // need thread pool to read from all sockets
    {
        while(m_answered == false)
        {
            std::string answer = m_tcp_dispatcher.ReceiveMessageFromClient(captain_socket);
            std::string captain_name = answer.substr(0, answer.find("-"));
            std::string answer_text = answer.substr(answer.find("-") + 1);
            Answer new_answer(captain_name, answer_text, Priority::ANSWER);
            m_answers.Push(std::make_shared<Answer>(new_answer));
        }
    }

    void Server::QueueAnswers()
    {
        // for all sockets, threadpool add task ReadCaptainAnswers(socket)
    }

    void Server::GetAnswer(std::shared_ptr<Answer> answer)
    {
        m_answers.Pop(answer);
    }

    void Server::EndRound()
    {
        m_answered = true;
        m_tcp_dispatcher.SendMessageToAll("end_round");
        m_answers.Push(std::make_shared<Answer>("", "end_round", Priority::END_ROUND));
    }

    void Server::EndGame()
    {
        m_tcp_dispatcher.SendMessageToAll("end_game");
    }

    void Server::SendMessageToCaptain(const std::string &message, const std::string &captain_name)
    {
        m_tcp_dispatcher.SendMessageToClient(message, m_captain_sockets[captain_name]);
    }


    

} // namespace pirates_speed
