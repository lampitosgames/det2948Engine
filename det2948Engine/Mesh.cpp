#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;

Mesh::Mesh() {
}

bool Mesh::bufferModel(string filepath) {
	vector<vec3> locs;
	vector<vec2> uvs;
	vector<vec3> norms;
	vector<VertInd> vertInds;

	//Open the object file
	ifstream infile(filepath);
	if (!infile.is_open()) {
		cout << "Error reading file: " << filepath << endl;
		return false;
	}

	//Loop for every line
	string line;
	while (getline(infile, line)) {
		//cout << "Line: " << line << endl;
		istringstream iss(line);
		//For each line, get a string label
		string label;
		if (!(iss >> label)) {
			//error reading file, return false
			cout << "Error reading the label: " << line << endl;
			continue;
		}
		//Line represents vertex coordinates
		if (!label.compare("v")) {
			vec3 vertex;
			if (!(iss >> vertex.x >> vertex.y >> vertex.z)) {
				cout << "Error reading line: " << line << endl;
				continue;
			}
			//DEBUG: Print the vertex location data
			//cout << vertex.x << ", " << vertex.y << ", " << vertex.z << endl;

			locs.push_back(vertex);

			//Line represents texture coordinates (uvs)
		}
		else if (!label.compare("vt")) {
			vec2 uv;
			if (!(iss >> uv.x >> uv.y)) {
				cout << "Error reading line: " << line << endl;
				continue;
			}
			//DEBUG: Print the uv data
			//cout << uv.x << ", " << uv.y << endl;

			uvs.push_back(uv);

			//Line represents normal vector
		}
		else if (!label.compare("vn")) {
			vec3 norm;
			if (!(iss >> norm.x >> norm.y >> norm.z)) {
				cout << "Error reading line: " << line << endl;
				continue;
			}
			//DEBUG: Print the normal data
			//cout << norm.x << ", " << norm.y << ", " << norm.z << endl;

			norms.push_back(norm);

			//Line represents a face
		}
		else if (!label.compare("f")) {
			//Loop three times for each of the three vertices
			for (int i = 0; i < 3; i++) {
				//Declare variables to store read data
				VertInd index;
				char slash;
				//Read data from the line, passing it to the index.  If there was an error, print to console
				if (!(iss >> index.locInd >> slash >> index.uvInd >> slash >> index.normInd)) {
					cout << "Error reading line: " << line << endl;
					continue;
				}
				//DEBUG: Print the face data
				//cout << "Index: " << index.locInd << ", " << index.uvInd << ", " << index.normInd << endl;
				
				//Decriment all values by 1 (For some stupid reason)
				index.locInd -= 1;
				index.uvInd -= 1;
				index.normInd -= 1;
				//Add the index to the list
				vertInds.push_back(index);
				//Increment vertex count
				this->vertCount += 1;
			}
		}
	}

	cout << "VertCount: " << this->vertCount << endl;

	//Create vertex buffer data
	vector<Vertex> vertBuffData(this->vertCount);
	//Get vertex buffer data from info read from the file
	for (int i = 0; i < this->vertCount; i++) {
		vertBuffData[i] = { locs[  vertInds[i].locInd],
							uvs[   vertInds[i].uvInd],
							norms[ vertInds[i].normInd] };
		//DEBUG Print the vertex
		//cout << "loc: {" << vertBuffData[i].loc.x << ", " << vertBuffData[i].loc.y << ", " << vertBuffData[i].loc.z << "}, uv: [" << vertBuffData[i].uv.x << ", " << vertBuffData[i].uv.y << "], norm: {" << vertBuffData[i].normal.x << ", " << vertBuffData[i].normal.y << ", " << vertBuffData[i].normal.z << "}" << endl;
	}
	

	//Call glGen functions.  OpenGL will create the buffers internally and give us back their indices
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);

	//Bind objects
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	//Copy our vertex data into a vertex buffer for OpenGL to use
	glBufferData(GL_ARRAY_BUFFER,						   //Where to copy to
				 sizeof(Vertex) * this->vertCount,		   //# of bytes to copy
				 &vertBuffData[0],						   //Data to send
				 GL_STATIC_DRAW);						   //How OpenGL should store the data (will it change, basically)

	//Then set the vertex attributes pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,					//Attribute index - which vertex attribute to configure. (denoted in the shader by location = 0)
						  3,					//Size of the attirbute.  {x, y, z} in this case.  
						  GL_FLOAT,				//Data type
						  GL_FALSE,				//Should we normalize the data?  If this is true, data that doesn't lie between 0 and 1 will be mapped to these values.  We don't want this since our positions are already normalized
						  sizeof(Vertex),		//Stride.  Space between consecutive vertex attribute sets.  Our data has colors, so its 6 floats away
						  (GLvoid*)0);			//Offset of where the position data begins in the buffer

	//Set uv attribute pointers
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(vec3));

	//Set normal attribute pointers
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(vec3)+sizeof(vec2)));

	//Unbind the vertex array
	glBindVertexArray(0);
	return true;
}

void Mesh::Render() {
	glBindVertexArray(this->VAO);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, this->vertCount);
	glBindVertexArray(0);
}
