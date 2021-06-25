#pragma once

# define DEBUG

# include <map>
# include <list>
# include <string>

class User;
class Server;

class Channel
{
	public:
		typedef std::list<User *>::iterator	iterator;

	private:
		//lista de usuarios en el canal
		std::list<User *>		_chanops;
		//un vector de chanops
		//atributos de commands: mensaje del día, etc.
		std::string	_name;
		std::string _topic;
		std::string	_whoTopicNick;
		std::string _whoTopicSetat;
		Channel();

	public:
	//	Constructors + Destructor
		Channel(std::string &name);
		~Channel();
		Channel(const Channel & other);
		Channel	&operator=(const Channel &rhs);

	//	Functions
		Channel				*clone(void) const;
		void				addChanop(User *chanop);
		void				deleteChanop(User *chanop);
		bool				isChanop(User *chanop);
//		void				chanMessage(Server &serv, const char *buff, int nbytes);

	//	Getters + Setters
		std::string			getName(void) const;
		std::list <User *>	getListChanops(void) const;
		std::string			getTopic(void) const;
		std::string			getWhoTopicNick(void) const;
		std::string			getWhoTopicSetat(void) const;

		void				setTopic(std::string topic);
		void				setWhoTopicNick(std::string str);
		void				setWhoTopicSetat(std::string str);

};
# include "User.hpp"
# include "Server.hpp"
