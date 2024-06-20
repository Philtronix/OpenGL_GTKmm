#include "COpenGL.h"

#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

COpenGL::COpenGL()
{
    g_print("[COpenGL]\r\n");

    // Get the path where we are running from
    if (getcwd(m_cwd, sizeof(m_cwd)) != NULL) 
    {
        printf("Current working dir: %s\n", m_cwd);
    } 
    else 
    {
        perror("getcwd() error");
        return;
    }
 
    GLenum err = glfwInit();
    if (err == GLFW_FALSE)
    {
        g_print("glewInit() - failed\r\n");
        exit(1); // or handle the error in a nicer way
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    set_auto_render(true);
    set_required_version(3, 3);
    set_has_depth_buffer(true);

    // Register our callback functions
    signal_realize().connect(sigc::mem_fun(*this, &COpenGL::onRealize));
    signal_unrealize().connect(sigc::mem_fun(*this, &COpenGL::onUnrealize), false);
    signal_render().connect(sigc::mem_fun(*this, &COpenGL::onRender), false);
}

COpenGL::~COpenGL()
{
    g_print("[~COpenGL]\r\n");
}

void COpenGL::onRealize()
{
    char   vertexPath[PATH_MAX + 100];
    char   fragmentPath[PATH_MAX + 100];
    char   modelPath[PATH_MAX + 100];

    g_print("onRealize()\r\n");

    make_current();

    // Tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // Build and compile shaders
    // -------------------------
    sprintf(vertexPath, "%s/%s", m_cwd, "resources/1.model_loading.vs");
    sprintf(fragmentPath, "%s/%s", m_cwd, "resources/1.model_loading.fs");
    m_ourShader.init(vertexPath, fragmentPath);

    // Load models
    // -----------
    sprintf(modelPath, "%s/%s", m_cwd, "resources/backpack.obj");
    
    m_ourModel.init(modelPath);

    // Draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    g_print("onRealize() - [done]\r\n");
}

void COpenGL::onUnrealize()
{
    g_print("onUnrealize()\r\n");

    make_current();

    g_print("onUnrealize() - [done]\r\n");
}

bool COpenGL::onRender(const Glib::RefPtr<Gdk::GLContext>& context)
{
    bool retVal = false;

    try
    {
        throw_if_error();

        processInput();

        // Clear the screen buffer
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Don't forget to enable shader before setting uniforms
        m_ourShader.use();

        // View/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        m_ourShader.setMat4("projection", projection);
        m_ourShader.setMat4("view", view);

        // Render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	    // it's a bit too big for our scene, so scale it down
        m_ourShader.setMat4("model", model);
        m_ourModel.Draw(m_ourShader);

        retVal = true;
    }
    catch(const Gdk::GLError& gle)
    {
        g_print("An error occurred in the render callback of the GLArea\r\n");
        g_print("%d-%d-%s\r\n", gle.domain(), gle.code(), gle.what());

        retVal = false;
    }

    return retVal;
}

void COpenGL::processInput()
{
    camera.Position.x = m_RotationAngles[X_AXIS] / 10.0;
    camera.Position.y = m_RotationAngles[Y_AXIS] / 10.0;
    camera.Position.z = m_RotationAngles[Z_AXIS] / 10.0;

    camera.updateCameraVectors();

    camera.Yaw   = m_RotationAngles[YAW];
    camera.Pitch = m_RotationAngles[PITCH];
}

