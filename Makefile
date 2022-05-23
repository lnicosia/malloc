# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/22 09:45:49 by lnicosia          #+#    #+#              #
#    Updated: 2022/05/23 14:45:46 by lnicosia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
FULLNAME = libft_malloc_$(HOSTTYPE).so

MAKEFILE = Makefile

LIB_DIR = lib
SRC_DIR = src
SRC_SIZE = $(shell ls src | wc -l)
OBJ_DIR = obj
BIN_DIR = .
INCLUDES_DIR = includes
LIBFT_DIR = $(LIB_DIR)/libft
LIBMFT_DIR = $(LIB_DIR)/libmft
INSTALL_DIR = install
SED = sed
ROOT = sudo

#LIBS
LIBFT = $(LIBFT_DIR)/libft.a

### Linking flags ###
# Linking libgs
LDLIBS = $(LIBFT)

LDFLAGS = -L $(LIBFT_DIR)

LIB_RAW = 

SRC_RAW =	malloc.c free.c show_alloc_mem.c realloc.c utils.c \
			others.c

HEADERS =	malloc.h

#
# Creation of files path
#

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_RAW:.c=.o))

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

RESOURCES =

OPTI_FLAGS = -O3

CFLAGS =	-Wall -Wextra -Werror -Wpadded -Wconversion -I $(INCLUDES_DIR) \
	  	-I $(LIBFT_DIR)/includes -I $(BMP_PARSER_DIR)/includes \
		-I $(LIBMFT_DIR)/includes -I $(GLAD_DIR)/include \
		-g3 -fPIC\
		#$(OPTI_FLAGS) \
		
	
#
# Setting right flags and files dependencies to link external libs
# according to user's os
#

ifeq ($(OS), Windows_NT)
else
	UNAME_S = $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
		OPTI_FLAGS += -flto
		SED = gsed
    else
		CFLAGS += -Wno-misleading-indentation
		OPTI_FLAGS += -flto
    endif
endif

#
# Color declarations
#

RED := "\e[0;31m"
GREEN := "\e[0;32m"
YELLOW := "\e[0;33m"
BLUE := "\e[0;34m"
MAGENTA := "\e[0;35m"
CYAN := "\e[0;36m"
RESET :="\e[0m"

#
# Rules
#

all:
	@printf $(CYAN)"[INFO] Building libft..\n"$(RESET)
	@make --no-print-directory -C $(LIBFT_DIR)
	@printf $(CYAN)"[INFO] Building $(NAME)..\n"$(RESET)
	@make --no-print-directory $(BIN_DIR)/$(NAME)


$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(LIBMFT):
	@make --no-print-directory -C $(LIBMFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

I = 1
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@printf $(YELLOW)"[$(I)/$(SRC_SIZE)] Compiling $<\n"$(RESET)
	$(eval I=$(shell echo $$(($(I) + 1))))
	gcc -c $< -o $@ $(CFLAGS) 

$(FULLNAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@printf $(CYAN)"[INFO] Linking ${BIN_DIR}/${FULLNAME}\n"$(RESET)
	gcc -shared $(CFLAGS) -o $(FULLNAME) $(OBJ) $(LDFLAGS) $(LDLIBS)
	@printf ${GREEN}"[INFO] Compiled $(BIN_DIR)/$(FULLNAME) with success!\n"

$(NAME): $(FULLNAME)
	@rm -f $(NAME)
	@printf ${RESET}
	ln -sv $(FULLNAME) $(NAME)

clean:
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@printf ${CYAN}"[INFO] Removing objs\n"${RESET}
	rm -rf $(OBJ_DIR)

fclean:
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	@printf ${CYAN}"[INFO] Removing objs\n"${RESET}
	rm -rf $(OBJ_DIR)
	@printf ${CYAN}"[INFO] Removing $(BIN_DIR)/$(NAME)\n"$(RESET)
	rm -rf $(BIN_DIR)/$(NAME)

re: fclean all

.PHONY: fclean all clean libft
