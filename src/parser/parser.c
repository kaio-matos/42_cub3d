#include "cub.h"

static char *get_variable(char *code, char *content);

t_parse_cub_result	parse_cub_file(char *content)
{
	t_parse_cub_result	res;

	res.textures.NO = get_variable("NO ", content);
	content += ft_strchri(content, '\n') + 1;
	res.textures.SO = get_variable("SO ", content);
	content += ft_strchri(content, '\n') + 1;
	res.textures.WE = get_variable("WE ", content);
	content += ft_strchri(content, '\n') + 1;
	res.textures.EA = get_variable("EA ", content);
	content += ft_strchri(content, '\n') + 1;
	content += ft_strchri(content, '\n') + 1;
	res.colors.floor = get_variable("F ", content);
	content += ft_strchri(content, '\n') + 1;
	res.colors.celing = get_variable("C ", content);
	content += ft_strchri(content, '\n') + 1;
	while (*content && (*content == '\n'))
		content++;
	res.map = ft_strdup(content);
	if (res.map)
		res.map[ft_strlen(res.map) - 1] = '\0';
	return (res);
}

static char *get_variable(char *code, char *content)
{
	char	*result;
	char	*line;
	int		line_length;

	line_length = 0;
	line = ft_strnstr(content, code, ft_strlen(content));
	if (!line)
		return (NULL);
	while (line[line_length] && line[line_length] != '\n')
		line_length++;
	result = ft_substr(line, ft_strlen(code), line_length - ft_strlen(code));
	return (result);
}
