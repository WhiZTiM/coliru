bool getStatic(std::string::const_iterator& pos, std::string::const_iterator end, std::string& result)
{

    result = "getStatic";
    pos++;

    return true;
}

std::map<u1, opcodeFunc> mapInit()
{
    std::map<u1, opcodeFunc> m;

    m[0xb2] = boost::bind(getStatic,_1,_2,_3);


    return m;
}
