# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 20:05:41 by arcebria          #+#    #+#              #
#    Updated: 2025/01/28 19:08:51 by arcebria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = src/main.c src/init_pipex.c src/run_pipex.c src/handlers.c src/parsing.c 
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

INCLUDE = inc/pipex.h \
		libft/libft.h libft/ft_printf.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address	


all: dir $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) Makefile
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

dir:
	@make -C $(LIBFT_DIR)

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
