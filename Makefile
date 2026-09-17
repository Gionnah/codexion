# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/17 22:45:00 by mvelonja          #+#    #+#              #
#    Updated: 2026/09/17 22:46:23 by mvelonja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = codexion

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I. -Ibase_action -Icoder -Ihandlers -Iutils
LDFLAGS     = -pthread

RM          = rm -f
DIR_DUP     = mkdir -p $(@D)

# Lists of Source Files
SRCS        = main.c \
              base_action/initialisation.c \
              base_action/log_state.c \
              base_action/monitoring.c \
              base_action/request_queue.c \
              base_action/scheduler.c \
              coder/coder_action.c \
              handlers/coder_handler.c \
              handlers/dongle_handler.c \
              handlers/free_memory_handler.c \
              handlers/input_handler.c \
              handlers/simulation_handler.c \
              utils/coder_action_utils.c \
              utils/dongle_handler_utils.c \
              utils/initialisation_utils.c \
              utils/input_handler_utils.c \
              utils/scheduler_utils.c \
              utils/simulation_handler_utils.c

# Object Files
OBJ_DIR     = obj
OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re