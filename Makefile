# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kscordel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 13:18:04 by kscordel          #+#    #+#              #
#    Updated: 2023/03/21 16:20:08 by kscordel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# SOURCE CLIENT
CLSRCD = src_client
CLOBJD = obj_client
#CLSRC = $(CLSRCD)/client.c $(CLSRCD)/test.c \
CLSRC = (wildcard $(CLSRCD)/*.c)
CLOBJ = $(patsubst $(CLSRCD)/%.c, $(CLOBJD)/%.o, $(ClSRC))

# SOURCE SERVEUR
SVSRCD = src_serveur
SVOBJD = obj_serveur
SVSRC = $(SVSRCD)/serveur.c \
SVOBJ = $(patsubst $(SVSRCD)/%.c, $(SVOBJD)/%.o, $(SVSRC))

CNAME =	client
SNAME = serveur

LIBPATH = libft/libft.a

all: $(CNAME)

$(CNAME): $(CLOBJ) | lib
	$(CC) $(CFLAGS) $^ $(LIBPATH) -o $@

$(SNAME): $(SVOBJ) | lib
	$(CC) $(CFLAGS) $(SVOBJ) $(LIBPATH) -o $@

$(CLOBJD)/%.o: $(CLSRCD)/%.c | $(CLOBJD)
	$(CC) $(CFLAGS) -c $< -o $@

$(SVOBJD)/%.o: $(SVSRCD)/%.c | $(SVOBJD)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLOBJD):
	mkdir -p $(CLOBJD)

$(SVOBJD):
	mkdir -p $(SVOBJD)

lib:
	@make -C ./libft

clean:
	rm -rf $(CLOBJD)
	rm -rf $(SVOBJD)
	make clean -C ./libft

fclean: clean
	rm -f $(CNAME)
	rm -f $(SNAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all lib clean fclean re
