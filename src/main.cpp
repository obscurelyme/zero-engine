// clang-format off
// NOTE: The order matters here. Need clang format to not mess with this.
// #include <GL/glew.h>
// #include <GL/gl.h>
// clang-format on

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>

#include <CLI/CLI.hpp>
#include <exception>
#include <string>

#include "Zero/App.hpp"

int main(int argc, char** argv) {
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