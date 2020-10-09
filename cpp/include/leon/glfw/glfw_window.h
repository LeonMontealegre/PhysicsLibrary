#ifndef __GLFW_WINDOW_H__
#define __GLFW_WINDOW_H__

#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "../log.h"
#include "../interfaces/window.h"

#include "init.h"

class GLFWWindow: public Window {
public:
    GLFWWindow(c_str title_, uint w_, uint h_, Color bg_col_ = Color(0), uint v_sync_ = 1):
            Window(title_, w_, h_, bg_col_, v_sync_) {
        // Initialize GLFW if not already initialized
        if (!init_GLFW())
            exit(EXIT_FAILURE);

        window = glfwCreateWindow(w, h, title, NULL, NULL);
        if (!window) {
            log_e("Failed to create window!\n");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        glfwSwapInterval(v_sync);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glDisable(GL_CULL_FACE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        log_i("----------------------------------------------------\n");
        log_i("         OpenGL Version: %s\n", glGetString(GL_VERSION));
        log_i("----------------------------------------------------\n");
    }
    ~GLFWWindow() override {
        glfwDestroyWindow(window);
    }

    bool should_close() const override {
        return glfwWindowShouldClose(window);
    }

protected:
    GLFWwindow* window;

    double get_time() const override {
        return glfwGetTime();
    }

    void clear() override {
        glClearColor(bg_col.r, bg_col.g, bg_col.b, bg_col.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void next() override {
        // Check for error
        GLenum err = glGetError();
        if (err != 0)
            log_e("GL err (%d)\n", err);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

};

#endif