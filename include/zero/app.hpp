#ifndef ZERO_ENGINE_APP_
#define ZERO_ENGINE_APP_

#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

#include <memory>

#include "zero/app-params.hpp"
#include "zero/renderer.hpp"
#include "zero/window.hpp"

class App {
  public:
    App();
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    ~App();
    int Init(const AppParams&);
    void Run();
    void Quit();

    static void Log(void* userdata, int category, SDL_LogPriority priority, const char* message);

  private:
    std::shared_ptr<Window> window = nullptr;
    std::shared_ptr<Renderer> renderer = nullptr;
    AppParams appParams;
    bool running;

    static std::shared_ptr<spdlog::logger> logger;
};

#endif