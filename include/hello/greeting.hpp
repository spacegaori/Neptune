// include/hello/greeting.hpp
#include <string>
namespace hello {
inline std::string greeting()
{
    std::string response = "Hello World!!";
    return response;
}
}