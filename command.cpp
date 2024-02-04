/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:33:59 by mlamarcq          #+#    #+#             */
/*   Updated: 2024/02/04 13:55:10 by mael             ###   ########.fr       */
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

	client * tempClient;
	close(fd);
	FD_CLR(fd, &(serv->M_struct->current_sockets));
	tempClient = serv->findClientBySocket(fd);
	//std::cout << "IN QUIT NICK IS " << tempClient->getNickName() << std::endl;
	if (tempClient != NULL)
		tempClient->goodBy();
	if (tempClient != NULL)
		serv->eraseClientFromList(tempClient->getNickName());

	// si le client appartient à un channel appeler la fonction
	// qui prévient tout le monde qu'il s'est barré
	return (" ");
}


std::string		command::USER(int fd, Server* serv)
{
	std::vector<std::string> temp;
	std::string arg;
	client* clientTmp;

	clientTmp = serv->findClientBySocket(fd);
	// dejà j'envoi pas l'erreur mauvais args
	// je vois pas le contenu de USER voir pk
	//std::cout << "c1\n";
	std::cout << "c2.4.1.1\n";
	// std::cout << 
	if (serv->M_cmdMap.find("USER") != serv->M_cmdMap.end() || serv->M_cmdMap.find("userhost") != serv->M_cmdMap.end())
	{
		//std::cout << "c2\n";
		std::cout << "c2.4.1.2\n";
		std::map<std::string, std::vector<std::string> > :: iterator it = serv->M_cmdMap.find("USER");
		if (it != serv->M_cmdMap.end())
		{
			//std::cout << "c3\n";
			std::cout << "c2.4.1.3\n";
			temp = serv->M_cmdMap["USER"];
			// char **tabSplit = ft_split(temp.c_str(), ' ');
			// int count = std::count(temp.begin(), temp.end(), ' ');
			if (temp.size() < 4)
			{
				std::string chaine;
  				for (std::vector<std::string>::iterator it = temp.begin(); it != temp.end(); ++it)
					chaine += *it;
				return (ERR_NEEDMOREPARAMS(clientTmp->getNickName(), chaine));
			}
			std::cout << "c2.4.1.4\n";
			//std::cout << "TABSPLIT[0] = " << tabSplit[0] << std::endl;
			clientTmp->setUserName(temp[0].append(clientTmp->getNickName()));
			clientTmp->setMode(temp[1]);
			clientTmp->setHostName(temp[2]);
			clientTmp->setRealName(temp[3]);
			
		//    if (serv->findClientByUserName(tabSplit[0]) != NULL)
		//        return (ERR_ALREADYREGISTRED(tabSplit[0]));
			// std::cout << "c2.4.1.5\n";
			// std::string name = tabSplit[0];
			// name.append(clientTmp->getNickName());
			// clientTmp->setUserName(name);
			// clientTmp->setMode(tabSplit[1]);
			// clientTmp->setHostName(tabSplit[2]);
			// clientTmp->setRealName(tabSplit[3]);
			return ("nothing");
		}
		else
		{
			//std::cout << "c4\n";
			std::cout << "c2.4.1.6\n";
			temp = serv->M_cmdMap["userhost"];
			// char **tabSplit = ft_split(temp.c_str(), ' ');
			// int count = std::count(temp.begin(), temp.end(), ' ');
			if (temp.size() < 4)
			{
				std::string chaine;
				for (std::vector<std::string>::iterator it = temp.begin(); it != temp.end(); ++it)
					chaine += *it;
				return (ERR_NEEDMOREPARAMS(clientTmp->getNickName(), chaine));
			}
			for (size_t i = 0; i < temp.size(); i++)
				std::cout << "temp[" << i << "] = " << temp[i] << std::endl;
			std::cout << "c2.4.1.7\n";
			//if (serv->findClientByUserName(tabSplit[0]) != NULL)
			  //  return (ERR_ALREADYREGISTRED(tabSplit[0]))f;
			std::cout << "c2.4.1.8\n";
			clientTmp->setUserName(temp[0].append(clientTmp->getNickName()));
			clientTmp->setMode(temp[1]);
			clientTmp->setHostName(temp[2]);
			clientTmp->setRealName(temp[3]);
			std::cout << "c2.4.1.9\n";
			return ("nothing");
		}
	}
	return ("BIZZARE");

}


