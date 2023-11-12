#include "Libs.h"
#include "Window.h"
#include "user.h"
#include "figures.h"
#include "Button.h"


int main() {
    /*
    gdd_list::_list<int> list;

    for (int i = 0; i < 3; i++)
        list.append(i);

    list.print();
    list.clear(1);
    list.print();

    return 0;
    */
    GLFWwindow* glfwwindow = CreateInitialWindow();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    InitSettings();
    WindowInit();
    while (!glfwWindowShouldClose(glfwwindow)) {
        CreateNewWindow(glfwwindow);
        srand(time(NULL));
        glClearColor(0.9, 0.9, 0.9, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //cout << window_list[Window_Index].rezult_string << endl;
        window_list[Window_Index].show();

        ClearParametry();
        glfwPollEvents();
        EventHandling(glfwwindow);
        glfwSwapBuffers(glfwwindow);
    }
    glfwTerminate();
    return 0;
}