class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer (const void*, unsigned int);

	~IndexBuffer ();

	void bind () const;

	void unbind () const;

	inline unsigned int GetCount () const { return m_Count; }
};
