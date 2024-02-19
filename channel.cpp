#include "channel.hpp"

channel::channel()
{
	this->_nbrClients = 0;
	this->_clientLimit = 100;
	this->_isInvite = false;
	this->_topicEstate = false;
	return ;
}

channel::channel(std::string channelName, int passWord)
{
	(void)channelName;
	(void)passWord;
}

channel::channel(const channel& copy)
{
	(void)copy;
}

channel & channel::operator=(const channel& copy)
{
	if (this!= &copy)
	{
		if (copy.getClientLimit())
			this->_clientLimit = copy.getClientLimit();
		if (copy.getNbrOfClients())
			this->_nbrClients = copy.getNbrOfClients();
		if (copy.getClientLimit())
			this->_name = copy.getName();
		if (copy.getClientLimit())
			this->_pswd = copy.getPassword();
		for (std::map<client *, bool>::iterator m_it = _listOfClients.begin(); m_it != _listOfClients.end(); ++m_it)
		{
			delete m_it->first;
		}
		this->_listOfClients.clear();
		std::map<client *, bool> map = copy.getListOfClients();
		std::map<client *, bool>::iterator it = map.begin();
		std::map<client *, bool>::iterator ite = map.begin();
		while (it != ite)
		{
			client *copy2 = copyClient(it->first);
			if (copy2)
			{
				this->_listOfClients[copy2] = it->second;
			}
			it++;
		}
	}
	(void)copy;
	return (*this);
}

channel::~channel()
{
	return ;
}

client	*channel::copyClient(client *original)
{
	if (!original)
	{
		std::cout << "Client doesn't exist" << std::endl;
		return (NULL);
	}
	client *copy = new client;
	copy->setNickName(original->getNickName());
	copy->setRealName(original->getRealName());
	copy->setUserName(original->getUserName());
	copy->setHostName(original->getHostName());
	copy->setOperatorStatus(original->getOperatorStatus());
	copy->setWelcomeMessageSent(original->isWelcomeMessageSent());
	copy->setsocketFd(original->getsocketFd());
	copy->setPort(original->getPort());
	copy->setIp(original->getIp());
	copy->setNumberOfChannelJoined(original->getNumberOfChannelJoined());
	return (copy);
}

std::string	channel::getName(void) const
{
	return (this->_name);
}

std::string channel::getPassword(void) const
{
	return (this->_pswd);
}

std::string channel::getTopic(void) const
{
	return (this->_topic);
}

int			channel::getNbrOfClients(void) const
{
	return (this->_nbrClients);
}

int			channel::getClientLimit(void) const
{
	return (this->_clientLimit);
}

bool		channel::getIsInvite(void) const
{
	return (this->_isInvite);
}

bool		channel::getTopicEstate(void) const
{
	return (this->_topicEstate);
}

void	channel::increaseNbrCLient(void)
{
	this->_nbrClients++;
	return ;
}

std::list<client *>		channel::getWaitingList(void) const
{
	return (this->_waitingList);
}

std::map<client*, bool> channel::getListOfClients(void) const
{
	return (this->_listOfClients);
}

void	channel::setWaitingList(client *client1)
{
	if (!client1)
		return ;
	this->_waitingList.push_back(client1);
	return ;
}

