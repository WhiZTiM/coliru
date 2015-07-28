#include <iostream>
#include <unordered_map>

// usual pattern any C library that has callbacks
typedef void (*callback)(int id, void* userdata);

std::unordered_map<int, std::pair<callback, void*>> callbacks;

void register_callback(int id, callback c, void* userdata)
{
    callbacks.emplace(id, std::make_pair(c, userdata));
}

void call(int id)
{
    auto& whatever = callbacks.at(id);
    whatever.first(id, whatever.second);
}

void my_callback(int id, void* userdata)
{
    // this function warns on -Wextra
    // parameter `userdata` is required to be here, I can't remove it entirely
    std::cout << id << "\n";
}

void my_callback_2(int id, void*)
{
    // avoid warning by not naming the parameter
    std::cout << id << "\n";
}

void my_callback_3(int id, void* userdata)
{
   // avoid warning by explicitly ignoring the parameter
   static_cast<void>(userdata);
   std::cout << id << "\n";
}

int main()
{
    register_callback(42, my_callback, nullptr);
    register_callback(666, my_callback_2, nullptr);
    register_callback(1337, my_callback_3, nullptr);
    call(42);
    call(666);
    call(1337);
}