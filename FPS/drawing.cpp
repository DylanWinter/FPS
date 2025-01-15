#include "SDL.h"
#include "drawing.h"
#include "utils.h"
#include <cmath>
#include "map.h"


void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, SDL_Color color, bool filled)
{
    // save the current render color so it can be reverted later
    SDL_Color prev;
    SDL_GetRenderDrawColor(renderer, &prev.r, &prev.g, &prev.b, &prev.a);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    // midpoint circle algorithm
    while (x >= y)
    {
        if (filled) {
            // Draw horizontal lines to fill the circle
            SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX + x, centreY - y);
            SDL_RenderDrawLine(renderer, centreX - x, centreY + y, centreX + x, centreY + y);
            SDL_RenderDrawLine(renderer, centreX - y, centreY - x, centreX + y, centreY - x);
            SDL_RenderDrawLine(renderer, centreX - y, centreY + x, centreX + y, centreY + x);
        }
        else {
            // Draw points for the circle's perimeter
            SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
            SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
            SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
            SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
            SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
            SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
            SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
            SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
        }

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    // revert draw color
    SDL_SetRenderDrawColor(renderer, prev.r, prev.g, prev.b, prev.a);
}

void drawWall(SDL_Renderer* renderer, int x, int height, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x, (HEIGHT - height) / 2, x, (HEIGHT + height) / 2);
}

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