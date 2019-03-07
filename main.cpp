#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>
#include <dear-imgui/imgui.h>

int main(int argc, char** argv)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello bgfx!", nullptr, nullptr);
    bgfx::init();
    return 0;
}
