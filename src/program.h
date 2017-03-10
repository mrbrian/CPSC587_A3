#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "ShaderTools.h"
#include "Vec3f.h"
#include "Mat4f.h"
#include "OpenGLMatrixTools.h"
#include "Camera.h"

class Program
{
	int g_play_speed = 1;

	// Drawing Program
	GLuint basicProgramID;

	// Data needed for Quad
	GLuint vaoID;
	GLuint vertBufferID;
	GLuint normBufferID;
	Mat4f M;

	// Data needed for Quad
	GLuint quad_vaoID;
	GLuint quad_vertBufferID;
	GLuint quad_normBufferID;
	Mat4f quad_M;

	// Only one camera so only one veiw and perspective matrix are needed.
	Mat4f V;
	Mat4f P;

	// Only one thing is rendered at a time, so only need one MVP
	// When drawing different objects, update M and MVP = M * V * P
	Mat4f MVP;

	// Camera and veiwing Stuff
	Camera camera;
	bool g_carView = false;
	int g_moveUpDown = 0;
	int g_moveLeftRight = 0;
	int g_moveBackForward = 0;
	int g_rotateLeftRight = 0;
	int g_rotateUpDown = 0;
	int g_rotateRoll = 0;
	float g_rotationSpeed = 0.015625;
	float g_panningSpeed = 0.25;
	bool g_cursorLocked;
	float g_cursorX, g_cursorY;

	bool g_play = false;

	int WIN_WIDTH = 800, WIN_HEIGHT = 600;
	int FB_WIDTH = 800, FB_HEIGHT = 600;
	float WIN_FOV = 60;
	float WIN_NEAR = 0.01;
	float WIN_FAR = 1000;

	//==================== FUNCTION DECLARATIONS ====================//
	void displayFunc();
	void resizeFunc();
	void init();
	void generateIDs();
	void deleteIDs();
	void setupVAO();
	void loadQuadGeometryToGPU();
	void reloadProjectionMatrix();
	void loadModelViewMatrix();
	void setupModelViewProjectionTransform();

	void reloadViewMatrix();
	void moveCamera();
	void reloadMVPUniform();
	void reloadColorUniform(float r, float g, float b);
	std::string GL_ERROR();
	int main(int, char **);
};

void windowSetSizeFunc();
void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
	int mods);
void windowSetSizeFunc(GLFWwindow *window, int width, int height);
void windowSetFramebufferSizeFunc(GLFWwindow *window, int width, int height);
void windowMouseButtonFunc(GLFWwindow *window, int button, int action,
	int mods);
static void windowMouseMotionFunc(GLFWwindow *window, double x, double y);
