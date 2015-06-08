    #include <vector>
    #include <string>

    class CharPtrPtr
    {
       std::vector<std::string> m_args;
       std::vector<char *> m_argsptr;
    
       public:
           void add(const std::string& s) { m_args.push_back(s); }
    
           char ** create_argsPtr() 
           { 
              m_argsptr.clear();
              for (size_t i = 0; i < m_args.size(); ++i)
                 m_argsptr.push_back(const_cast<char*>(m_args[i].c_str()));
              m_argsptr.push_back(NULL);
              return &m_argsptr[0]; 
           }
           
           char **get_argsPtr() { return m_argsptr.empty()?NULL:&m_argsptr[0]; }
           
           void clear_args() { m_args.clear(); }
    };

           
    #include <iostream>

    void legacy_function(char **myList) 
    {
        for (int i = 0; myList[i]; ++i)
            std::cout << myList[i] << "\n";
    }

    int main()
    {
        CharPtrPtr args;
        args.add("first");
        args.add("second");
        legacy_function(args.create_argsPtr());
   }  
