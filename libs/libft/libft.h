/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:44:33 by kmatos-s          #+#    #+#             */
/*   Updated: 2023/01/24 19:52:01 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

# define MAX_INT_LENGTH 10

/* Black, Red, Green, Yellow, Blue, Purple, Cyan, White */
# define SHELL_BK "\033[0;30m"
# define SHELL_R "\033[0;31m"
# define SHELL_G "\033[0;32m"
# define SHELL_Y "\033[0;33m"
# define SHELL_B "\033[0;34m"
# define SHELL_P "\033[0;35m"
# define SHELL_C "\033[0;36m"
# define SHELL_W "\033[0;37m"

/* Bold */
# define SHELL_BKB "\033[1;30m"
# define SHELL_RB "\033[1;31m"
# define SHELL_GB "\033[1;32m"
# define SHELL_YB "\033[1;33m"
# define SHELL_BB "\033[1;34m"
# define SHELL_PB "\033[1;35m"
# define SHELL_CB "\033[1;36m"
# define SHELL_WB "\033[1;37m"

/* Reset Color */
# define SHELL_RC "\033[0m"

/******************************************************************************\
* LIBFT																		   *
\******************************************************************************/

/**
 * @brief Checks if is alphabetic char or not
 *
 * @param c
 * @return int Non-zero integer if `c` is an alpha character, if not returns 0
 */
int				ft_isalpha(int c);

/**
 * @brief checks for a digit (0 through 9).
 *
 * @param c
 * @return int Non-zero integer if `c` is an digit character, if not returns 0
 */
int				ft_isdigit(int c);
int				ft_isinteger(char *string);

/**
 * @brief checks for an alphanumeric character;
 * 		it is equivalent to (isalpha(c) || isdigit(c)).
 *
 * @param c
 * @return int Non-zero integer if `c` is an digit or character, if not returns 0
 */
int				ft_isalnum(int c);

/**
 * @brief checks for an alphanumeric character;
 * 		it is equivalent to (isalpha(c) || isdigit(c)).
 *
 * @param c
 * @return int Non-zero integer if `c` is an digit or character, if not returns 0
 */
int				ft_isascii(int c);

/**
 * @brief checks for any printable character including space.
 *
 * @param c
 * @return int Non-zero integer if `c` is an printable character,
 * 		if not returns 0
 */
int				ft_isprint(int c);

/**
 * @brief The strlen() function calculates the length of the string pointed
 * 		to by s, excluding the terminating null byte ('\0').
 *
 * @param s String to get the length
 * @return size_t  The strlen() function returns the number
 * 				of bytes in the string pointed to by s.
 */
size_t			ft_strlen(const char *s);

/**
 * @brief fills the first n bytes of the memory area
 * 		pointed to by s with the constant byte c.
 *
 * @param s The memory area pointer. (Returned by malloc or normal arrays)
 * @param c The character to fulfill the memory
 * @param n The size in bytes of the memory area to be fulfilled
 * @return void* a pointer to the memory area s
 */
void			*ft_memset(void *s, int c, size_t n);

/**
 * @brief erases the data in the n bytes of the memory
 * 		starting at the location pointed to by s, by writing zeros (bytes
 * 		containing '\0') to that area.
 *
 * @param s The memory area pointer. (Returned by malloc or normal arrays)
 * @param n The size in bytes of the memory area to be erased
 */
void			ft_bzero(void *s, size_t n);

/**
 * @brief copies n bytes from memory area src to
 * 		memory area dest.  The memory areas must not overlap.  Use
 * 		memmove(3) if the memory areas do overlap.
 *
 * @param dest Memory area to be fulfilled
 * @param src Memory area to be copied
 * @param n Number of bytes to copy
 * @return void* Returns a pointer to dest
 */
void			*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief The memmove() function copies n bytes from memory area src to
 * 		memory area dest.
 *
 * @param dest Memory area to be fulfilled with the new data
 * @param src Memory area to be moved
 * @param n Number of bytes to copy
 * @return void* Returns a pointer to dest.
 */
