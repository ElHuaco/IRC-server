#pragma once

# define DEBUG

# include <map>
# include <list>
# include <string>

class User;

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
		void				deleteChanop(User  *chanop);
		void				chanMessage(Server &serv, const char *buff, int nbytes);

	//	Getters + Setters
		std::string			getName(void) const;
		std::list <User *>	getListChanops(void) const;
		std::string			getTopic(void) const;

		void				setTopic(std::string topic);

};
# include "User.hpp"
