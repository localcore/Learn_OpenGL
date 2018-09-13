class VertexBuffer {
private:
	unsigned int m_RendererID;
public:
	VertexBuffer (const void*, unsigned int);

	~VertexBuffer ();

	void bind () const;

	void unbind () const;
};