void			*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief copies up to size - 1 characters from the
 *	NUL-terminated string src to dst,
 *	NUL-terminating the result.
 *
 * @param dst String to receive the copy
 * @param src String to be copied
 * @param size The size in bytes to copy
 * @return length of the src string
 */
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief appends the NUL-terminated string src to the end of dst.
 *		It will append at most size - strlen(dst) - 1 bytes,
 * 		NUL-terminating the result.
 *
 * @param dst String to receive src to your end.
 * @param src String to be appended
 * @param size The size in bytes to append
 * @return the sum of the length of dst and src
 */
size_t			ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief If c is a lowercase letter, returns its uppercase equivalent
 *
 * @param c
 * @return int
 */
int				ft_toupper(int c);

/**
 * @brief If c is a uppercase letter, returns its lowercase equivalent
 *
 * @param c
 * @return int
 */
int				ft_tolower(int c);

/**
 * @brief Returns a pointer to the first occurrence
 * 		of the character c in the string s
 *
 * @param s String to iterate
 * @param c Character to point
 * @return char*
 */
char			*ft_strchr(const char *s, int c);

/**
 * @brief Returns a pointer to the last occurrence
 * 		of the character c in the string s.
 *
 * @param s String to iterate
 * @param c Character to point
 * @return char*
 */
char			*ft_strrchr(const char *s, int c);

/**
 * @brief The  strcmp()  function compares the two strings s1 and s2.
 *     It returns an integer less than, equal to, or greater than
 * 	   zero if s1 is  found,  respectively,  to  be
 *     less than, to match, or be greater than s2.
 *
 *     The strncmp() function is similar, except it compares only the
 * 	   first (at most) n bytes of s1 and s2.
 *
 * @param s1 String 1 to be compared
 * @param s2 String 2 to be compared
 * @param n Bytes to compare
 * @return int
 */
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief The  memchr()  function  scans  the  initial n bytes of
 *		the memory area pointed to by s for the first instance of c.
 *		Both c and the bytes of the memory area pointed to by s are
 *		interpreted as unsigned char.
 *
 * @param s Memory area to be scanned
 * @param c Byte to be found
 * @param n Bytes to read
 * @return a pointer to the matching byte or NULL
 *		if the character does  not  occur
 *		in the given memory area.
 */
void			*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief compares the first n bytes (each interpreted as unsigned char) of
 *		the memory areas s1 and s2.
 *
 * @param s1 Memory area 1 to be compared
 * @param s2 Memory area 2 to be compared
 * @param n Bytes to compare
 * @return an integer less than, equal to, or greater than zero
 *		if the first n bytes of s1 is found, respectively, to be
 *		less than, to match, or be greater than the first n bytes of s2.
 *
 *		For a nonzero return value, the sign is determined by the sign of
 *		the difference between the  first  pair  of  bytes (interpreted as
 *		unsigned char) that differ in s1 and s2.
 *
 *		If n is zero, the return value is zero.
 */
int				ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief locates the first occurrence of the null-terminated string little
 *		in the string big, where not more than len characters are searched.
 *		Characters that appear after a ‘\0’ character are not searched.
 *
 *		Since the strnstr() function is a FreeBSD specific API, it should
 *		only be used when portability is not a concern.
 *
 * @param big String to find little
 * @param little String to be found
 * @param len Bytes to compare
 * @return If little is an empty string, big is returned;
 * 		if little occurs nowhere in big, NULL is returned;
 *		otherwise a pointer to the first character of the
 *		first occurrence of little is returned.
 */
char			*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief converts the initial portion of the string pointed to by nptr to int.
 * 		The behavior is the same as strtol(nptr, NULL, 10);
 *		except that atoi() does not detect errors.
 *
 * 		The atol() and atoll() functions behave the same as atoi(), except that
 * 		they convert  the
 *		initial portion of the string to their return type of long or long long.
 *
 * @param nptr String to be converted to a number
 * @return int The converted value.
 */
