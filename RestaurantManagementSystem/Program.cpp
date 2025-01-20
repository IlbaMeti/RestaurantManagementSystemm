
#include "LoginForm.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    // Enable visual styles and set compatible text rendering
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Create and show the login form
    RestaurantManagementSystem::LoginForm LoginForm;
    LoginForm.ShowDialog();

    // Handle user login result
    User^ user = LoginForm.user;
    if (user != nullptr) {
        MessageBox::Show("Successful Authentication of " + user->name,
            "Login Success", MessageBoxButtons::OK);
    }
    else {
        MessageBox::Show("Authentication Canceled",
            "Login Canceled", MessageBoxButtons::OK);
    }

    return 0; // Return 0 to indicate successful execution
}