int	channel::setName(std::string parameter)
{
	std::cout << "parameter = " << parameter << std::endl;
	// std::cout << "On regarde chaque caractere quand pas de mdp avant" << std::endl;
	// size_t i = 0;
	// while (i < parameter.size())
	// {
	// 	std::cout << "parameter[" << i << "] = " << parameter[i] << std::endl;
	// 	i++;
	// }
	if (parameter.size() > 200)
	{
		std::cout << "+ de 200" << std::endl;
		return (0);
	}
	size_t space = parameter.find(' ');
	size_t coma = parameter.find(',');
	std::cout << "coma = " << coma << std::endl;
	size_t sound = parameter.find('\a');
	if (space != std::string::npos || coma != std::string::npos || sound != std::string::npos)
	{
		std::cout << "ici" << std::endl;
		this->_name = parameter;
		return (0);
	}
	size_t r = parameter.find('\r');
	if (r != std::string::npos)
	{
		std::cout << " trouve !" << std::endl;
		parameter = parameter.substr(0, r);
	}
	// std::cout << "On regarde chaque caractere quand pas de mdp apres" << std::endl;
	// i = 0;
	// while (i < parameter.size())
	// {
	// 	std::cout << "parameter[" << i << "] = " << parameter[i] << std::endl;
	// 	i++;
	// }
	this->_name = parameter;
	return (1);
}
void	channel::setPassword(std::string password)
{
	// std::string password;
	// bool toggle = false;
	// std::cout << "Please choose a password for this channel (4 digits): ";
	// while (toggle == false)
	// {
	// 	if (!std::getline(std::cin, password))
	// 	{
	// 		std::cout << "End of file called. Channel setup failed. Cancel all actions" << std::endl;
	// 		return (0);
	// 	}
	// 	if (password.empty())
	// 	{
	// 		std::cout << "Empty password. Please ty again : ";
	// 	}
	// 	if (isDigit(password) == 1)
	// 	{
	// 		this->_pswd = password;
	// 		// std::cout << "Password for " << this->_name << "set. It is : " << this->_pswd << std::endl;
	// 		toggle = true;
	// 	}
	// 	password.erase();
	// }
	// // std::cout << "Le nom du channel est : " << this->_name << std::endl;
	// // std::cout << "Le mot de passe est : " << this->_pswd << std::endl;
	this->_pswd = password;
	return ;
}

void	channel::setListofClient(client *client1)
{
	if (!client1)
	{
		std::cout << "Error, client does not exist" << std::endl;
		return ;
	}
	this->_listOfClients[client1] = false;
	return ;
}

void	channel::setTopic(std::string topic)
{
	if (topic.empty())
	{
		std::cout << "No topic" << std::endl;
		return ;
	}
	if (this->_topic.empty() == 0)
		this->_topic.erase();
	this->_topic = topic;
	return ;
}

void	channel::setOperators(client *client1)
{
	if (!client1)
	{
		std::cout << "Error, client does not exist" << std::endl;
		return ;
	}
	this->_listOfClients[client1] = true;
	return ;
}

void	channel::addClientToTheChannel(client *client1)
{
	if (!client1)
	{
		std::cout << "Client doesn't exist" << std::endl;
		return ;
	}
	this->_listOfClients[client1] = false;
	return ;
}

void	channel::printMap(void) const
{
	std::map<client *, bool>::const_iterator it = this->_listOfClients.begin();
	std::map<client *, bool>::const_iterator ite = this->_listOfClients.end();
	// std::cout << "le nom du client : " << it->first->getNickName() << std::endl;
	// std::cout << "Le nom du channel = " << this->_name << std::endl;
	std::cout << std::internal << std::setw(10) << "Channel | ";
	std::cout << std::internal << std::setw(10) << "Client name | ";
	std::cout << std::internal << std::setw(10) << "Is operator |" << std::endl;
	while (it != ite)
	{
		std::cout << this->_name << " | ";
		// std::cout << "Le nom du channel = " << this->_name << std::endl;
		if (it->first->getNickName().size() > 10)
			std::cout << std::setw(9) << std::internal << it->first->getNickName().substr(0, 9) << "." << "| ";
		else
			std::cout << std::setw(10) << std::internal << it->first->getNickName().substr(0, 10) << " | ";
		if (it->second == true)
			std::cout << std::setw(10) << std::internal << "Yes |" << std::endl;
		else
			std::cout << std::setw(10) << std::internal << "No |" << std::endl;
		it++;
	}
	// std::cout << "Le nom du channel = " << this->_name << std::endl;
	// std::cout << std::setw(10) << std::internal << "Yes |" << std::endl;
	// std::cout << std::setw(10) << std::internal << "No |" << std::endl;
	return ;
}

