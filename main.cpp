#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <vector>

void print_array(int arr[]);
void draw_state(int arr[], int screen_width, SDL_Window* window, SDL_Renderer* renderer, int i, int j, double delay_ms);
void draw_state(int arr[], int width, SDL_Window* window, SDL_Renderer* renderer, int i, double delay_ms);
void initialize_state(int arr[], int screen_width, SDL_Window* window, SDL_Renderer* renderer, double delay_ms);
void bubble_sort(int arr[], int screen_width, SDL_Window* window, SDL_Renderer* renderer, double delay_ms);
void insertion_sort(int arr[], int screen_width, SDL_Window* window, SDL_Renderer* renderer, double delay_ms);
void randomize_arr(int arr[],int screen_width);

int main()
{
    int width {800};
    int arr[width];
    double delay_ms{10};
    randomize_arr(arr, width);

    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, width, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    initialize_state(arr, width, window, renderer, delay_ms);
    bool running{true};
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                
            }
            
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_SPACE) {
                    randomize_arr(arr, width);
                    initialize_state(arr, width, window, renderer, delay_ms);
                }
                if(!std::is_sorted(arr, arr + sizeof(arr) / sizeof(arr[0]))) {
                    if(event.key.keysym.sym == SDLK_b) {
                        bubble_sort(arr, width, window, renderer, delay_ms);
                    }
                    if(event.key.keysym.sym == SDLK_i) {
                        insertion_sort(arr, width, window, renderer, delay_ms);
                    }
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

void randomize_arr(int arr[], int width)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, width - 1);

    std::fill_n(arr, width, 0);
    for (int i = 0; i < width; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < width; i++) {
        int random_index = dist(gen);
        std::swap(arr[i], arr[random_index]);
    }
}


void bubble_sort(int arr[], int width, SDL_Window* window, SDL_Renderer* renderer, double delay_ms)
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
        draw_state(arr, width, window, renderer, i, delay_ms);
    }
   
}

void insertion_sort(int arr[], int width, SDL_Window* window, SDL_Renderer* renderer, double delay_ms)
{
    for (int i = 0; i < width - 1; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        draw_state(arr, width, window, renderer, i, delay_ms);
    }
}


void draw_state(int arr[], int width, SDL_Window* window, SDL_Renderer* renderer, int i, int j, double delay_ms)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int k = 0; k < width; k++) {
        if(i == k) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer, k, width, k, width - arr[k]);
        }else if(j == k || (j + 1) == k) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, k, width, k, width - arr[k]);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, k, width, k, width - arr[k]);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(delay_ms);
}

void draw_state(int arr[], int width, SDL_Window* window, SDL_Renderer* renderer, int i, double delay_ms)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int k = 0; k < width; k++) {
        if(i == k) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer, k, width, k, width - arr[k]);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, k, width, k, width - arr[k]);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(delay_ms);
}

void initialize_state(int arr[], int width, SDL_Window* window, SDL_Renderer* renderer, double delay_ms)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int k = 0; k < width; k++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, k, width, k, width - arr[k]);
        
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(delay_ms);
}
