/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:06:31 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static const t_parser_entry	g_entries[6] = {
{"A", &pars_ambient_light},
{"C", &pars_camera},
{"L", &pars_light},
{"sp", &pars_sphere},
{"pl", &pars_plane},
{"cy", &pars_cylinder}
};

/* Dispatches one line to the matching parser entry; false on unknown token. */
bool	parse_line(t_scene *scene, const char **line_pos)
{
	int	pos;

	if (line_pos == NULL || *line_pos == NULL)
		return (false);
	pars_skip_space(line_pos);
	if (*line_pos[0] == '#' || *line_pos[0] == '\0')
		return (true);
	pos = 0;
	while (pos < 6)
	{
		if (ft_strncmp(*line_pos, g_entries[pos].name,
				ft_strlen(g_entries[pos].name)) == 0)
		{
			*line_pos += ft_strlen(g_entries[pos].name);
			return (g_entries[pos].func(scene, line_pos));
		}
		pos++;
	}
	return (false);
}

/* Opens the .rt file from argv[1]; exits on invalid extension or failure. */
static int	open_file_from_arg(char const *argv[], char const **filename)
{
	size_t	len;
	int		fd;

	*filename = argv[1];
	len = ft_strlen(*filename);
	if (len < 3 || ft_strncmp(*filename + len - 3, ".rt", 4) != 0)
		msg_2_exit(*filename, "Invalid file: '.rt' extension required");
	fd = open(*filename, O_RDONLY);
	if (fd < 0)
		perror_exit(*filename);
	return (fd);
}

/* Returns the fd of the scene file (argv[1]) or stdin if no argument. */
int	open_correct_file(int argc, char const *argv[], char const **filename)
{
	if (argc == 1)
	{
		*filename = "standard input";
		ft_printf("Reading from standard input. Press Ctrl+D to finish.\n");
		return (STDIN_FILENO);
	}
	if (argc == 2)
		return (open_file_from_arg(argv, filename));
	*filename = NULL;
	msg_exit("Too many arguments, expected only the scene file");
	return (-1);
}

/* Reads and parses all lines from the fd; false on first parse error. */
static bool	parse_all_lines(t_scene *scene, int fd, const char *filename)
{
	int			line_count;
	char		*line;
	const char	*line_pos;

	line_count = 0;
	while (true)
	{
		line_count++;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line_pos = line;
		if (!parse_line(scene, &line_pos))
		{
			ft_printf("%s:%d:%d: parsing error at: '%c' in:\n%s",
				filename, line_count, line_pos - line + 1, *line_pos, line);
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}

/* Opens the scene file, parses all lines, and exits on any error. */
void	pars_scene_exit(t_scene *scene, int argc, char const *argv[])
{
	int			file_fd;
	char const	*file_name;

	file_name = NULL;
	file_fd = open_correct_file(argc, argv, &file_name);
	if (!parse_all_lines(scene, file_fd, file_name))
	{
		if (file_fd >= 0)
			close(file_fd);
		program_exit(EXIT_FAILURE);
	}
	if (file_fd >= 0)
		close(file_fd);
}
