#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> names;
  std::vector<int> textures;

  std::string path = "abc";

  auto add = [&textures, &names](std::string name, int texture, std::string path) mutable {
    names.push_back(path+=name);
    std::cout << "path: " << path << "\n";
    textures.push_back(texture);
  };

  auto get = [&names, &textures](std::string name) mutable -> int {
    std::cout << "name: " << name << "\n";
    for(size_t i = 0; i < names.size(); ++i) {
      if (name == names[i]) {
        return textures[i];
      }
    }

    return 0;
  };

  add("A", 1, path);
  std::cout << "path: " << path << "\n";
  add("B", 2, path);
  std::cout << "path: " << path << "\n";
  add("C", 3, path);
  std::cout << "path: " << path << "\n";

  std::cout << get("abcA") << std::endl;



  return 0;
}