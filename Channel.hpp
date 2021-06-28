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
		std::string	_name;
		std::string _topic;
		std::string	_whoTopicNick;
		std::string _whoTopicSetat;
		int			_chanusers;
		Channel();

	public:
	//	Constructors + Destructor
		Channel(std::string &name);
		~Channel();
		Channel(const Channel & other);
		Channel	&operator=(const Channel &rhs);

	//	Functions
		Channel				*clone(void) const;

	//	Getters + Setters
		std::string			getName(void) const;
		std::string			getTopic(void) const;
		std::string			getWhoTopicNick(void) const;
		std::string			getWhoTopicSetat(void) const;
		int					getChanUsers() const;

		void				setTopic(std::string topic);
		void				setWhoTopicNick(std::string str);
		void				setWhoTopicSetat(std::string str);
		void				setChanUsers(int);

};
# include "User.hpp"
# include "Server.hpp"
