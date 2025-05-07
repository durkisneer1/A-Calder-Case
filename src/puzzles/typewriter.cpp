#include "puzzles/TypeWriter.hpp"
#include <algorithm>

TypeWriter::TypeWriter()
    : writer("../assets/writer.png")
    , writerHighlight("../assets/writer-highlight.png")
    , writerRect(writer.getRect())
    , writerBig("../assets/typewriter.png")
    , font("kraken-retro", 8)
    , clickSfx("../assets/audio/type.wav")
    , submitSfx("../assets/audio/submit.wav")
{
    writerRect.topLeft({ 251, 78 });

    clickSfx.setVolume(0.1f);
    submitSfx.setVolume(0.1f);
}

void TypeWriter::update(const kn::Event& event)
{
    if (!opened && !justOpened)
        return;

    if (event.type == kn::TEXTINPUT || event.type == kn::KEYDOWN)
    {
        if (event.type == kn::TEXTINPUT)
        {
            clickSfx.play();
            if (userInput.size() > 8)
                return;

            userInput += event.text.text;
        }
        else if (event.type == kn::KEYDOWN)
        {
            if (event.key.keysym.sym == kn::K_BACKSPACE)
            {
                clickSfx.play();
                if (!userInput.empty())
                    userInput.pop_back();
            }
            else if (event.key.keysym.sym == kn::K_RETURN)
            {
                submitSfx.play();
                submitted = true;
            }
        }
        inputTex = font.render(userInput, false, { 31, 31, 41 });
    }
}

bool TypeWriter::isSubmitted() const
{
    return submitted;
}

bool TypeWriter::isCorrect() const
{
    std::string upperInput = userInput;
    std::transform(upperInput.begin(), upperInput.end(), upperInput.begin(), [](unsigned char c)
        { return std::toupper(c); });
    return answer == upperInput;
}

bool TypeWriter::isOpened() const
{
    return opened;
}

void TypeWriter::drawWriter(const kn::Rect& playerRect)
{
    kn::window::blit(writer, writerRect);
    if (opened)
        return;

    if (writerRect.collideRect(playerRect))
    {
        kn::window::blit(writerHighlight, writerRect);
        if (kn::key::isJustPressed(kn::S_e))
        {
            opened = true;
            justOpened = true;
        }
    }
}

void TypeWriter::drawInput()
{
    kn::camera = { 0, 0 };

    if (kn::key::isJustPressed(kn::K_ESC))
    {
        opened = false;
        return;
    }

    if (!opened)
        return;

    if (justOpened)
    {
        justOpened = false;
        return;
    }

    kn::draw::rect({ kn::camera, kn::window::getSize() }, { 0, 0, 0, 150 });
    kn::window::blit(writerBig, kn::window::getSize() / 2, kn::CENTER);
    kn::window::blit(inputTex, { 125, 36 });
}