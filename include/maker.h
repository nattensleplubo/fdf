#ifndef MAKER_H

# define MAKER_H

//! DEFINES
# define MENU_WIDTH 500
# define MENU_HEIGHT 500

# define TILE_SIZE 30

# define KEY_ESC 65307
# define KEY_Q 113

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

# define RED 0xFF0000
# define LGREY 0x808080
# define GREY 0x505050
# define BLACK 0x1000000
# define WHITE 0xFFFFFF
# define LIME 0x00FF00 
# define GREEN 0x008000 
# define PURPLE 0x800080 
# define TEAL 0x008080 
# define BLUE 0x0000FF 
# define AQUA 0x00FFFF
# define PINK 0xFFC0CB

# define SOL_1 0xF89F5B
# define XMUR_1 0xE53F71
# define YMUR_1 0x9C3587
# define PLA_1 0x653780

# define SOL_2 0x3F1651
# define XMUR_2 0x3F1651
# define YMUR_2 0x3F1651
# define PLA_2 0x3F1651

//!LIBRARIES
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include "libft.h"


//! STRUCTS
typedef struct	s_data
{
	char	*map_name;
	int		fd;
	
	char			**map;
	int				map_size;
	int				curs_coord[2];
	struct s_mlx	*graphics;
	
	int				map_created;
}	t_data;

typedef struct	s_img
{
	void	*image;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*editor_ptr;
	void	*menu_ptr;
	void	*window_ptr;
	t_img	menu_img;
	t_img	editor_img;
}	t_mlx;

//! PROTOS
t_data	*_data(void);
int		print_menu(int keycode);
void     ft_put_rectangle(t_img *img, int x0, int y0, int x1, int y1, int color);
int		update_window(void);
void	render_background(t_img *img, int color);
int		exit_game();
int		editor_key(int keycode);

#endif
