#include "Dialogue.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Dialogue::Dialogue(const std::string& name, const std::string& failChoice)
    : nextTextTimer(4)
    , m_failChoice(failChoice)
{
    const auto winSize = kn::window::getSize();
    const std::array<kn::Vec2, 4> choicePos = {
        {
            { winSize.x / 2 - 70,
                winSize.y - 24 },
            { winSize.x / 2 + 70,
                winSize.y - 24 },
            { winSize.x / 2 - 70,
                winSize.y - 68 },
            { winSize.x / 2 + 70,
                winSize.y - 68 },
        }
    };

    std::ifstream file("../assets/dialogues.json");
    json data;
    file >> data;
    auto it = data.find(name);

    kn::Font font("kraken-retro", 8);
    for (const auto& [choice, lines] : it->items())
    {
        std::vector<Text> renderedLines;

        for (const auto& line : lines)
        {
            Text t;
            t.texture = font.render(line, false, { 234, 240, 216 }, 120);
            t.rect = t.texture.getRect();
            t.rect.center({ winSize.x / 2, winSize.y - 50 });
            renderedLines.push_back(std::move(t));
        }

        if (!renderedLines.empty() && choice != "0")
        {
            // Re-render preview so we don't move from renderedLines
            const std::string& previewText = lines.front();
            Text preview;
            preview.texture = font.render(previewText, false, { 234, 240, 216 }, 120);
            preview.rect = preview.texture.getRect();
            m_choicePreviews[choice] = std::move(preview);
        }

        m_choices[choice] = std::move(renderedLines);
    }

    size_t idx = 0;
    for (auto& [choiceKey, text] : m_choicePreviews)
    {
        if (idx < choicePos.size())
        {
            text.rect.center(choicePos[idx]);
            ++idx;
        }
    }
}

bool Dialogue::isDone() const
{
    return done;
}

void Dialogue::reset()
{
    m_currentLineIndex = 0;
    chose = false;
    done = false;
    m_currentChoice.clear();

    if (hasFailed)
    {
        m_currentChoice = "0";
        chose = true;
        nextTextTimer.start();
    }
}

void Dialogue::animate()
{
    const auto mousePos = kn::mouse::getPos();

    if (!chose)
    {
        // Render choices
        for (const auto& [choiceKey, text] : m_choicePreviews)
        {
            kn::Rect uiRect = text.rect;
            uiRect.center(uiRect.center() + kn::camera); // cancel out camera scroll

            kn::Rect bgRect = uiRect;
            bgRect.w += 4;
            bgRect.x -= 2;
            bgRect.h -= 2;
            kn::draw::rect(bgRect, { 31, 31, 41 });
            kn::draw::rect(bgRect, { 234, 240, 216 }, 1);
            kn::window::blit(text.texture, uiRect);
        }

        // Handle input
        for (const auto& [choiceKey, text] : m_choicePreviews)
        {
            kn::Rect collisionRect = text.rect;
            collisionRect.center(collisionRect.center() + kn::camera);
            collisionRect.w += 4;
            collisionRect.x -= 2;
            collisionRect.h -= 2;

            if (collisionRect.collidePoint(mousePos) && kn::mouse::isJustPressed(kn::M_LEFT))
            {
                m_currentChoice = choiceKey;
                m_currentLineIndex = 0;
                chose = true;
                done = false;
                nextTextTimer.start();

                if (choiceKey == m_failChoice)
                {
                    canCall = false;
                    hasFailed = true;
                    m_choicePreviews.clear();
                }
                else
                {
                    m_choicePreviews.erase(choiceKey);
                }
                break;
            }
        }

        return;
    }

    if (nextTextTimer.isFinished())
    {
        ++m_currentLineIndex;
        nextTextTimer.start();
    }

    const auto& currentLines = m_choices[m_currentChoice];
    if (m_currentLineIndex < currentLines.size())
    {
        const auto& currentText = currentLines[m_currentLineIndex];
        kn::Rect uiRect = currentText.rect;
        uiRect.center(uiRect.center() + kn::camera); // cancel out camera scroll
        kn::Rect bgRect = uiRect;
        bgRect.w += 4;
        bgRect.x -= 2;
        bgRect.h -= 2;
        kn::draw::rect(bgRect, { 31, 31, 41 });
        kn::draw::rect(bgRect, { 234, 240, 216 }, 1);
        kn::window::blit(currentText.texture, uiRect);
        kn::window::blit(currentText.texture, uiRect);
    }
    else
    {
        chose = false;
        m_currentLineIndex = 0;
        done = true;
    }
}
