/**************************************************************************\
 * BSD 3-Clause License
 *
 * Copyright (c) 2025, Fabrizio Morciano
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#include "Inventor/Fl/widgets/SoFlGLArea.h"
#include "Inventor/Fl/SoFlGLWidgetP.h"
#include "sofldefs.h"

#include <map>
#include <GL/gl.h>

static void Timer_CB(void *userdata) {
    auto pb = static_cast<SoFlGLArea *>(userdata);
    if (!pb)
        return;

    SoDebugError::postInfo("::SoFlGLArea::Timer_CB","%s", "Timer_CB");
    pb->redraw();
    Fl::repeat_timeout(1.0 / 24.0, Timer_CB, userdata);
}
SoFlGLArea::SoFlGLArea(Fl_Widget *parent,
    SoFlGLWidgetP* parentW,
                       const std::vector<int> &attributes)
    : Fl_Gl_Window(parent->x(),
                   parent->y(),
                   parent->w(),
                   parent->h()),widget_p(parentW){
    SOFL_STUB();
    Fl::add_timeout(1.0 / 24.0, Timer_CB, (void *) this); // 24fps timer

    mode(&attributes[0]);
    this->label("SoFlGLArea");
    is_gl_initialized = false;
    gl_format = attributes;
}

SoFlGLArea::~SoFlGLArea() {
    SOFL_STUB();
}

void SoFlGLArea::draw() {
    SOFL_STUB();
#if SOFL_DEBUG
    SoDebugError::postInfo("SoFlGLArea::draw",
                           "size:%d %d",
                           w(),
                           h());
#endif

    if (!valid()) {
        InitGL();
        // ...other initialization...
#if SOFL_DEBUG
        SoDebugError::postInfo("SoFlGLArea::draw",
                               "%s",
                               "!valid()");
#endif
    }

    if (!context_valid()) {
        // ...load textures, etc. ...
#if SOFL_DEBUG
        SoDebugError::postInfo("SoFlGLArea::draw",
                               "%s",
                               "!context_valid()");
#endif
      }

    glClear(GL_DEPTH_BUFFER_BIT);
    static bool onOff= true;
    if (onOff) {
        onOff= false;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    } else {
        onOff= true;
        glClearColor(1,1,1,0);
    }
#if SOFL_DEBUG
    SoDebugError::postInfo("SoFlGLArea::draw",
                           "%s",
                           "DRAW!!!!");
#endif
    widget_p->gl_exposed(9);
}

int SoFlGLArea::handle(int event) {
    SOFL_STUB();
    // this->redraw();
    return Fl_Gl_Window::handle(event);
}

void SoFlGLArea::InitGL() {
    SOFL_STUB();
    if (!is_gl_initialized) {
        is_gl_initialized = true;
        this->make_current();
        gl_real_context = this->context();
        assert(gl_real_context != nullptr);
    }
}

void SoFlGLArea::makeCurrent() {
    SOFL_STUB();
    this->make_current();
}
