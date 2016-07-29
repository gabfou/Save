#include "project.h"
#include "stdafx.h"

/*
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

# define STDIN	0
# define STDOUT	1
# define STDERR	2

# define WRITE(fd, what) (write(fd, what, sizeof(what) - 1))

# define RETURN_ERROR			-1
# define RETURN_SUCCESS			0
# define WORD_CHARS				"_-."
# define RAYTRACER				"rt"
# define ERR_SEPARATOR			": "
# define ERR_TOO_MANY_ARGS		"Too many arguments"
# define ERR_TOO_FEW_ARGS		"Too few arguments"
# define ERR_NO_DIR				"No such file or directory"
# define ERR_PERMISSION_DENIED	"Permission denied"
# define ERR_INACCESSIBLE		"File is inaccessible"
# define UNIVERSE				"I just saved the universe"
# define ERROR					"ERROR"

typedef struct s_symbol		t_symbol;
typedef struct s_obj		t_obj;
typedef struct s_token		t_token;
typedef int(*t_stream_reader)(char **, t_token *);

typedef enum				e_token_type
{
	OPENING_BRACKET,
	CLOSING_BRACKET,
	WORD,
	COLON,
	COMMA
}							t_token_type;

struct						s_token
{
	t_token_type	type;
	char			*lexeme;
	int				line;
};

struct						s_symbol
{
	t_token_type	type;
	char			c;
};

int							read_opening_bracket(char **stream, t_token *token);
int							read_closing_bracket(char **stream, t_token *token);
int							read_colon(char **stream, t_token *token);
int							read_comma(char **stream, t_token *token);
t_list						*tokenize(char *string, int line_number);
int							is_whitespace(char c);
void						ignore_whitespaces(char **stream);
void						free_token(void *p_token, size_t size);

int							terminal(t_list **tokens, t_token_type type);
t_token						*get_token(t_list **tokens);

void						next_elem(t_list **elems);
void						print_tokens(t_list *tokens);

int							parsetout(int fd);

void						fatal_error(const char *name,
	const char *error, const char *info);

int		parse_return(t_list **tokens, t_list *save)
{
	(*tokens) = save;
	return (0);
}

int		parse_properties(t_list **tokens, t_env *par)
{
	t_list	*save;

	save = *tokens;
	if (terminal(tokens, WORD) == 0)
		return (parse_return(tokens, save));
	next_elem(tokens);
	if (terminal(tokens, COLON) == 0)
		return (parse_return(tokens, save));
	next_elem(tokens);
	if (terminal(tokens, WORD) == 0)
		return (parse_return(tokens, save));
	next_elem(tokens);
	if (terminal(tokens, COMMA))
	{
		next_elem(tokens);
		parse_properties(tokens, par);
	}
	return (1);
}

int		parse_shape(t_list **tokens, t_env *par)
{
	t_list	*save;

	save = *tokens;
	if (terminal(tokens, WORD) == 0)
		return (parse_return(tokens, save));
	next_elem(tokens);
	if (terminal(tokens, OPENING_BRACKET) == 0)
		return (0);
	next_elem(tokens);
	if (parse_properties(tokens, par) == 0)
		return (0);
	if (terminal(tokens, CLOSING_BRACKET) == 0)
		return (0);
	next_elem(tokens);
	return (1);
}

int		parse_exp(t_list **tokens, t_env *par)
{
	while (parse_shape(tokens, par))
		continue;
	return (1);
}

int				tlen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char			**file_to_tab(char *name)
{
	int		fd;
	int		ret;
	char	**file;
	char	*tmp;
	char	b[1024];

	if ((fd = open(name, O_RDONLY)) == -1)
		ft_error("error");
	tmp = ft_strdup("");
	ft_bzero(b, sizeof(b));
	while ((ret = read(fd, b, sizeof(b))) > 0)
	{
		b[ret] = '\n';
		tmp = ft_strjoin(tmp, b);
		ft_bzero(b, sizeof(b));
	}
	file = ft_strsplit(tmp, '\n');
	return (file);
}*/
