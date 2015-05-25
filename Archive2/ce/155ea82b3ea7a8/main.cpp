#include <iostream>
#include <memory>
#include <cstddef>
#include <cassert>


struct matrix_type {

   matrix_type() : matrix_type(0, 0) {}
   
   matrix_type(const std::size_t width_, const std::size_t height_) : width_(width_), height_(height_) {}
   
   std::size_t width() const {
      return width_;    
   }
   
   std::size_t height() const {
      return height_;    
   }

private:
   std::size_t width_;
   std::size_t height_;
};

struct array_type {
    
   array_type() : array_type(0) {}
    
   explicit array_type(const std::size_t size_) : size_(size_) {}

   std::size_t size() const {
      return size_;    
   }

private:
   std::size_t size_;
};

struct scalar_type {

   scalar_type() : scalar_type(0) {}
   
   explicit scalar_type(const int value_) : value_(value_) {}
   
   int value() const {
      return value_;    
   }

private:
   int value_;
};


matrix_type * create_matrix(const std::size_t width, const std::size_t height) {
   std::clog << "creating matrix_type(" << width << ", " << height << ")" << std::endl;
   return new matrix_type{width, height};    
}

void release_matrix(matrix_type ** const matrix) {
   assert(matrix && *matrix);
   std::clog << "releasing matrix_type(" << (*matrix)->width() << ", " << (*matrix)->height() << ")" << std::endl;    
   delete *matrix;
}

array_type * create_array(const std::size_t size) {
   std::clog << "creating array_type(" << size << ")" << std::endl;
   return new array_type{size};
}

void release_array(array_type ** const array) {
   assert(array && *array);
   std::clog << "releasing array_type(" << (*array)->size() << ")" << std::endl;
   delete *array;
}

scalar_type * create_scalar(const int value) {
   std::clog << "creating scalar_type(" << value << ")" << std::endl;
   return new scalar_type{value};
}

void release_scalar(scalar_type ** const scalar) {
   assert(scalar && *scalar);
   std::clog << "releasing scalar_type(" << (*scalar)->value() << ")" << std::endl;    
   delete *scalar;
}

void use(scalar_type * const scalar) {
   assert(scalar);
   std::clog << "using scalar_type(" << scalar->value() << ")" << std::endl;
}

void use(array_type * const array) {
   assert(array);
   std::clog << "using array_type(" << array->size() << ")" << std::endl;
}

void use(matrix_type * const matrix) {
   assert(matrix);
   std::clog << "using matrix_type(" << matrix->width() << ", " << matrix->height() << ")" << std::endl;
}


struct scalar_deleter {

   void operator ()(scalar_type * scalar) const {
      if (scalar) {
         release_scalar(&scalar);
      }
   }
};

struct array_deleter {

   void operator ()(array_type * array) const {
      if (array) {
         release_array(&array);  
      }
   }
};

struct matrix_deleter {

   void operator ()(matrix_type * matrix) const {
      if (matrix) {
         release_matrix(&matrix);    
      }    
   }
};


namespace wrapped_1 {
    
using scalar_type = std::unique_ptr<::scalar_type, scalar_deleter>;
using array_type  = std::unique_ptr<::array_type,  array_deleter>;
using matrix_type = std::unique_ptr<::matrix_type, matrix_deleter>;
    
}


namespace wrapped_2 {
    
struct scalar_type : std::unique_ptr<::scalar_type, scalar_deleter> {

   using base_type = std::unique_ptr<::scalar_type, scalar_deleter>;

   explicit scalar_type(const int value) : base_type(create_scalar(value)) {}
   
   scalar_type(scalar_type && other) : base_type(other.release()) {}
   
   scalar_type & operator =(scalar_type && other) {
      reset(other.release());    
      return *this;
   }
};

struct array_type : std::unique_ptr<::array_type, array_deleter> {

   using base_type = std::unique_ptr<::array_type, array_deleter>;
   
   explicit array_type(const std::size_t size) : base_type(create_array(size)) {}
   
   array_type(array_type && other) : base_type(other.release()) {}
   
   array_type & operator =(array_type && other) {
      reset(other.release());    
      return *this;
   }
};

struct matrix_type : std::unique_ptr<::matrix_type, matrix_deleter> {

   using base_type = std::unique_ptr<::matrix_type, matrix_deleter>;
   
   matrix_type(const std::size_t width, const std::size_t height) : base_type(create_matrix(width, height)) {}
   
   matrix_type(matrix_type && other) : base_type(other.release()) {}
   
   matrix_type & operator =(matrix_type && other) {
      reset(other.release());  
      return *this;
   }
};
    
}


namespace wrapped_3 {

namespace detail {

template<typename Creator, typename Deleter>
struct holder;

template<typename R, typename ...Args, typename Deleter>
struct holder<R (*Creator)(Args...), Deleter> : std::unique_ptr<typename std::pointer_traits<R>::element_type, Deleter> {

   using base_type = std::unique_ptr<R (Args...), Deleter>;

   explicit holder(Args && ...args) : base_type(Creator(std::forward<Args>(args)...)) {}
   
   holder(holder && other) : base_type(other.release()) {}
   
   holder & operator =(holder && other) {
      reset(other.release());
      return *this;
   }
};

}

}


int main() {
   {
      auto scalar = create_scalar(1);
      auto array  = create_array(2);
      auto matrix = create_matrix(3, 4);
   
      use(scalar);
      use(array);
      use(matrix);
   
      release_matrix(&matrix);
      release_array(&array);
      release_scalar(&scalar);
   }
   
   std::clog << " -/--/--/--/-" << std::endl;
   
   {
      wrapped_1::scalar_type scalar(create_scalar(1));
      wrapped_1::array_type  array(create_array(2));
      wrapped_1::matrix_type matrix(create_matrix(3, 4));
      
      use(scalar.get());
      use(array.get());
      use(matrix.get());
   }
   
   std::clog << " -/--/--/--/-" << std::endl;
   
   {
      wrapped_2::scalar_type scalar(1);
      wrapped_2::array_type  array(2);
      wrapped_2::matrix_type matrix(3, 4);
      
      use(scalar.get());
      use(array.get());
      use(matrix.get());
   }
}