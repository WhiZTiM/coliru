#include <ctime>
#include <unistd.h>
#include <cstdlib>

Clave::Clave(char const* clave)
{
    if (strlen(clave) < 5)
        throw Incorrecta(Razon::CORTA);

    char salt[11] = { '$', '1', '$' };
    char const MD5chars[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwyxz";
    size_t const chsetSize = sizeof(MD5chars);

    srand(time(nullptr));

    for (unsigned i = 3; i < 11; ++i) {
        // El producto devolverá un número entre 0 y chsetSize, pero tenemos
        // que devolver un número entre 0 y chsetSize - 1 (índice del vector).
        // Así que utilizamos el módulo para transformar el valor chsetSize en 0.
        unsigned randomCharIdx = unsigned(rand() * chsetSize) % chsetSize;

        salt[i] = MD5chars[randomCharIdx];
    }

    char* encriptado = crypt(clave, salt);

    if (encriptado == nullptr)
        throw Incorrecta(Razon::ERROR_CRYPT);

    s_clave = encriptado;
}
