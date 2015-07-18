#include <stdexcept>
#include <iostream>
#include <algorithm>

// memory mapping
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <cstring>
#include <cassert>

template <size_t N, size_t M, typename T = int> 
struct Tiles {

    Tiles(char const* fname)
        : fd(open(fname, O_RDWR | O_CREAT)) 
    {
        if (fd == -1) {
            throw std::runtime_error(strerror(errno));
        }

        auto size = N*M*sizeof(T);
        if (int err = posix_fallocate(fd, 0, size)) {
            throw std::runtime_error(strerror(err));
        }

        tiles = static_cast<T*>(mmap(nullptr, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0));

        if (MAP_FAILED == tiles) {
            throw std::runtime_error(strerror(errno));
        }
    }

    ~Tiles() {
        if (-1 == munmap(tiles, N*M*sizeof(T))) {
            throw std::runtime_error(strerror(errno));
        }
        if (-1 == close(fd)) {
            throw std::runtime_error(strerror(errno));
        }
    }

    void init(T value) {
        std::fill_n(tiles, N*M, value);
    }

    T& operator()(size_t row, size_t col) { 
        assert(row >= 0 && row <= N);
        assert(col >= 0 && col <= M);
        return tiles[(row*M)+col];
    }

    T const& operator()(size_t row, size_t col) const { 
        assert(row >= 0 && row <= N);
        assert(col >= 0 && col <= M);
        return tiles[(row*M)+col];
    }
  private:
    int fd   = -1;
    T* tiles = nullptr;
};

int main(int argc, char** argv) {
    using Map = Tiles<3, 3, uint16_t>;

    Map data("tiles.dat");

    if (argc>1) switch(atoi(argv[1])) {
        case 1: 
            data.init(0x0001);
            break;
        case 2:
            data(1, 1) = 0x0002;
            break;
    }
}
