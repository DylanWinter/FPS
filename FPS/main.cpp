#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "drawing.h"
#include "utils.h"
#include "input.h"
#include <cmath>
#include <iostream>
#include <vector>

bool draw2d = false;

const Vector2 startPos = { 15.0f, 14.0f };

SDL_Renderer* topDownRenderer;
SDL_Window* topDownWindow;
SDL_Texture* weapon;

const int mapw = 30;
const int maph = 30;
int map[mapw][maph] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void drawTopDown(SDL_Renderer* renderer, Player player) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // draw the player
    int x = (int)player.position.x * (TOPDOWN_WIDTH / mapw);
    int y = (int)player.position.y * (TOPDOWN_HEIGHT / maph);
    drawCircle(renderer, x, y, 10, YELLOW, true);
    // draw the view line
    int x2 = x + static_cast<int>(100 * std::cos(player.angle));
    int y2 = y + static_cast<int>(100 * std::sin(player.angle));
    SDL_RenderDrawLine(renderer, x, y, x2, y2);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 0; y < maph; y++) {
        for (int x = 0; x < mapw; x++) {
            if (map[x][y] == 1) {
                SDL_Rect wallRect = { x * (TOPDOWN_WIDTH / mapw), y * (TOPDOWN_HEIGHT / maph), TOPDOWN_WIDTH / mapw, TOPDOWN_HEIGHT / maph };
                SDL_RenderFillRect(renderer, &wallRect);
            }
        }
    }
}

void fireShot(Player player) {
    float rayAngle = player.angle;
    float stepX = cos(rayAngle);
    float stepY = sin(rayAngle);

    float dist = 0.0f;
    bool found = false;
    int testX = 0; int testY = 0;

    while (true) {
        dist += 0.1f;
        testX = (int)(player.position.x + stepX * dist);
        testY = (int)(player.position.y + stepY * dist);

        // hit a wall!
        if (map[testX][testY] != 0) {
            // for now we'll just change the colour, to confirm it's working
            map[testX][testY] = 5;
            break;
        }

        // put enemy hit condition here

        // hit nothing
        if (testX < 0 || testX >= mapw || testY < 0 || testY >= maph) {
            break;
        }
    }
}

int main()
{
    // init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library" << std::endl;
        return -1;
    }

    // init main window
    SDL_Window* window = SDL_CreateWindow("3D Raycasting",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        return -1;
    }

    // init top-down window
    if (draw2d) {
        SDL_Window* topDownWindow = SDL_CreateWindow("Top-Down View",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            TOPDOWN_WIDTH, TOPDOWN_HEIGHT,
            0);


        if (!topDownWindow)
        {
            std::cout << "Failed to create top-down window" << std::endl;
            return -1;
        }

        topDownRenderer = SDL_CreateRenderer(
            topDownWindow,                       // Top-down window renderer
            -1,                             // Use the first available driver
            SDL_RENDERER_ACCELERATED      // Enable hardware acceleration
        );
        if (!topDownRenderer) {
            std::cerr << "Failed to create top-down renderer: " << SDL_GetError() << std::endl;
            return -1;
        }
    }

    // init renderers
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,                       // Main window renderer
        -1,                             // Use the first available driver
        SDL_RENDERER_ACCELERATED      // Enable hardware acceleration
    );
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return -1;
    }

    weapon = SDL_CreateTextureFromSurface(renderer, IMG_Load("assets/shotgun.png"));

    Uint32 time_step_ms = 1000 / 60;
    Uint32 next_game_step = SDL_GetTicks();

    Player player = { {startPos.x, startPos.y}, 0.0f };
    bool close_window = false;
    Vector2 movementDir = { 0, 0 };

    // main render loop
    while (!close_window)
    {
        Uint32 now = SDL_GetTicks();

        if (next_game_step <= now)
        {
            SDL_Event e;
            while (SDL_PollEvent(&e) > 0)
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    close_window = true;
                    std::cout << "closing window..." << std::endl;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_SPACE)
                    {
                        printf("shot fired\n");
                        fireShot(player);
                    }
                    break;
                }
            }
            // get input
            SDL_PumpEvents();
            const Uint8* keyState = SDL_GetKeyboardState(NULL);
            movementDir = getDirection(keyState);
            // move the player
            Vector2 newPos = player.position;
            if (movementDir.y != 0) { // forward or backward
                newPos.x += -movementDir.y * moveSpeed * cos(player.angle);
                newPos.y += -movementDir.y * moveSpeed * sin(player.angle);
            }
            if (movementDir.x != 0) { // strafing
                newPos.x += movementDir.x * moveSpeed * cos(player.angle + (M_PI / 2));
                newPos.y += movementDir.x * moveSpeed * sin(player.angle + (M_PI / 2));
            }
            // handle collisions with walls
            if (map[(int)newPos.x][(int)player.position.y] == 0) {
                player.position.x = newPos.x;
            }
            if (map[(int)player.position.x][(int)newPos.y] == 0) {
                player.position.y = newPos.y;
            }
            player.angle += getRotation(keyState);
            // clamp angle
            player.angle = fmod(player.angle + 2 * M_PI, 2 * M_PI);

            // main window rendering
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderClear(renderer);

            // raycasting
            int numRays = WIDTH;
            float fov = M_PI / 2.5f; // 72 degree FOV
            for (int i = 0; i < numRays; i++)
            {
                float rayAngle = (player.angle - fov / 2) + ((float)i / numRays) * fov;
                float stepX = cos(rayAngle);
                float stepY = sin(rayAngle);

                float dist = 0.0f;
                bool found = false;
                int testX = 0; int testY = 0;
                
                while (true) {
                    dist += 0.1f;
                    testX = (int)(player.position.x + stepX * dist);
                    testY = (int)(player.position.y + stepY * dist);

                    // hit a wall!
                    if (map[testX][testY] != 0) {
                        found = true;
                        break;
                    }

                    // if we hit nothing, draw nothing
                    if (testX < 0 || testX >= mapw || testY < 0 || testY >= maph) {
                        break;
                    }
                }

                // draw the wall, if one was found
                if (found)
                {
                    int wallHeight = (int)(HEIGHT / dist);
                    drawWall(renderer, i, wallHeight, colors[map[testX][testY]]);
                }
            }

            // top-down window rendering
            if (draw2d) {
                SDL_SetRenderDrawColor(topDownRenderer, 0, 0, 0, 255);
                SDL_RenderClear(topDownRenderer);
                drawTopDown(topDownRenderer, player);
                SDL_SetRenderDrawColor(topDownRenderer, 255, 255, 0, 255);
            }

            // draw the weapon 
            SDL_Rect pos;
            pos.w = 192;
            pos.h = 192;
            pos.x = (WIDTH / 2) - (pos.w / 2);
            pos.y = (HEIGHT * 0.9) - (pos.h / 2);
            SDL_RenderCopy(renderer, weapon, nullptr, &pos);

            // update windows
            next_game_step += time_step_ms;
            SDL_RenderPresent(renderer);
            SDL_RenderPresent(topDownRenderer);
        }
        // delay to maintain constant frame rate
        else {
            SDL_Delay(next_game_step - now);
        }
    }

    // clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(topDownRenderer);
    if (draw2d) { SDL_DestroyWindow(topDownWindow); }
    SDL_Quit();
    return 0;
}
