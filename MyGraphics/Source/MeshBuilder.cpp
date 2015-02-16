#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"
#include "LoadOBJ.h"


/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName,Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;

	std::vector<Vertex>vertex_buffer_data;
	v.pos.Set(-1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, -1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, -1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, 1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);


	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof (GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName,Color color, float lengthX, float lengthY)
{
	// An array of 3 vectors which represents 3 vertices
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f,-0.5f,0.0f);	//back btm left
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,-0.5f, 0.0f);
	v.color = color;//back btm right
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.0f);	//back top right
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f,0.0f);	//back top left
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);
	/*
	v.pos.Set(-0.5f,-0.5f, 0.5f);	//front btm left
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, 0.5f);	//front btm right
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);	//front top right
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);//front top left
	v.color = color;
	vertex_buffer_data.push_back(v);
	*/

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);

	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName,Color color, float length)
{	
	// An array of 3 vectors which represents 3 vertices
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f,-0.5f,-0.5f);	//back btm left
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,-0.5f, -0.5f);
	v.color = color;				//back btm right
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, -0.5f);	//back top right
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f,-0.5f);	//back top left
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f,-0.5f, 0.5f);	//front btm left
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, 0.5f);	//front btm right
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);	//front top right
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);//front top left
	v.color = color;
	vertex_buffer_data.push_back(v);


	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);

	index_buffer_data.push_back(5);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);

	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(2);

	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(5);

	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);

	index_buffer_data.push_back(6);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(7);

	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);

	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(7);

	index_buffer_data.push_back(4);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(0);

	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(0);

	index_buffer_data.push_back(4);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName,Color color,unsigned numSlices, float radius)
{	
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 360.0f / numSlices;

	for(unsigned slice = 0; slice < numSlices; ++slice)
	{
		float theta = slice * degreePerSlice;
		float theta2 = (slice + 1) * degreePerSlice;
		//v0
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		//v1
		v.pos.Set(0, 0, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		//v2
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta2)), 0, radius * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (unsigned index = 0; index < numSlices * 3; ++index)
	{
		index_buffer_data.push_back(index);
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName,Color color,unsigned numSlices, float outerR, float innerR)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 360.0f / numSlices;

	for(unsigned slice = 0; slice < numSlices; ++slice)
	{
		float theta = slice * degreePerSlice;
		float theta2 = (slice + 1) * degreePerSlice;
		//v0
		v.pos.Set(outerR * cos(Math::DegreeToRadian(theta)), 0, outerR * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(innerR * cos(Math::DegreeToRadian(theta)), 0, innerR * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		//v1
		v.pos.Set(outerR * cos(Math::DegreeToRadian(theta2)), 0, outerR * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(innerR * cos(Math::DegreeToRadian(theta2)), 0, innerR * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice < numSlices; ++slice)
	{
		index_buffer_data.push_back(slice * 4 + 0);
		index_buffer_data.push_back(slice * 4 + 1);
		index_buffer_data.push_back(slice * 4 + 2);

		index_buffer_data.push_back(slice * 4 + 3);
		index_buffer_data.push_back(slice * 4 + 2);
		index_buffer_data.push_back(slice * 4 + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

float sphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}

float sphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}

float sphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName,Color color,unsigned numStack, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 180.0f / numStack;
	float degreePerSlice = 360.0f / numSlices;

	for(unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		float phi = -90 + stack * degreePerStack;
		for(unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * degreePerSlice;
			//v0
			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi,theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi,theta));
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for(unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(stack * (numSlices +1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices +1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if(!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);


	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	// An array of 3 vectors which represents 3 vertices
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for(unsigned i = 0; i < numRow; ++i)
	{
		for(unsigned j = 0; j < numCol; ++j)
		{
			//Task: Add 4 vertices into vertex_buffer_data
			v.pos.Set(-0.5f,-0.5f, 0.0f);	//back btm left
			v.texCoord.Set(j * width, 1.f - height - i * height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f,-0.5f, 0.0f);
			v.texCoord.Set(j * width + width,1.f - height -  i * height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f, 0.0f);	//back top right
			v.texCoord.Set(j * width + width, 1.f - height - i * height + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f,0.0f);	//back top left
			v.texCoord.Set(j * width, 1.f - height - i * height + height);
			vertex_buffer_data.push_back(v);

			//Task: Add 6 indices into index_buffer_data
			index_buffer_data.push_back(offset + 3);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);

			offset = offset + 4;
		}
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateTopPart(const std::string &meshName,Color color,unsigned numSlices, float radius)
{	
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 140.0f / numSlices;

	for(unsigned slice = 0; slice < numSlices; ++slice)
	{
		float theta = slice * degreePerSlice;
		float theta2 = (slice + 1) * degreePerSlice;
		//v0
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		//v1
		v.pos.Set(0, 0, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		//v2
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta2)), 0, radius * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (unsigned index = 0; index < numSlices * 3; ++index)
	{
		index_buffer_data.push_back(index);
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
/******************************************************************************/
/*!
\brief
Generate the vertices for the btm part of MetaKnight's mask
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color - color of object
\param numSlices - number of slices for object
\param radius - radius of object

\return Pointer to mesh storing VBO/IBO of btm part
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateBtmPart(const std::string &meshName,Color color,unsigned numSlices, float radius)
{	
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 200.0f / numSlices;

	for(unsigned slice = 0; slice < numSlices; ++slice)
	{
		float theta = slice * degreePerSlice;
		float theta2 = (slice + 1) * degreePerSlice;
		//v0
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		//v1
		v.pos.Set(0, 0, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		//v2
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta2)), 0, radius * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (unsigned index = 0; index < numSlices * 3; ++index)
	{
		index_buffer_data.push_back(index);
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

float cylinderX(float theta)
{
	return cos(Math::DegreeToRadian(theta));
}

float cylinderZ(float theta) 
{
	return sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius, float height)
{
	float stackHeight = height / numStack;
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;
	for(unsigned stack = 0; stack < numStack + 1; ++ stack)
	{
		float phi = -90 + stack * degreePerStack;
		for(unsigned slice = 0; slice < numSlice + 1; slice ++)
		{//height / 2 + stack  * stackHeight -height / 2 + (stack + 1) * stackHeight
			float theta = slice * degreePerSlice;
			v.pos.Set(radius * cylinderX(theta), height / 2 + stack * stackHeight, radius * cylinderZ(theta));
			v.color = color;
			v.normal.Set( cylinderX(theta), 0,  cylinderZ(theta));
			v.pos.Set(radius * cylinderX(theta), -height / 2 + stack * stackHeight, radius * cylinderZ(theta));

			v.pos.Set(radius * cylinderX(theta), -height / 2 + (stack + 1) * stackHeight, radius * cylinderZ(theta));
			v.color = color;
			v.normal.Set( cylinderX(theta), 0,  cylinderZ(theta));
			v.pos.Set(radius * cylinderX(theta), -height / 2 + (stack + 1) * stackHeight, radius * cylinderZ(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for(unsigned stack = 0; stack < numStack; ++stack) 
	{
		for(unsigned slice = 0; slice < numSlice + 1; ++slice) 
		{
			index_buffer_data.push_back(stack * (numSlice + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlice + 1) + slice);
		}
	}
	Mesh *mesh = new Mesh(meshName);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	return mesh;
}

Mesh* MeshBuilder::GenerateHemiSphere(const std::string &meshName,Color color,unsigned numStack, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 180.0f / numStack;
	float degreePerSlice = 180.0f / numSlices;

	for(unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		float phi = -90 + stack * degreePerStack;
		for(unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * degreePerSlice;
			//v0
			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi,theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi,theta));
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for(unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(stack * (numSlices +1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices +1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius, float height)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float degreePerStack = 90.0f / numStack;
	float degreePerSlice = 180.0f / numSlice;
	float stackHeight = height / numStack;
	for(unsigned slice = 0; slice < 370; slice+=10)
	{
		v.pos.Set(radius*cylinderX(slice), -height/2, radius* cylinderZ(slice));
		v.color = color;
		v.normal.Set(radius*cylinderX(slice), -height/2, radius* cylinderZ(slice));
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, height/2, 0);
		v.color = color;
		v.normal.Set(0, height/2, 0);
		vertex_buffer_data.push_back(v);
	}

	for(unsigned slice = 0; slice < 180; slice+=30)
	{

		v.pos.Set(0, -height/2, 0);
		v.color = color;
		v.normal.Set(0, height/2, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(radius*cylinderX(slice), -height/2, radius* cylinderZ(slice));
		v.color = color;
		v.normal.Set(radius*cylinderX(slice), -height/2, radius* cylinderZ(slice));
		vertex_buffer_data.push_back(v);
	}

	for ( unsigned slice = 0; slice < numSlice+1; ++slice)
	{
		index_buffer_data.push_back(slice * 3 + 0);
		index_buffer_data.push_back(slice * 3 + 1);
		index_buffer_data.push_back(slice * 3 + 2);
	}


	Mesh *mesh = new Mesh(meshName);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color, float ringRadius, float distRadius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	for(float theta = 0; theta <= 360; theta += 10)
	{
		for(float phi = 0; phi <= 360; phi += 10)
		{
			float radtheta = Math::DegreeToRadian(theta);
			float radphi = Math::DegreeToRadian(phi);
			float radthetaIn = Math::DegreeToRadian(theta + 10);

			v.pos.Set((distRadius  + ringRadius * cos(radthetaIn)) * cos(radphi), (distRadius + ringRadius * cos(radthetaIn)) * sin(radphi), ringRadius * sin(radthetaIn));
			v.color = color;
			v.normal.Set((ringRadius * cos(radthetaIn)) * cos(radphi), (ringRadius * cos(radthetaIn)) * sin(radphi),  ringRadius * sin(radthetaIn));
			vertex_buffer_data.push_back(v);

			v.pos.Set((distRadius  + ringRadius * cos(radtheta)) * cos(radphi), (distRadius + ringRadius * cos(radtheta)) * sin(radphi), ringRadius * sin(radtheta));
			v.color = color;
			v.normal.Set((ringRadius * cos(radtheta)) * cos(radphi), (ringRadius * cos(radtheta)) * sin(radphi),  ringRadius * sin(radtheta));
			vertex_buffer_data.push_back(v);
		}
	}
	
	for(int index = 0; index < vertex_buffer_data.size(); index++)
	{
		index_buffer_data.push_back(index);
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateMask(const std::string &meshName, Color color, float ringRadius, float distRadius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	for(float theta = 0; theta <= 360; theta += 10)
	{
		for(float phi = 0; phi <= 360; phi += 10)
		{
			float radtheta = Math::DegreeToRadian(theta);
			float radphi = Math::DegreeToRadian(phi);
			float radthetaIn = Math::DegreeToRadian(theta + 10);

			v.pos.Set((distRadius *+ ringRadius * cos(radthetaIn)) * cos(radphi), (distRadius *+ ringRadius * cos(radthetaIn)) * sin(radphi), ringRadius * sin(radthetaIn));
			v.color = color;
			v.normal.Set((ringRadius * cos(radthetaIn)) * cos(radphi), (ringRadius * cos(radthetaIn)) * sin(radphi),  ringRadius * sin(radthetaIn));
			vertex_buffer_data.push_back(v);

			v.pos.Set((distRadius  *+ ringRadius * cos(radtheta)) * cos(radphi), (distRadius *+ ringRadius * cos(radtheta)) * sin(radphi), ringRadius * sin(radtheta));
			v.color = color;
			v.normal.Set((ringRadius * cos(radtheta)) * cos(radphi), (ringRadius * cos(radtheta)) * sin(radphi),  ringRadius * sin(radtheta));
			vertex_buffer_data.push_back(v);
		}
	}
	
	for(int index = 0; index < 370; index++)
	{
		index_buffer_data.push_back(index);
	}

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
