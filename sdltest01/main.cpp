#include <iostream>
#include <sdl/SDL.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    // 1.��ʼ����ʹ����Ƶ��ϵͳ��ͬʱ��ʼ���¼����ļ�I/O���߳�ϵͳ��
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2.��������
    SDL_Window *window = SDL_CreateWindow(
        "SDL Test 01",              // ����
        SDL_WINDOWPOS_UNDEFINED,    // ����x����
        SDL_WINDOWPOS_UNDEFINED,    // ����y����
        640,                        // ���ڿ�
        480,                        // ���ڸ�
        SDL_WINDOW_OPENGL           // ��־��ʹ��OPENGL
    );
    
    if (window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 3.������Ⱦ��
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,                        // ��Ⱦ��ʾ�Ĵ���
        -1,                         // ��Ⱦ����������-1�Զ���������Ҫ�����Ⱦ��
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // ��־��ʹ��Ӳ�����ٲ�������ֱͬ��
    );

    if (renderer == nullptr)
    {
        std::cout << "SDL_createRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 4.����ͼƬ��Դ
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

    // 5.����Texture(����)
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

    // 6.����Texture. clear renderer -> render texture -> present
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
    
    // 7.����
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}