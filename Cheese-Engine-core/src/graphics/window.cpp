#include "window.h"

namespace cheese { namespace graphics {

		
	bool Window::m_Keys[MAX_KEYS];
	bool Window::m_MouseButtons[MAX_BUTTONS];
	double Window::mx;
	double Window::my;

	void window_resize(GLFWwindow *window, int width, int height);

#pragma region Window::Window
	Window::Window(const char *title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init())
			glfwTerminate();

		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
		}
		for (int n = 0; n < MAX_KEYS; n++)
		{
			m_Keys[n] = false;
		}

	}
#pragma endregion Window::Window
#pragma region Window::~Window
	Window::~Window()
	{
		glfwTerminate();
	}
#pragma endregion Window::~Window
#pragma region Window::init
	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			return false;
		}
		
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize);


		if (glewInit() != GLEW_OK)
		{
			std::cout << "Could not initialize GLEW!" << std::endl;
			return false;
		}

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		return true;
	}
#pragma endregion Window::init
#pragma region isKeyPressed
	bool Window::isKeyPressed(unsigned int keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;
		//log error
		return m_Keys[keycode];
	}
#pragma endregion isKeyPressed
#pragma region clear
	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
#pragma endregion clear
#pragma region update
	void Window::update()
	{
		glfwPollEvents();
//		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glfwSwapBuffers(m_Window);
	}
#pragma endregion update
#pragma region closed
	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}
#pragma endregion closed
#pragma region window_resize
	void window_resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
#pragma endregion windowResize
#pragma region key_callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}
#pragma endregion key_callback

} }