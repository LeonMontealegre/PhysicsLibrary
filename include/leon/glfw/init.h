#ifndef __GLFW_INIT_H__
#define __GLFW_INIT_H__

#include <GLFW/glfw3.h>
#include <stdio.h>
#include "../types.h"
#include "../log.h"

static void error_callback(int err, c_str desc) {
    log_e("GL Error (%d), %s\n", err, desc);
}

bool init_GLFW(uint v_maj = 3, uint v_min = 2, uint msaa_samples = 1, bool forward_compat = true) {
    static bool initialized = false;

    if (initialized)
        return true;

	glfwSetErrorCallback(error_callback);

    // Initialize GLFW
	if (!glfwInit())
		return false;
    initialized = true;

	// We will ask it to specifically open an OpenGL 3.2 context
	glfwWindowHint(GLFW_SAMPLES, msaa_samples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, v_maj);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, v_min);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, forward_compat ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

#endif