int	channel::setChannelFirstTime(client *client1, Server *serv, std::vector<std::string> temp)
{
	if (this->setName(temp[0]) == 0)
	{
		serv->setChanName(this->getName());
		std::cout << "ERROR CHANNEL" << std::endl;
		std::cout << "COMMAND JOIN SOCKET FD = " << client1->getsocketFd() << std::endl;
		// std::string message = ERR_NOSUCHCHANNEL(client1->getNickName(), this->getName());
		// std::cout << "le message = " << message << std::endl;
		return (403);
	}
	// if (temp.size() == 2)
	// 	this->setPassword(temp[1]);
	this->setListofClient(client1);
	this->setOperators(client1);
	serv->setNewChannel(this);
	this->increaseNbrCLient();
	return (0);
}

void		channel::changeIsInviteOn(std::string name, std::string username, std::string mode)
{
	std::string message;
	
	if (name.empty())
	{
		std::cout << "NO CLIENT NAME" << std::endl;
		return ;
	}
	if (username.empty())
	{
		std::cout << "NO CLIENT USERNAME" << std::endl;
		return ;
	}
	if (this->_isInvite == false)
		this->_isInvite = true;
	message = MODE_CHANNEL_YES_INVITE(name, username, this->getName(), mode);
	this->sendToAllChan(message);
	return ;
}

void		channel::changeIsInviteOff(std::string name, std::string username, std::string mode)
{
	std::string message;
	
	if (name.empty())
	{
		std::cout << "NO CLIENT NAME" << std::endl;
		return ;
	}
	if (username.empty())
	{
		std::cout << "NO CLIENT USERNAME" << std::endl;
		return ;
	}
	if (this->_isInvite == true)
		this->_isInvite = false;
	message = MODE_CHANNEL_NO_INVITE(name, username, this->getName(), mode);
	this->sendToAllChan(message);
	return ;
}

void	channel::setNewPassWord(std::string pass, std::string name, std::string username, std::string mode)
{
	std::string message;

	if (pass.empty())
	{
		std::cout << "NO PASSWORD" << std::endl;
		return ;
	}
	if (this->_pswd.empty() == 0)
	{
		std::cout << "Password already set" << std::endl;
		return ;
	}
	this->_pswd = pass;
	//message = RPL_PASSWORD_CHANGED(name, this->getName(), pass);
	message = MODE_CHANNEL_NEWMDP(name, username, this->getName(), mode, pass);
	std::cout << message << std::endl;
	this->sendToAllChan(message);
	(void)username;
	(void)name;
	(void)pass;
	return ;
}

void	channel::clearPassWord(std::string name, std::string username, std::string mode)
{
	std::string message;

	if (this->_pswd.empty())
	{
		std::cout << "NO PASSWORD" << std::endl;
		return ;
	}
	this->_pswd.erase();
	message = MODE_CHANNEL_CLEARMDP(name, username, this->getName(), mode);
	this->sendToAllChan(message);
	(void)username;
	(void)name;
	return ;
}


