#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <cmath>
#include <cstdlib>
#include <limits>

// We use these constants so we don't have magic numbers floating around when drawing the UI
const int ROWS = 5;
const int COLS = 3;

// These 2D arrays act as the blueprint for our calculator's display grid.
const std::string symbol[ROWS][COLS] = {
    {"+", "-", "*"},
    {"/", "m", "L"},
    {"S", "C", "P"},
    {"s", "c", "t"},
    {"r", "k", "."}};

const std::string operation[ROWS][COLS] = {
    {"Add", "Minus", "Multiply"},
    {"Divide", "Mod", "Log"},
    {"Square", "Cube", "Power"},
    {"sin", "cos", "tan"},
    {"Sq Root", "Clear", "Close"}};

// Standard ANSI escape codes to make the terminal look a bit more polished.
const std::string RESET = "\033[0m";
const std::string BLUE = "\033[34m";
const std::string CYAN = "\033[36m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string MAGENTA = "\033[35m";
const std::string BOLD = "\033[1m";
const std::string BLACK = "\033[30m";
const std::string WHITE = "\033[37m";
const std::string BG_GREEN = "\033[42m";
const std::string BG_BLUE = "\033[44m";
const std::string BG_RED = "\033[41m";
const std::string BG_YELLOW = "\033[43m";
const std::string BG_CYAN = "\033[46m";

// Function prototypes so main() knows these exist before they are actually defined.
void showCalculator();
void displayOutput(double answer);
void initializeMenu();
void userInput();
void clearScreen();
double getValidNumber(const std::string &prompt);

double add(double num1, double num2);
double subtract(double num1, double num2);
double multiply(double num1, double num2);
double divide(double num1, double num2);
int mod(int num1, int num2);
double square(double num1);
double cube(double num1);

int main()
{
    // Keep main clean. All the heavy lifting is done inside userInput.
    userInput();
    return 0;
}

// This function loops through our arrays and draws the UI grid.
// It uses std::setw to make sure everything lines up perfectly, regardless of word length.
void initializeMenu()
{
    std::cout << std::right;
    for (int i = 0; i < 5; i++)
    {
        std::cout << BLUE << "|" << RESET;

        // Draw the symbols (e.g., +, -, *)
        for (int j = 0; j < 3; j++)
        {
            std::cout << YELLOW
                      << std::setw(15) << symbol[i][j]
                      << RESET
                      << BLUE << std::setw(5) << "|"
                      << RESET;
        }

        std::cout << '\n';
        std::cout << BLUE << "|" << RESET;

        // Draw the text labels right underneath the symbols (e.g., Add, Minus, Multiply)
        for (int j = 0; j < 3; j++)
        {
            std::cout << GREEN
                      << std::setw(15) << operation[i][j]
                      << RESET
                      << BLUE << std::setw(5) << "|"
                      << RESET;
        }

        std::cout << '\n';
        std::cout << BLUE
                  << "-------------------------------------------------------------\n"
                  << RESET;
    }
}

// Just prints the top header banner before drawing the rest of the menu.
void showCalculator()
{
    std::cout << BLUE
              << "-------------------------------------------------------------\n";
    std::cout << "|"
              << BOLD << CYAN
              << "\t\tSCIENTIFIC CALCULATOR\t\t"
              << RESET << BLUE << std::setw(14) << "|\n";
    std::cout << "-------------------------------------------------------------\n"
              << RESET;
    initializeMenu();
}

// Swaps out the top header banner with the live running total.
void displayOutput(double answer)
{
    std::cout << BLUE
              << "-------------------------------------------------------------\n";
    std::cout << "|"
              << BOLD << CYAN
              << std::setw(37) << "CURRENT"
              << RESET << BLUE
              << std::setw(24) << "|\n";
    std::cout << "-------------------------------------------------------------\n";
    std::cout << BLUE << "|"
              << BG_GREEN << BLACK << BOLD
              << std::left << std::setw(59)
              << (" OUTPUT : " + std::to_string(answer))
              << RESET
              << BLUE << "|\n";
    std::cout << "-------------------------------------------------------------\n"
              << RESET;

    initializeMenu();
}

// This is a crucial safety net.
// If cin expects a number and the user types a letter, the program will crash into an infinite loop.
// This function traps them until they type an actual number, clearing the error flags each time.
double getValidNumber(const std::string &prompt)
{
    double num;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> num)
        {
            return num; // Got a good number, we can leave.
        }

        // Input was bad. Clear the error state and dump whatever garbage was in the buffer.
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << BG_RED << WHITE << " Error: Invalid input. Please enter a number. " << RESET << '\n';
    }
}

