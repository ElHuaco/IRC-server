/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:56:29 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/14 11:23:49 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
//#include "Commands.hpp"

#include <iostream>
#include <string>

//signal_handlers con signal(SIGKILL)

//bool	is_cmd(const std::string &str);
std::string	*ft_argv_parser(int argc, char **argv)
{
	if (argc == 3)		// Two arguments case, no need to parse
	{
		std::string		array[2];
		array[0] = argv[1];
		array[1] = argv[2];
		return (array);
	}
	if (argc == 4)		// Three arguments case, the IRC network provided must be parsed (first one)
	{
		std::string		array[5];
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
	
	//Parsear argv en host, post_network, pass_network, port, password.
	Server server(); //Hace todo el setup desde getaddrinfo() hasta listen().
	//posibles exceptions en creacion del objeto Server.
	fd_set read_fds; //lista sockets sobre los que hacer select();
	//Bucle principal sobre select() y los sockets que estén listos entonces.
	while (1)
	{
		read_fds = server.getMasterFD();
		//select(&read_fds);
		for (int i = 0; i <= server.getMaxFD(); ++i)
		{
			if (FD_ISSET(i, &read_fds) == false)
				continue ;
			//Si es nueva conexión, server.newUser();
			if (i == server.getListerner())
			{
				//server.addUser(); El nuevo socket va al nuevo objeto Usere
			}
			//Si no es nueva conexión, parsea para ver si es un Command y entonces
			// el command.execute(server, ...) hace su función o se envía el mensaje.
			else
			{
				//parsear xq puede ser mensaje simple en vez de command
				//recv();
				std::string info(buf);
				if (/*es un command*/ is_cmd(info) == true)
				{
					Command cmd(info);
					cmd.execute();
				}
				else
					//User.mensaje(info);
			}
		}
	}
	return (0);
}
