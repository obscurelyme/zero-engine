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
        std::cerr << "Abnormal termination" << std::endl;
        break;
      }
      case SIGFPE: {
        // NOTE: Floating-point error
        std::cerr << "Floating-point error" << std::endl;
        break;
      }
      case SIGILL: {
        // NOTE: Illegal instruction
        std::cerr << "	Illegal instruction" << std::endl;
        break;
      }
      case SIGINT: {
        // NOTE: CTRL+C signal
        std::cerr << "CTRL+C signal" << std::endl;
        break;
      }
      case SIGSEGV: {
        // NOTE: Illegal storage access
        std::cerr << "Illegal storage access" << std::endl;
        break;
      }
      case SIGTERM: {
        // NOTE: Termination request
        std::cerr << "	Termination request" << std::endl;
        break;
      }
      default:
        std::cerr << "Unknown signal" << std::endl;
        break;
    }
  }
}  // namespace Zero