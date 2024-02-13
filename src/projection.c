#include "maker.h"

void printMatrixx(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void	iso(int *x, int *y, int z)
{
	fprintf(stderr, "%d ", z);
	int previous_x;
	int previous_y;

	*x = *x * _data()->fdf->zoom;
	*y = *y * _data()->fdf->zoom;

	previous_x = *x;
	previous_y = *y;
	// z = z / 15;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
	*x = *x + _data()->fdf->x_offset;
	*y = *y + _data()->fdf->y_offset;
}

void	link_dots(void)
{
	int i;
	int j;
	t_point **coord;

	coord = _data()->fdf->p;


	i = 0;
	while (i < _data()->fdf->rows)
	{
		j = 0;
		while (j < _data()->fdf->cols)
		{
			if (i != _data()->fdf->rows - 1)
				ft_draw_line(&_data()->graphics->menu_img, AQUA, coord[i][j].x, coord[i][j].y, coord[i + 1][j].x, coord[i + 1][j].y);
			if (j != _data()->fdf->cols - 1)
				ft_draw_line(&_data()->graphics->menu_img, AQUA, coord[i][j].x, coord[i][j].y, coord[i][j + 1].x, coord[i][j + 1].y);
			j++;
		}
		i++;
	}
}

void	project(void)
{
	_data()->fdf->projected_map = ft_cpy_int_tab(_data()->fdf->map, _data()->fdf->rows, _data()->fdf->cols);
	for (int i = 0; i < _data()->fdf->rows; i++) {
		for (int j = 0; j < _data()->fdf->cols; j++) {
			iso(&_data()->fdf->p[i][j].x, &_data()->fdf->p[i][j].y, _data()->fdf->p[i][j].z);
		}
	}
	link_dots();
}