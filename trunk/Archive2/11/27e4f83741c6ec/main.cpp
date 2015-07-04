#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> names;
  std::vector<int> textures;

  std::string path = "abc";

  auto add = [path, &textures, &names](std::string name, int texture) mutable {
    names.push_back(path+=name);
    std::cout << "path: " << path << "\n";
    textures.push_back(texture);
  };

  auto get = [path, &names, &textures](std::string name) mutable -> int {
    path+=name;
    std::cout << "path: " << path << "\n";
    for(size_t i = 0; i < names.size(); ++i) {
      if (path == names[i]) {
        return textures[i];
      }
    }

    return 0;
  };

  add("A", 1);
  std::cout << "path: " << path << "\n";
  add("B", 2);
  std::cout << "path: " << path << "\n";
  add("C", 3);
  std::cout << "path: " << path << "\n";

  std::cout << get("abcA") << std::endl;



  return 0;
}