    #include <vector>
    #include <unordered_set>
    #include <chrono>
    #include <algorithm>
    #include <iostream>
     
    int main()
    {
      long count1, count2;
      {
        std::vector<int> v;
        std::default_random_engine e;
        std::uniform_int_distribution<int> d(1, 100);
        for (int i = 0; i < 20; ++i)
          v.push_back(d(e));
        size_t cnt1{0};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 4000000; ++i)
        {
          int x = d(e);
          auto pos = std::find(v.begin(), v.end(), x);
          if (pos != v.end())
          {
          //  v.erase(v.begin());
          //  v.push_back(x);
           cnt1++;
          }
        }
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "cnt1 " << cnt1 << std::endl;
     
        count1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
      }
     
    {
        std::unordered_set<int> u;
        std::default_random_engine e;
        std::uniform_int_distribution<int> d(1, 100);
        for (int i = 0; i < 20; ++i)
          u.insert(d(e));
        size_t cnt2{0};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 4000000; ++i)
        {
          int x = d(e);
          if (u.count(x))
          //if (std::find(u.begin(), u.end(), x) !=u.end())
          {
            //u.erase(u.begin());
            //u.insert(x);
            cnt2++;
          }
        }
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "cnt2 " << cnt2<< std::endl;
        
        count2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
      }
     
      std::cout << "vector: " << count1 << "ms,"
        " unordered_set: " << count2 << "ms"
        " (" << int(100.0 * count2 / count1) << "%)\n";
    }