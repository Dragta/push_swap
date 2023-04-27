### FILES AND DIRECTORIES ###
NAME = push_swap
GC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c89 #-g3 -fsanitize=address
INCLUDES = include

DIR_PUSH_SWAP = src/
FILES_PUSH_SWAP = push_swap tools ops1 ops2 ops3 ops4 

FILES_SRC += $(addprefix $(DIR_PUSH_SWAP), $(FILES_PUSH_SWAP))

DIR_OBJ = obj/
FILES_OBJ = $(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILES_PUSH_SWAP)))


#####################
### PROGRAM RULES ###
#####################

all: $(NAME)

$(NAME): $(FILES_OBJ)
	$(GC) $(FILES_OBJ) -o $(NAME) #-fsanitize=address
#	@ar rsc $(NAME) $(FILES_OBJ)
	@echo "SUCCESSFULLY COMPILED $(NAME)"

$(DIR_OBJ)%.o: $(DIR_PUSH_SWAP)%.c | DIRECTORIES #LIB
	@$(GC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@
	@echo "COMPILED OBJECT $@"

DIRECTORIES:
	@mkdir -p $(DIR_OBJ)
	

bonus: all

###################
### CLEAN RULES ###
###################

clean:
	@rm -rf $(DIR_OBJ)
	@echo "-PUSH_SWAP- OBJECTS DELETED. CLEAN SUCCESSFUL!"

fclean: clean
	@rm -rf $(NAME)
	@echo "-PUSH_SWAP- LIBRARY DELETED. CLEAN SUCCESSFUL!"

re:	fclean all
