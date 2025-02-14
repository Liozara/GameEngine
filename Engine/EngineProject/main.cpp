#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//vertex shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//fragment sahder source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";



int main() {
	glfwInit();

	//def la version de opengl utilisé
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//selectionne selement les modules les plus modernes (GLFW_OPENGL_COMPAT_PROFILE pour inclure les obsolètes)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat points[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	GLFWwindow* window = glfwCreateWindow(500, 500, "GameEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	//def la portée de gl sur la fenetre bottom left -> top right
	glViewport(0, 0, 500, 500);

	//create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//give it source code
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile source code
	glCompileShader(vertexShader);

	//same as vertexshader but for fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//create a program to use shaders
	GLuint shaderProg = glCreateProgram();
	//attach shaders to prog
	glAttachShader(shaderProg, vertexShader);
	glAttachShader(shaderProg, fragmentShader);
	glLinkProgram(shaderProg);

	//delete shaders because they are in prog
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VAO = vertex array object (pointers to VBOs to quickly switch of VBO) [had to be gen before and delete after all VBOs]
	// VBO = vertex buffer object (buffer = gros paquet de données)
	GLuint VAO, VBO;

	//first argu are number of 3d object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//set current working vertex
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//fourth argu : GL
	//				  _STREAM=modify one and use many times
	//				  _STATIC=modify one and use many many times
	//				  _DYNAMIC=modify multiple times and use many many times
	//						  _DRAW
	//						  _READ
	//						  _COPY
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//first argu : index of this attribute
	//second argu : nbr of data per vertex
	//third argu : type of data
	//fourth argu : only if data are int
	//fifth argu : size of one vertex
	//sixth argu : where start array (void*)0 = beginning
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	//enable attributes with index argu
	glEnableVertexAttribArray(0);

	//reset current working vertex
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//set color on back buffer
	glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//swap back and front buffer
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProg);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		//prendre en compte les actions effectué sur la fenetre
		glfwPollEvents();
	}

	//delete to clear data after execution
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProg);

	glfwTerminate();
	return 0;
}