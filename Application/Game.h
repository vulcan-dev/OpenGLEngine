#pragma once

#include "../Engine/Vision.h"

class Game : public Vision::Layer {
public:
    Game();

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(const float& dt) override;
    void OnRender(const float& dt) override;

    ~Game();
};