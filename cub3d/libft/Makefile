OBJS_DIR = objects

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
INCLUDE_PATH=.
CCF_INCLUDES = -I $(INCLUDE_PATH)

ORIGINAL_LIBFT_SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c\
ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c\
ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c\
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
ft_strmapi.c ft_striteri.c
#ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OTHERS_SRCS = ft_mtxiteri.c ft_mtxdup.c ft_mtxpush.c ft_mtxlen.c ft_strljoin.c ft_atol.c ft_isinteger.c

WRITE_SRCS = write/ft_putchar.c write/ft_putchar_fd.c write/ft_putendl_fd.c write/ft_putnbase_fd.c write/ft_putnbase.c write/ft_putnbr_fd.c write/ft_putstr.c write/ft_putstr_fd.c write/ft_putstrn_fd.c write/ft_putstrn.c

GET_NEXT_LINE_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

FT_PRITF_SRCS = ft_printf/ft_printf.c ft_printf/deal.c\
				ft_printf/conversions/char.c ft_printf/conversions/string.c ft_printf/conversions/pointer.c ft_printf/conversions/decimal.c ft_printf/conversions/int.c ft_printf/conversions/unsigned.c ft_printf/conversions/hexadecimal.c ft_printf/conversions/percent.c\
				ft_printf/slot/slot.c ft_printf/slot/utils.c\

FILES_SRCS = files/ft_pread_file.c files/ft_read_file_fd.c files/ft_read_file.c

LOGGER_SRCS = logger/ft_notify.c logger/ft_printf_mtx.c logger/ft_throw_error.c

MEMORY_SRCS = memory/ft_free_matrix.c memory/ft_memory_actions.c memory/ft_memory.c memory/ft_palloc.c memory/ft_salloc.c

SRCS = $(ORIGINAL_LIBFT_SRCS) $(OTHERS_SRCS) $(GET_NEXT_LINE_SRCS) $(FT_PRITF_SRCS) $(WRITE_SRCS) $(FILES_SRCS) $(LOGGER_SRCS) $(MEMORY_SRCS)
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $(OBJS)

$(OBJS_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CCF_INCLUDES) -c $< -o $@

norm:
	norminette $(SRCS)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
