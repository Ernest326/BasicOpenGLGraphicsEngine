#pragma once

#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <string>
#include "file_utils.h"
#include "Mat4.h"
#include "Vectors.h"

class Shader
{
private:

	GLuint m_shaderID;
	const char *m_vertPath, *m_fragPath;

public:

	Shader(const char* vertPath, const char* fragPath);
	Shader() {};
	~Shader();

	void enable() const;
	void disable() const;

	GLuint shaderProgram() { return m_shaderID; }

private:

	GLuint load();

public:

	void SetMatrix4(char* location, Mat4 &value) const;
	void SetVector3f(char* location, Vector3 &value) const;
	void SetFloat(std::string &location, float value) const;
	void SetFloat(char* location, float value) const;
	void SetInt(char* location, int value) const;
	void SetBool(char* location, bool value) const;


};

