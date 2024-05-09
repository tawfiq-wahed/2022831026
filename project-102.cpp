#include <SDL2/SDL.h>
#include <iostream>

const int screenWidth = 500;
const int screenHeight = 480;
const int initialRadius = 50;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO); 

    SDL_Window *window = SDL_CreateWindow("Circle Collision",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          screenWidth, screenHeight,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(window); 
    Uint32 *pixelBuffer = (Uint32 *)surface->pixels;     

    int radius = initialRadius;
    int x = screenWidth / 2;
    int y = screenHeight / 2;

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        
        if (x - radius < 0 || x + radius > screenWidth)
        {
            radius = initialRadius; 
        }
        if (y - radius < 0 || y + radius > screenHeight)
        {
            radius = initialRadius;
        }

        
        for (int dy = -radius; dy <= radius; ++dy)
        {
            int dySquared = dy * dy;
            for (int dx = -radius; dx <= radius; ++dx)
            {
                int dxSquared = dx * dx;
                if (dxSquared + dySquared <= radius * radius)
                {
                    int pixelX = x + dx;
                    int pixelY = y + dy;
                    if (pixelX >= 0 && pixelX < screenWidth && pixelY >= 0 && pixelY < screenHeight)
                    {
                        
                        pixelBuffer[pixelY * screenWidth + pixelX] = 0xFFFFFF; 
                    }
                }
            }
        }

      
        SDL_UpdateWindowSurface(window); 
        radius++;

        
        memset(pixelBuffer, 0, screenWidth * screenHeight * sizeof(Uint32)); 
    }

    SDL_FreeSurface(surface); 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
