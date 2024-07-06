#include "engine/subsystems/renderer/RendererTypes.h"
using namespace GLESC::Render;
ColorRgb::ColorRgb(const ColorRgba& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
}
ColorRgb::ColorRgb(ColorRgba& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
}
ColorRgba::ColorRgba(ColorRgb& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
    this->setA(1.0f);
}

ColorRgba::ColorRgba(const ColorRgb& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
    this->setA(1.0f);
}

const ColorRgb ColorRgb::Red = ColorRgb(220.0f, 20.0f, 60.0f);        // Crimson red, vibrant but natural
const ColorRgb ColorRgb::Green = ColorRgb(60.0f, 179.0f, 113.0f);     // Medium sea green, vibrant
const ColorRgb ColorRgb::DarkGreen = ColorRgb(34.0f, 139.0f, 34.0f); // Forest green, rich and dark
const ColorRgb ColorRgb::Blue = ColorRgb(30.0f, 144.0f, 255.0f);      // Dodger blue, bright sky blue
const ColorRgb ColorRgb::White = ColorRgb(255.0f, 250.0f, 240.0f);    // Floral white, slightly warm
const ColorRgb ColorRgb::Black = ColorRgb(40.0f, 40.0f, 40.0f);       // Darker charcoal black
const ColorRgb ColorRgb::Yellow = ColorRgb(255.0f, 215.0f, 0.0f);     // Gold, bright and cartoonish
const ColorRgb ColorRgb::Cyan = ColorRgb(0.0f, 255.0f, 255.0f);       // Cyan, vibrant and bold
const ColorRgb ColorRgb::Magenta = ColorRgb(255.0f, 0.0f, 255.0f);    // Magenta, bright and vibrant
const ColorRgb ColorRgb::Orange = ColorRgb(255.0f, 165.0f, 0.0f);     // Orange, bright and cartoonish
const ColorRgb ColorRgb::Purple = ColorRgb(138.0f, 43.0f, 226.0f);    // Blue violet, vibrant
const ColorRgb ColorRgb::Pink = ColorRgb(255.0f, 105.0f, 180.0f);     // Hot pink, bright and vibrant
const ColorRgb ColorRgb::Brown = ColorRgb(210.0f, 105.0f, 30.0f);     // Chocolate, rich and warm
const ColorRgb ColorRgb::DarkBrown = ColorRgb(139.0f, 69.0f, 19.0f); // Saddle brown, dark and warm
const ColorRgb ColorRgb::Grey = ColorRgb(169.0f, 169.0f, 169.0f);     // Light grey, standard neutral
const ColorRgb ColorRgb::LightGrey = ColorRgb(211.0f, 211.0f, 211.0f);// Lighter grey
const ColorRgb ColorRgb::DarkGrey = ColorRgb(105.0f, 105.0f, 105.0f); // Dark grey

const ColorRgb ColorRgb::ClearSkin = ColorRgb(255.0f, 224.0f, 189.0f); // Natural skin tone