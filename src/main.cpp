// clang-format off
// NOTE: The order matters here. Need clang format to not mess with this.
#include <GL/glew.h>
// #include <GL/gl.h>
// clang-format on

#include <CLI/CLI.hpp>
#include <string>

#include "App/App.hpp"

int main(int argc, char** argv) {
  CLI::App app{"Zero Engine"};
  App game;

  std::string scene = "";
  std::string windowTitle = "Zero Engine";
  int windowHeight = 600;
  int windowWidth = 800;

  app.add_option("-t,--title", windowTitle, "Window title");
  app.add_option("-q,--height", windowHeight, "Window height");
  app.add_option("-w,--width", windowWidth, "Window width");
  app.add_option("-s,--scene", scene, "Scene to load.");

  CLI11_PARSE(app, argc, argv);

  game.Init({
      .appTitle = windowTitle,
      .windowHeight = windowHeight,
      .windowWidth = windowWidth,
  });

  game.Run();
  game.Quit();

  return 0;
}