/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:33:59 by mlamarcq          #+#    #+#             */
/*   Updated: 2024/02/14 17:33:24 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

# define CLRF	"\r\n"
//# define SERVER_NAME				"ircserv"
# define SERVER_NAME				"localhost"
//# define SERVER_HOSTNAME			std::string(SERVER_NAME) + ".fr"
#define SERVER_HOSTNAME				std::string("localhost")
# define SERVER_VERSION				"v4.2"
# define CHANNEL_MODES				"klnt"
# define USER_MODES					"io"
# define RPL_PREFIX(code, nick)		std::string(":" + SERVER_HOSTNAME + " " + code + " " + nick)
# define CLIENT_ID(nickname, username, command) (":" + nickname + "!~" + username + "@" + SERVER_NAME + " " + command + " ")

//		RPL
# define RPL_WELCOME(nick, user, host)			RPL_PREFIX("001", nick) + " :Welcome to the " + SERVER_NAME + " Network, " + nick + "!" + user + "@" + host + CLRF
# define RPL_YOURHOST(nick)						RPL_PREFIX("002", nick) + " :Your host is " + SERVER_HOSTNAME + ", running version " + SERVER_VERSION + CLRF
# define RPL_CREATED(nick, datetime)			RPL_PREFIX("003", nick) + " :This server was created " + datetime + CLRF
# define RPL_MYINFO(nick)						RPL_PREFIX("004", nick) + " " + SERVER_HOSTNAME + " " + SERVER_VERSION + " " + USER_MODES + " " + CHANNEL_MODES + CLRF
# define RPL_UMODEIS(nick, modes)				RPL_PREFIX("221", nick) + " :" + modes + CLRF
# define RPL_AWAY(nick, senderNick, msg)		RPL_PREFIX("301", nick) + " " + senderNick + " " + msg + CLRF
# define RPL_CHANNELMODEIS(channel, mode)		RPL_PREFIX("324", "") + " " + channel + " " + mode + " " + CLRF
# define RPL_NOTOPIC(nick, chan)				RPL_PREFIX("331", nick) + " " + chan + " :No topic is set" + CLRF
# define RPL_TOPIC(nick, chan, topic)			RPL_PREFIX("332", nick) + " " + chan + " " + topic + CLRF
// # define RPL_NAMREPLY(nick, chan, names)		RPL_PREFIX("353", nick) + " = " + chan + " :" + names + CLRF
// # define RPL_ENDOFNAMES(nick, chan)				RPL_PREFIX("366", nick) + " " + chan + " :End of /NAMES list" + CLRF
# define RPL_NAMREPLY(nickname, channel, list_client) (std::string(":") + SERVER_NAME + " 353 " + nickname + " = " + channel + " :" + list_client  + "\r\n")
# define RPL_ENDOFNAMES(nickname, channel) (std::string(":") + SERVER_NAME + " 366 " + nickname + " " + channel + " :End of /NAMES list" + "\r\n")
// # define RPL_PASSWORD_CHANGED(nickname, channel, new_password) (std::string(":") + SERVER_NAME + " 370 " + nickname + " " + channel + " :Password for " + channel + " changed to " + new_password + "\r\n")
#define RPL_PASSWORD_CHANGED(nickname, channel, new_password) ("Password for " + std::string(channel) + " changed to " + std::string(new_password))


# define RPL_YOUREOPER(nick)					RPL_PREFIX("381", nick) + " :You are now an IRC operator" + CLRF
# define RPL_QUIT(nick, senderNick, msg)		RPL_PREFIX("999", nick) + " :" + senderNick + " " + msg + CLRF

//		ERROR
# define ERR_NOSUCHNICK(nick, errNick)				RPL_PREFIX("401", nick) + " " + errNick + " :No such nick" + CLRF
# define ERR_NOSUCHCHANNEL(nick, chan)				RPL_PREFIX("403", nick) + " " + chan + " :No such channel" + CLRF
# define ERR_CANNOTSENDTOCHAN(nick, chan)			RPL_PREFIX("404", nick) + " " + chan + " :Cannot send to channel" + CLRF
# define ERR_TOOMANYTARGETS(nick)					RPL_PREFIX("407", nick) + " :Too many targets" + CLRF
# define ERR_NORECIPIENT(nick, command)				RPL_PREFIX("411", nick) + " :No recipient given (" + command + ")" + CLRF 
# define ERR_NOTEXTTOSEND(nick)						RPL_PREFIX("412", nick) + " :No text to send" + CLRF
# define ERR_UNKNOWNCOMMAND(nick, command)			RPL_PREFIX("421", nick) + " :" + command + " :Unknown command" + CLRF
# define ERR_NONICKNAMEGIVEN(nick)					RPL_PREFIX("431", nick) + " :No nickname given" + CLRF
# define ERR_ERRONEUSNICKNAME(nick, errNick)		RPL_PREFIX("432", nick) + " " + errNick + " :Erroneous nickname" + CLRF
# define ERR_NICKNAMEINUSE(nick, errNick)			RPL_PREFIX("435", nick) + " " + errNick + " :Nickname is already in use" + CLRF 
# define ERR_USERNOTINCHANNEL(nick, userNick, chan)	RPL_PREFIX("441", nick) + " " + chan + " " + userNick + " :They aren't on that channel" + CLRF
# define ERR_NOTONCHANNEL(nick, chan)				RPL_PREFIX("442", nick) + " :" + chan + " :You're not on that channel" + CLRF
# define ERR_NEEDMOREPARAMS(nick, cmd)				RPL_PREFIX("461", nick) + " :" + cmd + " :Not enough parameters" + CLRF
# define ERR_ALREADYREGISTRED(nick)					RPL_PREFIX("462", nick) + " :Unauthorized command (already registered)" + CLRF
# define ERR_PASSWDMISMATCH(nick)					RPL_PREFIX("464", nick) + " :Password incorrect" + CLRF
# define ERR_CHANNELISFULL(nick, chan)				RPL_PREFIX("471", nick) + " " + chan + " :Cannot join channel (+l)" + CLRF
# define ERR_UNKNOWNMODE(nick, chan)				RPL_PREFIX("472", nick) + " " + chan + " is unknown mode char to me" + CLRF
# define ERR_BANNEDFROMCHAN(nick, chan)				RPL_PREFIX("474", nick) + " " + chan + " :Bannded from channel (+b)" + CLRF
# define ERR_BADCHANNELKEY(nick, chan)				RPL_PREFIX("475", nick) + " " + chan + " :Cannot join channel (+k)" + CLRF
# define ERR_NOPRIVILEGES(nick)						RPL_PREFIX("481", nick) + " :Permission Denied- You're not an IRC operator" + CLRF
# define ERR_CHANOPRIVSNEEDED(channel)				RPL_PREFIX("482", "") + channel + " :You're not channel operator\r\n"
# define ERR_NOOPERHOST(nick)						RPL_PREFIX("491", nick) + " :No O-lines for your host" + CLRF
# define ERR_UMODEUNKNOWNFLAG(target)				RPL_PREFIX("501", "") + " " + target + " :Unknown MODE flag" + CLRF
# define ERR_USERSDONTMATCH(target)					RPL_PREFIX("502", "") + " " + target + " :Cant change mode for other users" +  CLRF
# define ERR_INVITEONLYCHAN(nick, channel)			(std::string(":") + SERVER_NAME + " 473 " + nick + " " + channel + " :Cannot join channel (+i)\r\n")
# define PONG(nickname) 							(std::string(":") + SERVER_NAME + " PONG " + SERVER_NAME + " :" + SERVER_NAME + "\r\n")
# define NO_INVITE(nick, chan) 						(std::string(":") + SERVER_NAME + " Mode " + chan + " -i (invite_only) remove by " + nick + ". The channel is no longer in restricted mode." + CLRF)
# define YES_INVITE(nick, chan)						(std::string(":") + SERVER_NAME + " Mode " + chan + " +i (invite_only) add by " + nick + ". The channel is now in restricted mode." + CLRF)
//# define JOIN_CHAN(nick, chan)						(std::string(":") + SERVER_NAME + " JOIN :" + chan + " " + nick + " has joined" + CLRF)
# define JOIN_CHAN(nick, chan)						(std::string(":") + SERVER_NAME + " 001 " + nick + " :Welcome in " + chan + ", " + nick + "!" + CLRF)


# define MODE_CHANNEL_NEWMDP(nickname, username, channel, mode, pass)		(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " password is now :" + pass + "\r\n")
# define MODE_CHANNEL_CLEARMDP(nickname, username, channel, mode)			(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " password is now erased" + "\r\n")
# define MODE_CHANNEL_NOWOP(nickname, username, channel, mode, name)		(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " " + name + " is now an operator" + "\r\n")
# define MODE_CHANNEL_NOMOREOP(nickname, username, channel, mode, name)		(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " " + name + " is no longer an operator" + "\r\n")
# define MODE_CHANNEL_CLIENTLIMIT(nickname, username, channel, mode, nb)	(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " " + "client limit is now " + nb + "\r\n")
# define MODE_CHANNEL_NOCLIENTLIMIT(nickname, username, channel, mode)		(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " " + "no more client limit" + "\r\n")
# define MODE_CHANNEL_NO_INVITE(nickname, username, channel, mode) 			(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " " + "(invite_only) remove " + "\r\n")
# define MODE_CHANNEL_YES_INVITE(nickname, username, channel, mode)			(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " " + "(invite_only) add. The channel is now in restricted mode." + "\r\n")

# define MODE_UNKNOW_MODE(nickname, username, channel, mode)				(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " is unknown mode char to me" + "\r\n")
# define MODE_TOPIC_OFF(nickname, username, channel, mode)					(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " Only operators can now change channel's topic." + "\r\n")
# define MODE_TOPIC_ON(nickname, username, channel, mode)					(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " Channel's topic can now be change by everyone." + "\r\n")

# define MODE_NEEDMOREPARAMS(nickname, username, channel, mode)				(CLIENT_ID(nickname, username, "MODE")  + channel + " " + mode + " Error. Need more prarameters." + "\r\n")

// # define NOTONCHANNEL(nickname, username, channel) 							(CLIENT_ID(nickname, username, "") + channel + " Error. You are not on that channel.\r\n")
#define NOTONCHANNEL(nickname, username, channel) 							(std::string(":") + SERVER_NAME + " 442 " + nickname + " " + channel + " :You are not on that channel\r\n")

# define NOSUCHCHANNEL(nickname, username, channel)							(CLIENT_ID(nickname, username, "") + " " + channel + " Error. No such channel." + "\r\n")
// # define TOPIC_IS_OFF(nick, chan)											(std::string(":") + SERVER_NAME + " " + nick + " :Topic changes desabled on " + chan + " !" + CLRF)
# define ERR_USERONCHANNEL(nickname, username, channel, name)				(CLIENT_ID(nickname, username, "") + " 443 " + channel + " " + name + " :is already on channel." + "\r\n")
// # define ERR_NOSUCHNICK(nickname, username, name)							(RPL_PREFIX("401", nickname) + " " + name + " :no such nick" + "\r\n")
# define INVITE_ON_CHAN(nickname, username, channel, name)					(CLIENT_ID(nickname, username, "") + " " + name + " You are invited on " + channel + " by " + nickname + "\r\n")
# define NEEDMOREPARAMS(nickname, username, cmd)							(CLIENT_ID(nickname, username, "")  + cmd + " Error. Need more prarameters." + "\r\n")
# define PRIVMSG_CHAN(nickname, username, dest, msg) 							(CLIENT_ID(nickname, username, "PRIVMSG") + dest + " :" + msg + "\r\n")




#include "server.hpp"

class client;
class Server;
class channel;

class command {

	public:
		command();
		command(const command& copy);
		command& operator=(const command& copy);
		~command();

		
		std::string		PASS(int fd, Server *serv);
		std::string		NICK(int fd, Server *serv);
		std::string		USER(int fd, Server *serv);
		std::string		PING(int fd, Server *serv);
		//std::string		PONG();
		std::string		OPER();
		std::string		QUIT(int fd, Server* serv);
		std::string		PART();
		std::string		KICK();
		std::string		NOTICE();
		std::string		KILL();
		std::string		WALLOPS();
		int				TOPIC(client *client1, Server *serv);
		int				MODE(client *client1, Server *serv);
		int				JOIN(client *client1, Server *serv);
		int				INVITE(client *client1, Server *serv);
		int				PRIVMSG(client *client1, Server *serv);

		std::string		bot();

		std::vector<std::string>	parsTemp(std::vector<std::string> temp);

		int			handleCmd(client *client1, Server *serv, std::string cmd);
		int			whatArg(std::vector<std::string> temp);
		int			whatSign(std::vector<std::string> temp);


		//Setters and Getters for handling errors
		// std::string			getCharErr(void) const;
		// void				setCharErr(std::string err);
};
#endif