#include <stdio.h>
#include <string>
//#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
//using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "objloader.h"

std::vector<GLfloat> LoadShaders(const char * object_file_path) 
{
	std::vector<GLfloat> vertices;
	//std::vector<GLuint> dummy;

	// Read the Vertex Data from file
	std::string ObjectData;
	std::ifstream ObjectDataStream(object_file_path, std::ios::in);
	while (getline(ObjectDataStream, ObjectData))
	{
		//std::cout << ObjectData << std::endl;
		ObjectData = ObjectData.erase(0, 2);
		//std::cout << ObjectData << std::endl;

		std::string delimiter = " ";
		size_t pos = 0;
		while ((pos = ObjectData.find(delimiter)) != std::string::npos)
		{
			std::string vertex = ObjectData.substr(0, pos);
		//	std::cout << vertex << std::endl;
			ObjectData.erase(0, pos + delimiter.length());
			vertices.push_back(std::stof(vertex));
		}
		vertices.push_back(std::stof(ObjectData));
		//std::cout << ObjectData << std::endl;
	}

	//for (int i = 0; i < vertices.size(); i++)
	//{
	//	std::cout << vertices[i] << std::endl;
	//}
	
	return vertices;
	//std::cout << ObjectData << std::endl;
}