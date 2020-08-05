class TextureManager
{
public:
	static void StaticInit();

	static std::unique_ptr< TextureManager >		sInstance;

	TexturePtr	GetTexture(const string& inTextureName);

private:
	TextureManager();

	//bool CacheTexture(string inName, const char* inFileName);
	bool CacheTexture(string inName, const char* inFileName, uint32_t inDistX, uint32_t inDistY);

	unordered_map< string, TexturePtr >	mNameToTextureMap;
};