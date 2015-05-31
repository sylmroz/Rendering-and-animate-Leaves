#include <iostream>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include "interpolations.h"
#include "mat.h"
#include "OBJLoader.h"
#include "transform.h"
float deCasteliau(std::vector<float> p,float t);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "my window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == nullptr)
		std::cout << "windows ups";
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW ups\n";
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	char *version = nullptr;
	char *shaderversion = nullptr;
	version = (char*)glGetString(GL_VERSION);
	shaderversion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << version << std::endl << shaderversion << std::endl;
	//GLuint sh = shader::LoadShader(GL_VERTEX_SHADER, "./res/basicshader.vs");
	GLuint program;
	//shader::AttachShader(program, sh);
	shader::AttachFragmentShader(program, "./res/lights.glsl");
	shader::AttachVertexShader(program, "./res/blinphong.vs");
	shader::AttachFragmentShader(program, "./res/blinphong.fs");
	shader::LinkProgram(program);
	

	//std::vector<float> point{ 0.9f,-0.8f,-0.4f, 0.9f, -0.9f};
	//std::vector<float> pointd{ -0.9f, -0.8f, -0.4f, 0.9f, 0.9f };
	//std::vector<float> point2{ -1.0f, -0.5f,0.0f, 0.8f, 1.0f };
	
	//GLuint MVP = glGetUniformLocation(program, "MVP");
	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), 45.0f, 0.01f, 100.0, 800 / 600);
	float rotate = 0.0f;
	
	//std::vector<glm::vec3> p;
	//MatLoader mat("./res/materal.mat");
	Mesh obj("./res/uchati.obj");
	
	//OBJLoader object("./res/teapot.obj");
	/*Interpolations *inter=new Langrage;
	Hermite H;
	H.SetX(point2);
	H.SetY(point);
	H.SetYprim(pointd);
	Langrage L;
	L.SetX(point2);
	L.SetY(point);
	DeCasteliau DE;
	DE.SetY(point);
	DeCasteliau DE2;
	DE2.SetY(point2);
	inter = &H;
	for (float i = -1; i <= 1; i += 0.01f)
		p.push_back(glm::vec3(i, inter->Calculate(i), 0.0));
	Mesh des(p);
	std::vector<glm::vec3> punkty;
	for (int i = 0; i < point.size(); ++i)
	{
		glm::vec3 temp(point2[i], point[i], 0.0f);
		punkty.push_back(temp);
	}
	Mesh pak(punkty);

	GLfloat clipPlaneRight[4] =
	{
		0.5f, 0.5f, 0.0f, 0.0f
	};

	GLfloat clipPlaneLeft[4] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f
	};

	GLfloat cLRed[4] =
	{
		0.9f, 0.1f, 0.1f, 1.0f
	};
	GLfloat cLBlue[4] =
	{
		0.1f, 0.1f, 0.9f, 1.0f
	};

	std::vector<glm::vec3> posit{ 
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f)
	};
	Mesh cube(posit);
	glEnable(GL_CLIP_DISTANCE0);*/
	glBindAttribLocation(program, 0, "positions");
	glBindAttribLocation(program, 1, "normals");
	Transform transform;
	transform.SetScale(glm::vec3(0.5f,0.5f,0.5f));
	//glm::vec4 LightPosition(0.0, 0.0, 5.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		//camera.Rotate(-0.1f, 0.0f);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		transform.SetRot(glm::vec3(rotate, rotate, rotate));
		//transform.SetPos(glm::vec3(-rotate+3, 0, 0));
		glUseProgram(program);
		glm::mat4 v =camera.GetVievMatrix();
		glm::mat4 P = camera.GetProjectionMatrix();
		glm::mat4 m = transform.GetModel();
		glm::mat4 mvp = P*v*m;
		glm::vec4 Eye = camera.GetEye();
		glm::mat3 modelView3x3 = glm::mat3(v)*glm::mat3(m);
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(modelView3x3));
		glm::mat4 mvinv = glm::inverse(v*m);
		//Eye = mvinv*Eye;
		glm::vec4 LightPosition = glm::vec4(6.0f, 6.0f, 6.0f,0.0f);
		//LightPosition = mvinv*LightPosition;
		//LightPosition = glm::normalize(LightPosition);

		glUniformMatrix4fv(glGetUniformLocation(program, "M"), 1, GL_FALSE, &m[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "V"), 1, GL_FALSE, &v[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "P"), 1, GL_FALSE, &P[0][0]);
		glUniformMatrix3fv(glGetUniformLocation(program, "normalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
		glUniform4fv(glGetUniformLocation(program, "Eye"), 1, &Eye[0]);
		glUniform4fv(glGetUniformLocation(program, "Light[0].position"), 1, &LightPosition[0]);
		//glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, &LightPosition[0]);
		//glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);
		/*glUniform4fv(glGetUniformLocation(program, "clipPlane[0]"), 1, clipPlaneLeft);
		glUniform4fv(glGetUniformLocation(program, "inColor"), 1, cLRed);
		//obj.DrawObject();
		cube.DrawLine(2);
		des.DrawLineStrip(2);
		pak.DrawPoints(10);
		glUniform4fv(glGetUniformLocation(program, "clipPlane[0]"), 1, clipPlaneRight);
		glUniform4fv(glGetUniformLocation(program, "inColor"), 1, cLBlue);
		obj.DrawObject();
		//cube.DrawLine(2);
		//des.DrawLineStrip(2);
		//pak.DrawPoints(10);*/
		obj.DrawObject();
		glUseProgram(0);
		
		
		glfwSwapBuffers(window);
		rotate += 0.01f;

	}
	shader::DeleteShader(program);
	glfwTerminate();
	return 0;
}

float deCasteliau(std::vector<float> p,float t)
{
	std::vector<float> ptemp=p;
	for (int j = 1; j < p.size(); ++j)
		for (int i = 0; i < p.size() - j; ++i)
			p[i] = (1 - t)*p[i] + t*p[i + 1];
	return p[0];
}