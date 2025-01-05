#include "SDL.h"

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, SDL_Color color, bool filled = true)
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