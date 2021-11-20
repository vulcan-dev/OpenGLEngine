#pragma once

namespace Vision {
    class Layer {
    public:
        Layer(std::string_view name = "Layer") : m_Name(name) {}

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(const float& dt) {}
        virtual void OnRender(const float& dt) {}

        virtual ~Layer() = default;

        const std::string_view GetName() const { return this->m_Name; }

    private:
        std::string_view m_Name;
    };
}