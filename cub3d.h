#ifndef CUB3D_H
# define CUB3D_H

/*------------------------------HEADER------------------------------*/

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
#include <fcntl.h>       // open, close
#include <unistd.h>      // read, write, close
#include <stdio.h>       // printf, perror
#include <stdlib.h>      // malloc, free, exit
#include <string.h>      // strerror
#include <sys/time.h>    // gettimeofday
#include <math.h>        //gcc your_program.c -lm
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <float.h>

# include "minilibx-linux/mlx.h"

/* DELETE BEFORE SUBMISSION */
# ifdef __linux__
    # include <X11/keysym.h>
    # include <X11/X.h>
# elif __APPLE__
    # include "mac.h"
# endif


/*------------------------------MACRO------------------------------*/

// #define WINDOW_WIDTH 960
// #define WINDOW_HEIGHT 544
// # define MINIMAP_SIZE 128

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1088
# define MINIMAP_SIZE 256

#define PLAYER_COLOR 0x00FF0000
#define RAYCAST_COLOR 0x0000FF00
#define WALL_COLOR 0x00AAAAAA
#define DOOR_COLOR 0x8B4513
#define DOOR_OPEN_COLOR 0xA52A2A
#define EMPTY_COLOR 0x404040
#define WIN_COLOR 0xFFD700

# define MINIMAP_TILE 8

#define STRIP_WIDTH 2
#define CEILING_COLOR 0x444444
#define FLOOR_COLOR 0x222222

#define TILE_SIZE  32

#define PI  3.14159265359
#define P2  (PI / 2)
#define P3  (3 * P2)

#define PLAYER_SIZE  2
#define NUM_RAYS ((WINDOW_WIDTH) / STRIP_WIDTH)
#define FOV (PI / 3)
#define MOVEMENT_SPEED 50
#define ROTATION_SPEED 2
#define MAX_DELTA_TIME 0.1
#define MOUSE_SENSITIVITY 0.1

#define MAX_SPRITES 1
#define SPRITE_SIZE 10
#define SPRITE_SIZE_MAP 2
#define ENEMY_COLOR 0xFFFF00 // Yellow

/*------------------------------STRUCT------------------------------*/

typedef struct {
    int x, y;
} Point;

typedef enum	direction
{
	NOTHING,
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING
}				direction;

typedef struct	s_identifier
{
	direction	direction;
	char		*filename;			// need to be freed
}				t_id;

typedef struct  s_map
{
	char	*name;
	
	int		elements_set;
	t_id	north;
	t_id	east;
	t_id	south;
	t_id	west;
	t_id	floor;
	t_id	ceiling;

	int		content_start;
    int		height;
    int		width;
    int		max_length;
    char	**arr;

	int xpos;
	int ypos;
}				t_map;

typedef struct	cub3d
{
	t_map	map;
}				t_cub;

