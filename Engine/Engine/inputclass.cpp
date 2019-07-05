#include "inputclass.h"



InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass &)
{
}


InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	int i = 0;
	for (i= 0;i < 256;i++)
	{
		m_keys[i] = false;
	}
}

void InputClass::KeyDown(unsigned int key)
{
	m_keys[key] = true;
}

void InputClass::KeyUp(unsigned int key)
{
	m_keys[key] = false;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}
