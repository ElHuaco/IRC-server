/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 09:56:29 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/11 12:01:46 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

//signal_handlers con signal(SIGKILL)

typedef
int main(int argc, char **argv)
{
	if (argc != 3 && argc != 4)
	{
		std::cout << "error: ircserv: bad arguments" << std::endl;
		return (EXIT_FAILURE);
	}
	//Distinto constructor según si hay que conectarse a una red IRC o no.
	Server server(); //Hace todo el setup desde getaddrinfo() hasta listen().
	fd_set read_fds; //lista sockets sobre los que hacer select();
	//Bucle principal sobre select() y los sockets que estén listos entonces.
	while (1)
	{
		read_fds = server.getMasterFD();
		//select();
		for (int i = 0; i <= server.getMaxFD(); ++i)
		{
			if (FD_ISSET(i, &read_fds))
			{
				//Si es nueva conexión, server.newClient();
				//Si no es nueva conexión, parsea el main, selecciona Command y
				// el command.execute(server, ...) hace su función.
				std::vector<string> info(3);
				info = parse(buf);//Solo parseo nombre command
				for (int i...)
					if (name_list[i] == info[1])
						Command cmd = constructor[i](info[0], info[2]);
						cmd.execute(); // Posibles errores de parseo aquí
			}
		}
	}
}
