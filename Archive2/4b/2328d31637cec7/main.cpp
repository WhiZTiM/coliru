class MyClass
{
private:
    enum class Color {
        None, Red, Green
    } _color;

    enum class Texture {
        None, Smooth, Rough
    } _texture;

public:
    MyClass()
        : _color(Color::Green)
                // ---------- <== ERROR: Member is inaccessible
        , _texture(Texture::Rough)
                   //-------------- <== ERROR: Member is inaccessible
    {
    }
};

int main()
{
    
}