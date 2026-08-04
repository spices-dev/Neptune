/**
* @file WindowImpl.cpp.
* @brief The WindowImpl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_WINDOW_GLFW

#include "WindowImpl.h"
#include "RenderBackendInterface.h"
#include "Core/Event/WindowEvent.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"

#include <GLFW/glfw3.h>

namespace Neptune::GLFW {

    WindowImpl::WindowImpl(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend)
        : Window(implement)
        , EventProducer(EventType::Count)
        , m_APIInterface(CreateInterface(backend))
    {
        NEPTUNE_PROFILE_ZONE

        // Initialize the library
        if(!glfwInit()) 
        {
            NEPTUNE_CORE_CRITICAL("glfw init failed.")
        }

        // Set Hint
        m_APIInterface->Hint();

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);                                  // @brief Set glfw enable resize feature.
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);                                  // @brief Set glfw enable title tab.
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_NONE);  // @brief Set glfw release behavior(no flush).

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwWindowHint(GLFW_RED_BITS     , mode->redBits     );
        glfwWindowHint(GLFW_GREEN_BITS   , mode->greenBits   );
        glfwWindowHint(GLFW_BLUE_BITS    , mode->blueBits    );
        glfwWindowHint(GLFW_REFRESH_RATE , mode->refreshRate );

        // Create the only window
        m_Windows = glfwCreateWindow(initInfo.width, initInfo.height, initInfo.name.c_str(), nullptr, nullptr);
        if(!m_Windows) 
        {
            glfwTerminate();
            NEPTUNE_CORE_CRITICAL("Window create failed.")
        }

        // Load APIs.
        m_APIInterface->APILoad(m_Windows);

        // Set glfw call back object pointer.
        glfwSetWindowUserPointer(m_Windows, this);

        // Set gltf event call back.
        SetInternalCallBack();
    }

    WindowImpl::~WindowImpl()
    {
        NEPTUNE_PROFILE_ZONE

        if (m_Windows) 
        {
            glfwDestroyWindow(m_Windows);
        }

        glfwTerminate();
    }

    bool WindowImpl::IsWindowActive() const
    {
        NEPTUNE_PROFILE_ZONE

        return !glfwWindowShouldClose(m_Windows);
    }

    void WindowImpl::PollEvents() const
    {
        NEPTUNE_PROFILE_ZONE

        glfwPollEvents();
    }

    glm::ivec2 WindowImpl::Extent() const
    {
        NEPTUNE_PROFILE_ZONE

        int width = 0, height = 0;
        glfwGetFramebufferSize(m_Windows, &width, &height);

        while (width == 0 || height == 0)
        {
            glfwGetFramebufferSize(m_Windows, &width, &height);

            glfwWaitEvents();
        }

        return { width , height };
    }

    std::vector<const char*> WindowImpl::Extension() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_APIInterface->Extension();
    }
    
    void* WindowImpl::NativeWindow() const
    {
        NEPTUNE_PROFILE_ZONE

        return m_Windows;
    }

    void WindowImpl::SetInternalCallBack() const
    {
        NEPTUNE_PROFILE_ZONE

        // print the version on the console
        NEPTUNE_CORE_INFO(glfwGetVersionString())

        // Error event Callback.
        glfwSetErrorCallback([](int error, const char* description){

            std::stringstream ss;
            ss << "glfwError: " << error << " | " << description;

            NEPTUNE_CORE_ERROR(ss.str())
        });

        // Framebuffer resize event Callback, not in use.
        //glfwSetFramebufferSizeCallback(m_Windows, WindowsResizeCallback);

        // Window resize event Callback.
        glfwSetWindowSizeCallback(m_Windows, [](GLFWwindow* window, int width, int height)
        {
            // reinterpret the pointer to this class.
            const auto thisWindows = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));

            WindowResizeEvent event(width, height);

            thisWindows->Dispatch(event);
        });

        // Window close event Callback.
        glfwSetWindowCloseCallback(m_Windows, [](GLFWwindow* window)
        {
            const auto thisWindows = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
            
            WindowCloseEvent event;
            
            thisWindows->Dispatch(event);
        });

        // Key event Callback.
        glfwSetKeyCallback(m_Windows, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            const auto thisWindows = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
            
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 0);
                    
                    thisWindows->Dispatch(event);

                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(static_cast<KeyCode>(key));
                    
                    thisWindows->Dispatch(event);

                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 1);
                    
                    thisWindows->Dispatch(event);

                    break;
                }
                default:
                    break;
            }
        });

        // Key Input event Callback.
        glfwSetCharCallback(m_Windows, [](GLFWwindow* window, unsigned int keycode)
        {
            const auto thisWindows = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
            
            KeyTypedEvent event(static_cast<KeyCode>(keycode));
            
            thisWindows->Dispatch(event);
        });

        // Mouse Button event Callback.
        glfwSetMouseButtonCallback(m_Windows, [](GLFWwindow* window, int button, int action, int mods)
        {
            const auto thisWindows = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
            
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                    
                    thisWindows->Dispatch(event);

                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                    
                    thisWindows->Dispatch(event);

                    break;
                }
                default:
                    break;
            }
        });

        // Mouse Scroll event Callback.
        glfwSetScrollCallback(m_Windows, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            const auto thisWindows = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
            
            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            
            thisWindows->Dispatch(event);
        });

        // Mouse Move event Callback.
        glfwSetCursorPosCallback(m_Windows, [](GLFWwindow* window, double xPos, double yPos)
        {
            const auto thisWindows = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
            
            MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            
            thisWindows->Dispatch(event);
        });
    }

}

#endif