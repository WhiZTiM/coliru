template<class... Ts>
class StreamList
{
};

template<class... Ts>
constexpr auto is_stream_list(StreamList<Ts...>)
{
    return true;
}

template<class T>
constexpr auto is_stream_list(T)
{
    return false;
}

int main()
{
    static_assert(is_stream_list(StreamList<float>()), "");
    static_assert(!is_stream_list(float()), "");
    return 0;
}
