#include "ParserJson.hpp"

int main(int ac, char const * const *av)
{
    JsonParser parse("config.json");

    std::cout << parse.getData("MCTEST") << std::endl;
    std::cout << parse.getData("MAX_COMPONENT") << std::endl;
    std::cout << parse.getData("realtry") << std::endl;
}
