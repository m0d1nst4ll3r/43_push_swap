# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 10:29:07 by rapohlen          #+#    #+#              #
#    Updated: 2025/12/19 15:04:13 by rapohlen         ###   ########.fr        #
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

CFILESSO			= 

SRCDIRCH			= src/checker
SRCDIRSO			= src/solver
BUILDDIR			= .build

SRCCH				= $(addprefix $(SRCDIRCH)/, $(CFILESCH))
SRCSO				= $(addprefix $(SRCDIRSO)/, $(CFILESSO))
OBJCH				= $(SRCCH:$(SRCDIRCH)/%.c=$(BUILDDIR)/%.o)
OBJSO				= $(SRCSO:$(SRCDIRSO)/%.c=$(BUILDDIR)/%.o)
OBJ					= $(OBJCH) $(OBJSO)
DEP					= $(OBJ:.o=.d)

INC					= inc \
					  libft/inc
LIB					= libft/libft.a

CC					= cc
CFLAGS				= -Wall -Wextra -Werror -g
CPPFLAGS			= $(addprefix -I,$(INC)) -MMD -MP
MAKEFLAGS			+= --no-print-directory -j

NAMECH				= checker
#NAMESO				= push_swap
NAME				= $(NAMECH) $(NAMESO)

all:				$(NAME)

$(NAMECH):			$(OBJCH) $(LIB)
					$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

$(NAMESO):			$(OBJSO) $(LIB)
					$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

$(LIB):
					$(MAKE) -C $(@D)

$(BUILDDIR)/%.o:	$(SRCDIRCH)/%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
					@for f in $(dir $(LIB)); do $(MAKE) -C $$f clean; done
					rm -rf $(BUILDDIR)

fclean:
					@for f in $(dir $(LIB)); do $(MAKE) -C $$f fclean; done
					rm -rf $(NAME) $(BUILDDIR)

re:
					$(MAKE) fclean
					$(MAKE) all

-include $(DEP)

.PHONY: clean fclean re
