/*
 *  mars_builtin_components.hpp
 *  Declarations a handful of useful built-in components
 */
#pragma once

#include "mars_core.hpp"

namespace mars {
/*=======================================================*/
/* Transform Component                                   */
/* Gives an entity position and movement                 */
/*=======================================================*/
class MARS_API ComponentTransform : public Component {
public:
	~ComponentTransform() {}
  void Update(float dt);

private:
	glm::vec3 pos = { 0, 0, 0 };
	glm::vec3 acc = { 0, 0, 0 };
	glm::vec3 last_pos = { 0, 0, 0 };
};

/*=======================================================*/
/* Step Component                                        */
/* Gives an entity a function call every game cycle      */
/*=======================================================*/
class MARS_API ComponentStep : public Component {
public:
	~ComponentStep() {}
  void Update(float dt);
private:
  std::function<void(float)> event;
};

}