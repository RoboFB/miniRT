/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:06:31 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/04 18:19:22 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// returns (true) on success/saved line, (false) on error/parsed line
bool parse_line(t_scene *scene, const char **line_pos)
{
	static const t_parser_entry parser_entries[6] = {
		{"A", &pars_ambient_light},
		{"C", &pars_camera},
		{"L", &pars_light},
		{"sp", &pars_sphere},
		{"pl", &pars_plane},
		{"cy", &pars_cylinder}
	};

	int pos = 0;
	if (line_pos == NULL || *line_pos == NULL)
		return (false);
	pars_skip_space(line_pos);
	if (*line_pos[0] == '#' || *line_pos[0] == '\0')
	{
		return (true);
	}
	while (pos < 6)
	{
		if (ft_strncmp(*line_pos, parser_entries[pos].name, ft_strlen(parser_entries[pos].name)) == 0)
		{
			*line_pos += ft_strlen(parser_entries[pos].name);
			return (parser_entries[pos].func(scene, line_pos));
		}
		pos++;
	}
	return (false);
}


// no file:	fd:0, filename:standard input
// normal:	fd:x, filename: filepath,   
// error:	fd:-1,filename: NULL  but it exits before it returns on invalid fd
int open_correct_file(int argc, char const *argv[], char const **filename)
{
	int file_fd;

	file_fd = -1;
	if (argc == 1)
	{
		*filename = "standard input";
		file_fd = STDIN_FILENO;
		ft_printf("Reading scene from standard input. Press Ctrl+D to finish.\n");
	}
	else if (argc == 2)
	{
		*filename = argv[1];
		size_t len = ft_strlen(*filename);
		if (len < 3 || ft_strncmp(*filename + len - 3, ".rt", 4) != 0)
			msg_2_exit(*filename, "Invalid file name. '.rt' at the end is missing");
		file_fd = open(*filename, O_RDONLY);
		if (file_fd < 0)
			perror_exit(*filename);
	}
	else
	{
		*filename = NULL;
		msg_exit("Too many arguments, expected only the scene file");
	}
	return (file_fd);
}


void	pars_scene_exit(t_scene *scene, int argc, char const *argv[])
{
	int file_fd;
	char const *file_name = NULL;

	file_fd = open_correct_file(argc, argv, &file_name);

	// call all parsing line convrting fuctions dont exit becose of the open file!
	bool run = true;
	int line_count = 0;
	while (run)
	{
		line_count++;
		char *line = get_next_line(file_fd);
		if (line == NULL)
			break;
		const char *line_pos = line;
		if (!parse_line(scene, &line_pos))
		{
			ft_printf("%s:%d:%d: parsing error at: '%c' in line: \n%s", file_name, line_count, line_pos-line+1, *line_pos, line);
			run = false;
		}
		free(line);
	}
	if (file_fd >= 0)
		close(file_fd);
	if (run == false)
		program_exit(EXIT_FAILURE);

	
	



	// example_first_spheres(scene->spheres);
	// example_fov_spheres(scene->spheres);
	// example_purple_spheres(scene->spheres);

	// debug_sphere(scene->spheres.first);
	return ;
}


