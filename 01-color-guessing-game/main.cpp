#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

// Detect operating system
#if defined(_WIN32)
    #include <windows.h>
    const std::string OS_NAME = "Windows";

#elif defined(__APPLE__)
    const std::string OS_NAME = "macOS";

#elif defined(__linux__)
    const std::string OS_NAME = "Linux";

#else
    const std::string OS_NAME = "Unknown OS";
#endif

// Available colors for the game
enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE
};

// Function declarations
Color generateRandomColor();
std::string colorToString(Color color);
std::string toLower(std::string str);

void clearScreen();
void pause(int milliseconds);

void setConsoleColor(Color color);
void resetColor();

int main() {

    // Seed random generator
    std::srand(
        static_cast<unsigned>(
            std::time(nullptr)
        )
    );

    Color targetColor =
        generateRandomColor();

    std::string guess;

    while (true) {

        clearScreen();

        std::cout
            << "=== Color Guessing Game ===\n";

        std::cout
            << "Running on: "
            << OS_NAME
            << "\n\n";

        std::cout
            << "Available colors:\n";

        for (int i = 0; i < 5; i++) {

            Color color =
                static_cast<Color>(i);

            setConsoleColor(color);

            std::cout
                << colorToString(color)
                << " ";
        }

        resetColor();

        std::cout
            << "\n\nEnter your guess: ";

        std::cin >> guess;

        // Ignore uppercase/lowercase differences
        if (toLower(guess)
            ==
            toLower(
                colorToString(targetColor)
            )) {

            setConsoleColor(targetColor);

            std::cout
                << "\nCorrect! "
                << "The color was "
                << colorToString(targetColor)
                << "!\n";

            resetColor();
            break;

        } else {

            std::cout
                << "\nWrong guess! "
                << "Try again...\n";

            pause(1500);
        }
    }

    return 0;
}

Color generateRandomColor() {

    return static_cast<Color>(
        std::rand() % 5
    );
}

std::string colorToString(
    Color color
) {

    switch (color) {

        case RED:
            return "Red";

        case GREEN:
            return "Green";

        case BLUE:
            return "Blue";

        case YELLOW:
            return "Yellow";

        case PURPLE:
            return "Purple";

        default:
            return "Unknown";
    }
}

// Convert text to lowercase
std::string toLower(
    std::string str
) {

    std::transform(
        str.begin(),
        str.end(),
        str.begin(),
        ::tolower
    );

    return str;
}

// Clear terminal screen
void clearScreen() {

#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif

}

// Pause program for a short time
void pause(int milliseconds) {

    std::this_thread
        ::sleep_for(
            std::chrono
            ::milliseconds(
                milliseconds
            )
        );
}

// Change terminal text color
void setConsoleColor(
    Color color
) {

#if defined(_WIN32)

    HANDLE hConsole =
        GetStdHandle(
            STD_OUTPUT_HANDLE
        );

    int colorCode = 7;

    switch (color) {

        case RED:
            colorCode = 12;
            break;

        case GREEN:
            colorCode = 10;
            break;

        case BLUE:
            colorCode = 9;
            break;

        case YELLOW:
            colorCode = 14;
            break;

        case PURPLE:
            colorCode = 13;
            break;
    }

    SetConsoleTextAttribute(
        hConsole,
        colorCode
    );

#else

    switch (color) {

        case RED:
            std::cout << "\033[31m";
            break;

        case GREEN:
            std::cout << "\033[32m";
            break;

        case BLUE:
            std::cout << "\033[34m";
            break;

        case YELLOW:
            std::cout << "\033[33m";
            break;

        case PURPLE:
            std::cout << "\033[35m";
            break;
    }

#endif
}

// Reset terminal color
void resetColor() {

#if defined(_WIN32)

    SetConsoleTextAttribute(
        GetStdHandle(
            STD_OUTPUT_HANDLE
        ),
        7
    );

#else

    std::cout
        << "\033[0m";

#endif
}