#ifndef __I_WINDOW_H__
#define __I_WINDOW_H__

#include "../color.h"
#include "../types.h"
#include "../log.h"

class Window {
public:
    Window(c_str title_, uint w_, uint h_, Color bg_col_ = Color(0), uint v_sync_ = 1):
        title(title_), w(w_), h(h_), bg_col(bg_col_), v_sync(v_sync_) {
    }
    virtual ~Window() {}

    template<typename F>
    void loop(const F& step) {
        uint frames = 0;
        double last_time = get_time();
        while (!should_close()) {
            // Measure FPS
            double cur_time = get_time();
            frames++;
            if ((cur_time - last_time) >= 1.0) { // Print FPS every 1 second
                log_i("%d FPS (%.2f ms/frame)\n", frames, 1000.0/frames);
                frames = 0;
                last_time += 1.0;
            }

            clear();
            step();
            next();
        }
    }

    void set_bg_color(Color c) {
        bg_col = c;
    }

    virtual bool should_close() const = 0;

protected:
    c_str title;
    uint w, h;
    Color bg_col;
    uint v_sync;

    virtual double get_time() const = 0;
    virtual void clear() = 0;
    virtual void next() = 0;
};

#endif