#ifndef CUB_H
# define CUB_H
#include <math.h>
# include "./MLX42/include/MLX42/MLX42.h"
# include "./get_next_line_1/get_next_line.h"
# include "./libft_1/libft.h"
# include <fcntl.h>
#include <limits.h>

// the libriry we delete
# include <stdio.h>

struct s_start;

#define RES = 4
# define TILE_SIZE 60
# define FOV_ANGLE (60 * ( M_PI / 180))
# define NUM_RAYS   1140
// #define EPSILON 0.00001
#define PLAYER_SPEED  15 
// #define move_speed  10
#define PLAYER_ROTATION_SPEED  10


typedef struct s_elements
{
	char			**element;
	int				floor[3];
	int				ceiling[3];
	mlx_texture_t	*north_t;
	mlx_image_t		*north_g;
	mlx_texture_t	*east_t;
	mlx_image_t		*east_g;
	mlx_texture_t	*south_t;
	mlx_image_t		*south_g;
	mlx_texture_t	*west_t;
	mlx_image_t		*west_g;

}					t_elements;


typedef struct s_move
{
	double 	coor_x;
	double	coor_y;
	double 	width_x;
	double 	height_y;

	double  turn_direction;
	double  walk_direction;
	double  rotation_angle;
	double  rotation_speed;
	double  move_speed;
}					t_move_player;

typedef struct	s_draw_line  
{
	double 	angle;
	double 	new_point_x;
	double 	new_point_y;

} t_draw_line;

typedef struct s_rays
{
	double  ray_angle;
	double	last_ray_angle;
	double  distance;
	double  x_inter_vertical ;
	double  y_inter_vaertical;
	double  x_inter_horizontal;
	double  y_inter_horizontal;
	int 	ray_flag;
}	t_rays;

typedef struct s_position_intersec
{
	double  x;
	double  y;
	double  distance;
	double  retur;
}	t_position_intersec;

typedef struct s_build_walls
{
	double pos_x;
	double pos_y;
	double distance;
}	build_walls_t;

typedef struct s_start
{
	mlx_t			*mlx;
	t_elements		config;
	char			**content;
	char			**map;
	char			**cpy_map;
	int				x;
	int				y;
	int				len_x;
	int				len_y;
	int				p_x;
	int				p_y;

	int 			offset;
	int 			len_map;
	char			player;
	bool			flag_up;
	bool			flag_down;
	mlx_image_t		*img;
	t_move_player	*move;
	t_draw_line     *draw;
	t_rays			*ray;
	build_walls_t	*wall;
	t_position_intersec *inter;
}					t_start;


typedef struct s_data
{
	char			*sub;
	char			*set;
	char			*trim;
}					t_data;

typedef struct s_data_2
{
	char			**split_sub;
	int				i;
	int				j;
	int				k;
	char			*native;
}					t_data_2;


typedef struct s_game
{
	char			**maap;
	int 			p_x;
	int				p_y;
	int 			w_map;
	int 			h_map;
}					t_game;


typedef struct t_var
{
	int				i;
	int				j;
	int				count;
}					t_var;
char				*get_next_line(int fd);

void				ft_validate(char *av, t_start *var);
void				fill_map(t_start *var);
void				fill_config(t_start *var);
void				ft_config_rgb(t_start *var, t_data *to, int *count);
void				ft_set_rgb(t_start *var, t_data *to, char c);
int					ft_set_element(t_start *var);

// game
void				ft_start_game(t_start *var);

// errors
void				ft_put_error(char *s, t_start *var, t_data *to);
void				ft_just_print_error(char *s);
void				ft_ini_val(int *k, int *i);
// utils
int					ft_search(char *s, char *d);

// free
void				free_double(char **array);
void				free_trim(t_data *to);
void				free_start(t_start *var);

void	ft_to_img(t_start *var);







//////////////////////////      RayCaster
void	ft_game_is_over(t_start *var);
char 	 **list_map(t_start *var );
void	print_pixel( t_start  *var);
int 	map_height(char   **map);
int 	map_width(char   **map);
void		ft_error();

void	print_pixel_player(t_start *var    );
////////////////////        MOVE PLYER
// void move_player_up(t_start *var, int dx, int dy);
// void move_player_down(t_start *var, int dx, int dy);
// void move_player_right(t_start *var, int dx, int dy);
// void move_player_left(t_start *var, int dx, int dy);
void move_player( mlx_key_data_t keydata, t_start *var);
void fix_rays(mlx_key_data_t keydata, t_start *var);


int check_map_lft_right(t_start *var , int new_position_y ,int new_position_x);
int check_player_in_map(t_start *var, int new_position_x, int new_position_y);

void       draw_line_dda(t_start *var);

///////////////    maths
double	deg_to_rad(double deg);
double	rad_to_deg(double red);

void	ft_intersection(t_start *var);
void ft_put_pixel(t_start *var, double x, double y);
int     check_is_valid(t_start *var);


bool is_looking_up(double angle);
bool  is_looking_down(double angle);
bool is_looking_right(double angle);
bool is_looking_left(double angle);	
double normalize_angle(double angle);


void ft_put_pixel_1(t_start *var, double x, double y);	
void  initialize_flags(mlx_key_data_t keydata, t_start *var);
int check_is_wall(t_start *var, double x, double y);
void ft_put_pixel_color(t_start *var, double x, double y , int color);
void    draw_floor_ceiling(t_start *var);








#endif
