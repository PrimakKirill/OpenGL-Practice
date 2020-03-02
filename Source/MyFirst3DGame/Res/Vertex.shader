#version 330 core
layout(location = 0) in vec4 position; // ������������� ������� �������� � 0

out vec4 vertexColor; // �������� ���� �� ����������� ������

void main()
{
	gl_Position = position;// vec4(position, 1.0); // �������� �������� vec3 � vec4
	vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f); // ������������� �������� �������� ���������� � �����-������� ����.
}