void	channel::changePrivileges(std::string name, std::string username, std::string mode, std::string client1, int code)
{
	std::string message;
	bool present = false;

	if (client1.empty())
	{
		std::cout << "NO NAME" << std::endl;
		return ;
	}
	if (name.empty())
	{
		std::cout << "NO CLIENT NAME" << std::endl;
		return ;
	}
	if (username.empty())
	{
		std::cout << "NO CLIENT USERNAME" << std::endl;
		return ;
	}
	std::map<client *, bool>::iterator it = this->_listOfClients.begin();
	std::map<client *, bool>::iterator ite = this->_listOfClients.end();
	// if (it == this->_listOfClients.end())
	// {
	// 	std::cout << "Client not in channel" << std::endl;
	// 	return ;
	// }
	while (it != ite)
	{
		if (it->first->getNickName().compare(client1) == 0)
		{
			present = true;
			break ;
		}
		it++;
	}
	if (present == false)
	{
		std::cout << "Client not in channel" << std::endl;
		//Peut-etre envoyer un msg ici
		return ;
	}
	if (code == 1)
	{
		if (it->second == false)
		{
			it->second = true;
			message = MODE_CHANNEL_NOWOP(name, username, this->getName(), mode, client1);
			this->sendToAllChan(message);
		}
	}
	else if (code == 2)
	{
		if (it->second == true)
		{
			it->second = false;
			message = MODE_CHANNEL_NOMOREOP(name, username, this->getName(), mode, client1);
			this->sendToAllChan(message);
		}
	}
	return ;
}

void	channel::setClientLimit(std::string name, std::string username, std::string mode, std::string nb)
{
	int check = 0;
	int res = 0;
	std::string message;

	if (nb.empty())
	{
		std::cout << "NO LIMIT SPECIFIED" << std::endl;
		return ;
	}
	if (name.empty())
	{
		std::cout << "NO CLIENT NAME" << std::endl;
		return ;
	}
	if (username.empty())
	{
		std::cout << "NO CLIENT USERNAME" << std::endl;
		return ;
	}
	check = isDigit(nb);
	if (check == 0)
	{
		std::cout << "WRONG AGUMENT" << std::endl;
		return ;
	}
	res = std::atoi(nb.c_str());
	this->_clientLimit = res;
	message = MODE_CHANNEL_CLIENTLIMIT(name, username, this->getName(), mode, nb);
	this->sendToAllChan(message); 
	return ;
}

void	channel::eraseClientLimit(std::string name, std::string username, std::string mode)
{
	std::string message;

	if (name.empty())
	{
		std::cout << "NO CLIENT NAME" << std::endl;
		return ;
	}
	if (username.empty())
	{
		std::cout << "NO CLIENT USERNAME" << std::endl;
		return ;
	}
	this->_clientLimit = 100;
	message = MODE_CHANNEL_NOCLIENTLIMIT(name, username, this->getName(), mode);
	this->sendToAllChan(message);
	return ;
}

void	channel::setTopicEstate(std::string name, std::string username, std::string mode, int code)
{
	std::string message;

	if (name.empty())
	{
		std::cout << "NO CLIENT NAME" << std::endl;
		return ;
	}
	if (username.empty())
	{
		std::cout << "NO CLIENT USERNAME" << std::endl;
		return ;
	}
	if (code == 1)
	{
		if (this->_topicEstate == true)
		{
			this->_topicEstate = false;
			message = MODE_TOPIC_OFF(name, username, this->getName(), mode);
			this->sendToAllChan(message);
		}
	}
	if (code == 2)
	{
		if (this->_topicEstate == false)
		{
			this->_topicEstate = true;
			message = MODE_TOPIC_ON(name, username, this->getName(), mode);
			this->sendToAllChan(message);
		}
	}
	return ;
}

