#include <iostream>
#include <sdl/SDL.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    // 1.初始化，使用视频子系统，同时初始化事件，文件I/O，线程系统。
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2.创建窗口
    SDL_Window *window = SDL_CreateWindow(
        "SDL Test 01",              // 标题
        SDL_WINDOWPOS_UNDEFINED,    // 窗口x坐标
        SDL_WINDOWPOS_UNDEFINED,    // 窗口y坐标
        640,                        // 窗口宽
        480,                        // 窗口高
        SDL_WINDOW_OPENGL           // 标志，使用OPENGL
    );
    
    if (window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 3.创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,                        // 渲染显示的窗口
        -1,                         // 渲染驱动索引，-1自动查找满足要求的渲染器
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 标志，使用硬件加速并开启垂直同步
    );

    if (renderer == nullptr)
    {
        std::cout << "SDL_createRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 4.加载图片资源
    std::string imagePath = getResourcePath() + "hello.bmp";
    SDL_Surface *image = SDL_LoadBMP(imagePath.c_str());
    if (image == nullptr)
    {
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 5.创建Texture(纹理)
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (texture == nullptr)
    {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 6.绘制Texture. clear renderer -> render texture -> present
    for (int i = 0; i < 3; i++)
    {
        // 6.1 Clear the renderer
        SDL_RenderClear(renderer);
        // 6.2 Draw texture
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        // 6.3 Update the screen
        SDL_RenderPresent(renderer);
        // Wait a while
        SDL_Delay(1000);
    }
    
    // 7.清理
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}