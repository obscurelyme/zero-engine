#ifndef ZERO_ENGINE_IPROCESSABLE_
#define ZERO_ENGINE_IPROCESSABLE_

class IProcessable {
  public:
    virtual void Process(float delta) = 0;
};

#endif