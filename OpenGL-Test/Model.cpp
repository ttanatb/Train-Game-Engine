#include "Model.h"
#include <float.h>
#include <iostream>

Model::Model() { }
Model::~Model() { }

bool Model::buffer(std::string filePath, ShaderLoader* shader)
{
	// Open in binary reading mode
	std::ifstream instream(filePath, std::ios::in);

	std::vector<glm::vec3> locs;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<VertInd> vertInds;


	for (std::string line; std::getline(instream, line, '\n'); )
	{
		std::stringstream strStream(line);
		std::string mode;
		strStream >> mode;

		if (mode == "v") 
		{
			float x, y, z;
			strStream >> x >> y >> z;
			locs.push_back(glm::vec3(x, y, z));
			vertexLocs.push_back(glm::vec4(x, y, z, 1));

			if (x > maxVert.x) maxVert.x = x;
			if (y > maxVert.y) maxVert.y = y;
			if (z > maxVert.z) maxVert.z = z;

			if (x < minVert.x) minVert.x = x;
			if (y < minVert.y) minVert.y = y;
			if (z < minVert.z) minVert.z = z;

		}

		else if (mode == "vt")
		{
			float u, v;
			strStream >> u >> v;
			uvs.push_back(glm::vec2(u, v));
		}

		else if (mode == "vn") 
		{
			float x, y, z;
			strStream >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		else if (mode == "f") {
			for (int i = 0; i < 3; i++) 
			{
				unsigned int a, b, c;
				char slash;

				strStream >> a >> slash >> b >> slash >> c;
				VertInd vertInd;
				vertInd.locInd = a - 1;
				vertInd.uvInd = b - 1;
				vertInd.normInd = c - 1;

				vertInds.push_back(vertInd);
			}
		}
	}

	instream.close();

	//incomplete model, error checking
	if (locs.size() == 0 || uvs.size() == 0 || normals.size() == 0 || vertInds.size() == 0)
		return false;

	//for debugging I/O

	//debugging
	//for (int i = 0; i < locs.size(); i++) 
	//	std::cout << locs[i].x << " " << locs[i].y << " " << locs[i].z << std::endl;
	//
	//for (int i = 0; i < uvs.size(); i++) 
	//	std::cout << uvs[i].x << " " << uvs[i].y << std::endl;
	//
	//for (int i = 0; i < normals.size(); i++) 
	//	std::cout << normals[i].x << " " << normals[i].y << " " << normals[i].z << std::endl;
	//}
	//for (int i = 0; i < vertInds.size(); i++) 
	//	std::cout << vertInds[i].locInd << " " << vertInds[i].uvInd << " " << vertInds[i].normInd << std::endl

	vertCount = vertInds.size();

	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i] = { 
			locs[vertInds[i].locInd],
			uvs[vertInds[i].uvInd],
			normals[vertInds[i].normInd] 
		};
	}
	
	//test rendering the box (min and max)
	/*
	std::vector<Vertex> vertBufData(36);
	vertBufData[0] = { glm::vec3(minVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[1] = { glm::vec3(minVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[2] = { glm::vec3(minVert.x, minVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[3] = { glm::vec3(minVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[4] = { glm::vec3(minVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[5] = { glm::vec3(minVert.x, maxVert.y, minVert.z), uvs[0], normals[0] };

	vertBufData[6] = { glm::vec3(maxVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[8] = { glm::vec3(maxVert.x, minVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[7] = { glm::vec3(maxVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[9] = { glm::vec3(maxVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[10] = { glm::vec3(maxVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[11] = { glm::vec3(maxVert.x, maxVert.y, minVert.z), uvs[0], normals[0] };

	vertBufData[12] = { glm::vec3(maxVert.x, minVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[13] = { glm::vec3(minVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[14] = { glm::vec3(maxVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[15] = { glm::vec3(maxVert.x, minVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[16] = { glm::vec3(minVert.x, minVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[17] = { glm::vec3(minVert.x, minVert.y, minVert.z), uvs[0], normals[0] };

	vertBufData[18] = { glm::vec3(maxVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[19] = { glm::vec3(minVert.x, maxVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[20] = { glm::vec3(maxVert.x, maxVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[21] = { glm::vec3(maxVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[22] = { glm::vec3(minVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[23] = { glm::vec3(minVert.x, maxVert.y, minVert.z), uvs[0], normals[0] };

	vertBufData[24] = { glm::vec3(maxVert.x, maxVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[25] = { glm::vec3(minVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[26] = { glm::vec3(maxVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[27] = { glm::vec3(maxVert.x, maxVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[28] = { glm::vec3(minVert.x, maxVert.y, minVert.z), uvs[0], normals[0] };
	vertBufData[29] = { glm::vec3(minVert.x, minVert.y, minVert.z), uvs[0], normals[0] };
				
	vertBufData[30] = { glm::vec3(maxVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[31] = { glm::vec3(minVert.x, minVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[32] = { glm::vec3(maxVert.x, minVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[33] = { glm::vec3(maxVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[34] = { glm::vec3(minVert.x, maxVert.y, maxVert.z), uvs[0], normals[0] };
	vertBufData[35] = { glm::vec3(minVert.x, minVert.y, maxVert.z), uvs[0], normals[0] };
	*/

	GLuint vertBuf;

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	//'uploads' the data
	glBufferData(GL_ARRAY_BUFFER,		//the loc the copy from (from func above)
		sizeof(Vertex) * vertCount,		//#num of bytes to copy
		&vertBufData[0],				//where to copy from (the vertices)
		GL_STATIC_DRAW);				//'settings'? They're called 'hints'

	GLint posAttrib = glGetAttribLocation(*(shader->getProgram()), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	GLint uvLoc = glGetAttribLocation(*(shader->getProgram()), "uv");
	glEnableVertexAttribArray(uvLoc);
	glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	GLint normalLoc = glGetAttribLocation(*(shader->getProgram()), "normal");
	glEnableVertexAttribArray(normalLoc);
	glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(5 * sizeof(float)));

	return true;
}

void Model::render()
{
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}

void Model::unload()
{

}

const std::vector<glm::vec4>* Model::getVertexLocs()
{
	return &vertexLocs;
}

float Model::getRadius()
{
	return glm::distance(minVert, maxVert) / 2.f;
}