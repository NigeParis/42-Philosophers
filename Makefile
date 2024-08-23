###############################################################################
## ARGUMENTS

NAME= philo
CFLAGS= -Wall -Wextra -Werror -g3
CC=gcc

###############################################################################
## SOURCES 

SRC_DIR=src/
OBJ_DIR=build/

SRC= main.c 

SRCS=$(addprefix $(SRC_DIR), $(SRC))
OBJ=$(SRC:.c=.o)
OBJS=$(addprefix $(OBJ_DIR), $(OBJ))

INCLUDE= -I ./include/

###############################################################################
## RULES

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Creating FILE .......\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "COMPILE all c files to .o FILES .......\n"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean 	
	@echo "FCLEAN all .o et .a files .......\n"
	@rm -f $(NAME)

re: fclean all
	@echo "All erased and re-compiled .......\n"

.PHONY: all clean fclean re
