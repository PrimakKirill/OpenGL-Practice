#shader vertex
#version 330 core
layout(location = 0) in vec3 position; // ������������� ������� �������� � 0
layout(location = 1) in vec2 voord;

out vec4 vertexColor; // �������� ���� �� ����������� ������

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * /*position;*/ vec4(position, 1.0); // �������� �������� vec3 � vec4
	vertexColor = vec4(2 * position.x, 2 * position.y , 2 * position.z, 1.0f); // ������������� �������� �������� ���������� � �����-������� ����.
}

#shader fragment
#version 330 core
in vec4 vertexColor; // ������� ���������� �� ���������� ������� (�� �� �������� � ��� �� ���)

out vec4 color;

void main()
{
	color = vertexColor;
}