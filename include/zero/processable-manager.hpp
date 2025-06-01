#ifndef ZERO_ENGINE_PROCESSABLE_MANAGER_
#define ZERO_ENGINE_PROCESSABLE_MANAGER_

#include <memory>
#include <vector>

#include "zero/iprocessable.hpp"

class ProcessableManager {
  public:
    static void Process(float delta);
    static void CleanProcessables();
    static void AddProcessable(const std::shared_ptr<IProcessable>& Processable);
    static std::vector<std::weak_ptr<IProcessable>>& GetProcessables();

  private:
    static std::vector<std::weak_ptr<IProcessable>> processables;

    ProcessableManager() = default;
    ProcessableManager(const ProcessableManager&) = delete;
    ProcessableManager& operator=(const ProcessableManager&) = delete;
};

#endif