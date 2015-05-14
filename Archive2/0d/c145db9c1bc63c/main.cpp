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
			Type* X = LambdaAlloc();

			if (!RamLoadHelper(child, X, failMessage))
			{
				LambdaDelete();
				continue;
			}

			AssetPtr ptr(t);
			textures.push_back(ptr);
		}

		m_assets[X->GetType()] = assets;
	}