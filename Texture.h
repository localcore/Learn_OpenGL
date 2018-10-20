#pragma once

#include <iostream>

class Texture {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture (const std::string&);

	~Texture ();

	void bind (unsigned int slot) const;

	void unbind () const;

	inline int getWidth () const { return m_Width; };

	inline int getHeight () const { return m_Height; };
};