// std::string		command::NICK(int fd, Server* serv)
// {

// 	//voit pk loic a pas été changé par toto
// 	std::string temp;
// 	std::string arg;
// 	client* clientTmp;
// 	temp = serv->M_cmdMap["NICK"];
// 	size_t notSpace = temp.find_first_not_of(' ');
// 	size_t end = temp.find(' ', notSpace);
// 	std::cout << "c2.1.1.1\n";
// 	if (end == std::string::npos)
// 	{
// 		std::cout << "c2.1.1.2\n";
// 		size_t lastcar = temp.find('\0');
// 		arg = temp.substr(notSpace, lastcar - 1);
// 		//std::cout << "ARG IS " << arg << std::endl;
// 		if (serv->findClientByNickName(arg) != NULL)
// 			return (ERR_NICKNAMEINUSE(arg, arg));
// 		std::cout << "c2.1.1.3\n";
// 		if (arg.empty())
// 			return (ERR_NONICKNAMEGIVEN(arg));
// 		std::cout << "c2.1.1.4\n";
// 		/*
// 		for (unsigned int i = 0; i < arg.length(); ++i)
// 		{
// 			if (!std::isalnum(arg[i]) && arg[i] != '-' && arg[i] != '_')
// 				return(ERR_ERRONEUSNICKNAME(arg, arg));
// 		}
// 		*/
// 		clientTmp = serv->findClientBySocket(fd);
// 		clientTmp->setNickName(arg);
// 		return ("nothing");
// 	}
// 	else
// 	{
// 		arg = temp.substr(notSpace, end);
// 		if (serv->findClientByNickName(arg) == NULL)
// 			return (ERR_NICKNAMEINUSE(arg, arg));
// 		if (arg.empty())
// 			return (ERR_NONICKNAMEGIVEN(arg));
// 		/*
// 		for (unsigned int i = 0; i < arg.length(); ++i)
// 		{
// 			if (!std::isalnum(arg[i]) && arg[i] != '-' && arg[i] != '_')
// 				return(ERR_ERRONEUSNICKNAME(arg, arg));
// 		}
// 		*/
// 		clientTmp = serv->findClientBySocket(fd);
// 		clientTmp->setNickName(arg);
		
// 		return ("nothing");
// 	}

// }

std::string		command::PASS(int fd, Server* serv)
{
	std::vector<std::string >temp;
	std::string arg;
	client* clientTmp;
	temp = serv->M_cmdMap["PASS"];
	clientTmp = serv->findClientBySocket(fd);
	if (clientTmp->isWelcomeMessageSent())
		return (ERR_ALREADYREGISTRED(clientTmp->getNickName()));
	if (temp.empty())
		return (ERR_NEEDMOREPARAMS(clientTmp->getNickName(), "PASS"));
	if (std::find(temp.begin(), temp.end(), serv->M_pass_wd) != temp.end())
		return (ERR_PASSWDMISMATCH(clientTmp->getNickName()));
	return ("nothing");
}