int	channel::handleIsInvite( client *client1, Server *serv, std::vector<std::string> temp)
{
	int check = 0;
	if (this->getIsInvite() == true)
	{
		bool isWaiting = false;
		std::list<client *> cl_list = this->_waitingList;
		std::list<client *>::iterator cl_it = cl_list.begin();
		std::list<client *>::iterator cl_ite = cl_list.end();
		std::list<client *>::iterator cl_find;
		cl_find = std::find(cl_it, cl_ite, client1);
		if (cl_find != cl_list.end())
		{
			std::cout << "TROUVEEEE" << std::endl;
			while (cl_it != cl_ite)
			{
				std::cout << YELLOW << "IN THE WAITING LIST AVANT : " << (*cl_it)->getNickName() << END << std::endl;
				if ((*cl_it)->getsocketFd() == client1->getsocketFd())
				{
					std::cout << PURPLE << "LES SOCKETS CORRESPONDENT" << END << std::endl;
					// cl_it = this->_waitingList.erase(cl_it);
					// cl_list.erase(cl_it);
					cl_it = cl_list.erase(cl_it);
					isWaiting = true;
					break ;
				}
				cl_it++;
			}
			this->_waitingList = cl_list;
			if (this->_waitingList.empty() == 0)
			{
				std::cout << BLUE2 << "--------------LA LISTE N'EST PAS VIDE----------------------" << END << std::endl;
				std::list<client *> cl_list_2 = this->_waitingList;
				std::list<client *>::iterator cl_it_2 = cl_list_2.begin();
				std::list<client *>::iterator cl_ite_2 = cl_list_2.end();
				while (cl_it_2 != cl_ite_2)
				{
					std::cout << RED << "IN THE WAITING LIST APRES : " << (*cl_it)->getNickName() << END << std::endl;
					cl_it_2++;
				}
			}
			else
			{
				std::cout << YELLOW << "--------------LA LISTE EST VIDE----------------------" << END << std::endl;
			}
		}
		std::list<client *>::iterator new_it = this->_waitingList.begin();
		std::list<client *>::iterator new_ite = this->_waitingList.end();
		for(; new_it != new_ite; new_it++)
			std::cout << PURPLE << "IN THE WAITING LIST APRES 2 : " << (*cl_it)->getNickName() << END << std::endl;
		std::cout << "ON ARRIVE A ALLER PLUS LOIN" << std::endl;
		if (isWaiting == false)
		{
			serv->setChanName(temp[0]);
			check = 6;
		}
	}
	return (check);
}

int	channel::addClientToChannel(client *client1, Server *serv, std::vector<std::string> temp)
{
	if (!client1)
	{
		std::cout << "Client doesn't exist" << std::endl;
		return (1);
	}
	// if (parameter.empty())
	// {
	// 	std::cout << "Channel name empty, please give a complete name" << std::endl;
	// 	return ;
	// }
	// std::cout << "On arrive bien jusque la" << std::endl;
	std::cout << YELLOW << "--------------------------I AM IN ADDCLIENTTOCHANNEL------------------------" << END << std::endl;
	std::string message;
	// std::list<channel *>::iterator it = this->M_listOfChannels.begin();
	// std::list<channel *>::iterator ite = this->M_listOfChannels.end();
	// while (it != ite)
	// {
	if (this->getName().compare(temp[0]) == 0)
	{
		if (this->getNbrOfClients() >= this->getClientLimit()) //poser la question aux gars
		{
			std::cout << "Limit of client reach, Can't join channel" << std::endl;
			serv->setChanName(this->getName());
			return (471);
		}
		std::cout << "Password in last = " << this->getPassword() << std::endl;
		// std::cout << "Temp[1] in last = " << temp[1] << std::endl;
		std::cout << "resultat du empty : " << this->getPassword().empty() << std::endl;
		if (this->getPassword().empty() == 0 && temp.size() >= 2)
		{
			std::cout << "resultat du compare : " << this->getPassword().compare(temp[1]) << std::endl;
			if (this->getPassword().compare(temp[1]) == 0)
			{
				this->addClientToTheChannel(client1);
				this->increaseNbrCLient();
				this->printMap();
				std::cout << "ON PASSE ICI DANS LE RAJOUT D'UN CLIENT AU CHAN AVC MDP" << std::endl;
				this->welcomeInChanMessage(client1);
				if (this->getTopic().empty() == 0)
				{
					message = RPL_TOPIC(client1->getNickName(), this->getName(), this->getTopic());
					send(client1->getsocketFd(), message.c_str(), message.length(), 0);
				}
				return (0);
			}
			else
			{
				serv->setChanName(this->getName());
				return (475);
			}
		}
		else if (this->getPassword().empty() && temp.size() < 2)
		{
			this->addClientToTheChannel(client1);
			this->increaseNbrCLient();
			this->printMap();
			std::cout << "ON PASSE ICI DANS LE RAJOUT D'UN CLIENT AU CHAN SANS MDP" << std::endl;
			this->welcomeInChanMessage(client1);
			if (this->getTopic().empty() == 0)
			{
				message = RPL_TOPIC(client1->getNickName(), this->getName(), this->getTopic());
				send(client1->getsocketFd(), message.c_str(), message.length(), 0);
			}
			return (0);
		}
		else
		{
			serv->setChanName(this->getName());
			return (475);
		}
			// std::cout << "Wrong password, can't join the channel" << std::endl;
		// std::cout << "C1" << std::endl;
		// break ;
	}
	// 	it++;
	// }
	// std::cout << "C2" << std::endl;
	return (0);
}



