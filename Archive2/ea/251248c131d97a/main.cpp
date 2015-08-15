int main(int argc, char* argv[])
{
 const char* messages[] = { "John says hi", "so does James", "Lucy just got home", "Boost.Asio is Fun!", 0 };
 boost::thread_group threads;
 for (const char ** message = messages; *message; ++message)
 {
  threads.create_thread(boost::bind(sync_echo, *message));
  boost::this_thread::sleep(boost::posix_time::millisec(100));
 }
 threads.join_all();
}