#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void data(vector<string>& categorys, vector<double>& expenses)
{
    for (int i = 0; i < expenses.size(); ++i)
    {
        cout << categorys.at(i) << " : " << expenses.at(i) << endl;
    }
}

double sum(vector<double>& total)
{
    double Total_expenses = 0;

    for (double v : total)
    {
        Total_expenses += v;
    }

    return Total_expenses;
}

void saveFile(vector<string>& categorys, vector<double>& expenses,
              double stay_monthly, double monthly_budget, double savings_goal,
              double Total_expenses, double Remaining, int index,
              double budget_percent, double needed_for_goal)
{
    string filename = "Report.txt";
    ofstream file(filename);

    file << "\n================ Expense Report ================\n";
    file << "Income: " << stay_monthly << endl;
    file << "Monthly Budget: " << monthly_budget << endl;
    file << "Savings Goal: " << savings_goal << endl;
    file << "Total Expenses: " << Total_expenses << endl;

    if (Remaining >= 0)
        file << "Remaining: " << Remaining << endl;
    else
        file << "Remaining: " << Remaining << " Your expenses exceeded your income." << endl;

    if (budget_percent >= 100)
        file << "Alert: You have reached or exceeded 100% of your budget." << endl;
    else if (budget_percent >= 80)
        file << "Warning: You have used " << budget_percent << "% of your budget." << endl;

    if (Remaining >= savings_goal)
        file << "Great! You reached your savings goal." << endl;
    else
        file << "You still need " << needed_for_goal << " to reach your savings goal." << endl;

    file << "\nExpenses List:" << endl;

    for (int i = 0; i < expenses.size(); ++i)
    {
        file << categorys.at(i) << " : " << expenses.at(i) << endl;
    }

    if (expenses.size() > 0)
        file << "\nBiggest Expense: " << categorys.at(index) << endl;

    if (Remaining < 0)
        file << "Warning: Your expenses exceeded your monthly income!" << endl;

    file << "==================================================" << endl;

    file.close();

    cout << "Report saved as: " << filename << endl;
}

int main()
{
    double stay_monthly, monthly_budget, savings_goal;
    double your_expenses, Total_expenses = 0;
    string category = "";

    cout << "=== EXPENSE TRACKER V2.0 ===" << endl;

    cout << "Please enter your monthly income: ";
    cin >> stay_monthly;

    cout << "Enter your monthly budget: ";
    cin >> monthly_budget;

    cout << "Enter your savings goal: ";
    cin >> savings_goal;

    vector<string> categorys;
    vector<double> expenses;

    double total = 0;

    while (true)
    {
        cout << "\nIncome: " << stay_monthly << endl;
        cout << "Current expenses: " << total << endl;
        cout << "\nChoose category [1-Food, 2-Transport, 3-Shopping, 4-Other, 0-Exit]: ";

        int pick;
        cin >> pick;

        if (pick == 0)
            break;

        if (pick == 1)
            category = "Food";
        else if (pick == 2)
            category = "Transport";
        else if (pick == 3)
            category = "Shopping";
        else if (pick == 4)
        {
            cout << "Enter custom category name: ";
            cin >> category;
        }
        else
        {
            cout << "Invalid choice, try again." << endl;
            continue;
        }

        categorys.push_back(category);

        cout << "Enter the expense: ";
        cin >> your_expenses;
        expenses.push_back(your_expenses);

        total = sum(expenses);

        if (total > stay_monthly)
        {
            cout << "Your expenses exceed your monthly income." << endl;
        }
    }

    Total_expenses = sum(expenses);
    double Remaining = stay_monthly - Total_expenses;

    int index = 0;
    if (expenses.size() > 0)
    {
        double max = expenses.at(0);

        for (int i = 0; i < expenses.size(); ++i)
        {
            if (expenses.at(i) > max)
            {
                max = expenses.at(i);
                index = i;
            }
        }
    }

    double budget_percent = 0;
    if (monthly_budget > 0)
    {
        budget_percent = (Total_expenses / monthly_budget) * 100;
    }

    double needed_for_goal = 0;
    if (Remaining < savings_goal)
    {
        needed_for_goal = savings_goal - Remaining;
    }

    cout << "\n================ Expense Report ================\n";
    cout << "Income: " << stay_monthly << endl;
    cout << "Monthly Budget: " << monthly_budget << endl;
    cout << "Savings Goal: " << savings_goal << endl;
    cout << "Total Expenses: " << Total_expenses << endl;

    if (Remaining >= 0)
        cout << "Remaining: " << Remaining << endl;
    else
        cout << "Remaining: " << Remaining << " Your expenses exceeded your income." << endl;

    if (budget_percent >= 100)
        cout << "Alert: You have reached or exceeded 100% of your budget." << endl;
    else if (budget_percent >= 80)
        cout << "Warning: You have used " << budget_percent << "% of your budget." << endl;

    if (Remaining >= savings_goal)
        cout << "Great! You reached your savings goal." << endl;
    else
        cout << "You still need " << needed_for_goal << " to reach your savings goal." << endl;

    cout << "\nExpenses List:" << endl;
    data(categorys, expenses);

    if (expenses.size() > 0)
        cout << "\nBiggest Expense: " << categorys.at(index) << endl;

    if (Remaining < 0)
        cout << "Warning: Your expenses exceeded your monthly income!" << endl;

    cout << "==================================================" << endl;

    char ch;
    cout << "\nDo you want to save as a file (y/n)? ";
    cin >> ch;

    if (ch == 'y' || ch == 'Y')
    {
        saveFile(categorys, expenses, stay_monthly, monthly_budget, savings_goal,
                 Total_expenses, Remaining, index, budget_percent, needed_for_goal);
    }

    return 0;
}
