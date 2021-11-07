#include "Input.h"
#include <algorithm>

std::vector<CInput*> CInput::_instances;

CInput::CInput(std::vector<int> keysToMonitor) : _isEnabled(true) {
  for (int key : keysToMonitor) {
    _keys[key] = false;
  }
  // Add this instance to the list of instances
  CInput::_instances.push_back(this);
}

CInput::~CInput() {
  // Remove this instance from the list of instances
  _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}

bool CInput::getIsKeyDown(int key) {
  bool result = false;
  if (_isEnabled) {
    std::map<int,bool>::iterator it = _keys.find(key);
    if (it != _keys.end()) {
      result = _keys[key];
    }
  }
  return result;
}

void CInput::setIsKeyDown(int key, bool isDown) {
  std::map<int,bool>::iterator it = _keys.find(key);
  if (it != _keys.end()) {
    _keys[key] = isDown;
  }
}

void CInput::setupKeyInputs(GLFWwindow& window) {
  glfwSetKeyCallback(&window, CInput::callback);
}

void CInput::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // Send key event to all KeyInput instances
  for (CInput* keyInput : _instances) {
    keyInput->setIsKeyDown(key, action != GLFW_RELEASE);
  }
}