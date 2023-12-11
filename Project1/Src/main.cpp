#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<KHR/khrplatform.h>
#include <application.h>
int main(int argc, char* argv) {

	Application app{ "CS320 Project" , 800, 600 };

	app.Run();
	
	

	return 0;


}