#pragma once

#include "GLES2/gl2.h"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "customTextures.hpp"

class RendererPrototype :public Renderer {
public: // Attributes
  Vector2 screenDim;
private:
  raylib::ShadowTexture target;
  raylib::Shader shader_shadow;
  raylib::Shader shader_depth;
  raylib::Shader shader_geom;
  raylib::Shader shader_default;
  const GLubyte *rendererName;

public: // Methods
  void process() override;
  RendererPrototype();
  ~RendererPrototype() = default;
private:
};