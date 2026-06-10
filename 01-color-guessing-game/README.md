# 🎨 Color Guessing Game

A simple **Color Guessing Game** made in **C++**.

The computer randomly selects a color, and the player has to guess the correct one.

This project works on:

* Windows
* Linux
* macOS

---

## Code Explanation

This project is written in **C++** and organized into small functions to make the code easier to understand.

The program starts inside the `main()` function, where a random color is generated and the game loop begins.

### How The Code Works

#### 1. Operating System Detection

The game automatically detects the operating system using:

```cpp
#if defined(_WIN32)
#elif defined(__APPLE__)
#elif defined(__linux__)
```

This is important because terminal commands are different on each system.

For example:

* **Windows** uses:

```cpp
system("cls");
```

* **Linux/macOS** use:

```cpp
system("clear");
```

The game also uses different methods for terminal colors depending on the operating system.

---

#### 2. Color Enum

The game stores colors using an `enum`:

```cpp
enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE
};
```

This makes the code easier to read.

Instead of using numbers:

```cpp
0
1
2
```

the code uses readable names:

```cpp
RED
GREEN
BLUE
```

---

#### 3. Random Color Generation

The computer randomly selects a color using:

```cpp
std::rand() % 5
```

The `% 5` keeps the result between:

```text
0 - 4
```

which matches the available colors.

To avoid the same result every time the game starts, the program uses:

```cpp
std::srand(
    static_cast<unsigned>(
        std::time(nullptr)
    )
);
```

This uses the current time as a random seed.

---

#### 4. Game Loop

The game runs inside:

```cpp
while(true)
```

This loop keeps the game running until the player guesses correctly.

When the guess is correct:

```cpp
break;
```

stops the loop.

---

#### 5. User Input

The player's guess is stored inside:

```cpp
std::string guess;
```

Input is taken using:

```cpp
std::cin >> guess;
```

---

#### 6. Case-Insensitive Input

The game ignores uppercase and lowercase letters.

Examples:

```text
RED
red
ReD
```

All work correctly.

This is done using the `toLower()` function.

---

#### 7. Terminal Colors

The game displays colors in the terminal.

Examples:

* Red appears in red
* Blue appears in blue
* Green appears in green

Windows uses:

```cpp
SetConsoleTextAttribute()
```

Linux and macOS use ANSI escape codes:

```cpp
"\033[31m"
```

for terminal colors.

---

#### 8. Helper Functions

The project is divided into small functions.

| Function                | Purpose                    |
| ----------------------- | -------------------------- |
| `generateRandomColor()` | Generates random color     |
| `colorToString()`       | Converts enum to text      |
| `toLower()`             | Converts text to lowercase |
| `clearScreen()`         | Clears terminal            |
| `pause()`               | Adds short delay           |
| `setConsoleColor()`     | Changes terminal color     |
| `resetColor()`          | Resets terminal color      |

Using functions makes the code cleaner and easier to manage.

---

## Features

* Random color generation
* Colored text in terminal
* Case-insensitive input (`RED`, `red`, `ReD`)
* Cross-platform support
* Beginner-friendly code

---

## Available Colors

```text
Red
Green
Blue
Yellow
Purple
```

---

## How It Works

1. The computer picks a random color.
2. Available colors are shown.
3. Enter your guess.
4. Guess the correct color to win.

Example:

```text
=== Color Guessing Game ===
Running on: Windows

Available colors:
Red Green Blue Yellow Purple

Enter your guess: blue

Wrong guess! Try again...

Enter your guess: red

Correct! The color was Red!
```

---

## Run The Project

### Option 1: Copy The Code

1. Copy the code.
2. Create a file named:

```text
main.cpp
```

3. Paste the code.
4. Compile and run.

---

### Option 2: Clone From GitHub

Clone repository:

```bash
git clone https://github.com/engg-angrejsingh/fun-cpp-projects.git
```

Go to project folder:

```bash
cd color-guessing-game
```

Compile:

```bash
g++ main.cpp -o game
```

Run:

### Windows

```bash
game
```

### Linux / macOS

```bash
./game
```

> https://github.com/engg-angrejsingh/fun-cpp-projects.git

---

## How To Run

### Windows

Compile:

```bash
g++ main.cpp -o game
```

Run:

```bash
game
```

---

### Linux

Compile:

```bash
g++ main.cpp -o game
```

Run:

```bash
./game
```

---

### macOS

Compile:

```bash
g++ main.cpp -o game
```

Run:

```bash
./game
```

If `g++` is missing:

```bash
xcode-select --install
```

---

## Project Structure

```text
01-color-guessing-game/
│── main.cpp
│── README.md
```

---

## About

This project was made **for fun and learning C++**.

It helps practice:

* Functions
* Loops
* Random numbers
* Strings
* Cross-platform programming

---

## Author

**Angrej Singh**

Made with C++ for fun and learning.

