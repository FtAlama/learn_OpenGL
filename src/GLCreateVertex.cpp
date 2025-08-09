#include "Application.hpp"

void	GLElementVertexRectangle()
{
	unsigned int vao;
	unsigned int	buff;
	unsigned int	ibo;	//index_buffer_object
	float				positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};
	unsigned int	indice[] = {
		0,1,2,
		2,3,0
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &buff);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
	glGenBuffers(2, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indice, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);
}

vertex_draw	GLTwoTriangle()
{
	vertex_draw vd;
	float					firstTriangle[] = {
			-0.5f, -0.5f, 0.0f, 
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
    };
    float				secondTriangle[] = {
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f, 
    };

	glGenVertexArrays(2, vd.vao);
	glGenBuffers(2, vd.vbo);

	glBindVertexArray(vd.vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vd.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vd.vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vd.vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);

	return (vd);
}
