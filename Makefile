# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/22 09:25:30 by aleon-ca          #+#    #+#              #
#    Updated: 2021/06/22 13:22:49 by fjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp Server.cpp User.cpp Channel.cpp Command.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = ircserv

FLAGS = -std=c++98 -Wall -Wextra -Werror
CLANG = clang++ $(FLAGS) 

RM = rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CLANG) $(OBJS) -o $(NAME)

clean:		
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
