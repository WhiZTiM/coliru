#include <iostream>
#include <stdexcept>

///////////////////////////////////////////////////////
// mocking ID3D*
    struct ID3D11ShaderResourceView;
    enum ERROR_CODE { ERR_OK };
#define FAILED(e) (ERR_OK != (e))
    static int gvDevice = 42;
    ERROR_CODE D3DX11CreateShaderResourceViewFromFile(int, char const* fname, void*, void*, ID3D11ShaderResourceView**, void*) {
        std::cout << "Loaded from " << fname << "\n";
        return ERR_OK;
    }
//
///////////////////////////////////////////////////////

struct frame{ virtual ~frame() = default; };

class button : public frame {
public:
    button() {};

    template <typename T1, typename T2>
    button(T1 const& texture, T2 const& hover_texture)
        : _texture(load(texture)), 
          _hover_texture(load(hover_texture))
    {
    };

private:
    // TODO Rule-Of-Three constructor/destructorl 
    // SUGGEST: Rule-Of-Zero using shared pointers instead
    ID3D11ShaderResourceView* _texture;
    ID3D11ShaderResourceView* _hover_texture;

    static ID3D11ShaderResourceView* load(ID3D11ShaderResourceView* v) { return v; }
    static ID3D11ShaderResourceView* load(char const* fname) { 
        ID3D11ShaderResourceView* p = NULL;
        if (FAILED(D3DX11CreateShaderResourceViewFromFile(gvDevice, fname, NULL, NULL, &p, NULL)))
            throw std::runtime_error(std::string("loading texture failed (") + fname + ")");

        return p;
    }
};

#include <cassert>

int main() {
    ID3D11ShaderResourceView* default_texture = NULL;
    assert(!FAILED( D3DX11CreateShaderResourceViewFromFile(gvDevice, "default_texture.bin", NULL, NULL, &default_texture, NULL)));

    try {

        button button1("t1.bin",        "hover1.bin");
        button button2(default_texture, "hover2.bin");
        button button3("t3.bin",        default_texture);
        button button4(default_texture, default_texture);

    } catch(std::exception const& e) {
        std::cout << "Oops: " << e.what() << "\n";
    }
}
