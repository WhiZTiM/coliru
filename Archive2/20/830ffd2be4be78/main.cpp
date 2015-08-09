#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

//----------------------------------------------------------------------------
std::string load_file_at_once( const std::string& filename )
{
  std::string s;
  std::ifstream f( filename, std::ios::binary );
  if (!f)
  {
    std::cerr << "Could not open INFILE " << filename << "\n";
    std::exit( 1 );
  }
  std::ostringstream ss;
  ss << f.rdbuf();
  return std::move( ss.str() );
}

//----------------------------------------------------------------------------
typedef std::vector <std::vector <std::size_t> > indices;
typedef std::tuple <std::string, indices, std::size_t> index_info;

//----------------------------------------------------------------------------
index_info parse( const std::string& text )
{
  indices     xys;
  std::size_t max_col = 0;
  std::size_t index   = 0;
  
  auto push_new = [ &xys, &index ]() -> void
  {
    xys.resize( xys.size() + 1 );
    xys.back().push_back( index );
  };
  
  push_new();
  for (char c : text)
  {
    ++index;
    switch (c)
    {
      case ',':  xys.back().push_back( index ); break;
      case '\n': max_col = std::max( max_col, xys.back().size() );
                 push_new();
      case '\r': break;
    }
  }
  if (xys.back().size() < 2) xys.resize( xys.size() - 1 );

  return std::make_tuple( text, std::move( xys ), max_col );
}

//----------------------------------------------------------------------------
void save_file( const std::string& filename, const index_info& info )
{
  const std::string& text    = std::get <0> (info);
  const indices&     xys     = std::get <1> (info);
  const std::size_t  max_col = std::get <2> (info);
  
  auto get = [ &text, &xys, &max_col ]( std::size_t row, std::size_t col ) -> std::string
  {
    if (col < xys[ row ].size())
    {
      std::size_t n = xys[ row ][ col ];
      std::size_t x = text.find_first_of( ",\n\r", n );
      return text.substr( n, x - n );
    }
    return "";
  };
  
  std::ofstream f( filename );
  for (std::size_t col = 0; col < max_col; col++)
  {
    f << get( 0, col );
    for (std::size_t row = 1; row < xys.size(); row++)
    {
      f << "," << get( row, col );
    }
    f << std::endl;
  }
}

//----------------------------------------------------------------------------
int main( int argc, char** argv )
{
  if (argc != 3)
  {
    std::cout << "usage:  " << argv[0] << " INFILE OUTFILE\n";
    return 1;
  }
  save_file( argv[2], parse( load_file_at_once( argv[1] ) ) );
}