// This is the core logic loop. It handles state, user choices, and routes to the math functions.
void userInput()
{
    // Grouping these makes our logic much cleaner later.
    // We know instantly if we need to ask the user for one number or two.
    std::set<char> two_operand_ops = {'+', '-', '*', '/', 'm', 'P'};
    std::set<char> one_operand_ops = {'L', 'S', 'C', 's', 'c', 't', 'r'};

    double num1 = 0.0;
    double num2 = 0.0;

    // Tracks if we are in the middle of a calculation.
    // If true, we chain the next math operation onto the previous answer.
    bool hasPreviousResult = false;

    double answer = 0.0;
    char input = '\n';

    while (true) // Run until they explicitly hit '.' to quit
    {
        // Decide whether to show the clean start screen or the one with the running total
        if (hasPreviousResult)
        {
            clearScreen();
            displayOutput(answer);
        }
        else
        {
            clearScreen();
            showCalculator();
        }

        std::cout << '\n'
                  << MAGENTA << "Enter Your Choice : " << RESET;
        std::cin >> input;

        // Handle early exits first so we don't accidentally ask for numbers
        if (input == '.')
            break;

        if (input == 'k')
        { // Reset the calculator state
            hasPreviousResult = false;
            answer = 0.0;
            continue;
        }

        // Figure out how many numbers we need to grab from the user based on their choice
        if (two_operand_ops.count(input))
        {
            if (hasPreviousResult)
            {
                num1 = answer; // Chain the previous result
                num2 = getValidNumber("Enter Number: ");
            }
            else
            {
                num1 = getValidNumber("Enter First Number: ");
                num2 = getValidNumber("Enter Second Number: ");
            }
            hasPreviousResult = true;
        }
        else if (one_operand_ops.count(input))
        {
            if (hasPreviousResult)
            {
                num1 = answer;
            }
            else
            {
                num1 = getValidNumber("Enter Number: ");
            }
            hasPreviousResult = true;
        }
        else
        {
            // They typed a letter that isn't on the menu.
            // We pause here so they can actually read the error before the loop clears the screen again.
            std::cout << CYAN << "~~~~~ You Entered an Invalid Value ~~~~~" << RESET << std::endl;
            hasPreviousResult = false;
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            continue;
        }

        // Now that we safely have our numbers, actually do the math.
        switch (input)
        {
        case '+':
            answer = add(num1, num2);
            break;
        case '-':
            answer = subtract(num1, num2);
            break;
        case '*':
            answer = multiply(num1, num2);
            break;
        case '/':
            if (num2 == 0)
            { // Math safety check
                std::cout << BG_RED << WHITE << " Error: Division by zero! " << RESET << std::endl;
                hasPreviousResult = false;
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }
            answer = divide(num1, num2);
            break;
        case 'm':
            answer = mod(static_cast<int>(num1), static_cast<int>(num2));
            break;
        case 'L':
            answer = log(num1);
            break;
        case 'S':
            answer = square(num1);
            break;
        case 'C':
            answer = cube(num1);
            break;
        case 'P':
            answer = pow(num1, num2);
            break;
        case 's':
            answer = sin(num1);
            break;
        case 'c':
            answer = cos(num1);
            break;
        case 't':
            answer = tan(num1);
            break;
        case 'r':
            answer = sqrt(num1);
            break;
        }
    }
}

// A quick cross-platform hack to clear the terminal window
void clearScreen()
{
#if defined(_WIN32)
    system("cls"); // For Windows
#else
    system("clear"); // For Mac/Linux
#endif
}

// ---------------------------------------------------------
// Actual math logic down here.
// ---------------------------------------------------------

double add(double num1, double num2) { return num1 + num2; }
double subtract(double num1, double num2) { return num1 - num2; }
double multiply(double num1, double num2) { return num1 * num2; }
double divide(double num1, double num2) { return num1 / num2; }
int mod(int num1, int num2) { return num1 % num2; }
double square(double num1) { return num1 * num1; }
double cube(double num1) { return num1 * num1 * num1; }