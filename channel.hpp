/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:33:59 by mlamarcq          #+#    #+#             */
/*   Updated: 2024/02/12 12:02:02 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"
#include "command.hpp"
#include "server.hpp"

class client;
class Server;
class command;

class channel {

	public:
		channel();
		channel(std::string channelName, int passWord);
		channel(const channel& copy);
		channel& operator=(const channel& copy);
		~channel();

		// si join 1ere fois -> client operator
		std::string	getName(void) const;
		std::string getPassword(void) const;
		int			getClientLimit(void) const;
		int			getNbrOfClients(void) const;
		bool		getIsInvite(void) const ;
		std::map<client*, bool> getListOfClients(void) const;
		
		void		increaseNbrCLient(void);
		void		changeIsInvite(void);

		
		int			setName(std::string parameter);
		void		setPassword(std::string password);
		void		setListofClient(client  *client1);
		void		setOperators(client *client1);
		void		setNewPassWord(std::string pass, std::string name, std::string username, std::string mode);
		void		clearPassWord(std::string name, std::string username, std::string mode);

		int			enterPassword(void) const;

		void		addClientToTheChannel(client *client1);

		int			isDigit(std::string str) const;

		void		printMap(void) const;

		client		*copyClient(client *original);

		int			setChannelFirstTime(client *client1, Server *serv, std::vector<std::string> temp);

		void		welcomeInChanMessage(client *client1);

		void		sendToAllChan(std::string message);

		void		changePrivileges(std::string name, std::string username, std::string mode, std::string client1, int code);

		void		setClientLimit(std::string name, std::string username, std::string mode, std::string nb);

		void		eraseClientLimit(std::string name, std::string username, std::string mode);


		// variables
	private :
	
		// std::list<client *>	_listOfClients;
		// std::list<client *>	_operators;
		int						_clientLimit;
		int						_nbrClients;
		std::map<client *, bool> _listOfClients;
		std::string				_name;
		std::string				_pswd;
		bool					_isInvite;
};

#endif