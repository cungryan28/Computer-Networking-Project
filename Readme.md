# Socket Template Project

This project is a template for creating socket-based client-server applications in C++. It includes both client and server implementations, along with necessary build configurations.

## Files and Directories

- **client.cpp**: Source code for the client application.
- **server.cpp**: Source code for the server application.
- **CMakeLists.txt**: CMake configuration file for building the project.
- **build/**: Directory containing build artifacts.
- **vcpkg/**: Directory for the vcpkg package manager, used for managing dependencies.

## Building the Project

To build the project, follow these steps:

1. Install [CMake](https://cmake.org/) and [vcpkg](https://github.com/microsoft/vcpkg).
2. Configure the project using CMake:
    ```sh
    cmake -S . -B build
    ```
3. Build the project:
    ```sh
    cmake --build build
    ```

## Running the Applications

After building the project, you can run the client and server applications:

- To run the server:
    ```sh
    ./build/server.exe
    ```

- To run the client:
    ```sh
    ./build/client.exe
    ```


## License

This project is licensed under the MIT License. See the [LICENSE.txt](vcpkg/LICENSE.txt) file for details.

## Contributing

Contributions are welcome! Please see the [CONTRIBUTING.md](vcpkg/CONTRIBUTING.md) file for guidelines.

## Contact

For any questions or issues, please open an issue on the GitHub repository.