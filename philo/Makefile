# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 16:04:19 by tkeil             #+#    #+#              #
#    Updated: 2025/01/29 16:30:30 by tkeil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = philo
INCLUDES = -I./headers
OBJSDIR = objs/
SRCSDIR = srcs/

SRCS = philosophers.c numbers.c clearing.c init_data.c logging.c strings.c threads.c gettime.c init_utils.c controller.c state.c thread_utils.c

SRCS_PATHS = $(addprefix $(SRCSDIR), $(SRCS))

OBJS = $(SRCS_PATHS:$(SRCSDIR)%.c=$(OBJSDIR)%.o)

all: $(NAME)

$(NAME): $(OBJS) $(OBJSDIR)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

assembly:
	$(CC) -S srcs/philosophers.c

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./philo

.PHONY: all clean fclean re bonus
