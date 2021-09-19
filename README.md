# Hello SFML

### Get Started

This README assumes you have VS Code, vcpkg, and the VS Code cmake-tools extension installed
You should be prompted to install all recommended extensions on VS Code startup.

Step 1: Choose your perferred Cmake Kit

- I typically use `Visual Studio Community 2019 Release - amd64`

Step 2: Run Cmake: Configure task

- This will run a localized `vcpkg install` which will place all project dependencies inside a directory
  named `vcpkg_installed`

Step 3: Run post-build-windows.bat

- This will copy over the assets into the cmake generated build directory.

Step 4: Run the Cmake: Build task

Step 5: Run the executable, you should see red text "Hello" on a blue background
