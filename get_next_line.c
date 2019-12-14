//#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

size_t  ft_strlen(char *s)
{
    size_t  i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char    *ft_strdup(char *s)
{
    char    *str;
    int     i;

    i = 0;
    while (s[i])
        i++;
    if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    i = 0;
    while (s[i])
    {
        str[i] = s[i];
        i++;
    }
    str[i] = 0;
    return (str);
}

char    *ft_strchr(char *s, int c)
{
    while (*s)
    {
        if (*s != c)
            s++;
        else
            return ((char*)s);
    }
    if (c == 0)
        return ((char *)s);
    return (NULL);
}

static char *ft_allocation(char *s, unsigned int start, size_t len)
{
    char    *str;

    if (s == NULL)
        return (NULL);
    if ((unsigned int)ft_strlen(s) <= start)
        len = 0;
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    return (str);
}

char        *ft_substr(char *s, unsigned int start, size_t len)
{
    char            *str;
    unsigned int    i;
    size_t          j;

    str = ft_allocation(s, start, len);
    if (!str)
        return (NULL);
    i = 0;
    while (s[i] && i < start)
        i++;
    if (i != start)
        str[0] = 0;
    else
    {
        j = 0;
        while (s[i] && j < len)
        {
            str[j++] = s[i];
            i++;
        }
        str[j] = 0;
    }
    return (str);
}

int		find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int		copy_line(char **dest, char **src)
{
	char	*tmp;
	int		index;

	if (*src != NULL && ft_strlen(*src) == 0)
	{
		free(*src);
		return (0);
	}
	if (!ft_strchr(*src, '\n'))
	{
		*dest = *src;
		*src = NULL;
	}
	else
	{
		index = find_index(*src, '\n');
		*dest = ft_substr(*src, 0, index);
		tmp = *src;
		*src = ft_strdup(ft_strchr(*src, '\n') + 1);
		free(tmp);
		if (*src == NULL)
			return (-1);
	}
	if (*dest == NULL)
	{
		free(*dest);
		return (-1);
	}
	return (1);
}

char    *ft_strjoin(char *s1, char *s2)
{
    char    *s;
    int     i;
    int     j;

    i = ft_strlen(s1);
    j = ft_strlen(s2);
    if (!(s = (char *)malloc(sizeof(char) * (i + j + 1))))
        return (NULL);
	if (s1 != NULL)
    {
		i = 0;
    	j = 0;
    	while (s1[j])
    	{
        	s[i] = s1[j++];
        	i++;
    	}
    	j = 0;
    	while (s2[j])
    	{
        	s[i] = s2[j++];
        	i++;
    	}
    	s[i] = 0;
	}
	else
    	s = ft_strdup(s2);
	free(s1);
	free(s2);
    return (s);
}



int		get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*prev_buff;
	int			r;

	r = 1;
	prev_buff = NULL;
	if (fd == -1 || line == 0  ) // || BUFF_SIZE <= 0)
		return (-1);
	if (!prev_buff || ft_strchr(buff, '\n') == NULL)
	{
		buff = malloc(sizeof(char) * 16);
		while(buff != NULL && ft_strchr(prev_buff, '\n') == NULL && r > 0)
		{
			r = read(fd, buff, 15);
			if (r >= 0)
				buff[15] = '\0';
			else
				buff[0] = '\0';
			if (r >= 0 && !(prev_buff = ft_strjoin(prev_buff, buff)))
				return (-1);
		}
	}
	if (r < 0 || buff == NULL)
	{
		free(prev_buff);
		return (-1);
	}
	return (copy_line(line, &prev_buff));
}

int	main(void)
{
	int	fd;
	int x;
	char	*s;

	fd = open("main.c", O_RDONLY);
    if (fd == -1)
        return (1);
    x = get_next_line(fd, &s);
	printf("%d\n", x);
   // printf("%s\n", s);
	//get_next_line(fd, &s);
    //printf("%s\n", s);

    return (0);
}
