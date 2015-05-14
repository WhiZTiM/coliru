    template <class Type, typename LambdaAlloc, typename LambdaDelete>
	void LoadAssets(XMLElement* assetsInXml,
				    const char* failMessage,
				    LambdaAlloc allocator,
				    LambdaDelete destructor)
	{
		Assets assets;

		for (XMLElement* child = elem->FirstChildElement();
			child;
			child = child->NextSiblingElement())
		{
			Type* X = allocator();

			if (!RamLoadHelper(child, X, failMessage))
			{
				destructor();
				continue;
			}

			AssetPtr ptr(t);
			textures.push_back(ptr);
		}

		m_assets[X->GetType()] = assets;
	}
    
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// Then I want to call it like this

    	if(tag == "Models") 
		{
			auto allocator = []() { return new Model; };
			auto destructor = [](Model* m) { delete m; };
			LoadAssets<Model>(elem, "Model", std::bind(allocator), std::bind(destructor));
			Log("Loaded models.");
		} 
		else if(tag == "Textures2D") 
		{
			auto allocator = []() { return AssetFactory::CreateTexture(GLDriver, Texture::d2D); };
			auto destructor = [](Texture* t) { return AssetFactory::DeleteTexture(GLDriver, t); };
			LoadAssets<Texture>(elem, "Texture", std::bind(allocator), std::bind(destructor));
			Log("Loaded 2D Textures.");
		} 