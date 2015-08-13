    std::streampos fsize = 0;
	fsize = f.tellg();
	f.seekg(0, 2);
	DWORD pDataLength = f.tellg() - fsize;
	f.seekg(0, 0);
	BYTE * data = new BYTE[pDataLength];
	f >> std::noskipws;
	f.read((char*)data, pDataLength);