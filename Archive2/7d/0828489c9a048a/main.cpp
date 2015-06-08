
#include <iostream>
#include <vector>

struct vec2 {
    vec2(float x, float y) :
			x(x), y(y) {
	}

	float x, y;
};

struct vec3 {
	vec3(float x, float y, float z) :
			x(x), y(y), z(z) {
	}

	float x, y, z;
};

struct vec4 {
	vec4(float x, float y, float z, float w) :
			x(x), y(y), z(z), w(w) {
	}

	float x, y, z, w;
};

struct DataHolder {

	template<typename T = float>
	std::vector<T> dataAs();

	std::vector<float> data;

};

template<typename T>
std::vector<T> DataHolder::dataAs() {

	std::vector<T> result;
	for (unsigned int i = 0; i < data.size(); i++) {
		result.push_back(static_cast<T>(data[i]));
	}
	return result;
}

template<>
std::vector<float> DataHolder::dataAs<float>() {
	return data;
}

template<>
std::vector<vec2> DataHolder::dataAs<vec2>() {
	std::vector<vec2> result;
	for (unsigned int i = 0; i < data.size(); i += 2) {
		result.emplace_back(data[i], data[i + 1]);
	}
	return result;
}

template<>
std::vector<vec3> DataHolder::dataAs<vec3>() {
	std::vector<vec3> result;
	for (unsigned int i = 0; i < data.size(); i += 3) {
		result.emplace_back(data[i], data[i + 1], data[i + 2]);
	}
	return result;
}

template<>
std::vector<vec4> DataHolder::dataAs<vec4>() {
	std::vector<vec4> result;
	for (unsigned int i = 0; i < data.size(); i += 4) {
		result.emplace_back(data[i], data[i + 1], data[i + 2],
				data[i + 3]);
	}
	return result;
}

int main() {

	DataHolder dh;

	for (int i = 0; i < 12; ++i) {
		dh.data.push_back(float(i)/2.0);
	}

	auto df = dh.dataAs();
	auto dd = dh.dataAs<double>();
	auto di = dh.dataAs<int>();
	auto dv2 = dh.dataAs<vec2>();
	auto dv3 = dh.dataAs<vec3>();
	auto dv4 = dh.dataAs<vec4>();

	std::cout << "Floats" << std::endl;
	for (unsigned int i = 0; i < df.size(); ++i) {
		std::cout << df[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Double" << std::endl;
	for (unsigned int i = 0; i < dd.size(); ++i) {
		std::cout << dd[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Int" << std::endl;
	for (unsigned int i = 0; i < di.size(); ++i) {
		std::cout << di[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Vec2" << std::endl;
	for (unsigned int i = 0; i < dv2.size(); ++i) {
		std::cout << "["<<dv2[i].x << " " << dv2[i].y << "] ";
	}
	std::cout << std::endl;
	std::cout << "Vec3" << std::endl;
	for (unsigned int i = 0; i < dv3.size(); ++i) {
		std::cout << "["<<dv3[i].x << " " << dv3[i].y << " " << dv3[i].z <<  "] ";
	}
	std::cout << std::endl;
	std::cout << "Vec4" << std::endl;
	for (unsigned int i = 0; i < dv4.size(); ++i) {
		std::cout << "["<<dv4[i].x << " " << dv4[i].y << " " << dv4[i].z <<" " << dv4[i].w<<  "] ";
	}
	std::cout << std::endl;



	return 0;
}
