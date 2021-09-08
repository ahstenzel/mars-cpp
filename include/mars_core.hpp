/*
 *  mars.hpp
 *  Global declarations for core MARS objects
 */
#pragma once

// Library includes
#include <iostream>         // Console output
#include <memory>           // Smart pointers
#include <chrono>           // Cycle timing
#include <unordered_map>    // Hash tables
#include <vector>           // Vectors
#include <string>           // Strings
#include <cstdint>          // Fixed size int types
#include <functional>       // Function references
#include <glm/glm.hpp>      // Linear algebra functionality

namespace mars {

// Defines
#ifdef MARS_EXPORTS
  #define MARS_API __declspec(dllexport)	// Export functions to DLL, used when building library
#else
  #define MARS_API __declspec(dllimport)	// Import functions from DLL, used when building your game
#endif

// Platform specific code
#if defined(WIN32)
	// Windows Header Files
	#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
	#include <windows.h>

	BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);
#endif


// Class forward declerations
class Component;
class System;
class Entity;
class Engine;



/*=======================================================================================*/
/* Engine                                                                                */
/* Highest level container for game state. Contains pointers to other critical objects,  */
/* timing information for measuring time between frames, and handles for initialization  */
/* and destruction functions.                                                            */
/*=======================================================================================*/
class MARS_API Engine {
public:
  virtual void OnStart() = 0;
  virtual void OnEnd() = 0;
  void Start();
  void Update();
  void End();
  float GetDelta();
  bool IsRunning();

private:
  float dt = 0.0f;
  float render_alpha = 0.0f;
  float time_accum = 0.0f;
  bool run = true;
  std::chrono::high_resolution_clock::time_point old_time;
  std::chrono::high_resolution_clock::time_point new_time;
  std::vector<System> systems;
  std::unordered_map<std::string, Entity> entities;
};



/*=======================================================================================*/
/* Components                                                                            */
/* Structs that give entities certain properties or functionality.                       */
/*=======================================================================================*/
class MARS_API Component {
public:
	virtual ~Component() {};
	virtual void Update(float dt) {};
};



/*=======================================================================================*/
/* Systems                                                                               */
/* Structs that manage a collection of componenets.                                      */
/*=======================================================================================*/
class MARS_API System {
public:
  void Update(float dt);
private:
  std::vector<Component> components;
};



/*=======================================================================================*/
/* Entity                                                                                */
/* Basic game object. Has a unique ID that is used to link it to components.             */
/*=======================================================================================*/
class MARS_API Entity {
public:
  template<typename T>
  std::shared_ptr<T> GetComponent();

private:
  std::vector<std::shared_ptr<Component>> components;
  std::string uuid;
};

}