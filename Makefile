# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 16:04:19 by tkeil             #+#    #+#              #
#    Updated: 2025/01/28 12:50:08 by tkeil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = philosophers
INCLUDES = -I./philo/headers
OBJSDIR = objs/philo/
SRCSDIR = philo/srcs/
B_OBJSDIR = objs/bonus/
B_SRCSDIR = bonus/srcs/

SRCS = philosophers.c numbers.c clearing.c init_data.c logging.c strings.c threads.c gettime.c init_utils.c controller.c
BONUS_SRCS = philosophers.c numbers.c clearing.c init_data.c logging.c strings.c threads.c gettime.c init_utils.c controller.c

SRCS_PATHS = $(addprefix $(SRCSDIR), $(SRCS))
BONUS_PATHS = $(addprefix $(B_SRCSDIR), $(BONUS_SRCS))

OBJS = $(SRCS_PATHS:$(SRCSDIR)%.c=$(OBJSDIR)%.o)
OBJS_BONUS = $(BONUS_PATHS:$(B_SRCSDIR)%.c=$(B_OBJSDIR)%.o)

all: $(NAME)

bonus: $(OBJS_BONUS) $(B_OBJSDIR)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(INCLUDES) -o $(NAME)

$(NAME): $(OBJS) $(OBJSDIR)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(B_OBJSDIR)%.o: $(B_SRCSDIR)%.c
	mkdir -p $(B_OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf objs/

fclean: clean
	rm -rf $(NAME) test

re: fclean all

assembly:
	$(CC) -S srcs/philosophers.c

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./philosophers

.PHONY: all clean fclean re bonus
