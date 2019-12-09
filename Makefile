# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/09 19:52:43 by ldemesla          #+#    #+#              #
#    Updated: 2019/12/09 19:53:37 by ldemesla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	srcs/bt_echo.c\
		srcs/bt_export_bis.c\
		srcs/exit.c\
		srcs/lst_commands.c\
		srcs/string_tools_1.c\
		srcs/bt_cd.c\
		srcs/bt_echo_bis.c\
		srcs/bt_export_ter.c\
		srcs/executable.c\
		srcs/init_clear.c\
		srcs/init_clear_2.c\
		srcs/main.c\
		srcs/string_tools_2.c\
		srcs/bt_cd_tools.c\
		srcs/bt_cd_tools_2.c\
		srcs/bt_export.c\
		srcs/bt_export_bis_2.c\
		srcs/bt_pwd.c\
		srcs/executable_2.c\
		srcs/exectuable_3.c\
		srcs/main_bis.c\
		srcs/main_bis_2.c\
		srcs/main_ter.c\
		srcs/redirection.c\
		srcs/string_tools_3.c\
		srcs/utils.c\

OBJECTS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

all : $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJECTS)
	$(CC) $(FLAGS) $(SRCS) -o $@

.PHONY : clean all fclean re bonus

clean : 
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all
