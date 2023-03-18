#include <Common/Debug.h>

#include <Common/Utils/FileUtils.h>

#include <Engine/Engine.h>
#include <Engine/Interface.h>
#include <Engine/Scene.h>

#include <Vendor/GLAD/glad.h>

#include <Vendor/GLFW/glfw3.h>

#include <Vendor/RAPIDJSON/rapidjson.h>
#include <Vendor/RAPIDJSON/document.h>

///////////////////////////////////////////////////////////
// Namespaces
///////////////////////////////////////////////////////////

namespace fs = std::filesystem;
namespace rj = rapidjson;

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

rj::Document gConfig = {};

rs::R32 gTime = 0.0F;
rs::R32 gTimePrev = 0.0F;
rs::R32 gTimeDelta = 0.0F;

rs::Interface* gInterface = nullptr;
rs::Scene* gScene = nullptr;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace rs
{
  void GlfwDebugProc(I32 Error, char const* Msg)
  {
    LOG("Error:%d Message:%s\n", Error, Msg);
  }

  void GlDebugCallback(U32 Source, U32 Type, U32 Id, U32 Severity, I32 Length, char const* Msg, void const* UserParam)
  {
    switch (Severity)
    {
      case GL_DEBUG_SEVERITY_NOTIFICATION: break;
      case GL_DEBUG_SEVERITY_LOW: LOG("Severity:Low Type:0x%x Message:%s\n", Type, Msg); break;
      case GL_DEBUG_SEVERITY_MEDIUM: LOG("Severity:Medium Type:0x%x Message:%s\n", Type, Msg); break;
      case GL_DEBUG_SEVERITY_HIGH: LOG("Severity:High Type:0x%x Message:%s\n", Type, Msg); break;
    }
  }
}

///////////////////////////////////////////////////////////
// Entry Point
///////////////////////////////////////////////////////////

rs::I32 main()
{
  gConfig.Parse(rs::FileUtils::ReadText("Config.json").c_str());

  glfwSetErrorCallback(rs::GlfwDebugProc);

  if (glfwInit())
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gConfig["glMajorVersion"].GetInt());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gConfig["glMinorVersion"].GetInt());
    glfwWindowHint(GLFW_SAMPLES, gConfig["msaaSampleCount"].GetInt());
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);

    GLFWwindow* glfwContext = glfwCreateWindow(gConfig["windowWidth"].GetInt(), gConfig["windowHeight"].GetInt(), "Redshift", nullptr, nullptr);

    if (glfwContext)
    {
      glfwMakeContextCurrent(glfwContext);
      glfwSwapInterval(0);

      if (gladLoadGL())
      {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(rs::GlDebugCallback, 0);

        gScene = new rs::Scene;
        gInterface = new rs::Interface{ glfwContext };

        while (!glfwWindowShouldClose(glfwContext))
        {
          gTime = (rs::R32)glfwGetTime();
          gTimeDelta = gTime - gTimePrev;
          gTimePrev = gTime;

          glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
          glClear(GL_COLOR_BUFFER_BIT);

          if (gInterface)
          {
            gInterface->Render();
          }

          glfwMakeContextCurrent(glfwContext);
          glfwSwapBuffers(glfwContext);
          glfwPollEvents();
        }

        if (gInterface)
        {
          delete gInterface;
          gInterface = nullptr;
        }

        if (gScene)
        {
          delete gScene;
          gScene = nullptr;
        }
      }
      else
      {
        LOG("Failed initializing GL\n");
      }

      glfwDestroyWindow(glfwContext);
      glfwTerminate();
    }
    else
    {
      LOG("Failed creating window\n");
    }
  }
  else
  {
    LOG("Failed initializing GLFW\n");
  }

  return 0;
}