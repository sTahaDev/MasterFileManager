#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

int screenWidth = 800;
int screenHeight = 600;

string path = "/";

vector<string> ListFiles(const string &userDirectoryPath)
{
    vector<string> fileList;
    fs::path userPath(userDirectoryPath);

    if (fs::is_directory(userPath))
    {
        for (const auto &entry : fs::directory_iterator(userPath))
        {

            fileList.push_back(entry.path().filename().string());
        }
    }
    else
    {
        cerr << "Hata: Kullanıcı dizini bulunamadı." << endl;
    }

    return fileList;
}
void ListItems()
{

    for (int i = 0; i < ListFiles(path).size(); i++)
    {

        if (i > 0)
        {
            ImGui::Separator();
        }

        if (ImGui::Button(ListFiles(path).at(i).c_str()))
        {

            path += (ListFiles(path).at(i) + "/");
            cout << path << endl;
        }
    }
    ImGui::Separator();
}
void pathBack()
{

    if (path != "/")
    {
        vector<string> result;

        // Girdiyi std::string stream'e (std::istringstream) dönüştürün.
        istringstream ss(path);
        string token;
        while (getline(ss, token, '/'))
        {
            result.push_back(token + "/");
        }

        result.pop_back();

        string newPath = "";
        for (const string &item : result)
        {
            newPath += item;
        }
        cout << newPath << endl;
        path = newPath;
    }
}
void RenderUI()
{

    ListItems();
}

void navbar()
{
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 originalButtonColor = style.Colors[ImGuiCol_Button];
    style.Colors[ImGuiCol_Button] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Özel renk (mavi tonu)

    if (ImGui::Button("<--", ImVec2(300, 40)))
    {
        pathBack();
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete Folder", ImVec2(200, 40)))
    {
    }
    // Stil özelleştirmesini geri yükleyin
    style.Colors[ImGuiCol_Button] = originalButtonColor;
}

int main()
{

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Master File Explorer", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    ImGuiIO &io = ImGui::GetIO();

    io.Fonts->AddFontFromFileTTF("./assets/roboto/Roboto-Bold.ttf", 20);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(screenWidth, 60));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::PushStyleColor(2, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
        ImGui::Begin("navbarwindow", NULL, window_flags);

        navbar();

        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(screenWidth, screenHeight - 60));
        ImGui::SetNextWindowPos(ImVec2(0, 60));

        // Arka plan rengini değiştir
        

        ImGui::Begin("mainwindow", NULL, window_flags);

        RenderUI();

        

        ImGui::End();
        ImGui::PopStyleColor();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
