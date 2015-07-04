#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> names;
  std::vector<int> textures;

  std::string path = "abc";

  auto add = [&, names, textures, path](std::string name, int texture) mutable {
    names.push_back(path+=name);
    textures.push_back(texture);
  };

  auto del = [&, names, textures, path](std::string name) mutable -> bool {
    for(size_t i = 0; i < names.size(); ++i) {
      std::cout << names[i];

      if (std::string(path).append(name) == names[i]) {
        
        std::swap(names[i], names.back());
        names.pop_back();
        std::swap(textures[i], textures.back());
        textures.pop_back();
        return true;
      }
    }

    return false;
  };

  auto get = [&, names, textures, path](std::string name) mutable -> int {
    for(size_t i = 0; i < names.size(); ++i) {
      if ((path+=name) == names[i]) {
        return textures[i];
      }
    }

    return 0;
  };

  add("A", 1);
  add("B", 2);
  add("C", 3);

  std::cout << get("abcA") << std::endl;



  return 0;
}