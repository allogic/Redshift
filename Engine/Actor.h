#pragma once

#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <algorithm>

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////

namespace rs
{
  class Component;
  class Transform;
}

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace rs
{
  class Actor
  {
  public:

    Actor(const std::string& Name);
    virtual ~Actor();

  public:

    inline auto begin() { return mChildren.begin(); }
    inline const auto begin() const { return mChildren.cbegin(); }

    inline auto end() { return mChildren.end(); }
    inline const auto end() const { return mChildren.cend(); }

  public:

    inline auto IsChild() const { return mChildren.size() == 0; }
    inline auto HasParent() const { return mParent != nullptr; }
    inline auto HasChildren() const { return mChildren.size() > 0; }

  public:

    inline const auto& GetName() const { return mName; }
    inline const auto& GetComponents() const { return mComponents; }
    inline const auto& GetChildren() const { return mChildren; }

    inline auto GetParent() const { return mParent; }
    inline auto GetTransform() const { return mTransform; }

  public:

    inline void SetName(const std::string& Value) { mName = Value; }

  public:

    inline void SetParent(Actor* Parent) { mParent = Parent; }

  public:

    virtual void Update() {}

  public:

    void AddChild(Actor* Child);
    void RemoveChild(Actor* Child);

    bool ContainsChild(Actor* Child);
    bool ContainsChildRecursive(Actor* Child);

  public:

    template<typename C, typename ... Args>
    C* AttachComponent(Args&& ... Arguments);

    template<typename C>
    C* GetComponent();

  private:

    std::string mName;
    std::vector<Actor*> mChildren;
    std::map<U64, Component*> mComponents;

    Actor* mParent = nullptr;
    Transform* mTransform = nullptr;
  };
}

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  template<typename C, typename ... Args>
  C* Actor::AttachComponent(Args&& ... Arguments)
  {
    U64 hash = typeid(C).hash_code();
    auto const findIt = mComponents.find(hash);

    if (findIt == mComponents.end())
    {
      auto const [emplaceIt, inserted] = mComponents.emplace(hash, new C{ this, std::forward<Args>(Arguments) ... });
      return (C*)emplaceIt->second;
    }

    return (C*)findIt->second;
  }

  template<typename C>
  C* Actor::GetComponent()
  {
    return (C*)mComponents[typeid(C).hash_code()];
  }
}