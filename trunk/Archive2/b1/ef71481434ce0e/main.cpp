#include <map>
#include <array>
#include <iostream>

class Simulator
{
public:
    enum class PROPS { PROP1, PROP2, PROP3 };
   
    template <typename T>
    T get(PROPS p) 
    {
        return _map.at(p);
    }
    
    template <typename T>
    void set(PROPS p, T value)
    {
        _map.at(p) = value;
    }
    
private:
    template <typename T>
    class Property
    {
    public:
        T operator =(const T & value) { set(value); return value; }
        operator T() const { return get(); }
    
    	Property(T defaultValue)
    	{
    		value = defaultValue;
    	}
    
    protected:
    	void set(T v) { value = v; }
    	T get() const { return value; }
    
    	T value;
    };
    
    std::map<PROPS, Property<float>> _map = { { PROPS::PROP1, Property<float>(5.0f) } };
};


int main()
{
    Simulator s;

    std::cout << s.get<bool>(Simulator::PROPS::PROP1) << std::endl;
    
    s.set(Simulator::PROPS::PROP1, 3.0f);
    
    std::cout << s.get<float>(Simulator::PROPS::PROP1);

	return 0;
}