# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2026/01/06 14:58:26 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILESCH			= main.c \
					  exit.c \
					  checker.c \
					  ops_p.c \
					  ops_r.c \
					  ops_rr.c \
					  ops_s.c \
					  util.c

CFILESSO			= main.c \
					  util.c \
					  stack_util.c \
					  op_util.c \
					  op_timize.c \
					  op_p.c \
					  op_r.c \
					  op_rr.c \
					  op_s.c \
					  op.c \
					  build.c \
					  lis.c \
					  lis_get.c \
					  lis_write.c \
					  pivot.c \
					  push_ahead.c \
					  push_back.c \
					  push_back_cost.c \
					  final_rotate.c \
					  exit.c

SRCDIRCH			= src/checker
SRCDIRSO			= src/solver

SRCCH				= $(addprefix $(SRCDIRCH)/, $(CFILESCH))
SRCSO				= $(addprefix $(SRCDIRSO)/, $(CFILESSO))
OBJCH				= $(SRCCH:.c=.o)
OBJSO				= $(SRCSO:.c=.o)
OBJ					= $(OBJCH) $(OBJSO)
DEP					= $(OBJ:.o=.d)

INC					= inc \
					  libft/inc
LIB					= libft/libft.a

CC					= cc
CFLAGS				= -Wall -Wextra -Werror
CPPFLAGS			= $(addprefix -I,$(INC)) -MMD -MP
MAKEFLAGS			+= --no-print-directory -j

NAMECH				= checker
NAMESO				= push_swap
NAME				= $(NAMECH) $(NAMESO)

all:				$(NAME)

$(NAMECH):			$(OBJCH) $(LIB)
					$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

$(NAMESO):			$(OBJSO) $(LIB)
					$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

$(LIB):
					$(MAKE) -C $(@D)

clean:
					@for f in $(dir $(LIB)); do $(MAKE) -C $$f clean; done
					rm -f $(OBJ) $(DEP)

fclean:
					@for f in $(dir $(LIB)); do $(MAKE) -C $$f fclean; done
					rm -rf $(NAME) $(OBJ) $(DEP)

re:
					$(MAKE) fclean
					$(MAKE) all

-include $(DEP)

.PHONY: clean fclean re
