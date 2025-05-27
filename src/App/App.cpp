#include "App/App.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> App::logger = nullptr;

App::App() {}

int App::Init(const AppParams &appParams) {
  if (logger == nullptr) {
    logger = spdlog::stdout_color_mt("console");
  }

  SDL_SetLogOutputFunction(App::Log, nullptr);

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
    SDL_Log("Could not initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer(appParams.appTitle.c_str(), appParams.windowWidth, appParams.windowHeight,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_Log("Could not create SDL window and/or renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_LogInfo(0, "Application \"%s\" started...", appParams.appTitle.c_str());

  return 0;
}

void App::Run() {
  SDL_Event event;
  bool running = true;

  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT: {
          running = false;
          return;
        }
      }
    }
  }
}

void App::Quit() { SDL_Quit(); }

void App::Log(void *, int, SDL_LogPriority priority, const char *message) {
  switch (priority) {
    case SDL_LOG_PRIORITY_CRITICAL: {
      logger->critical(message);
      break;
    }
    case SDL_LOG_PRIORITY_INFO: {
      logger->info(message);
      break;
    }
    case SDL_LOG_PRIORITY_WARN: {
      logger->warn(message);
      break;
    }
    case SDL_LOG_PRIORITY_DEBUG: {
      logger->debug(message);
      break;
    }
    case SDL_LOG_PRIORITY_ERROR: {
      logger->error(message);
      break;
    }
    default: {
      logger->trace(message);
      break;
    }
  }
}