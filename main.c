#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_YELLOW 0xFF9F00
#define COLOR_BLUE 0x309898
#define COLOR_BROWN 0xBB3E00
#define RAYS_NUMBER 500

struct Circle 
{
  double x;
  double y;
  double radius;
};

struct Ray
{
  double startX, startY;
  double angle;
  double endX, endY;
};


void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color)
{
  double radiusSquared = pow(circle.radius, 2);
  for (double x=circle.x - circle.radius; x <= circle.x + circle.radius; x++)
  {
    for (double y=circle.y - circle.radius; y <= circle.y + circle.radius; y++)
    {
      double distanceFromCenterSquared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
      if (distanceFromCenterSquared < radiusSquared)
      {
        SDL_Rect pixel = (SDL_Rect) {x, y, 1, 1};
        SDL_FillRect(surface, &pixel, color);
      }
    }
  }
}

void GenerateRays(struct Circle circle, struct Ray rays[RAYS_NUMBER])
{
  for (int i = 0; i < RAYS_NUMBER; i++)
  {
    double angle = ((double) i / RAYS_NUMBER) * 2 * M_PI;
    struct Ray ray = {circle.x, circle.y, angle};
    rays[i] = ray;
  }
}

void FillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 color, struct Circle object)
{
  double radiusSquared = pow(object.radius, 2);

  for(int i = 0; i < RAYS_NUMBER; i++)
  {
    struct Ray ray = rays[i];

    int endOfScreen = 0;
    int objectHit = 0;
    double drawX = ray.startX;
    double drawY = ray.startY;

    double step = 1;
    while(!endOfScreen && !objectHit)
    {
      drawX += step * cos(ray.angle);
      drawY += step * sin(ray.angle);

      SDL_Rect pixel = (SDL_Rect) {drawX, drawY, 1, 1};
      SDL_FillRect(surface, &pixel, color);
    
      if (drawX < 0 || drawX > WIDTH)
        endOfScreen = 1;
      if (drawY < 0 || drawY > HEIGHT)
        endOfScreen = 1;

      double distanceFromCenterSquared = pow(drawX - object.x, 2) + pow(drawY - object.y, 2);
      if (distanceFromCenterSquared < radiusSquared)
      {
        break;
      }
    }
  }
}

int main()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("RayTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  
  SDL_Surface* surface = SDL_GetWindowSurface(window);

  SDL_Rect rect = (SDL_Rect) {200, 200, 200, 200};

  struct Circle circle = {200, 200, 50};
  struct Circle shadowCircle = {650, 300, 140};
  SDL_Rect eraseRect = (SDL_Rect) {0, 0, WIDTH, HEIGHT}; // Permet de tout supprimer sur la fenetre.

  struct Ray rays[RAYS_NUMBER];
  GenerateRays(circle, rays);

  SDL_Event event;

  int running = 1;
  while (running)
  {
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = 0;
      }
      if (event.type == SDL_MOUSEMOTION && event.motion.state != 0)
      {
        circle.x = event.motion.x;
        circle.y = event.motion.y;
        GenerateRays(circle, rays);
      }
    }

    SDL_FillRect(surface, &eraseRect, COLOR_BLUE);
  	FillCircle(surface, circle, COLOR_YELLOW);
  	FillCircle(surface, shadowCircle, COLOR_BROWN);
    FillRays(surface, rays, COLOR_YELLOW, shadowCircle);

  
  	SDL_UpdateWindowSurface(window);
	  SDL_Delay(10);
  }
  return 0;
}
