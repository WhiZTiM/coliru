size_t checksum = 0;
boost::system::error_code compute_file_checksum(std::string file_name)
{
 HANDLE file = ::CreateFile(file_name.c_str(), GENERIC_READ, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
 windows::random_access_handle h(service, file);

 long buff[1024];
 checksum = 0;
 size_t bytes = 0;
 size_t at = 0;
 boost::system::error_code ec;
 
 while ((bytes = boost::asio::read_at(h, at, boost::asio::buffer(buff), ec)) > 0)
 {
  at += bytes;
  bytes /= sizeof(long);
  for (size_t i = 0; i < bytes; ++i)
   checksum += buff[i];
 }
 return boost::system::error_code(0, boost::system::generic_category());
}
