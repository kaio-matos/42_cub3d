OBJS_DIR			= objects
SRC_DIR				= src
BONUS_DIR			= bonus
LIBFT_DIR			= libs/libft
MINILIBX_DIR		= libs/minilibx-linux

CC					= cc
CCF_STRICT			= -Wall -Wextra -Werror
CCF_DEBUG			= -g3 -D VERBOSE=1
LIBFT				= $(LIBFT_DIR)/libft.a
MINILIBX			= $(MINILIBX_DIR)/libmlx.a
LIBS_TO_COMPILE		= $(LIBFT) $(MINILIBX)
LIBS				= $(LIBS_TO_COMPILE) -lm -lXext -lX11

RM					= rm -rf

ifdef VERBOSE
	CCF_STRICT += $CCF_DEBUG
endif

################################################################################
# MANDATORY
################################################################################

NAME				= cub3D
CCF_INCL_MANDATORY	= -I ./$(SRC_DIR)/includes -I $(LIBFT_DIR) -I $(MINILIBX_DIR)

C_FILES_WINDOW		= $(addprefix window/,window.c w__render.c w__draw.c)
C_FILES_MODEL		= $(addprefix model/,position/position.c)

C_FILES_MANDATORY	= main.c $(C_FILES_WINDOW) $(C_FILES_MODEL)
FILES_MANDATORY		= $(C_FILES_MANDATORY)
SRCS_MANDATORY		= $(addprefix $(SRC_DIR)/,$(FILES_MANDATORY))
OBJS_MANDATORY		= $(addprefix $(OBJS_DIR)/,$(FILES_MANDATORY:.c=.o))

all: $(NAME);


$(NAME): $(OBJS_MANDATORY) $(LIBS_TO_COMPILE)
	$(CC) $(OBJS_MANDATORY) $(LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCF_STRICT) $(CCF_INCL_MANDATORY) -c $< -o $@

debug: $(LIBS_TO_COMPILE)
	@echo "Compiling..."
	@$(CC) $(CCF_DEBUG) $(CCF_INCL_MANDATORY) $(SRCS_MANDATORY) $(LIBS) -o $(NAME)

rebuild: $(LIBS_TO_COMPILE)
	@$(CC) $(CCF_STRICT) $(CCF_INCL_MANDATORY) $(SRCS_MANDATORY) $(LIBS) -o $(NAME)

################################################################################
# LIBS
################################################################################

$(LIBFT):
	make all -C $(LIBFT_DIR)

$(MINILIBX):
	make all -C $(MINILIBX_DIR)

################################################################################
# CLEAN UP
################################################################################

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME_B)
	$(RM) $(NAME)

re:	fclean all

################################################################################
# CONFIGURATION
################################################################################

.PHONY: all bonus clean fclean re rebuild debug

################################################################################
# Colors
################################################################################

# Black, Red, Green, Yellow, Blue, Purple, Cyan, White
BK = \033[0;30m
R = \033[0;31m
G = \033[0;32m
Y = \033[0;33m
B = \033[0;34m
P = \033[0;35m
C = \033[0;36m
W = \033[0;37m
# Bold
BKB = \033[1;30m
RB = \033[1;31m
GB = \033[1;32m
YB = \033[1;33m
BB = \033[1;34m
PB = \033[1;35m
CB = \033[1;36m
WB = \033[1;37m
# Reset Color
RC = \033[0m
