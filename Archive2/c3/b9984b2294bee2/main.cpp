#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

void string_permutation( std::string& orig, std::string& perm )
    {
        if( orig.empty() )
        {
            std::cout<<perm<<std::endl;
            return;
        }

        for(std::string::size_type i=0;i <orig.size();++i)
        {
            std::string orig2  (orig);

            orig2.erase(i,1);

            std::string perm2(perm);

            perm2 += orig.at(i);

            string_permutation(orig2,perm2);
        } 
    }
    
   
   void vec_permute( std::vector<char> &orig, std::vector<char> &perm)
   {
       if(orig.empty())
       {
            for( auto &x : perm)
                std::cout<<x;
            std::cout<<"\n";
            return;
       }
       for(std::vector<char>::size_type i=0;i <orig.size();++i)
       {
            std::vector<char> orig2(orig);
            orig2.erase(std::find(orig2.begin(),orig2.end(),orig.at(i)));
            std::vector<char> perm2(perm);
            perm2.push_back(orig.at(i));
            vec_permute(orig2,perm2);            
       }
   }
    
    
   
   
   int main()
   {
        std::string ori="hello";
        std::string perm;
        //string_permutation(ori,perm);
        std::cout<<perm;
        
        std::vector<char> o_vec{'h','e','l','l','o'};
        std::vector<char> p_vec;
        vec_permute(o_vec,p_vec);
        for( auto &x : p_vec)
                std::cout<<x;
       
   }