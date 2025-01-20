#include "LoginForm.h"
#include "MainForm.h"
#include "RegisterForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    // Enable visual styles and set compatible text rendering
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    User^ user = nullptr;
    while (true) {
        RestaurantManagementSystem::LoginForm loginForm;
        loginForm.ShowDialog();
        if (loginForm.switchToRegister) {
            RestaurantManagementSystem::RegisterForm registerForm;
            registerForm.ShowDialog();
            if (registerForm.switchToLogin) {
                continue;
            }
            else {
                user = registerForm.user;
                break;
            }
        }
        else {
            user = loginForm.user;
            break;
        }
    } // Added missing closing brace for while loop

    if (user != nullptr) {
        RestaurantManagementSystem::MainForm mainForm(user);
        Application::Run(% mainForm);
    }
    else {
        MessageBox::Show("Authentication Canceled",
            "Login Canceled", MessageBoxButtons::OK);
    }
    return 0; // Return 0 to indicate successful execution
}