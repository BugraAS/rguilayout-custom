#pragma once

#include "GLES2/gl2.h"
#include "Renderer.hpp"
#include <memory>
#include <vector>

class RendererDefault :public Renderer {
public: // Attributes
  int screenDim[2] = {};
private:
  const GLubyte *rendererName;

public: // Methods
  void process() override;
  RendererDefault();
  virtual ~RendererDefault() = default;
private:
};