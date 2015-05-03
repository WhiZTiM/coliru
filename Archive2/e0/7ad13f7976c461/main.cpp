struct cudaTextureObject_t {};

class CudaTexture
{
    operator cudeTextureObject_t () const { return t; }
    
private:
    cudaTextureObject_t t;
};