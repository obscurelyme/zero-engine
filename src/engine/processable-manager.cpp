#include <algorithm>
#include <memory>
#include <vector>
#include <zero/processable-manager.hpp>

#include "zero/iprocessable.hpp"

std::vector<std::weak_ptr<IProcessable>> ProcessableManager::processables{};

void ProcessableManager::Process(float delta) {
  // NOTE: clear out stale processables
  CleanProcessables();

  // NOTE: run process on each processable
  for (const auto& obj : processables) {
    if (auto processable = obj.lock()) {
      processable->Process(delta);
    }
  }
}

void ProcessableManager::AddProcessable(const std::shared_ptr<IProcessable>& processable) {
  processables.push_back(processable);
}

std::vector<std::weak_ptr<IProcessable>>& ProcessableManager::GetProcessables() { return processables; }

void ProcessableManager::CleanProcessables() {
  processables.erase(std::remove_if(processables.begin(), processables.end(),
                                    [](const std::weak_ptr<IProcessable>& wkptr) { return wkptr.expired(); }),
                     processables.end());
}