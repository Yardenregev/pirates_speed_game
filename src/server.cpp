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
        std::cout << "Captain socket: " << m_captain_sockets.at(captain_details.first) << std::endl;

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
    

    void Server::ReadCaptainAnswers(int captain_socket)
    {
        if (m_answered == false)
        {
            std::cout << "Reading captain answers..." << std::endl;
            std::string answer = m_tcp_dispatcher.ReceiveMessageFromClient(captain_socket);
            if(m_answered)
            {
                std::cout<<"answered, closing thread" << std::endl;
                return;
            }
            std::string captain_name = answer.substr(0, answer.find("-"));
            std::string answer_text = answer.substr(answer.find("-") + 1);
            
            m_answers.Push(std::make_shared<Answer>(captain_name, answer_text));
        }
    }

    void Server::QueueAnswers()
    {
        m_answered = false;
        for(auto &socket : m_captain_sockets)
        {
            m_thread_pool.AddTask(std::bind(&Server::ReadCaptainAnswers, this, socket.second),TaskPriority::LOW);
        }
    }

    void Server::GetAnswer(std::shared_ptr<Answer> &answer)
    {
        m_answers.Pop(answer);
    }

    void Server::EndRound()
    {
        m_answered = true;
        m_answers.Push(std::make_shared<Answer>("end_round", "end_round",Priority::END_ROUND));
    }

    void Server::EndGame()
    {
        // m_tcp_dispatcher.SendMessageToAll("end_game");
        EndRound();
    }

    void Server::SendMessageToCaptain(const std::string &captain_name, const std::string &message)
    {
        m_tcp_dispatcher.SendMessageToClient(message, m_captain_sockets.at(captain_name));
    }

    void Server::ClearAnswerQueue()
    {
        m_answers.Clear();
    }

    void Server::SendMessageToAll(const std::string &message)
    {
        m_tcp_dispatcher.SendMessageToAll(message);
    }


    

} // namespace pirates_speed
