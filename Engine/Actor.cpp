#include <Engine/Actor.h>

#include <Engine/Components/Transform.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  Actor::Actor(const std::string& Name)
    : mName{ Name }
    , mTransform{ AttachComponent<Transform>() }
  {

  }

  Actor::~Actor()
  {
    for (auto& [hash, component] : mComponents)
    {
      delete component;
    }
  }

  void Actor::AddChild(Actor* Child)
  {
    mChildren.emplace_back(Child);
  }

  void Actor::RemoveChild(Actor* Child)
  {
    mChildren.erase(std::find(mChildren.begin(), mChildren.end(), Child));
  }

  bool Actor::ContainsChild(Actor* Child)
  {
    return std::find(mChildren.begin(), mChildren.end(), Child) != mChildren.end();
  }

  bool Actor::ContainsChildRecursive(Actor* Child)
  {
    bool contains = ContainsChild(Child);

    for (const auto& child : mChildren)
    {
      contains |= child->ContainsChildRecursive(Child);
    }

    return contains;
  }
}