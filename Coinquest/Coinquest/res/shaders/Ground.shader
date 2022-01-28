#shader vertex
#version 330 core

layout(location=0) in vec4 Position;

void main()
{
   gl_Position = Position;
};

#shader fragment
#version 330 core

layout(location=0) out vec4 colour;

void main()
{
	colour = vec4(0.3, 0.54, 0.5, 1.0);
};
