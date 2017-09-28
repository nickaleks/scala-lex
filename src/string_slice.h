#ifdef __cpp_lib_string_view
#include <string_view>
using StringSlice = StringSlice;
#else
#include <experimental/string_view>
using StringSlice = std::experimental::string_view;
#endif