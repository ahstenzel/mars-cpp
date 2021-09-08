/*
 *  mars_core.cpp
 *  Definition for core MARS functionality
 */
#ifndef MARS_EXPORTS
#define MARS_EXPORTS
#endif
#include "mars_core.hpp"

namespace mars {

// Platform specific code
#if defined(WIN32)
// DLL Entrypoint function
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
#endif

/*=======================================================================================*/
/* void Engine::Start()                                                                  */
/* Initializes critical game objects and runs overrided virtual OnStart function.        */
/*=======================================================================================*/
void Engine::Start() {
  // Get current time
  old_time = std::chrono::high_resolution_clock::now();

  // Run override function
  OnStart();
}

/*=======================================================================================*/
/* void Engine::Update()                                                                 */
/* Advances game state and runs overrided virtual OnUpdate function.                     */
/*=======================================================================================*/
void Engine::Update() {
  // Get current cycle time
  new_time = std::chrono::high_resolution_clock::now();
  float cycle_time = std::chrono::duration_cast<std::chrono::duration<float>>(new_time - old_time).count();
  time_accum += cycle_time;
  old_time = new_time;

  // Consume it in dt sized chunks
  while(time_accum >= dt) {
    // Update systems
    for(auto it : systems) {
      it.Update(dt);
    }

    // Reduce remaining time
    time_accum -= dt;
  }

  // Normalize remaining time
  render_alpha = time_accum / dt;

  // Update render state
  // TODO
}

/*=======================================================================================*/
/* void Engine::End()                                                                    */
/* Cleans up game objects and runs overrided virtual OnEnd function.                     */
/*=======================================================================================*/
void Engine::End() {
  // Run override function
  OnEnd();
}

/*=======================================================================================*/
/* void Engine::GetDelta()                                                               */
/* Get the amount of time between game updates in seconds.                               */
/*=======================================================================================*/
float Engine::GetDelta() { return dt; }

/*=======================================================================================*/
/* void Engine::End()                                                                    */
/* Check whether the game loop should still be executing.                                */
/*=======================================================================================*/
bool Engine::IsRunning() { return run; }

/*=======================================================================================*/
/* void System::Update()                                                                 */
/* Iterate through all components in the system, triggering their updates.               */
/*=======================================================================================*/
void System::Update(float dt) {
  for(auto it : components) {
    it.Update(dt);
  }
}

/*=======================================================================================*/
/* shared_ptr<T> Entity::GetComponent<T>                                                 */
/* Get a reference to the component for this entity, or nullptr if the entity doesn't    */
/* have that component.                                                                  */
/*=======================================================================================*/
template<typename T>
std::shared_ptr<T> Entity::GetComponent() {
  for(auto it : components) {
    if (T component = dynamic_cast<T>(*it)) {
      return std::make_shared<T>(component);
    }
  }
  return nullptr;
}

}