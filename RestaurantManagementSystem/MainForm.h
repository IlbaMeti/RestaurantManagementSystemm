#pragma once
#include "Userr.h"

namespace RestaurantManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(User^ user)
        {
            InitializeComponent();
            lbUserInfo->Text = "ID=" + user->id + ", Name=" + user->name + ", email=" + user->email + ", address=" + user->address;
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ lbUserInfo;
        System::Windows::Forms::Button^ btnProcessOrder;
        System::Windows::Forms::Button^ btnAddOrder;
        System::Windows::Forms::DataGridView^ dgvOrders;
        System::Windows::Forms::Timer^ processTimer; // Declare the Timer

        System::ComponentModel::Container^ components;

        List<array<String^>^>^ dynamicOrders = gcnew List<array<String^>^>(); // Correct List declaration
        DataGridViewRow^ selectedRow; // Store the selected row
        int processingTime = 2000; // Set processing time in milliseconds (2 seconds)

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->lbUserInfo = (gcnew System::Windows::Forms::Label());
            this->btnProcessOrder = (gcnew System::Windows::Forms::Button());
            this->btnAddOrder = (gcnew System::Windows::Forms::Button());
            this->dgvOrders = (gcnew System::Windows::Forms::DataGridView());
            this->processTimer = (gcnew System::Windows::Forms::Timer()); // Initialize the Timer

            this->SuspendLayout();

            // label1
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F));
            this->label1->Location = System::Drawing::Point(2, 7);
            this->label1->Size = System::Drawing::Size(697, 51);
            this->label1->Text = L"Welcome To Dashboard";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // lbUserInfo
            this->lbUserInfo->AutoSize = true;
            this->lbUserInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F));
            this->lbUserInfo->Location = System::Drawing::Point(10, 70);
            this->lbUserInfo->Size = System::Drawing::Size(70, 26);

            // btnProcessOrder
            this->btnProcessOrder->Location = System::Drawing::Point(10, 120);
            this->btnProcessOrder->Size = System::Drawing::Size(150, 30);
            this->btnProcessOrder->Text = L"Process Order";
            this->btnProcessOrder->Click += gcnew System::EventHandler(this, &MainForm::btnProcessOrder_Click);

            // btnAddOrder
            this->btnAddOrder->Location = System::Drawing::Point(180, 120);
            this->btnAddOrder->Size = System::Drawing::Size(150, 30);
            this->btnAddOrder->Text = L"Add Order";
            this->btnAddOrder->Click += gcnew System::EventHandler(this, &MainForm::btnAddOrder_Click);

            // dgvOrders
            this->dgvOrders->Location = System::Drawing::Point(10, 170);
            this->dgvOrders->Size = System::Drawing::Size(680, 200);
            this->dgvOrders->ColumnCount = 4;
            this->dgvOrders->Columns[0]->Name = L"Order ID";
            this->dgvOrders->Columns[1]->Name = L"Table Number";
            this->dgvOrders->Columns[2]->Name = L"Item";
            this->dgvOrders->Columns[3]->Name = L"Status";

            // processTimer
            this->processTimer->Interval = processingTime; // Set the timer interval to 2 seconds
            this->processTimer->Tick += gcnew System::EventHandler(this, &MainForm::processTimer_Tick);

            // MainForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->ClientSize = System::Drawing::Size(701, 401);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->lbUserInfo);
            this->Controls->Add(this->btnProcessOrder);
            this->Controls->Add(this->btnAddOrder);
            this->Controls->Add(this->dgvOrders);
            this->Text = L"MainForm";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        System::Void btnAddOrder_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Simulate user adding a new order
            String^ orderId = (dynamicOrders->Count + 101).ToString(); // Generate unique ID
            String^ tableNumber = (dynamicOrders->Count + 1).ToString();
            String^ item = "Item " + (dynamicOrders->Count + 1).ToString();
            String^ status = "Pending";

            // Add new order to the list
            dynamicOrders->Add(gcnew array<String^> { orderId, tableNumber, item, status });

            // Add the new order to the DataGridView
            this->dgvOrders->Rows->Add(orderId, tableNumber, item, status);

            // Inform the user
            MessageBox::Show("New order added!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        System::Void btnProcessOrder_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (this->dgvOrders->SelectedRows->Count > 0)
            {
                // Get the selected row
                selectedRow = this->dgvOrders->SelectedRows[0];

                // Change status to "Processing" in DataGridView immediately
                selectedRow->Cells[3]->Value = "Processing";

                // Start the timer to simulate processing delay
                processTimer->Start();
            }
            else
            {
                MessageBox::Show("Please select an order to process!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        System::Void processTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            // Stop the timer after 2 seconds
            processTimer->Stop();

            // Change status to "Processed"
            selectedRow->Cells[3]->Value = "Processed";

            // Inform the user that the order has been processed
            MessageBox::Show("Order processed!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

    };
}
