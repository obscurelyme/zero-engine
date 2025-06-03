#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>

#include <CLI/CLI.hpp>
#include <exception>
#include <string>

#include "zero/app.hpp"
#include "zero/crash-handler.hpp"
#include "zero/font-manager.hpp"

int main(int argc, char** argv) {
  Zero::HandleSignals();

  CLI::App app{"Zero Engine"};

  std::string scene = "";
  std::string windowTitle = "Zero Engine";
  unsigned int windowHeight = 600;
  unsigned int windowWidth = 800;

  app.add_option("-t,--title", windowTitle, "Window title");
  app.add_option("-q,--height", windowHeight, "Window height");
  app.add_option("-w,--width", windowWidth, "Window width");
  app.add_option("-s,--scene", scene, "Scene to load.");

  CLI11_PARSE(app, argc, argv);

  try {
    App game;

    game.Init({
        .appTitle = windowTitle,
        .windowHeight = windowHeight,
        .windowWidth = windowWidth,
    });
    FontManager::Init();
    FontManager::LoadFont("fonts/Silkscreen-Regular.ttf");

    game.Run();
    game.Quit();

    return 0;
  } catch (const std::exception& e) {
    SDL_LogError(0, "%s", e.what());
    return 1;
  } catch (...) {
    SDL_LogCritical(0, "Unknown exception occured! %s", SDL_GetError());
    return 2;
  }
}