std::string		command::JOIN(client *client1, Server *serv)
{
	std::vector<std::string> temp;
	std::string chan;
	temp = serv->M_cmdMap["JOIN"];
	int check = 0;
	if (temp.empty())
	{
		std::cout << "To join a channel, please enter it's name" << std::endl;
		return (" ");
	}
	// if (client1->getBan() == true)
	// 	return ();
	// for (size_t li = 0; li < temp.size(); li++)
	// 	std::cout << "temp[" << li << "] = " << temp[li] << std::endl;
	// std::cout << "temp.size() = " << temp.size() << std::endl;
	// if (temp.size() > 2)
	// {
	// 	std::string chaine;
	// 	for (std::vector<std::string>::iterator it = temp.begin(); it != temp.end(); ++it)
	// 		chaine += *it;
	// 	return (ERR_NEEDMOREPARAMS(client1->getNickName(), chaine));
	// }
	if (serv->checkChannel() == false)
	{
		std::cout << "No channel in the list, it will be the first !" << std::endl;
		channel *new_one = new channel;
		//faire une fonction dans client pour delete, utiliser algo for each : delete (it);
		//ou utiliser QUIT
		// std::vector<std::string>::iterator s1 = temp.begin();
		// std::vector<std::string>::iterator s2 = temp.end();
		// while (s1 != s2)
		// {
		// 	std::cout << "la chaine = " << (*s1) << " sa taille = " << (*s1).size() << std::endl;
		// 	s1++;
		// }
		new_one->setName(temp[0]);
		if (temp.size() == 2)
			new_one->setPassword(temp[1]);
		new_one->setListofClient(client1);
		new_one->setOperators(client1);
		serv->setNewChannel(new_one);
		std::cout << "Channel name = " << new_one->getName() << std::endl; //"d'une taille de : " << new_one->getName().size() << std::endl;
		std::cout << "Channel password = " << new_one->getPassword() << std::endl;
		return (" ");
	}
	// // std::cout << "On passe la" << std::endl;
	std::list<channel *> listOfChannels = serv->getListOfChannels();
	std::list<channel *>::iterator it = listOfChannels.begin();
	std::list<channel *>::iterator ite = listOfChannels.end();
	bool found = false;
	while (it != ite)
	{
		// std::cout << "Parameter = " << parameter << std::endl;
		std::cout << "Channel name = " << (*it)->getName() << std::endl; //" d'une taille de : " << (*it)->getName().size() << std::endl;
		std::cout << "temp[0] = " << temp[0] << std::endl; //" d'une taille de : " << temp.size() << std::endl;
		std::cout << "res du compare : " << (*it)->getName().compare(temp[0]) << std::endl;
		if ((*it)->getName().compare(temp[0]) == 0)
		{
			std::cout << "Channel found !" << std::endl;
			chan = temp[0];
			found = true;
			break ;
		}
		it++;
	}
	if (found == false)
	{
		channel *new_one = new channel;
		//faire une fonction dans client pour delete, utiliser algo for each : delete (it);
		//ou utiliser QUIT
		new_one->setName(temp[0]);
		if (temp.size() == 2)
			new_one->setPassword(temp[1]);
		new_one->setListofClient(client1);
		new_one->setOperators(client1);
		serv->setNewChannel(new_one);
		std::cout << "Channel name = " << new_one->getName() << std::endl;
		std::cout << "Channel password = " << new_one->getPassword() << std::endl;
		return (" ");
	}
	check = serv->addClientToChannel(client1, temp);
	switch (check)
	{
		case 0 :
		{
			break ;
		}
		case 1 :
		{
			std::cout << "Welcome to the channel !" << std::endl;
			break ;
		}
		default :
		{
			return (ERR_BADCHANNELKEY(client1->getNickName(), chan));
			break ;
		}
	}
	// // std::cout << "Parameter in JOIN = " << parameter << std::endl;
	// // std::cout << "Client1 nickname in JOIN : " << client1->getNickName() << std::endl;
	// // std::cout << "Client1 FD in JOIN : " << client1->getsocketFd() << std::endl;
	(void)client1;
	(void)serv;
	// (void) found;
	return (" ");
}
// std::string		JOIN();
// std::string		PART();
// std::string		TOPIC();
// std::string		KICK();
// std::string		MODE();
// std::string		PRIVMSG();
// std::string		NOTICE();
// std::string		KILL();
// std::string		WALLOPS();
// std::string		bot();
