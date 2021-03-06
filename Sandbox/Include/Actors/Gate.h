#pragma once

#include <Redshift.h>

#include <Components/Brain.h>
#include <Components/Renderable.h>

class Gate : public Actor
{
public:

  Gate(
    World& world,
    ActorProxy* proxy,
    std::string const& name)
    : Actor(world, proxy, name)
    , mTransform{ World::AttachComponent<Transform>(mWorld, this, R32V3{ 0.0f }, R32V3{ 0.0f }, R32V3{ 0.007f }) }
    , mRenderable{ World::AttachComponent<Renderable>(mWorld, this, "Gate", "CrossHatch", "GateAlbedo", "GateNormal", "", "GateMetallic", "GateRoughness")}
  {

  }

public:

  inline Transform* GetTransform() const { return mTransform; }
  inline Renderable* GetRenderable() const { return mRenderable; }

private:

  Transform* mTransform;
  Renderable* mRenderable;
};