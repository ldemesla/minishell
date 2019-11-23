# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabois <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 12:06:19 by mabois            #+#    #+#              #
#    Updated: 2019/10/09 12:06:21 by mabois           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	bt_echo.c\
		bt_export_bis.c\
		exit.c\
		lst_commands.c\
		string_tools_1.c\
		bt_cd.c\
		bt_echo_bis.c\
		bt_export_ter.c\
		executable.c\
		init_clear.c\
		init_clear_2.c\
		main.c\
		string_tools_2.c\
		bt_cd_tools.c\
		bt_cd_tools_2.c\
		bt_export.c\
		bt_export_bis_2.c\
		bt_pwd.c\
		executable_2.c\
		exectuable_3.c\
		main_bis.c\
		main_bis_2.c\
		main_ter.c\
		redirection.c\
		string_tools_3.c\
		utils.c\

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
