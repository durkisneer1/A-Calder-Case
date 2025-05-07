#pragma once

#include <KrakenEngine.hpp>

class TypeWriter
{
public:
    TypeWriter();
    ~TypeWriter() = default;

    void update(const kn::Event& event);

    void drawWriter(const kn::Rect& playerRect);

    void drawInput();

    bool isSubmitted() const;

    bool isCorrect() const;

    bool isOpened() const;

private:
    const kn::Texture writer;
    const kn::Texture writerHighlight;
    kn::Rect writerRect;

    const kn::Texture writerBig;

    bool opened = false;
    bool justOpened = false;

    std::string userInput = "";
    kn::Texture inputTex;
    kn::Font font;

    kn::Sound clickSfx;
    kn::Sound submitSfx;

    const std::string answer = "TREVOR";
    bool submitted = false;
};
