#pragma once

# include <map>
# include <locale>
# include "Server.hpp"
# include "User.hpp"

class Command
{
	private:
		//cadenas prefix, nombre, params
		//int _num_params
		Server					&_server;
		User					&_commander;
		std::string				_prefix;
		std::string				_command;
		std::string				*_params;
		std::string				*_erroneous;
		int						_paramsNum;

		Command(void);
		Command(const Command &other);
	public:
		// Constructor + Destructor
		Command(std::string str, Server &server, User &commander); // Prefix, Command and Parameters parser.
		~Command(void);

		// Getters + Setters
		std::string		getCommand(void) const;
		std::string		*getParams() const;
		std::string		*getErroneous() const;

		// Functions
		int				parseStr(std::string str);
		void			execute();
		void			numeric_reply(int key);

		// Commands
		void				ftNICK();
		void				ftUSER();
		void				ftOPER();
		void				ftQUIT();
		void				ftJOIN();
		void				ftPART();
		void				ftTOPIC();
		void				ftNAMES();
		void				ftLIST();
		void				ftKICK();
		void				ftPRIVMSG();
};
