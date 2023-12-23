#include "get_next_line.h"

char	*line_by_line(char *s)
{
	int		i;
	char	*str;

	if (!*s)
		return (NULL);
	str = malloc(ft_strlen(s) + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*del_line(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	str = malloc(ft_strlen(s) - i + 1);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (s[i] != '\0')
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*read_line(char *str, int fd)
{
	int		chars_read;
	char	*buffer;

	buffer = malloc((long)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	chars_read = 1;
	while (!ft_strchr(str, '\n') && chars_read != 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read < 0)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[chars_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (0);
	str = read_line(str, fd);
	if (!str)
		return (NULL);
	line = line_by_line(str);
	str = del_line(str);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("how.txt", O_RDONLY);
// 	// line = get_next_line(fd);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
