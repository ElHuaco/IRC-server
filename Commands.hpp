/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 11:00:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/11 11:36:51 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Command
{
	private:
		//cadenas prefix, nombre, params
		//int _num_params
	public:
		//Todo lo normal
		Command(_prefix, _name, _params); //coge las cadenas y separa por espacios
		void	execute(Server server, Client commander) = 0;
		static	std::vector<string> name_list = {"USER", "...", ..}
}

Command		&constructor_A (void)
{
	return (USER_cmd());
}

class USER_cmd : public Command
{
	public:
		USER_cmd(_prefix, _params) : Command(_prefix, "USER", _params) {}
		virtual ~USER_cmd(void) {}
		execute(Ser....)
		{
			//comprueba errores de número de parámetros y demás
		}
}
