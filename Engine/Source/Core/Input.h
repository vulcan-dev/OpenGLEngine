#include <GLFW/glfw3.h>
#include <map>
#include <vector>

class CInput {
public:
    CInput(std::vector<int> keysToMonitor);

    bool IsKeyDown(const int& key);
    inline const bool& GetIsEnabled() const { return this->m_IsEnabled; }

    void SetIsEnabled(const bool& value) { this->m_IsEnabled = value; }
    void SetIsKeyDown(const int& key, const bool& isDown);

    ~CInput();

public:
    static void SetupKeyInputs(GLFWwindow& window);
    static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    static std::vector<CInput*> m_Instances;
    std::map<int, bool> m_Keys;
    bool m_IsEnabled;
};