NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = ./include
INCLUDE_PACH = -I$(INCLUDE)
SRC_DIR	= ./src/

# Source files and object files
SRC_FILES	= philo init_table utils cleanup_table \
			routine lock_unclok
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(SRC:.c=.o)

# Main target
all: $(NAME)

# To link with the required internal Linux API:
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -pthread

# Compile object files
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_PACH)

# Clean object files
clean:
	rm -f $(OBJ)

# Clean object files and executables
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all
