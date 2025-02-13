#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//TODO Faire un truc bien inchallah
//lalala teste voir si ça marche

int main() {
	glfwInit();

	//def la version de opengl utilisé
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//selectionne selement les modules les plus modernes (GLFW_OPENGL_COMPAT_PROFILE pour inclure les obsolètes)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(500, 500, "GameEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		//prendre en compte les actions effectué sur la fenetre
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}