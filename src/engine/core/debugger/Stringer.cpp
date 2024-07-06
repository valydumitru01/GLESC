#include "engine/core/debugger/Stringer.h"


int GLESC::Stringer::floatPrecision = DEFAULT_FLOAT_PRECISION;

std::string GLESC::Stringer::replace(const std::string& string, const std::string& stringToReplace,
                                     const std::string& replacement) {
    std::string result = string;
    size_t pos = 0;
    while ((pos = result.find(stringToReplace, pos)) != std::string::npos) {
        result.replace(pos, stringToReplace.length(), replacement);
        pos += replacement.length();
    }
    return result;
}

std::string GLESC::Stringer::strip(const std::string& string, const std::string& chars) {
    const std::string& result = string;
    size_t start = result.find_first_not_of(chars);
    if (start == std::string::npos) {
        return ""; // Return an empty string if all characters are to be stripped
    }
    size_t end = result.find_last_not_of(chars);
    return result.substr(start, end - start + 1);
}

bool GLESC::Stringer::contains(const std::string& string, const std::string& substring) {
    return string.find(substring) != std::string::npos;
}