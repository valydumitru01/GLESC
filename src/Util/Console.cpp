#include "util/Console.h"

#include <color.hpp>

void Console::init() {
}

void Console::error(const string& text) {
    cout << dye::red(string("ERROR: .::") + text + string("::.")) << endl;
}

void Console::warning(const string& text) {
    cout << dye::yellow(string("WARNING !!! ") + text + string(" !!!")) << endl;
}

void Console::info(const string& text) {
    cout << dye::grey(text) << endl;
}

void Console::importantInfo(const string& text) {
    cout << dye::grey(string("IMPORTANT: ---") + text + string("---")) << endl;
}

void Console::success(const string& text) {
    cout << dye::light_green(string("SUCCESS!: ") + text) << endl;
}
