#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.hpp"
#include "Point.hpp"
#include "Text.hpp"
#include "RenderWindow.hpp"
#include "Vector2D.hpp"
#include "Utils.hpp"

using namespace std;
using namespace Utils;

void writeRecord(float time) {
    ofstream records;
    records.open("res/data/Records.dat", ios::app);
    records << time << endl;
    records.close();
}

int main(int argc, char *args[]) {
    std::string path = std::filesystem::current_path().string();
    std::filesystem::current_path(path + "/..");
    SDL_Log("%s\n", std::filesystem::current_path().string().c_str());

    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        cout << "SDL_Init FAILED.\n SDL_ERROR: " << SDL_GetError() << endl;
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        cout << "IMG_Init FAILED.\n SDL_ERROR: " << SDL_GetError() << endl;
        return 0;
    }

    if (TTF_Init() == -1) {
        cout << "TTF_Init FAILED.\n SDL_ERROR: " << SDL_GetError() << endl;
        return 0;
    }

    // Window
    RenderWindow window("GravitySurvival", WIDTH, HEIGHT);
    window.setBackgroundColor(48, 56, 66);

    // Player
    SDL_Texture *playerTexture = window.loadTexture("res/gfx/Player.png");
    Player *player = Player::getInstance(playerTexture);

    SDL_Texture *pointTexture = window.loadTexture("res/gfx/Point.png");

    // Events
    SDL_Event event;
    bool keyPressed[TOTAL_KEYS];
    for (int i = 0; i < TOTAL_KEYS; i++) {
        keyPressed[i] = false;
    }
    int xY[2] = {0, 0};

    // FPS
    float timeAccumulator = 0;
    float dt = 0;
    float lastTime = getTime();
    int cptLag = 0;

    // Variables for Attracting the Player
    int attractTime = 0;
    float attractTimeAccumulator = 0;
    float attractDirection = 0; // In [0;2π]
    float attractMaxSpeed = 0;
    float attractSpeed = 0;

    vector<Point> points;

    // Loop
    bool gameRunning = true;

    /*
    0 : Main Menu
    1 : Game
    2 : Pause
    3 : Lost Menu
    4 : Best Scores
    */
    int menu = 0;

    while (gameRunning) {

        if (menu == 0) {
            Text startText(100, 100, "res/fonts/Consola.ttf", 30, "Press Space to Start !", {255, 255, 255, 255},
                           window.getRenderer());
            window.clear();
            window.render(startText);
            window.display();

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        gameRunning = false;
                        break;

                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            menu = 1;
                            lastTime = getTime();
                        }
                        break;
                }
            }
        }


        if (menu == 1) {
            dt = getTime() - lastTime;
            lastTime = getTime();
            timeAccumulator += dt;
            if (dt > 0.1) {
                cptLag++;
                if (cptLag >= 4) {
                    cout << "FPS < 10. Achète toi un PC mon gars." << endl;
                    gameRunning = false;
                }
            } else {
                cptLag = 0;
            }

            player->updateVelocity(xY, dt);
            player->move(dt);

            attractTimeAccumulator += dt;
            if (attractTimeAccumulator > attractTime) {
                attractTimeAccumulator = 0;
                attractSpeed = 0;
                attractTime = (int) 2 + randomFloat() * 6;
                attractMaxSpeed = 1 + randomFloat();
                attractDirection = randomFloat() * 2 * PI;
            }
            if (attractSpeed < attractMaxSpeed) {
                attractSpeed += dt * TARGET_FPS;
            }

            player->attract(attractMaxSpeed, attractDirection, dt);
            Text attractTimerText(WIDTH - 100, 30,
                                  "res/fonts/Consola.ttf", 30,
                                  to_string(attractTime - attractTimeAccumulator).substr(0, 4),
                                  {255, 255, 255, 255}, window.getRenderer());
            Text timerText(30, 30,
                           "res/fonts/Consola.ttf", 30,
                           to_string(timeAccumulator).substr(0, 4),
                           {255, 255, 255, 255}, window.getRenderer());

            float proba = dt * timeAccumulator;
            if (randomFloat() < min(proba, 0.32f)) {
                points.push_back(Point::generateRandomPoint(pointTexture));
            }

            float playerX = player->getPos().getX();
            float playerY = player->getPos().getY();
            if (playerX < 0 || playerX + PLAYER_SIZE > WIDTH ||
                playerY < 0 || playerY + PLAYER_SIZE > HEIGHT) {
                writeRecord(timeAccumulator);
                menu = 3;
            }

            vector<int> indexToErase;
            int i = 0;
            for (Point &point: points) {
                float x = point.getPos().getX();
                float y = point.getPos().getY();
                if (x < 0 or x > WIDTH or y < 0 or y > HEIGHT) {
                    indexToErase.push_back(i);
                } else {
                    if ((x < (playerX + PLAYER_SIZE)) &&
                        (x + POINT_SIZE > playerX) &&
                        (y < (playerY + PLAYER_SIZE)) &&
                        (y + POINT_SIZE > playerY)) {
                        writeRecord(timeAccumulator);
                        menu = 3;
                    }
                    point.move(dt);
                }
                i += 1;
            }

            i = 0;
            for (int j: indexToErase) {
                points.erase(points.begin() + j - i);
                i += 1;
            }

            window.clear();
            window.render(*player);
            window.render(attractTimerText);
            window.render(timerText);
            for (Point &point: points) {
                window.render(point);
            }
            window.display();

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        gameRunning = false;
                        break;

                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym) {
                            case SDLK_SPACE:
                                menu = 2;
                                break;
                            case SDLK_LEFT:
                                keyPressed[0] = true;
                                xY[0] = -!(keyPressed[1]);
                                break;
                            case SDLK_RIGHT:
                                keyPressed[1] = true;
                                xY[0] = !(keyPressed[0]);
                                break;
                            case SDLK_UP:
                                keyPressed[2] = true;
                                xY[1] = -!(keyPressed[3]);
                                break;
                            case SDLK_DOWN:
                                keyPressed[3] = true;
                                xY[1] = !(keyPressed[2]);
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        switch (event.key.keysym.sym) {
                            case SDLK_LEFT:
                                keyPressed[0] = false;
                                xY[0] = keyPressed[1];
                                break;
                            case SDLK_RIGHT:
                                keyPressed[1] = false;
                                xY[0] = -keyPressed[0];
                                break;
                            case SDLK_UP:
                                keyPressed[2] = false;
                                xY[1] = keyPressed[3];
                                break;
                            case SDLK_DOWN:
                                keyPressed[3] = false;
                                xY[1] = -keyPressed[2];
                                break;
                        }
                        break;
                }
            }
        }


        if (menu == 2) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        gameRunning = false;
                        break;

                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            menu = 1;
                            lastTime = getTime();
                        }
                        break;
                }
            }
        }

        if (menu == 3) {
            Text restartText(30, HEIGHT - 160,
                             "res/fonts/Consola.ttf", 60,
                             "You lost, press SPACE to restart.",
                             {255, 255, 255, 255}, window.getRenderer());
            window.render(restartText);
            Text recordsText(30, HEIGHT - 80,
                             "res/fonts/Consola.ttf", 60,
                             "Press R to see your records.",
                             {255, 255, 255, 255}, window.getRenderer());
            window.render(recordsText);
            window.display();

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        gameRunning = false;
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            menu = -1;
                        } else if (event.key.keysym.sym == SDLK_r) {
                            menu = 4;
                        }
                        break;
                }
            }
        }

        if (menu == 4) {
            window.clear();
            Text restartText(30, 10,
                             "res/fonts/Consola.ttf", 30,
                             "Press SPACE to restart.",
                             {255, 255, 255, 255}, window.getRenderer());
            window.render(restartText);
            Text recordsText(30, 50,
                             "res/fonts/Consola.ttf", 30,
                             "Your best records :",
                             {255, 255, 255, 255}, window.getRenderer());
            window.render(recordsText);
            vector<string> times;
            ifstream records;
            string tmp;
            records.open("res/data/Records.dat");
            while (records) {
                records >> tmp;
                if (records) {
                    times.push_back(tmp);
                }
            }
            records.close();
            triNaif(times);
            int y = 90;
            for (string time: times) {
                Text recordText(30, y,
                                "res/fonts/Consola.ttf", 30,
                                time,
                                {255, 255, 255, 255}, window.getRenderer());
                y += 30;
                window.render(recordText);
                if (y >= HEIGHT) {
                    break;
                }
            }
            window.display();
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        gameRunning = false;
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            menu = -1;
                        }
                        break;
                }
            }
        }

        if (menu == -1) { // reset all
            player->reset();
            for (int i = 0; i < TOTAL_KEYS; i++) {
                keyPressed[i] = false;
            }
            xY[0] = 0;
            xY[1] = 0;
            timeAccumulator = 0;
            dt = 0;
            lastTime = getTime();
            cptLag = 0;
            attractTime = 0;
            attractTimeAccumulator = 0;
            attractDirection = 0;
            attractMaxSpeed = 0;
            points.clear();
            menu = 1;
            lastTime = getTime();
        }

    }

    window.cleanUp();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}