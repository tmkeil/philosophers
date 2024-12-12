# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 16:04:19 by tkeil             #+#    #+#              #
#    Updated: 2024/12/12 18:46:11 by tkeil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# CFLAGS = -Wall -Wextra -Werror

NAME = philosophers
INCLUDES = -Iheaders
OBJSDIR = objs/
SRCSDIR = srcs/
LIBFTDIR = libft/
LIBFT = libft/libft.a

SRCS = philosophers.c
BONUS_SRCS = philosophers.c

SRCS_PATHS = $(addprefix $(SRCSDIR), $(SRCS))
BONUS_PATHS = $(addprefix $(SRCSDIR), $(BONUS_SRCS))

OBJS = $(addprefix $(OBJSDIR), $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJSDIR), $(BONUS_SRCS:.c=.o))

all: $(NAME)

bonus: $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(INCLUDES) -o $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o $(NAME)

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	rm -rf $(OBJSDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME) $(CHECKER)
	make -C $(LIBFTDIR) fclean

re: fclean all

assembly:
	$(CC) -S srcs/philosophers.c

.PHONY: all clean fclean re bonus
