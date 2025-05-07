#pragma once

#include <KrakenEngine.hpp>

class Dialogue
{
public:
    Dialogue(const std::string& name, const std::string& failChoice);
    Dialogue(Dialogue&&) noexcept = default;
    Dialogue& operator=(Dialogue&&) noexcept = default;
    Dialogue(const Dialogue&) = delete;
    Dialogue& operator=(const Dialogue&) = delete;
    ~Dialogue() = default;

    void animate();

    bool isDone() const;

    void reset();

private:
    struct Text
    {
        kn::Texture texture;
        kn::Rect rect;

        Text() = default;

        // Move constructor
        Text(Text&& other) noexcept
            : texture(std::move(other.texture))
            , rect(other.rect)
        {
        }

        // Move assignment
        Text& operator=(Text&& other) noexcept
        {
            if (this != &other)
            {
                texture = std::move(other.texture);
                rect = other.rect;
            }
            return *this;
        }

        // Delete copy constructor and assignment
        Text(const Text&) = delete;
        Text& operator=(const Text&) = delete;
    };

    std::unordered_map<std::string, Text> m_choicePreviews;
    std::unordered_map<std::string, std::vector<Text>> m_choices;

    kn::Timer nextTextTimer;

    bool canCall = true;
    bool chose = false;
    bool done = false;
    bool hasFailed = false;

    std::string m_currentChoice = "";
    size_t m_currentLineIndex = 0;

    std::string m_failChoice;
};