int				ft_atoi(const char *nptr);
long long int	ft_atol(const char *nptr);

/**
 * @brief allocates memory for an array of nmemb elements of size bytes each
 *		and returns a pointer to the allocated memory.  The memory is set to zero.
 *		If nmemb or size is 0, then calloc() returns either NULL, or  a unique
 *		pointer value that can later be successfully passed to free().
 *		If the multiplication of nmemb and size would result in integer overflow,
 *		then calloc() returns an error.  By contrast, an integer overflow
 *		would not be detected  in the following call to malloc(), with the
 *		result that an incorrectly sized block of memory would
 *		be allocated: malloc(nmemb * size);
 *
 * @param nmemb String to find little
 * @param size String to be found
 * @return Return a pointer to the allocated memory, which is suitably
 *		aligned for any built-in  type.  On error, these functions return NULL.
 *		NULL may also be returned by a successful call to calloc() with nmemb
 *		or size equal to zero.
 */
void			*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief returns a pointer to a new string which is a duplicate of the string s.
 *		Memory for the new string is obtained with malloc(3), and can be freed
 *		with free(3).
 *
 * @param s String to be duplicated
 * @return int returns a pointer to the duplicated string.
 *		It returns NULL if in‐sufficient memory was available,
 *		with errno set to indicate the cause of the error.
 */
char			*ft_strdup(const char *s);

// PART 2

/**
 * @brief Allocates (with malloc(3)) and returns a substring
		from the string ’s’.
		The substring begins at index ’start’ and is of
		maximum size ’len’.
 *
 *
 * @param s The string from which to create the substring.
 * @param start The start index of the substring in the string ’s’.
 * @param len The maximum length of the substring.
 *
 * @return char* The substring. NULL if the allocation fails.
 */
char			*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Allocates (with malloc(3)) and returns a new
		string, which is the result of the concatenation
		of ’s1’ and ’s2’.
 *
 *
 *
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return char* The new string. NULL if the allocation fails.
 */
char			*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Allocates (with malloc(3)) and returns a copy of ’s1’
 * 		with the characters specified in ’set’ removed from the
 * 		beginning and the end of the string.
 *
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return char* The trimmed string. NULL if the allocation fails.
 */
char			*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Allocates (with malloc(3)) and returns an array
 * 		of strings obtained by splitting ’s’ using the
 * 		character ’c’ as a delimiter. The array must end
 * 		with a NULL pointer.
 *
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return char** The array of new strings resulting from the split.
 * 		NULL if the allocation fails.
 */
char			**ft_split(char const *s, char c);

/**
 * @brief Allocates (with malloc(3)) and returns a string
 *		representing the integer received as an argument.
 *		Negative numbers must be handled.
 *
 * @param n The integer to convert.
 * @return char* The string representing the integer.
 *		NULL if the allocation fails.
 */
char			*ft_itoa(int n);

/**
 * @brief Applies the function ’f’ to each character of the
 * string ’s’, and passing its index as first argument
 * to create a new string (with malloc(3)) resulting
 * from successive applications of ’f’.
 *
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return char* The string created from the successive applications
 * 		of ’f’. Returns NULL if the allocation fails.

 */
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies the function ’f’ on each character of
		the string passed as argument, passing its index
		as first argument. Each character is passed by
		address to ’f’ to be modified if necessary.
 *
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 */
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief Outputs the character ’c’ to the given file descriptor.
 *
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 * @return Number of written bytes
 */
int				ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string ’s’ to the given file descriptor.
 *
 * @param s The string to output.
 * @param fd  The file descriptor on which to write.
 * @return Number of written bytes
 */
int				ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs the string ’s’ to the
 * 		given file descriptor followed by a newline.
 *
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void			ft_putendl_fd(char *s, int fd);

/**
 * @brief Outputs the integer ’n’ to the given file descriptor.
 *
 * @param n The integer to output.
 * @param fd  The file descriptor on which to write.
 */
void			ft_putnbr_fd(int n, int fd);

void			ft_mtxiteri(
					char **mtx,
					void (*f) (unsigned int, unsigned int, char *)
					);
