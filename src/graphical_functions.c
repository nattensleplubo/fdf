#include "maker.h"

void    ft_pixel_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    //TODO research to understand this formula cf aurelienbrabant.fr
	if (x < 0 || x > WIN_HEIGHT - 1)
		return ;
	if (y < 0 || y > WIN_WIDTH- 1)
		return ;
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(int *)pixel = color;
}

void	ft_draw_line(t_img *img, int color, int x1, int y1, int x2, int y2)
{
	double	dist[2];
	double	pos[2];
	int		p;

	dist[0] = x2 - x1;
	dist[1] = y2 - y1;
	p = sqrt((dist[0] * dist[0]) + (dist[1] * dist[1]));
	dist[0] /= p;
	dist[1] /= p;
	pos[0] = x1;
	pos[1] = y1;
	while (p)
	{
		ft_pixel_put(img, pos[0], pos[1], color);
		pos[0] += dist[0];
		pos[1] += dist[1];
		--p;
	}
}
