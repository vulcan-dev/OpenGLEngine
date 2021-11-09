#pragma once

#include "Include.h"

class CLayer {
public:
    CLayer(std::string_view name = "Layer") : m_Name(name) {
        CORE_DEBUG("Layer {}", name.data());
    }

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(const float& dt) {}
    virtual void OnRender() {}

    virtual ~CLayer() = default;

    const std::string_view GetName() const { return this->m_Name; }

private:
    std::string_view m_Name;
};