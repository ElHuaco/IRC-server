/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:56:29 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/16 11:40:00 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
//#include "Commands.hpp"

#include <iostream>

//signal_handlers con signal(SIGKILL)

//bool	is_cmd(const std::string &str);
std::string	*ft_argv_parser(int argc, char **argv)
{
	if (argc == 3)		// Two arguments case, no need to parse
	{
		static std::string		array[2];
		array[0] = argv[1];
		array[1] = argv[2];
		return (array);
	}
	if (argc == 4)		// Three arguments case, the IRC network provided must be parsed (first one)
	{
		static std::string		array[5];
		int i = 0;
		char *aux = strtok(argv[1], ":"); // Using strtok to separate the tokens
		while (aux != 0 && i < 5)
		{
			array[i++] = aux;
			aux = strtok(0, ":");
		}
		if (i != 3) // In case there are more or less tokens an error will be returned
			return (0);
		array[3] = argv[2];
		array[4] = argv[3];
		return (array);
	}
	return (0); // In case there are too many or too few arguments an error will be returned
}

int main(int argc, char **argv)
{
	std::string *arg = ft_argv_parser(argc, argv);
	if (arg == 0)
	{
		std::cout << "error: ircserv: bad arguments" << std::endl;
		return (EXIT_FAILURE);
	}
	Server server;
	if (argc == 3)
	{
		server.setPassword(arg[1]);
		server.start(arg[0]);
	}
	else
	{
		server.setPassword(arg[4]);
		server.start(arg[3], arg[0], arg[1], arg[2]);
	}
	fd_set read_fds;
	while (1)
	{
		//Quizá need write_fds para connect()?
		read_fds = server.getMaster();
		if (select(server.getMax() + 1, &read_fds, NULL, NULL, NULL) == -1)
			throw std::runtime_error(strerror(errno));
		for (int i = 0; i <= server.getMax(); ++i)
		{
			if (FD_ISSET(i, &read_fds) == false)
				continue ;
			if (i == server.getListener())
			{
				server.addUser();
				std::cout << "New connection. " << std::endl;
			}
			//Si no es nueva conexión, parsea para ver si es un Command y 
			// entonces command.execute(server, ...)  o se envía el mensaje.
			else
			{
				char buff[412];
				int nbytes;
				if ((nbytes = recv(i, buff, sizeof buff, 0)) <= 0)
				{
					if (nbytes != 0)
						throw std::runtime_error(strerror(errno));
					server.deleteUser(i);
				}
				else
				{
					for (int j = 0; j <= server.getMax(); ++j)
					{
						if (FD_ISSET(j, &server.getMaster())
							&& j != server.getListener() && j != i)
							if (send(j, buff, nbytes, 0) == -1)
								throw std::runtime_error(strerror(errno));
					}
				}
				//parsear xq puede ser mensaje simple en vez de command
				//recv();
				/*std::string info(buf);
				if (is_cmd(info) == true)
				{
					Command cmd(info);
					if ((ret = cmd.execute() != 0)
						server.reply_error(ret);
				}
				else
					User.mensaje(info);
				*/
			}
		}
	}
}