bool	channel::isInThechan(client *client1) const
{
	bool res = false;
	std::map<client *, bool>::const_iterator found = this->_listOfClients.find(client1);
	std::map<client *, bool>::const_iterator ite = this->_listOfClients.end();

	if (found != ite)
		res = true;
	return (res);
}

bool	channel::isOperatorInChan(client *client1) const
{
	bool res = false;
	std::map<client *, bool>::const_iterator found = this->_listOfClients.find(client1);
	// std::map<client *, bool>::iterator ite = this->_listOfClients.end();

	if (found->second == true)
		res = true;
	return (res);
}

void	channel::sendToAllChan(std::string message)
{
	std::map<client *, bool>::iterator it = this->_listOfClients.begin();
	std::map<client *, bool>::iterator ite = this->_listOfClients.end();
	while (it != ite)
	{
		send(it->first->getsocketFd(), message.c_str(), message.length(), 0);
		it++;
	}
	return ;
}

void	channel::sendPrivMsg(client *client1, std::string message)
{
	int i = 0;
	std::map<client *, bool> m_client = this->_listOfClients;
	std::map<client *, bool>::iterator it = m_client.begin();
	std::map<client *, bool>::iterator ite = m_client.end();
	while (it != ite)
	{
		std::cout << PURPLE << "i = " << i << END << std::endl;
		if (it != ite && it->first->getsocketFd() == client1->getsocketFd())
			it++;
		if (it != ite)
			send(it->first->getsocketFd(), message.c_str(), message.length(), 0);
		if (it != ite)
			it++;
		i++;
	}
	return ;
}

int	channel::isDigit(std::string str) const
{
	int i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9'))
			i++;
		else
		{
			// std::cout << "Wrong password. Only Digit accepted. Please try again : ";
			return (0);
		}
	}
	// if (i != 4)
	// {
	// 	std::cout << "Too much digit. Please try again : ";
	// 	return (0);
	// }
	return (1);
}

void	channel::welcomeInChanMessage(client *client1)
{
	std::string message, clientList;
	int toSend;

	std::map<client *, bool>::iterator it = this->_listOfClients.begin();
	std::map<client *, bool>::iterator ite = this->_listOfClients.end();
	while(it != ite)
	{
		if (it->second == true)
			clientList = clientList + "@";
		clientList = clientList + it->first->getNickName() + " ";
		it++;
	}
	message = RPL_NAMREPLY(client1->getNickName(), this->getName(), clientList);
	std::cout << RED << "MESSAGE DANS UN PREMIER TEMPS = " << message << END << std::endl;
	toSend = (send(client1->getsocketFd(), message.c_str(), message.length(), 0));
	if (toSend < 0)
	{
		std::cout << "ERROR SENDING IN WELCOME CHAN" << std::endl;
		return ;
	}
	message.erase();
	message = RPL_ENDOFNAMES(client1->getNickName(), this->getName());
	std::cout << RED << "MESSAGE DANS UN SECOND TEMPS = " << message << END << std::endl;
	toSend = (send(client1->getsocketFd(), message.c_str(), message.length(), 0));
	if (toSend < 0)
	{
		std::cout << "ERROR SENDING IN WELCOME CHAN" << std::endl;
		return ;
	}
	return ;
}

