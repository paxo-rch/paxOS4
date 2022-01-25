#include <graphics/include/screen.hpp>
#include <widgets/include/window.hpp>


Window::Window()
{
    m_isOpen = true;
}

void Window::close(void)
{
    this->m_opened = false;
}

void Window::open(void)
{
    this->m_opened = true;
}


bool Window::opened(void)
{
    return m_opened;
}

void Window::draw(void)
{
    if (!m_opened) return;
    clearAllScreen(backgroundColor);
}