typedef struct s_img {
    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;


typedef struct s_play {
	float px;
	float py;
	float pa;
	float pdx;
	float pdy;
}   t_play;

typedef struct s_drawp {
	int ipx;
	int ipy;
	int rel_x;
	int rel_y;
	float offset_x;
	float offset_y;
	int draw_x;
	int draw_y;
}   t_drawp;

typedef struct s_emini {
    float ex;
    float ey;
    int enemy_tile_x;
    int enemy_tile_y;
    int rel_x;
    int rel_y;
    float offset_x;
    float offset_y;
    int draw_x;
    int draw_y;
    int radius;
    int bx;
    int by;
    int px;
    int py;
} t_emini;

typedef struct s_move {
	int move_w;
	int move_a;
	int move_s;
	int move_d;
	int move_al;
	int move_ar;
}   t_move;

typedef struct s_movestat{
	double delta_time;
	int xo;
	int yo;
	int ipx;
	int ipx_add_xo;
	int ipx_sub_xo;
	int ipy;
	int ipy_add_yo;
	int ipy_sub_yo;
} t_movestat;

typedef struct s_sprite {
	int sprite_size;
	float x;
	float y;
	float dx;
    float dy;
    float dist_sq;
    float min_dist;
    float dist;
    float overlap;
    float adjust_x;
    float adjust_y;
	float speed;
    float margin;
    float lil_margin;
    int spx;
    int spy;
    int spx_left;
    int spx_right;
    int spy_up;
    int spy_down;
	int is_unstucking;
} t_sprite;

typedef struct s_direction {
    int dx;
    int dy;
} t_direction;

typedef struct s_minimap
{
    int start_x;
    int start_y;
    int tile_size;
}   t_minimap;

typedef struct s_line {
	float px;
	float py;
	float rx;
	float ry;
	float dx;
	float dy;
	int steps;
	float x_inc;
	float y_inc;
	int px_int;
	int py_int;
} t_line;

typedef struct s_ray {
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	int side; 
	float vx;
	float vy;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	float disV;
	float disH;
	float tan;
} t_ray;

typedef struct s_edraw {
    int anim_sequence[16];
    int anim_len;
    struct timeval now;
    double elapsed;
    float sx;
    float sy;
    float sin_pa;
    float cos_pa;
    float dx;
    float dy;
    float fov_scale;
    float proj_x;
    float sprite_height;
    int sprite_size;
    int max_sprite_size;
    float lineH;
    int floorY;
    int screen_x;
    int screen_y;
    int frame;
    t_img *cur_img;
    int px;
    int ray_idx;
    int py;
    int tx;
    int ty;
    int offset;
    char *pixel;
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
    int color;
    int x;
    int y;
} t_edraw;


typedef struct s_rayhit
{
    int p_tile_x;
    int p_tile_y;
    float p_offset_x;
    float p_offset_y;
    int draw_px;
    int draw_py;
    int r_tile_x;
    int r_tile_y;
    float r_offset_x;
    float r_offset_y;
    int draw_rx;
    int draw_ry;
} t_rayhit;

typedef struct s_gif {
	t_img zero;
	t_img one;
	t_img two;
	t_img three;
	t_img four;
	t_img five;
	t_img six;
	t_img seven;
	t_img eight;
} t_gif;

typedef struct s_place {
	int count;
    int index;
    int i;
    int y;
    int x;
} t_place;

typedef struct s_bfs {
    int empty_spaces;
    int ipx;
    int ipy;
    int dirs[4][2];
    int *queue_x;
    int *queue_y;
    bool **reachable;
    int front;
    int rear;

	int **prev_y;
	int **prev_x;
} t_bfs;

typedef struct s_enemy_bfs {
    int *queue_x;
    int *queue_y;
    int front;
    int rear;

    bool **visited;
    int **prev_x;
    int **prev_y;

    int dir[4][2];

    int width;
    int height;
    int goal_x;
    int goal_y;
	int start_x;
	int start_y;

    int size;
    int x;
    int y;
    int i;
    int nx;
    int ny;
    int tpx;
    int tpy;
    int px;
    int py;
} t_enemy_bfs;


typedef struct s_var {
    void *mlx;
    void *win;
	int last_mouse_x;
	int mouse_state;
	int minimap_offset_x;
	int minimap_offset_y;
	int num_sprites;
	t_map	map;
	t_img   image;
	t_play   player;
	t_move move;
	struct timeval last_time;
	t_minimap minimap;
	t_sprite *sprites;
	float zbuffer[NUM_RAYS];
	t_gif gif;
	int current_anim_index;
	struct timeval last_anim_time;
} t_var;

/*------------------------------MAP_VALIDATION------------------------------*/

// from extract.c
int		extract_map(t_map *map);
int		check_map_name(char *file);
void    handle_error(char *err);

// from extract_elements.c
int		extract_elements(t_map *map, int fd);
int		verify_id(t_map *map, char **arr, int line);
int		verify_rgb(char *value);
t_id	*set_id(t_id *id, direction value);

// from extract_content.c
int		extract_content(t_map *map, int fd);
void	get_map_height(t_map *map, int fd);
int		fill_map_arr(t_map *map);
void	skip_to_content(t_map *map, int fd);

// from check_map_utils.c
void	find_max_row_length(t_map *map);
void	adjust_map_length(char **map_row, t_map *map);
void	replace_space(t_map *map);

// from check_map.c
void	validate_map_char(t_map *map);
void	check_surrounding(t_map *map, int y, int x);
void	check_wall(t_map *map);
int	check_map(t_map *map);
void	change_player(t_map *map);

/*------------------------------ERROR_HANDLING------------------------------*/

// from handle_error.c
void	handle_error(char *err);
int		element_err(int line);

/*------------------------------WINDOW------------------------------*/

// from window.c
int	create_visual(t_cub *cube);
int	close_window(t_var *data);
int render(t_var *data);

// from init_struct.c
void init_player(t_var *data);
void init_sprites(t_var *data);
void init_all(t_var *data, t_cub *cube);

// from window_utils.c
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
void create_image_buffer(t_var *data);

// from init_win.c
void place_winning_tiles(t_var *data);
void change_to_win(t_var *data, t_bfs *bfs, int index);

// from init_enemy.c
void load_single_gif_frame(t_var *data, t_img *img, const char *path);
void load_enemy_gifs(t_var *data);
void place_enemy(t_var *data, t_bfs *bfs);
void init_sprites(t_var *data);
void place_enemy_helper(t_var *data, t_bfs *bfs, t_place *enemy);

// from init_enemy_bfs.c
void init_dir(t_var *data, t_bfs *bfs);
void init_bfs(t_var *data, t_bfs *bfs);
void bfs_check(t_var *data, t_bfs *bfs, int nx, int ny);
void do_bfs(t_var *data, t_bfs *bfs);


/*------------------------------MINIMAP------------------------------*/

// from minimap.c
void    create_minimap(t_var *data);
void 	draw_tile(t_img *img, int x, int y, int color);
void 	draw_map(t_var *data, int x, int y, int draw_x, int draw_y);
void 	map_shift(t_var *data);
void 	clamp_map(t_var *data);

/*------------------------------PLAYER------------------------------*/

// from player.c
void draw_player(t_var *data);
void player_start(t_var *data, int y, int x);
void player_location(t_var *data, t_drawp *drawp);

/*------------------------------MOVEMENT------------------------------*/

// from movement_helper.c
void mouse_state(t_var *data);
void create_door(t_var *data);
void open_door(t_var *data);
int get_front_tile_x(t_var *data);
int get_front_tile_y(t_var *data);

// from update_movement.c
void update_movement(t_var *data);
void movement_init(t_var *data, t_movestat *movestat);
void movement_ws(t_var *data, t_movestat *movestat);
void movement_da(t_var *data, t_movestat *movestat);
void win(t_var *data);

//from movement.c
int handle_keypress(int keysym, t_var *data);
int handle_keyrelease(int keysym, t_var *data);
int handle_mouse_move(int x, int y, t_var *data);
float normalize_radians(float angle);
double get_delta_time(t_var *data);

/*------------------------------RAYCAST------------------------------*/

// from raycast.c
void draw_line(t_var *data, t_line line, int color);
void cast_rays(t_var *data, t_ray *ray);
void draw_rays(t_var *data);
void create_rayhit(t_var *data, t_ray *ray, t_rayhit *rayhit, int tile_size);

// from raycast_3d.c
void draw_3d_helper(t_var *data, t_ray *ray, int lineOff, int lineH);
void draw_3d(t_var *data, t_ray *ray);

// from raycast_helper.c
void cast_vertical (t_var* data, t_ray* ray);
void vertical_dof(t_var* data, t_ray* ray);
void cast_horizontal (t_var *data, t_ray * ray);
void horizontal_dof(t_var* data, t_ray* ray);
bool is_wall(t_map *map, int x, int y);

/*------------------------------ENEMY------------------------------*/

// from enemy_sprites.c
int is_player_caught(t_sprite *sp, t_play *player, float radius);
bool is_cell_valid(t_var *data, int x, int y);
void resolve_enemy_dist(t_var *data, t_sprite *sp, t_sprite *other);
void resolve_enemy_collisions(t_var *data, t_sprite *sp);
void move_enemy_towards_player(t_var *data, t_sprite *sp);

// from enemy_move.c
int enemy_left(t_var *data, t_sprite *sp);
int enemy_right(t_var *data, t_sprite *sp);
int enemy_up(t_var *data, t_sprite *sp);
int enemy_down(t_var *data, t_sprite *sp);

// from enemy_unstuck.c
void ebfs_five(t_direction *step,t_enemy_bfs *bfs);
t_direction find_first_step_to_player(char **map, t_enemy_bfs *bfs);
void unstuck_move(t_var *data, t_sprite *sp);

// from enemy_unstuck_helper.c
void ebfs_one(t_enemy_bfs *bfs);
void ebfs_two(t_enemy_bfs *bfs);
void ebfs_three(t_enemy_bfs *bfs);
void ebfs_four_helper(char **map,t_enemy_bfs *bfs);
void ebfs_four(char **map, t_enemy_bfs *bfs);

// from enemy_minimap.c
void draw_enemies_minimap(t_var *data);
void draw_enemies_init(t_var *data, t_emini *mini, int i);
void draw_enemies_loop(t_var *data, t_emini *mini);

// from enemy_draw.c
float calculate_distance(t_var *data, t_sprite *sp);
void sort_sprites_by_distance(t_var *data);
void init_seq(t_edraw *draw);
void init_enemy_draw(t_var *data, t_edraw *draw);
int enemy_size(t_var *data, t_edraw *draw, t_sprite *sp);

// from enemy_draw_helper.c
void select_frame(t_var *data, t_edraw *draw);
void screen_rgba(t_var *data, t_edraw *draw);
void screen_draw_helper(t_var *data, t_edraw *draw);
void screen_draw(t_var *data, t_edraw *draw);
void draw_sprites(t_var *data);




#endif