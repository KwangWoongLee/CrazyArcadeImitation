class Texture
{
public:
	Texture(uint32_t inWidth, uint32_t inHeight, SDL_Texture* inTexture);
	~Texture();

	void	SetDist(uint32_t inDistX, uint32_t inDistY)
	{
		mDistX = inDistX;
		mDistY = inDistY;
	};
	uint32_t	GetDistX()	const { return mDistX; }
	uint32_t	GetDistY()	const { return mDistY; }
	uint32_t	GetWidth()	const { return mWidth; }
	uint32_t	GetHeight()	const { return mHeight; }
	SDL_Texture* GetData() const { return mTexture; }

private:
	uint32_t		mDistX;
	uint32_t		mDistY;
	uint32_t		mWidth;
	uint32_t		mHeight;
	SDL_Texture* mTexture;
};


typedef shared_ptr< Texture >	TexturePtr;