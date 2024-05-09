#include <SDL2/SDL.h>
#include <cmath> // for std::sqrt

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int CIRCLE_RADIUS = 300;
const int MOVE_SPEED = 500;

// Function to check collision between two circles
bool isCollision(const SDL_Rect &circle1, const SDL_Rect &circle2)
{
    int centerX1 = circle1.x + circle1.w / 2;
    int centerY1 = circle1.y + circle1.h / 2;
    int centerX2 = circle2.x + circle2.w / 2;
    int centerY2 = circle2.y + circle2.h / 2;

    double distance = std::sqrt(std::pow(centerX2 - centerX1, 2) + std::pow(centerY2 - centerY1, 2));
    return distance <= CIRCLE_RADIUS * 2; // Check if distance is less than or equal to combined radii
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Circle Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Create circles
    SDL_Rect movingCircle = {0, SCREEN_HEIGHT - CIRCLE_RADIUS * 2, CIRCLE_RADIUS * 2, CIRCLE_RADIUS * 2};
    SDL_Rect staticCircle = {SCREEN_WIDTH / 2 - CIRCLE_RADIUS, 0, CIRCLE_RADIUS * 2, CIRCLE_RADIUS * 2};

    bool isCollided = false;

    SDL_Event event;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    staticCircle.y -= MOVE_SPEED;
                    break;
                case SDLK_DOWN:
                    staticCircle.y += MOVE_SPEED;
                    break;
                case SDLK_LEFT:
                    staticCircle.x -= MOVE_SPEED;
                    break;
                case SDLK_RIGHT:
                    staticCircle.x += MOVE_SPEED;
                    break;
                default:
                    break;
                }
            }
        }

        // Update moving circle position
        movingCircle.x += MOVE_SPEED;

        // Check for collision
        isCollided = isCollision(movingCircle, staticCircle);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw circles with appropriate color based on collision
        Uint8 r = isCollided ? 255 : 0;
        Uint8 g = isCollided ? 0 : 255;
        SDL_SetRenderDrawColor(renderer, r, g, 0, 255);

        // Draw squares representing the circles
        SDL_RenderDrawRect(renderer, &movingCircle); // Draw moving circle as a square
        SDL_RenderDrawRect(renderer, &staticCircle); // Draw static circle as a square

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