void	channel::eraseCLientFromChan(client *client1, std::string reason)
{
	std::string message, tmp;
	std::map<client *, bool>::iterator found_it = this->_listOfClients.find(client1);
	std::map<client *, bool>::iterator it = this->_listOfClients.begin();
	std::map<client *, bool>::iterator ite = this->_listOfClients.end();
	

	while (it != ite)
	{
		std::cout << PURPLE << "-------------------ON FAIT UN PRINT DU CLIENT TROUVE DANS ERASE CLIENT FROM CHAT-----------------------" << END << std::endl;
		std::cout << "LE NICK NAME = " << it->first->getNickName() << std::endl;
		std::cout << "LE REAL NAME = " << it->first->getRealName() << std::endl;
		std::cout << "LE USER NAME = " << it->first->getUserName() << std::endl;
		std::cout << "LE HOST NAME = " << it->first->getHostName() << std::endl;
		std::cout << "LE MODE = " << it->first->getMode() << std::endl;
		std::cout << "LE MESSAGE DE BIENVENU A ETE ENVOYE (1 = oui) = " << it->first->isWelcomeMessageSent() << std::endl;
		std::cout << "LE SOCKET FD = " << it->first->getsocketFd() << std::endl;
		std::cout << "LE PORT = " << it->first->getPort() << std::endl;
		std::cout << "L'ADRESSE IP = " << it->first->getIp() << std::endl;
		std::cout << PURPLE << "-------------------FIN DU PRINT CLIENT TROUVE-----------------------" << END << std::endl;
		it++;
	}

	if (found_it != ite)
	{
		this->_listOfClients.erase(client1);
	}
	std::map<client *, bool>::iterator cit = this->_listOfClients.begin();
	std::map<client *, bool>::iterator cite = this->_listOfClients.end();
	while (cit != cite)
	{
		std::cout << RED << "-------------------ON FAIT UN PRINT DU CLIENT TROUVE DANS ERASE CLIENT FROM CHAT-----------------------" << END << std::endl;
		std::cout << "LE NICK NAME = " << cit->first->getNickName() << std::endl;
		std::cout << "LE REAL NAME = " << cit->first->getRealName() << std::endl;
		std::cout << "LE USER NAME = " << cit->first->getUserName() << std::endl;
		std::cout << "LE HOST NAME = " << cit->first->getHostName() << std::endl;
		std::cout << "LE MODE = " << cit->first->getMode() << std::endl;
		std::cout << "LE MESSAGE DE BIENVENU A ETE ENVOYE (1 = oui) = " << cit->first->isWelcomeMessageSent() << std::endl;
		std::cout << "LE SOCKET FD = " << cit->first->getsocketFd() << std::endl;
		std::cout << "LE PORT = " << cit->first->getPort() << std::endl;
		std::cout << "L'ADRESSE IP = " << cit->first->getIp() << std::endl;
		std::cout << RED << "-------------------FIN DU PRINT CLIENT TROUVE-----------------------" << END << std::endl;
		cit++;
	}
	// if (reason.empty())
	// {
	// 	tmp = "";
	// 	message = KICK(client1->getNickName(), client1->getUserName(), this->getName(), client1->getNickName(), tmp);
	// 	send(client1->getsocketFd(), message.c_str(), message.length(), 0);
	// }
	// else
	// {
	// 	message = KICK(client1->getNickName(), client1->getUserName(), this->getName(), client1->getNickName(), reason);
	// 	send(client1->getsocketFd(), message.c_str(), message.length(), 0);
	// }
	(void)reason;
	return ;
}
