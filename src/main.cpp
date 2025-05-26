#include <CLI/App.hpp>

int main(int argc, char** argv) {
  CLI::App app{"Zero Engine"};
  CLI11_PARSE(app, argc, argv);

  return 0;
}