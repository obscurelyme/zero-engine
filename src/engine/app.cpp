#include "zero/app.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

#include "zero/game-object.hpp"
#include "zero/input-manager.hpp"
#include "zero/processable-manager.hpp"
#include "zero/renderer.hpp"
#include "zero/text.hpp"
#include "zero/triangle.hpp"
#include "zero/window.hpp"

std::shared_ptr<spdlog::logger> App::logger = nullptr;

App::App() {}

App::~App() {}

int App::Init(const AppParams &appParams) {
  this->appParams = appParams;

  if (logger == nullptr) {
    logger = spdlog::stdout_color_mt("app");
  }

  SDL_SetLogOutputFunction(App::Log, nullptr);

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
    SDL_Log("Could not initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  window = std::make_shared<Window>(appParams.appTitle, appParams.windowWidth, appParams.windowHeight);
  renderer = std::make_shared<Renderer>(window->GetWindow(), appParams.windowWidth, appParams.windowHeight);

  SDL_LogInfo(0, "Application \"%s\" started...", appParams.appTitle.c_str());

  return 0;
}

void App::Run() {
  SDL_Event event;
  bool running = true;

  std::shared_ptr<Triangle> triangle = CreateGameObject<Triangle>();
  std::shared_ptr<Text> myText = CreateGameObject<Text>("Hello, World!");
  myText->SetPosition(0.0f, 0.0f);

  Uint64 last = SDL_GetTicks();
  Uint64 now;
  while (running) {
    now = SDL_GetTicks();
    float delta = (now - last) / 1000.0f;
    last = now;

    InputManager::SetInput({});

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT: {
          running = false;
          break;
        }
        case SDL_EVENT_WINDOW_RESIZED: {
          SDL_LogInfo(0, "Window resized: (%dx%d)", event.window.data1, event.window.data2);
          glViewport(0, 0, event.window.data1, event.window.data2);
          break;
        }
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP: {
          InputManager::SetInput(event.key);
        }
      }
    }

    ProcessableManager::Process(delta);

    renderer->ClearScreen();

    renderer->RenderScene();

    renderer->ClearUsedShaderProgram();
    renderer->SwapBuffers();
  }
}

void App::Quit() {
  Text::ClearShader();
  SDL_LogInfo(0, "Quitting application...");
  renderer = nullptr;
  window = nullptr;
  SDL_Quit();
}

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