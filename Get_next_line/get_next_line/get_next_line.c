#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

size_t ft_strlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 && !s2)
		return (0);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	str[ft_strlen(s1) + i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(const char *s, char pc)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (1)
	{
		if (s[i] == pc)
			return ((char *)&s[i]);
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

char	*copy_to_xyata(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	s = malloc (ft_strlen (str) - i + 1);
	while (str[i] != '\0')
	{
		s[j] = str[i];
		i++;
		j++;
	}
	s[j] = '\0';
	free(str);
	return (s);
}

char	*cut(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	s = malloc (i + 1);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_read(char *all, int fd)
{
	int		n;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	n = 1;
	while (n > 0 && !(ft_strchr(all, '\n')))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n < 0)
		{
			free(buff);
			free(all);
			all = NULL;
			return (all);
		}
		buff[n] = '\0';
		all = ft_strjoin(all, buff);
	}
	free(buff);
	return (all);
}

char	*get_next_line(int fd)
{
	static char	*xyata; 
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	xyata = ft_read(xyata, fd);
	if (!xyata)
		return (0);
	if (xyata[0] == '\0')
	{
		free(xyata);
		xyata = NULL;
		return (xyata);
	}
	line = cut(xyata);
	xyata = copy_to_xyata(xyata);
	return (line);
}

