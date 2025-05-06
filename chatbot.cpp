#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to convert input to lowercase for easy comparison
string toLower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Chatbot logic
void chatBot()
{
    cout << "🤖 Welcome to QuickShop Customer Support!\n";
    cout << "How can I assist you today?\n";
    cout << "Type 'exit' to end the conversation.\n\n";

    while (true)
    {
        cout << "You: ";
        string input;
        getline(cin, input);
        string lowerInput = toLower(input);

        if (lowerInput == "exit")
        {
            cout << "Bot: Thank you for visiting QuickShop. Have a great day! 👋\n";
            break;
        }
        else if (lowerInput.find("order") != string::npos && lowerInput.find("status") != string::npos)
        {
            cout << "Bot: Please provide your order ID to check the status.\n";
        }
        else if (lowerInput.find("return") != string::npos)
        {
            cout << "Bot: To return an item, go to 'My Orders' > 'Return Item'. Need help with a specific order?\n";
        }
        else if (lowerInput.find("refund") != string::npos)
        {
            cout << "Bot: Refunds are processed within 5-7 business days after a return is approved.\n";
        }
        else if (lowerInput.find("delivery") != string::npos || lowerInput.find("shipping") != string::npos)
        {
            cout << "Bot: Standard delivery takes 3-5 business days. Express delivery is available too!\n";
        }
        else if (lowerInput.find("help") != string::npos || lowerInput.find("support") != string::npos)
        {
            cout << "Bot: You can contact our 24/7 support at support@quickshop.com or call 1800-123-456.\n";
        }
        else
        {
            cout << "Bot: I'm sorry, I didn't understand that. Can you rephrase or ask something else?\n";
        }
    }
}

// Main function
int main()
{
    chatBot();
    return 0;
}
