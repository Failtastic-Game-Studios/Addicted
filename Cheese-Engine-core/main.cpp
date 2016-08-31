#include "src\graphics\window.h"
#include "src\maths\vec2.h"

int main()
{
	using namespace cheese;
	using namespace graphics;
	using namespace maths;

	Window window("Cheese!", 1920, 1080);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vec2 a(1.0f, 2.0f);
	vec2 b(1.0f, 2.0f);

	std::cout << (a!=b) << std::endl;
	while (!window.closed())
	{
		window.clear();


		glBegin(GL_QUADS);
		glVertex2f(-0.1f, -0.1f);
		glVertex2f(-0.1f, 0.1f);
		glVertex2f(0.1f, 0.1f);
		glVertex2f(0.1f, -0.1f);
		glEnd();
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
		window.update();
	}

	return 0;
}