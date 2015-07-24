{
	std::vector<glm::vec3> vertices;
	std::cout << "image size: [" << img.width << "x" << img.height << "]\n";
	vertices.resize(img.width * img.height);
	for(int y = 0; y < img.height; y++) {
		for(int x = 0; x < img.width; x++) {
			vertices[x + y * img.width] = glm::vec3(static_cast<float>(x) - static_cast<float>(img.width) / 2.0f, static_cast<float>(img.bitmap[x + y * img.width]) * 0.3, static_cast<float>(y) - static_cast<float>(img.height) / 2.0f);
		}
	}
	auto vbuf = vbuffer.bind();
	vbuf.data(vertices.size() * sizeof(float) * 3, vertices.data());
}
{
	std::vector<unsigned short> indices;
	int row_length = 2 * img.width + 2;
	indices.resize(img.height * row_length);
	
	for (int y = 0; y < img.height; y++) {
		for (int x = 0; x <= img.width; x++) {
			indices[y * row_length + x * 2] =     y * img.height + x;
			indices[y * row_length + x * 2 + 1] = y * img.height + x + img.height;
		}
		// Degenerate strip
		if (y != img.height - 1) {
			indices[y * row_length + img.width * 2 + 2] = y * img.height + img.width - 1;
			indices[y * row_length + img.width * 2 + 3] = y * img.height + img.width * 2 - 1;
		}
	};
	auto ebuf = ebuffer.bind();
	ebuf.data(indices.size() * sizeof(decltype(indices)::value_type), indices.data());
};