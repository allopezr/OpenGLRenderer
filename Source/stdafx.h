#include <any>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <execution>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// IMPORTANTE: El include de GLEW debe estar siempre ANTES de el de GLFW
#include "GL/glew.h"								
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/ext/vector_relational.hpp>   
#include <glm/gtc/epsilon.hpp>     

// Gui
#include "imgui.h"
#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"

// Rename
typedef glm::vec4 vec4;
typedef glm::mat4 mat4;

typedef glm::vec3 vec3;
typedef glm::mat3 mat3;

typedef glm::vec2 vec2;
typedef glm::uvec3 uvec3;
typedef glm::uvec2 uvec2;

typedef glm::ivec3 ivec3;
typedef glm::ivec2 ivec2;

// Millis time

//#include <windows.h>
//
//// Used to measure intervals and absolute times
//typedef int64_t msec_t;
//
//msec_t time_ms(void)
//{
//    return timeGetTime();
//}

