#ifndef ZERO_ENGINE_APP_
#define ZERO_ENGINE_APP_

#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string>

struct AppParams {
    std::string appTitle;
    int windowHeight;
    int windowWidth;
};

class App {
  public:
    App();
    int Init(const AppParams&);
    void Run();
    void Quit();
    static void Log(void* userdata, int category, SDL_LogPriority priority, const char* message);

  private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    static std::shared_ptr<spdlog::logger> logger;
};

#endif