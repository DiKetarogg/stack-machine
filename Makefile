#* ************************************************************************** *#
#*                                                                            *#
#*                                    :::::::         :::         :::::::     *#
#*   Makefile                       :+:    :+:       :+:         :+:    :+:   *#
#*                                 +:+      +:+     +:+         +:+           *#
#*                                +#+       +#+  +#+#+#+       +#+            *#
#*                               +#+       +#+    +#+         +#+   #+#+#+    *#
#*   Stack machine              #+#      #+#     #+#    #+    #+#     +#+     *#
#*                             ##########         ######       ########       *#
#*                                                                            *#
#* ************************************************************************** *#
#*
#* ************************************************************************** *#
#*                             Executable name                                *#
#* ************************************************************************** *#
#*
TARGET_NAME		=stack
DEBUG_TARGET_NAME	=deb_stack
#*
#* ************************************************************************** *#
#*                             Directories                                    *#
#* ************************************************************************** *#
#*
OBJS_DIR	=Objects
SRCS_DIR	=Sources
TARGET_DIR	=bin
INCLUDE_DIR	=Includes
DEBUG_DIR	=bin
#*
#* ************************************************************************** *#
#*                             Compilation variables                          *#
#* ************************************************************************** *#
#*
SRCS_EXT	=.cpp
OBJS_EXT	=.o
HEADER_EXT	=.hpp
CC		=g++-9 --std=c++17
CFLAGS		=-Wextra -Werror -Wall
DEBUG_FLAGS	=-g3
DEBUG_PROGRAM	=gdb
#*
#* ************************************************************************** *#
#*                             Do not edit below                              *#
#* ************************************************************************** *#
#*

SRCS = $(shell find $(SRCS_DIR) -type f -name *$(SRCS_EXT))
OBJS = $(patsubst $(SRCS_DIR)/%,$(OBJS_DIR)/%,$(SRCS:$(SRCS_EXT)=$(OBJS_EXT)))
DIRS = $(SRCS_DIR) $(TARGET_DIR) #$(OBJS_DIR)

INCLUDES	= $(addprefix -I,$(sort $(dir $(shell find $(SRCS_DIR) -type f -name *$(HEADER_EXT)))))\
			-I$(INCLUDE_DIR)

TARGET		= $(TARGET_DIR)/$(TARGET_NAME)

DEBUG_TARGET	= $(DEBUG_DIR)/$(DEBUG_TARGET_NAME)

DIRS = $(OBJS_DIR) $(SRCS_DIR) $(TARGET_DIR) $(INCLUDE_DIR)

all: $(TARGET)

debug: $(DEBUG_TARGET)

de: debug

drun: debug
	$(DEBUG_PROGRAM) $(DEBUG_DIR)/$(DEBUG_TARGET_NAME)

$(TARGET): $(DIRS) ${OBJS}
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)
$(DEBUG_TARGET): $(DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) $(SRCS) -o $(DEBUG_TARGET)
	
$(OBJS_DIR)/%$(OBJS_EXT): $(SRCS_DIR)/%$(SRCS_EXT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}
re: fclean all

remake: re

run: ${TARGET}
	./$(TARGET)
rerun: re run
test:
	@echo '	SRCS: $(SRCS)'
	@echo '	OBJS: $(OBJS)'
	@echo '	INCLUDES: $(INCLUDES)'
.PHONY: all clean fclean re remake debug de drun rerun run
