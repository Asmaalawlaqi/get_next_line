/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:23:00 by asmalawl          #+#    #+#             */
/*   Updated: 2024/01/03 15:30:48 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line_by_line(char *s)
{
	int		i;
	char	*str;

	if (!*s)
		return (NULL);
	str = malloc(ft_strlen(s) + 2); // in case of the \n and the \0
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
	if (!s[i]) //if the character is invalid after going through the string then return NULL
	{
		free(s);
		return (NULL);
	}
	str = malloc(ft_strlen(s) - i + 1); //for example: if fd has 3 lines of characters, it will skip the 1st line and copy the other 2 lines
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
	int		chars_read;  //how many characters i am going to read
	char	*buffer;             //buffer is the name of the string

	buffer = malloc((long)BUFFER_SIZE + 1); //It enters a loop that reads from the file descriptor (fd) into the buffer, and we type cast buffer_size with long because it has a higher limit
	if (!buffer)
		return (NULL);//
	chars_read = 1; //in case there is nothing to read we would always have one character to read because of "\0" null character
	while (!ft_strchr(str, '\n') && chars_read != 0) //we use strrchr to check if we have a \n in str or not and ,, (chars_read != 0)we have characters to read
	{
		chars_read = read(fd, buffer, BUFFER_SIZE); //whatever is in fd, put in buffer and the BUFFER_SIZE is how many characters there are in fd, and then it also returns how many characters we read
		if (chars_read < -1) //in case of an error in the read function, it gives us -1
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
	static char	*str; //retains its original value even after using it in functions

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647) // is less than or equal to 0, or  //error checking
	//if BUFFER_SIZE is greater than the maximum allowed value
		return (0);
	str = read_line(str, fd); //calls a function read_line with the current value of str fd. The result is then assigned to the str variable.   // copy whatever in fd to str
	if (!str)
		return (NULL);
	line = line_by_line(str);
	str = del_line(str);
	return (line);// the function returns the pointer line,
	//which should contain the next line read from the file.
}
xfcgvcbcbgss\n
vbnvnbvbvsss
bvdstfacsyta
