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
	z = z / 10;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
	ft_pixel_put(&_data()->graphics->menu_img, *x + 300, *y + 300, WHITE);
}

void	link_dots(void)
{
	
}

void	project(void)
{
	_data()->fdf->projected_map = ft_cpy_int_tab(_data()->fdf->map, 5, 5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			iso(&_data()->fdf->p[i][j].x, &_data()->fdf->p[i][j].y, _data()->fdf->p[i][j].z);
		}
	}
	link_dots();
}