char			**ft_mtxdup(char **mtx, size_t rows);
char			**ft_mtxpush(char **mtx, char *string);
int				ft_mtxlen(char **mtx);
char			*ft_strljoin(char const *s1, char const *s2, int bytes);

/******************************************************************************\
* GET_NEXT_LINE																   *
\******************************************************************************/

char			*gnl_strljoin(char *s1, char const *s2, int bytes);

/**
 * @brief Write a function that returns a line read from a
 *		file descriptor
 * External funcs -> read, malloc, free
 *
 * @param int The file descriptor to read from
 * @param const int buffer size to read for each iteration
 * @return Read line: correct behavior
 *      NULL: there is nothing else to read, or an error
 *      occurred
 */
char			*get_next_line(int fd, const int BUFFER_SIZE);

/******************************************************************************\
* FT_PRINTF																	   *
\******************************************************************************/

typedef struct s_slot
{
	char	*string;
	char	conversion;
	int		p_initial;
	int		p_end;
	int		length;
}	t_slot;

int				ft_printf(const char *str, ...);
int				ft_vprintf(const char *str, va_list args);
int				ft_fprintf(int fd, const char *str, ...);
int				ft_vfprintf(int fd, const char *str, va_list args);
int				deal_args(t_slot finded, va_list args, int printed, int fd);

int				ft_putchar(char c);
int				ft_putstrn(char	*str, int n);
int				ft_putstrn_fd(char *str, int n, int fd);
int				ft_putstr(char	*str);
int				ft_putnbase(unsigned long long nb, char *base);
int				ft_putnbase_fd(unsigned long long nb, char *base, int fd);

int				deal_with_c(char arg, int fd);
int				deal_with_d(int arg, int fd);
int				deal_with_i(int arg, int fd);
int				deal_with_p(long long int arg, int fd);
int				deal_with_s(char *arg, int fd);
int				deal_with_u(unsigned int arg, int fd);
int				deal_with_x(unsigned int arg, int fd);
int				deal_with_x_upper(unsigned int arg, int fd);
int				deal_with_percent(char arg, int fd);

/**
 * @brief Checks if a determined character is a printf conversion
 *
 * @param c char
 * @return int 1 or 0
 */
int				ft_isconversion(char c);

/**
 * @brief Checks if a string is made out of digits only
 *
 * @param str string
 * @return int 1 or 0
 */
int				ft_strdigit(char *str);

/**
 * @brief Returns the character `c` found position inside the string `s`
 *
 * @param s string
 * @param c char
 * @return int position or -1
 */
int				ft_strchri(const char *s, int c);

/**
 * @brief Find a slot inside a string
 *
 * @param string string
 * @param starts int where to start searching
 * @return t_slot that have the readed string, the current printf conversion,
 * 			the initial position, the final position of the slot,
 * 			and the length (including % and conversion)
 */
t_slot			get_slot(char *string, int starts);

/**
 * @brief Reset a slot
 *
 * @param item t_slot
 * @return t_slot the same slot cleared
 */
t_slot			reset_slot(t_slot *item);

/******************************************************************************\
* FILES																		   *
\******************************************************************************/

char			*ft_read_file_fd(int fd);
char			*ft_read_file(char *filename);
char			*ft_pread_file(char *filename);

/******************************************************************************\
* LOGGER																	   *
\******************************************************************************/

void			ft_notify(char	*success_message);
void			ft_throw_error(char	*error_message);
void			ft_printf_mtx(char **m);

/******************************************************************************\
* MEMORY																	   *
\******************************************************************************/

enum		e_memory_actions
{
	FREE,
	PUSH
};

void			ft_memory(enum e_memory_actions action, void *payload);
void			ft_new_memory(void *content);
void			ft_free_memory(void);
void			ft_free_matrix(char **matrix);
void			*ft_salloc(size_t size);
void			*ft_palloc(size_t size);

/******************************************************************************\
* COMING																	   *
\******************************************************************************/

#endif
