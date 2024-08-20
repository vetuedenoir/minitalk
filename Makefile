# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kscordel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 17:30:54 by kscordel          #+#    #+#              #
#    Updated: 2023/03/28 17:54:52 by kscordel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

C_SRC_DIR = src_client/
C_SRC = $(addprefix $(C_SRC_DIR), client.c)
C_OBJ = $(C_SRC:.c=.o)

S_SRC_DIR = src_serveur/
S_SRC = $(addprefix $(S_SRC_DIR), serveur.c check_id.c)
S_OBJ = $(S_SRC:.c=.o)

C_NAME = client
S_NAME = server

LIBPATH = libft/libft.a

all:	$(C_NAME) $(S_NAME)

$(C_NAME):	$(C_OBJ) | lib
		$(CC) $(CFLAGS) -o $@ $(C_OBJ) $(LIBPATH) 

$(S_NAME):	$(S_OBJ) | lib
		$(CC) $(CFLAGS) -o $@ $(S_OBJ) $(LIBPATH)

lib:
	@make -C ./libft

clean:
		$(RM) $(C_OBJ) $(S_OBJ)
		@make clean -C ./libft

fclean:	clean
		$(RM) $(C_NAME) $(S_NAME)
		@make fclean -C ./libft

re:	fclean all

.PHONY: all clean fclean re
	
