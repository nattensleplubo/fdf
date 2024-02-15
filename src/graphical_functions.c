#include "maker.h"

double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

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
	if (x1 > WIN_HEIGHT + 140 || x2 > WIN_HEIGHT + 150)
		return ;
	if (y1 > WIN_WIDTH + 150 || y2 > WIN_WIDTH + 150)
		return ;
	if (x1 < -150 || x2 < -150)
		return ;
	if (y1 < -150 || y2 < -150)
		return ;
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
