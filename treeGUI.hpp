// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef TREEGUI_HPP
#define TREEGUI_HPP

#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "node.hpp"
#include <algorithm>

template <typename T>
class TreeGUI {
public:
    // Function to render a single node in the tree
    void renderNode(SDL_Renderer* renderer, TTF_Font* font, Node<T>* node, int x, int y, int level, int horizontalSpacing) const {
        if (!node) return;

        // Convert node value to string for rendering
        std::stringstream ss;
        ss << node->getValue();
        SDL_Color textColor = {0, 0, 0, 255}; // Black color for text
        SDL_Surface* surface = TTF_RenderText_Solid(font, ss.str().c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int textWidth, textHeight;
        SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

        // Calculate ellipse size based on text size
        int ellipseWidth = std::max(textWidth + 20, 60);  // At least 60 pixels wide
        int ellipseHeight = std::max(textHeight + 20, 40);  // At least 40 pixels tall

        // Draw the ellipse around the node value
        SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);  // Light blue color for the ellipse
        for (int w = -ellipseWidth/2; w <= ellipseWidth/2; w++) {
            for (int h = -ellipseHeight/2; h <= ellipseHeight/2; h++) {
                if (4*w*w/(float)(ellipseWidth*ellipseWidth) + 4*h*h/(float)(ellipseHeight*ellipseHeight) <= 1) {
                    SDL_RenderDrawPoint(renderer, x + w, y + h);
                }
            }
        }

        // Render the node value text
        SDL_Rect dstRect = {x - textWidth / 2, y - textHeight / 2, textWidth, textHeight};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        // Render the children nodes
        int childCount = node->getChildren().size();
        int totalWidth = (childCount - 1) * horizontalSpacing;
        int startX = x - totalWidth / 2;

        for (int i = 0; i < childCount; i++) {
            auto& child = node->getChildren()[i];
            int childX = startX + i * horizontalSpacing;
            int childY = y + 120;  // Increase vertical distance between nodes

            // Draw line from parent to child node
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);  // Dark gray color for lines
            SDL_RenderDrawLine(renderer, x, y + ellipseHeight/2, childX, childY - ellipseHeight/2);

            // Recursively render the child node
            renderNode(renderer, font, child, childX, childY, level + 1, horizontalSpacing / 2);
        }
    }

    // Function to render the entire tree starting from the root node
    void renderTree(Node<T>* root) const {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }

        // Create SDL window
        SDL_Window* window = SDL_CreateWindow("Tree Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        // Create SDL renderer
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return;
        }

        // Initialize SDL_ttf for font rendering
        TTF_Init();
        TTF_Font* font = TTF_OpenFont("arial.ttf", 20);
        if (!font) {
            std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return;
        }

        // Set background color
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);  // Light gray background color
        SDL_RenderClear(renderer);

        // Start rendering the tree from the root node
        renderNode(renderer, font, root, 512, 50, 0, 300);

        // Present the rendered tree on the screen
        SDL_RenderPresent(renderer);

        // Event loop to keep the window open until the user closes it
        bool quit = false;
        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
        }

        // Clean up and close SDL resources
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }
};

#endif // TREEGUI_HPP
