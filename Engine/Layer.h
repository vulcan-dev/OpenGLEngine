#pragma once

#include "Include.h"

namespace VK {
    class CLayer {
    public:
        CLayer(std::string_view name = "Layer") : m_Name(name) {}

        virtual void OnAttach(CWindow* window) {}
        virtual void OnDetach() {}
        virtual void OnUpdate(const float& dt) {}
        virtual void OnRender(const float& dt) {}

        virtual ~CLayer() = default;

        const std::string_view GetName() const { return this->m_Name; }

    private:
        std::string_view m_Name;
    };
}