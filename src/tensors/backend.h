#pragma once

#include "common/definitions.h"

namespace marian {

class Backend {
protected:
  DeviceId deviceId_;
  size_t seed_;

  // global clipping value for matrix-multiplies, should soon be removed.
  float clipValue_{0.f};

public:
  Backend(DeviceId deviceId, size_t seed) : deviceId_(deviceId), seed_(seed) {}

  virtual DeviceId getDeviceId() { return deviceId_; };

  // for GPU only, calls cudaSetDevice, does nothing on CPU. Maybe change name.
  virtual void setDevice() = 0;
  virtual void synchronize() = 0;

  virtual void setClip(float clipValue) { clipValue_ = clipValue; }

  float getClip() { return clipValue_; }
};

Ptr<Backend> BackendByDeviceId(DeviceId deviceId, size_t seed);
}  // namespace marian
