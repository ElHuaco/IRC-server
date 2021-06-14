/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:56:29 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/14 09:45:31 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

//signal_handlers con signal(SIGKILL)

//bool	is_cmd(const std::string &str);

int main(int argc, char **argv)
{
	if (argc != 3 && argc != 4)
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
			//Si es nueva conexión, server.newClient();
			if (i == server.getListerner())
			{
				//server.addClient(); El nuevo socket va al nuevo objeto Cliente
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
					//cliente.mensaje(info);
			}
		}
	}
}
