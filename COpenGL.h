#ifndef CLASS_OPENLGL_H
#define CLASS_OPENLGL_H


#include <gtkmm.h>
#include <epoxy/gl.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"

#include <iostream>


#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define YAW    3
#define PITCH  4

const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 480;

class COpenGL : public Gtk::GLArea
{
public:
    COpenGL();
    ~COpenGL();

    float m_RotationAngles[5] = {0.0f};

protected:
    void onRealize();
    void onUnrealize();
    bool onRender(const Glib::RefPtr<Gdk::GLContext>& context);
    void processInput();

    /////////////////////////////////////////////////////////////////////////////////////

    Shader m_ourShader;
    Model  m_ourModel;
    char   m_cwd[PATH_MAX];

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    /////////////////////////////////////////////////////////////////////////////////////
};

#endif //CLASS_OPENLGL_H
