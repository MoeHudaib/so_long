#include "fdf.h"

int	get_height(char *file)
{
	int		fd;
	int		height = 0;
	char	ch;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read(fd, &ch, 1))
		if (ch == '\n')
			height++;
	close(fd);
	return (height);
}

int	get_width(char *file)
{
	int		fd;
	int		width = 0;
	char	ch;
	int		in_number = 0;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read(fd, &ch, 1) && ch != '\n')
	{
		if ((ch >= '0' && ch <= '9') || ch == '-')
		{
			if (!in_number)
			{
				width++;
				in_number = 1;
			}
		}
		else
			in_number = 0;
	}
	close(fd);
	return (width);
}

void	fill_matrix(int *z_line, char *line, int expected_width, int row, t_fdf *data)
{
	char	**nums = ft_split(line, ' ');
	int		i = 0;

	if (!nums)
	{
		fprintf(stderr, "[ERROR] ft_split failed at row %d\n", row);
		exit(1);
	}

	while (nums[i])
	{
		z_line[i] = atoi(nums[i]);
		if (z_line[i] < data->z_min)
			data->z_min = z_line[i];
		if (z_line[i] > data->z_max)
			data->z_max = z_line[i];
		i++;
	}

	if (i != expected_width)
	{
		fprintf(stderr, "[ERROR] Line %d has %d numbers, expected %d\n", row, i, expected_width);
		exit(1);
	}

	i = 0;
	while (nums[i])
		free(nums[i++]);
	free(nums);
}

void	read_map(char *file, t_fdf *data)
{
	int		fd;
	int		y = 0;
	char	*line;

	data->height = get_height(file);
	data->width = get_width(file);
	data->z_min = INT_MAX;
	data->z_max = INT_MIN;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}

	data->z_matrix = malloc(sizeof(int *) * data->height);
	if (!data->z_matrix)
	{
		perror("Memory allocation failed");
		exit(1);
	}

	while ((line = get_next_line(fd)) && y < data->height)
	{
		data->z_matrix[y] = malloc(sizeof(int) * data->width);
		if (!data->z_matrix[y])
		{
			perror("Memory allocation error (z_matrix row)");
			exit(1);
		}
		fill_matrix(data->z_matrix[y], line, data->width, y, data);
		free(line);
		y++;
	}
	close(fd);
	if (y != data->height)
	{
		fprintf(stderr, "[ERROR] Only read %d rows, expected %d\n", y, data->height);
		exit(1);
	}
}
