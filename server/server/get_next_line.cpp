static int		find_new_line(const char *str)
{
	const char	*istr;

	if (str)
	{
		istr = str;
		while (*istr)
		{
			if (*istr == '\n')
				return (istr - str);
			++istr;
		}
	}
	return (-1);
}

static void		str_append_new(char **head, char *tail, ssize_t tail_len)
{
	char		*temp;

	tail[tail_len] = '\0';
	temp = (*head ? ft_strjoin(*head, tail) : ft_strdup(tail));
	free(*head);
	*head = temp;
}

static int		str_split_new(char **head, char **left, int index)
{
	size_t		len;
	char		*temp;

	if (!*head || !**head)
		return (0);
	temp = 0;
	if (index < 0)
		*left = ft_strdup(*head);
	else
	{
		*left = ft_strsub(*head, 0, index);
		len = ft_strlen(*head + index);
		if (len)
			temp = ft_strsub(*head, index + 1, len - 1);
	}
	free(*head);
	*head = temp;
	return (1);
}

void			check_nope(char *b, int i)
{
	while (i >= 0)
	{
		if (b[i] == '\0')
			ft_error("nope.");
		i--;
	}
}

int				get_next_line(const int fd, char **line)
{
	static char	*remains = 0;
	char		buff[BUFF_SIZE + 1];
	int			i_endl;
	size_t		size_read;

	if (!line)
		return (-1);
	size_read = 1;
	while ((i_endl = find_new_line(remains)) < 0 && size_read)
	{
		if ((size_read = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		check_nope(buff, size_read - 1);
		if (size_read > 0)
			str_append_new(&remains, buff, size_read);
	}
	return (str_split_new(&remains, line, i_endl));
}