#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <utility>
#include <sdl/SDL.h>

/*
 * Get the resource path for resources located in res/subDir
 * It's assumed the project directory is structured like:
 * bin/
 *   the executable
 * res/
 *   sub/
 *   xx.xx
 *
 * Paths returned will be res/sub/
 */
std::string getResourcePath(const std::string &subDir = "");

/*
 * Recurse through the list of arguments to clean up, cleaning up
 * the first one in the list each iteration.
 */
template<typename T, typename ... Args>
void cleanup(T *t, Args&&... args)
{
    // Cleanup the first item in the list
    cleanup(t);
    // Recurse to clean up the remaining arguments
    cleanup(std::forward<Args>(args)...);
}

template<>
inline void cleanup<SDL_Window>(SDL_Window *window)
{
    if (window)
    {
        SDL_DestroyWindow(window);
    }
}

template<>
inline void cleanup<SDL_Renderer>(SDL_Renderer *renderer)
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
}

template<>
inline void cleanup<SDL_Texture>(SDL_Texture *texture)
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

template<>
inline void cleanup<SDL_Surface>(SDL_Surface *surface)
{
    if (surface)
    {
        SDL_FreeSurface(surface);
    }
}

#endif // UTILS_H