#include "zero/crash-handler.hpp"

#include <csignal>
#include <iostream>

namespace Zero {
  void HandleSignals() {
    std::signal(SIGABRT, Zero::HandleSignal);
    std::signal(SIGFPE, Zero::HandleSignal);
    std::signal(SIGILL, Zero::HandleSignal);
    std::signal(SIGINT, Zero::HandleSignal);
    std::signal(SIGSEGV, Zero::HandleSignal);
    std::signal(SIGTERM, Zero::HandleSignal);
  }

  void HandleSignal(int signal) {
    switch (signal) {
      case SIGABRT: {
        // NOTE: 	Abnormal termination
        std::cerr << "Abnormal termination\n";
        break;
      }
      case SIGFPE: {
        // NOTE: Floating-point error
        std::cerr << "Floating-point error\n";
        break;
      }
      case SIGILL: {
        // NOTE: Illegal instruction
        std::cerr << "	Illegal instruction\n";
        break;
      }
      case SIGINT: {
        // NOTE: CTRL+C signal
        std::cerr << "CTRL+C signal\n";
        break;
      }
      case SIGSEGV: {
        // NOTE: Illegal storage access
        std::cerr << "Illegal storage access\n";
        break;
      }
      case SIGTERM: {
        // NOTE: Termination request
        std::cerr << "	Termination request\n";
        break;
      }
      default:
        std::cerr << "Unknown signal\n";
        break;
    }
  }
}  // namespace Zero