# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 16:04:19 by tkeil             #+#    #+#              #
#    Updated: 2025/01/27 19:04:10 by tkeil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = philo
INCLUDES = -Iheaders
OBJSDIR = objs/
SRCSDIR = srcs/

SRCS = philosophers.c numbers.c clearing.c init_data.c logging.c strings.c threads.c gettime.c init_utils.c observer.c
TEST_SRCS = ./srcs/testing.c
BONUS_SRCS = philosophers.c numbers.c clearing.c init_data.c logging.c strings.c threads.c gettime.c init_utils.c observer.c

SRCS_PATHS = $(addprefix $(SRCSDIR), $(SRCS))
TESTING_PATHS = $(addprefix $(SRCSDIR), $(TEST_SRCS))
BONUS_PATHS = $(addprefix $(SRCSDIR), $(BONUS_SRCS))

OBJS = $(addprefix $(OBJSDIR), $(SRCS:.c=.o))
OBJS_TESTING = $(addprefix $(OBJSDIR), $(TEST_SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJSDIR), $(BONUS_SRCS:.c=.o))

all: $(NAME)

bonus: $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(INCLUDES) -o $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME) test

re: fclean all

testing:
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRCS) -o test

assembly:
	$(CC) -S srcs/philosophers.c

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./philosophers

.PHONY: all clean fclean re bonus
