#include "stdafx.h"

int main()
{
    try
    {
        // - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
        if (glfwInit() != GLFW_TRUE)
        {
            throw std::runtime_error("Failed to initialize GLFW!");
        }

        // - Definimos las características que queremos que tenga el contexto gráfico
        // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
        // modo Core Profile.
        glfwWindowHint(GLFW_SAMPLES, 4); // - Activa antialiasing con 4 muestras.
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // - Esta y las 2
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // siguientes activan un contexto
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // OpenGL Core Profile 4.1.

        // - Tamaño, título de la ventana, en ventana y no en pantalla completa, sin compartir recursos con otras ventanas.
        GLFWwindow* window = glfwCreateWindow(1080, 960, "Algoritmos Geometricos", nullptr, nullptr);

        // - Comprobamos si la creación de la ventana ha tenido éxito.
        if (window == nullptr)
        {
            glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
            throw std::runtime_error("Failed to open GLFW window!");
        }

        // - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
        // ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
        glfwMakeContextCurrent(window);

        // - Ahora inicializamos GLEW.
        // IMPORTANTE: GLEW debe inicializarse siempre DESPUÉS de que se haya
        // inicializado GLFW y creado la ventana
        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            glfwDestroyWindow(window);
            glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
            throw std::runtime_error("Failed to initialize GLEW!");
        }

        // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto 3D construido.
        std::cout << glGetString(GL_RENDERER) << std::endl << glGetString(GL_VENDOR) << std::endl
                  << glGetString(GL_VERSION) << std::endl << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


        // RENDERER
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE);

        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xffffffff);

        glEnable(GL_PROGRAM_POINT_SIZE);

        glEnable(GL_POLYGON_OFFSET_FILL);

        // LOOP
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // Draw call

            glfwSwapBuffers(window);
        }
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }

    // - Una vez terminado el ciclo de eventos, liberar recursos, etc.
    std::cout << "Finishing application..." << std::endl;
}



