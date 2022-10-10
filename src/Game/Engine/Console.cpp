#include "Console.h"

#include <color.hpp>
void Console::init()
{
}
void Console::error(string text)
{
    cout << dye::red(string("ERROR: .::") + text + string("::.")) << endl;
}

void Console::warning(string text)
{
    cout << dye::yellow(string("WARNING !!! ") + text + string(" !!!")) << endl;
}

void Console::info(string text)
{
    cout << dye::grey(text) << endl;
}

void Console::importantInfo(string text)
{
    cout << dye::grey(string("IMPORTANT: ---") + text + string("---")) << endl;
}

void Console::success(string text)
{
    cout << dye::light_green(string("SUCCESS!: ") + text) << endl;
}
