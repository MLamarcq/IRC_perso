/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:33:59 by mlamarcq          #+#    #+#             */
/*   Updated: 2024/01/31 18:18:16 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

// std::string		PASS();
// std::string		NICK();
// std::string		USER();
// std::string		PING();
// std::string		PONG();
// std::string		OPER();

command::command()
{

}
command::command(const command& copy)
{
    (void)copy;
}
command& command::operator=(const command& copy)
{
    (void) copy;
    return (*this);
}
command::~command()
{

}

std::string		command::QUIT(int fd, Server* serv)
{
	if (!serv)
	{
		std::cout << "Server error" << std::endl;
		return (NULL);
	}
	client * tempClient;
	close(fd);
	FD_CLR(fd, &(serv->M_struct->current_sockets));
	tempClient = serv->findClientBySocket(fd);
	if (tempClient != NULL)
		tempClient->goodBy();
	if (tempClient != NULL)
		serv->eraseClientFromList(tempClient->getNickName());
    return (" ");
}
std::string		command::JOIN(client *client1, std::string parameter, Server *serv)
{
	if (parameter.empty())
	{
		std::cout << "In order to join a channel, pease refer a name" << std::endl;
		return (" ");
	}
	if (serv->checkChannel() == false)
	{
		std::cout << "No channel in the list, it will be the first !" << std::endl;
		channel *new_one = new channel;
		//faire une fonction dans client pour delete, utiliser algo for each : delete (it);
		//ou utiliser QUIT
		new_one->setName(parameter);
		if (new_one->setPassword() == 0)
		{
			delete new_one;
			std::cout << "ERROR" << std::endl;
			return (" ");
		}
		new_one->setListofClient(client1);
		new_one->setOperators(client1);
		serv->setNewChannel(new_one);
		return (" ");
	}
	// std::cout << "On passe la" << std::endl;
	std::list<channel *>::iterator it = serv->getListOfChannels().begin();
	std::list<channel *>::iterator ite = serv->getListOfChannels().end();
	bool found = false;
	while (it != ite)
	{
		// std::cout << "Parameter = " << parameter << std::endl;
		// std::cout << "Channel name = " << (*it)->getName() << std::endl;
		if ((*it)->getName().compare(parameter) == 0)
		{
			std::cout << "Channel found !" << std::endl;
			found = true;
			break ;
		}
		it++;
	}
	if (found == false)
	{
		std::cout << "Channel doesn't exist, let's create it" << std::endl;
		channel *new_one = new channel;
		//faire une fonction dans client pour delete, utiliser algo for each : delete (it);
		new_one->setName(parameter);
		if (new_one->setPassword() == 0)
		{
			delete new_one;
			// std::cout << "ERROR" << std::endl;
			return (" ");
		}
		new_one->setListofClient(client1);
		//new_one->setOperators(client1);
		serv->setNewChannel(new_one);
		return (" ");
	}
	serv->addClientToChannel(client1, parameter);
	// std::cout << "Parameter in JOIN = " << parameter << std::endl;
	// std::cout << "Client1 nickname in JOIN : " << client1->getNickName() << std::endl;
	// std::cout << "Client1 FD in JOIN : " << client1->getsocketFd() << std::endl;
	(void)client1;
	(void) found;
	return (" ");
}


// std::string		PART();
// std::string		TOPIC();
// std::string		KICK();
// std::string		MODE();
// std::string		PRIVMSG();
// std::string		NOTICE();
// std::string		KILL();
// std::string		WALLOPS();
// std::string		bot();
