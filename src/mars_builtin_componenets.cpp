/*
 *  mars_builtin_components.cpp
 *  Definitions a handful of useful built-in components
 */
#ifndef MARS_EXPORTS
#define MARS_EXPORTS
#endif
#include "mars_builtin_components.hpp"

namespace mars {

void ComponentTransform::Update(float dt) {
  // Verlet integration
  glm::vec3 _temp = pos;
  pos = (2.0f*_temp) - last_pos + (dt*dt*acc);
  last_pos = _temp;
}

void ComponentStep::Update(float dt) {
  event(dt);
}

}