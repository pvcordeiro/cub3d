# Cub3D 🎮

An advanced 3D raycasting game engine featuring sophisticated rendering, multiplayer split-screen gameplay, and intelligent AI systems. This project implements a complete Wolfenstein 3D-style engine with modern enhancements, showcasing complex computer graphics algorithms and real-time game development techniques.

![ScreenRecording2025-06-28at02 09 27-ezgif com-optimize](https://github.com/user-attachments/assets/88c514d8-0dd8-4d95-9930-51d3a666a5f2)

## 🎯 Project Overview

This is a highly technical implementation of a 3D raycasting engine that demonstrates:
- **Advanced DDA Raycasting Algorithm** with fisheye correction
- **Multi-threaded Rendering Pipeline** with 4 parallel camera threads
- **Split-screen Multiplayer** supporting up to 4 simultaneous players
- **Intelligent Enemy AI** with line-of-sight detection and spatial audio
- **Complex Map System** with animated sprites and interactive elements
- **Real-time Audio Engine** with SDL2 integration

## ✨ Key Features

- **🎮 Split-Screen Multiplayer**: Dynamic viewport management for 1-4 players
- **� Advanced AI Systems**: Intelligent enemies with proximity-based behavior and spatial audio detection
- **🎨 Sophisticated Rendering**: Multi-threaded raycasting with fisheye correction and depth sorting
- **🗺️ Complex Map Support**: Animated sprites, interactive elements, and extensive configuration options
- **🎵 Spatial Audio**: 3D positional sound with SDL2 integration
- **🎯 Precise Controls**: Full gamepad support with pressure-sensitive triggers and deadzone compensation
- **⚡ Performance Optimized**: Multi-threaded rendering pipeline and efficient memory management

![starting](https://github.com/user-attachments/assets/a98e8efd-9139-4b9b-80be-b759be669e0b)

## 🚀 Getting Started

### Prerequisites
- **MinilibX**: Graphics library and window management
- **SDL2**: Audio processing and gamepad support
- **X11**: Display server (Linux)
- **pthread**: Multi-threading support
- **libm**: Mathematical functions

### Build & Run
```bash
# Clone the repository
git clone <repository-url>
cd cub3d

# Compile the engine
make

# Launch the hub world
make run

# Alternative: Direct map loading
./cub3d maps/42lisboa.cub
./cub3d maps/e1m1.cub
./cub3d maps/e1m2.cub
```

## 🎮 Controls

### Keyboard (Primary Player)
- `W/S` - Forward/Backward movement
- `A/D` - Strafe left/right  
- `←/→` - Camera rotation
- `E` - Interact with objects
- `Space` - Use/Attack with equipped item
- `Q` - Drop current item
- `R` - Cycle through inventory
- `Shift` - Sprint mode

### Multiplayer Setup
- **Split-Screen**: Press `P` to activate additional players (up to 4), press `O` to remove players
- **Controller Setup**: Connect gamepads and press `F7` to detect
- **Keyboard Sharing**: Use `K` to toggle keyboard-only mode for Player 1

### Gamepad Support (Multiplayer)
- **Left Stick** - Movement (8-directional with pressure sensitivity)
- **Right Stick** - Camera look (with deadzone compensation)
- **L2/R2 Triggers** - Item use/drop (pressure sensitive)
- **Face Buttons** - Action/Sprint/Menu
- **Shoulder Buttons** - Inventory management

### Debug & System Controls
- `F1` - Toggle fullscreen
- `F2` - Stats HUD toggle  
- `F3` - Debug overlay (FPS, coordinates, entity count)
- `F4` - Minimap toggle
- `F5` - Interaction prompts toggle
- `F6` - Complete HUD toggle
- `F7` - Reload gamepad controllers
- `H` - Go back to hub map
- `P/O` - Add/Remove multiplayer participants
- `K` - Toggle keyboard-only mode for Player 1
- `M` - Toggle mouse capture
- `+/-/0` - Minimap zoom controls

## 🗺️ Map System

### Advanced .cub Format
The enhanced map format supports extensive configuration:

### Map Elements
- `1/g/M` - Various wall types with different textures
- `0` - Empty traversable space
- `N/S/E/W` - Player spawn points with orientation
- Complex character identifiers for NPCs with specific behaviors

```cub
# Sprite Animation Configuration
WALKING_8_SPRITE assets/textures/billboards/afonsomaria/front1.xpm:still-front.xpm:front2.xpm
WALKING_8_SPRITE_UPDATE_DELAY 0.2
WALKING_8_SPRITE_LOOP TRUE

# AI Behavior Parameters  
OPTIMAL_PROXIMITY 2.5
FRIENDLY_FIRE FALSE

# Environmental Settings
MINIMAP_HUD TRUE
BACKGROUND_SPRITE assets/42lisboa/424242.xpm
```

### Configuration Options:
- **BACKGROUND_SPRITE** - Background texture
- **STILL_X_SPRITE** - Static sprite textures
- **WALKING_X_SPRITE** - Animated sprite sequences
- **SPRITE_UPDATE_DELAY** - Animation timing
- **SPRITE_LOOP** - Animation loop settings
- **ETC**

### 🎨 Custom Maps

Create your own maps following the `.cub` format:
- Configure textures and sprites at the top
- Design your map layout using the supported characters
- Place the players starting position with N, S, E, or W

## 📊 Technical Specifications

- **Resolution**: 1024x768 (configurable)
- **Ray Count**: Dynamic per viewport (typically 512-1024 rays)
- **Thread Count**: 4 parallel rendering threads
- **Max Players**: 4 simultaneous with split-screen
- **AI Entities**: Unlimited with LOD optimization
- **Audio Channels**: Multi-threaded SDL2 processing
- **Map Size**: Virtually unlimited (tested up to 500x500)

## 🎯 Advanced Performance Features

- **Fisheye Correction**: Mathematical compensation for perspective distortion
- **Texture Mapping**: Precise UV coordinate calculation for wall textures  
- **Z-buffering**: Proper depth sorting for sprites and transparent surfaces
- **Spatial Audio**: 3D positional sound with distance attenuation
- **Memory Optimization**: Efficient sprite caching and texture management
- **Delta Time Processing**: Frame-rate independent movement and animation

![ending](https://github.com/user-attachments/assets/02e60445-97e6-44a4-9ce7-ceaffe376755)

## 🧮 Technical Implementation Details

### Raycasting Engine
The core rendering system implements a sophisticated **Digital Differential Analyzer (DDA)** algorithm:

```c
// Complete DDA raycast implementation with step calculation
static void	init_ray(t_dda_raycast_data *ray, t_dda_raycast_config ddarc)
{
	ray->rdir.x = ft_cos_degrees(ddarc.start_pos.yaw);
	ray->rdir.y = ft_sin_degrees(ddarc.start_pos.yaw);
	ray->pos.x = (int)ddarc.start_pos.x;
	ray->pos.y = (int)ddarc.start_pos.y;
	ray->deltadist.x = ft_ternary_double(fabs(ray->rdir.x) < FT_EPSILON,
			FT_MAX_RAY_LENGTH, fabs(1.0 / ray->rdir.x));
	ray->deltadist.y = ft_ternary_double(fabs(ray->rdir.y) < FT_EPSILON,
			FT_MAX_RAY_LENGTH, fabs(1.0 / ray->rdir.y));
	ray->step.x = ft_ternary_double(ray->rdir.x < 0, -1, 1);
	ray->step.y = ft_ternary_double(ray->rdir.y < 0, -1, 1);
}

// DDA algorithm main loop
static void	*perform_dda_algorithm(t_dda_raycast_data *ray)
{
	void	*hit;

	while (true)
	{
		ray->side = ray->side_dist.x >= ray->side_dist.y;
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->deltadist.x;
			ray->pos.x += ray->step.x;
		}
		else
		{
			ray->side_dist.y += ray->deltadist.y;
			ray->pos.y += ray->step.y;
		}
		if ((int)ray->pos.x < 0 || (int)ray->pos.x >= ray->objs_size.width
			|| (int)ray->pos.y < 0 || (int)ray->pos.y >= ray->objs_size.height)
			continue ;
		hit = ray->objs[(int)ray->pos.y][(int)ray->pos.x];
		if (hit && hit != ray->ignored_obj)
			return (hit);
	}
}

// Fisheye correction in wall rendering
ray_size.height = canvas->size.height / (fmax(ray.distance, 0.1)
		* ft_cos_degrees((ray.yaw - camera->character->billboard.entity.coords.yaw)));
```

### Split-Screen Multiplayer System
Dynamic viewport management automatically adjusts screen real estate based on active players:

```c
// Actual split-screen rendering logic from render1.c
static t_player_canvas_data	get_player_canvas_data(t_game *game, t_size cs,
	int player_index)
{
	int	i;

	i = -1;
	while (++i < PLAYER_MAX)
		if (!game->players[i] || !((t_entity *)game->players[i])->active)
			break ;
	if (player_index >= i)
		return ((t_player_canvas_data){{cs.width / 2, cs.height / 2},
			{0, cs.height / 2, 0}});
	if (i == 1)  // Single player - full screen
		return ((t_player_canvas_data){cs, {0, 0, 0}});
	if (i == 2)  // Two players - horizontal split
		return ((t_player_canvas_data){{cs.width / 2, cs.height / 2},
			{player_index * (cs.width / 2), (cs.height / 2) / 2, 0}});
	if (i == 3)  // Three players - complex layout
	{
		if (player_index == 0 || player_index == 1)
			return ((t_player_canvas_data){{cs.width / 2, cs.height / 2},
				{player_index * cs.width / 2, 0, 0}});
		return ((t_player_canvas_data){{cs.width / 2, cs.height / 2},
			{(cs.width / 2) / 2, cs.height / 2, 0}});
	}
	return (get_player_canvas_data_2(cs, player_index));  // Four players - quad split
}
```

### Advanced AI System
Intelligent enemy behavior with sophisticated targeting and movement algorithms:

```c
// Enemy movement with proximity-based behavior from enemy1.c
void	update_movement(t_entity *entity, t_entity *target_entity)
{
	double	dist;

	dist = ft_distance(entity->coords, target_entity->coords);
	if (dist > entity->controller.optimal_proximity + 1.5)
	{
		entity->controller.sprinting = true;
		entity->controller.walking_forward = true;
	}
	else if (dist < entity->controller.optimal_proximity - 1.5)
		entity->controller.walking_backward = true;
	if (ft_get_time() - entity->controller.last_strafe > STRAFE_INTERVAL)
	{
		entity->controller.last_strafe = ft_get_time();
		if (rand() % 2)
			entity->controller.walking_left = true;
		else
			entity->controller.walking_right = true;
	}
}

// Spatial audio detection system from enemy2.c
void	hearment(t_game *game, t_character *character)
{
	t_player	*player;
	t_item		*item;
	double		dist;
	int			i;

	i = -1;
	while (game->billboards[++i])
	{
		if (!game->billboards[i] || game->billboards[i]->type != ENTITY_PLAYER)
			continue ;
		player = (t_player *)game->billboards[i];
		item = player->character.inventory[player->character.inventory_index];
		dist = ft_distance(character->billboard.entity.coords,
				game->billboards[i]->coords);
		if (!(game->billboards[i]->controller.sprinting && dist < SPRINT_HEARING_RANGE)
			&& !(item && item->user && dist < SHOT_HEARING_RANGE))
			continue ;
		do_has_heard(game, character, player);
		return ;
	}
}
```

### Multi-threaded Rendering Pipeline
```c
// Actual parallel wall rendering implementation from render.c
void	render_walls(t_game *game, t_ftm_image *canvas, t_camera *camera)
{
	t_thread_render_rays_data			trrd[CAMERA_THREADS];
	unsigned int						i;
	unsigned int						index_scaler;

	i = -1;
	index_scaler = (camera->rays / CAMERA_THREADS);
	while (++i < CAMERA_THREADS)
	{
		trrd[i].canvas = canvas;
		trrd[i].camera = camera;
		trrd[i].game = game;
		trrd[i].start = index_scaler * i;
		trrd[i].end = index_scaler * (i + 1);
		game->camera_threads[i]->routine = thread_render_rays;
		game->camera_threads[i]->data = &trrd[i];
		ftt_thread_run(game->camera_threads[i]);
	}
	i = -1;
	while (++i < CAMERA_THREADS)
		ftt_thread_wait(game->camera_threads[i]);
}

// Thread configuration
#define CAMERA_THREADS 4
```

### Billboard Rendering with Depth Sorting
```c
// Advanced sprite rendering with wall occlusion detection from render1.c
static bool	is_behind_wall(int i, int ray_index,
	t_render_billboard_slices_config rbsc)
{
	double			offset;
	double			world_x;
	double			world_y;
	double			dist;

	if (ray_index >= rbsc.camera->rays || ray_index < 0)
		return (false);
	offset = (i - rbsc.new_size.width / 2.0) / rbsc.new_size.width;
	world_x = rbsc.bill_coords.x + offset
		* cos(ft_radians(rbsc.bill_coords.yaw + 90));
	world_y = rbsc.bill_coords.y + offset
		* sin(ft_radians(rbsc.bill_coords.yaw + 90));
	dist = ft_distance(rbsc.camera->character->billboard.entity.coords,
			(t_coords){world_x, world_y, 0});
	return (dist >= rbsc.camera->ray_distances[ray_index]);
}

// Fisheye correction for billboard scaling from render0.c
static t_size	get_size(t_get_size_config gsc)
{
	double		distance;
	double		fov_factor;
	double		fix_fisheye;

	distance = ft_distance(gsc.camera->character->billboard.entity.coords,
			gsc.bill_coords);
	fix_fisheye = distance * ft_cos_degrees(gsc.relative_angle);
	fov = gsc.camera->fov;
	if (!fov)
		fov = 1.0;
	fov_factor = 73.5 / fov;
	return ((t_size){(gsc.bill_image_size.width / distance)
		* (gsc.canvas_size.height / 125) * fov_factor,
		(gsc.bill_image_size.height / fix_fisheye)
		* (gsc.canvas_size.height / 125)});
}
```

### Intelligent Enemy Behavior
```c
// AI movement with optimal proximity calculations from enemy1.c
void	update_movement(t_entity *entity, t_entity *target_entity)
{
	double	dist;

	dist = ft_distance(entity->coords, target_entity->coords);
	if (dist > entity->controller.optimal_proximity + 1.5)
	{
		entity->controller.sprinting = true;
		entity->controller.walking_forward = true;
	}
	else if (dist < entity->controller.optimal_proximity - 1.5)
		entity->controller.walking_backward = true;
	if (ft_get_time() - entity->controller.last_strafe > STRAFE_INTERVAL)
	{
		entity->controller.last_strafe = ft_get_time();
		if (rand() % 2)
			entity->controller.walking_left = true;
		else
			entity->controller.walking_right = true;
	}
}
```

## � Project Structure

```
cub3d/
├── src/
│   ├── main.c                 # Entry point and initialization
│   ├── ft_audio/              # Audio system implementation
│   ├── ft_mlx_utils/          # Graphics utilities and controller support
│   ├── ft_utils/              # Core utilities (DDA, math, data structures)
│   └── utils/
│       ├── entities/          # Game entity system (players, AI, items)
│       ├── game/              # Game state management
│       ├── loop/              # Main game loop and input handling
│       └── render/            # Rendering pipeline (walls, sprites, HUD)
├── headers/                   # Header files
├── maps/                      # Game maps (.cub format)
├── assets/                    # Textures, sounds, and fonts
└── Makefile                   # Build configuration
```

---

### 🚀 Enjoy!

Use the controls listed above to navigate the 3D world, explore different areas, and experience the immersive raycasting engine.

## ⚖️ License

This project is developed as part of the 42 School curriculum - a challenging implementation showcasing advanced computer graphics, real-time systems, and game engine architecture.
