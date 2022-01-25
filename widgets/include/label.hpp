#ifndef __LABEL__
#define __LABEL__

#include <widgets/include/guielement.hpp>
#include <graphics/graphics.h>

class Label : public GUI
{
    public:

        Label(const uint16_t x, const uint16_t y,
              const uint16_t width, const uint16_t height,
              std::string innerText,
              TextAlignment textAlignment = CENTER);

        std::string getInnerText(void) const;
        void setInnerText(const std::string innerText);

        color_t getTextColor(void) const;
        void setTextColor(const color_t textColor);

        uint16_t getTextSize(void) const;
        void setTextSize(const uint16_t textSize);

        TextAlignment getTextAlignment(void) const;
        void setTextAlignment(const TextAlignment textAlignment);

        void setFont(const GFXfont* font);
        GFXfont* getFont(void) const;

        virtual void draw(void);

    private:

        std::string m_innerText;
        color_t m_textColor;
        uint16_t m_textSize;
        TextAlignment m_textAlignment;
        GFXfont* m_font;

};

#endif /* __LABEL__ */
