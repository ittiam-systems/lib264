# **AVC/H.264 Library**

## **Introduction**

This is an implementation of AVC/H.264 library. Following are the features of this repository.

- Supports H264 decoder functionality upto High Profile and Level 5.1
- Optimized on ARM and Intel platforms
- Decoder is multi thread enabled
- Repository contains source and header files for lib264 decoder along with sample application files
- Supports resolution upto 4K
- Supports parsing and exporting of ```SEI messages``` like ```MDCV```, ```CLLI```, ```FGC```, etc.

### **Prerequisites**

- cmake >= 3.24
- gcc / clang toolchain (For x86-64 and aarch64 Linux builds)

### **After Cloning**

- To download all submodules -

  ```bash
    lib264Path=<Path to lib264 repo>
    cd ${lib264Path}
    git submodule update --init --recursive
  ```

### **Supported Platforms**

- x86_64 on Linux.
- aarch64 on Linux.
- aarch64 on Android.
- x86_64 on Windows.

### **lib264 Build steps**

#### **Building for x86-64 Linux**

- Create a buildtree

  ```bash
    lib264Path=<Path to lib264 repo>
    buildTree=<Name of buildTree folder>
    installPath=<Path to install folder>
    cd ${lib264Path}
    cmake . -B ${buildTree} -DCMAKE_INSTALL_BINDIR:STRING=${installPath}
  ```

- Build using buildtree

  ```bash
    cmake --build ${buildTree}
  ```

- Install (Installs to 'installPath' folder)

  ```bash
    cmake --install ${buildTree}
  ```

- Command to run the executable

  ```bash
    ./lib264dec <path of configuration file>
  ```

#### **Building for aarch64 Linux**

- Create a buildtree

  ```bash
    toolchainPath=<Path to aarch64 toolchain>
    lib264Path=<Path to lib264 repo>
    buildTree=<Name of buildTree folder>
    installPath=<Path to install folder>
    cd ${lib264Path}
    PATH=${toolchainPath}:${PATH} cmake . -B ${buildTree}\
    -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchains/aarch64_toolchain.cmake\
    -DCMAKE_INSTALL_BINDIR:STRING=${installPath}
  ```

- Build using buildtree

  ```bash
    cmake --build ${buildTree}
  ```

- Install (Installs to 'installPath' folder)

  ```bash
    cmake --install ${buildTree}
  ```

- Command to run the executable

  ```bash
    ./lib264dec <path of configuration file>
  ```

#### **Building for aarch64 Android**

- Create a buildtree

  ```bash
    lib264Path=<Path to lib264 repo>
    buildTree=<Name of buildTree folder>
    installPath=<Path to install folder>
    cd ${lib264Path}
    PATH=${toolchainPath}:${PATH} cmake . -B ${buildTree}\
    -DCMAKE_SYSTEM_NAME=Android\
    -DCMAKE_SYSTEM_PROCESSOR=aarch64\
    -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a\
    -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang\
    -DCMAKE_ANDROID_NDK=<Path to android-ndk folder>\
    -DCMAKE_INSTALL_BINDIR:STRING=${installPath}
  ```

- Build using buildtree

  ```bash
    cmake --build ${buildTree}
  ```

- Install (Installs to 'installPath' folder)

  ```bash
    cmake --install ${buildTree}
  ```

- Command to run the executable

  ```bash
    ./lib264dec <path of configuration file>
  ```

#### **Building for x86-64 Windows**

> ***Using command line in git bash***

- Create a buildtree

  ```bash
    libfgsPath=<Path to libfgs repo>
    buildTree=<Name of buildTree folder>
    installPath=<Path to install folder>
    cd ${libfgsPath}
    cmake . -B ${buildTree} -A x64\
    -DCMAKE_INSTALL_BINDIR:STRING=${installPath}
  ```

- Build using buildtree

  ```bash
    cmake --build ${buildTree} -- -p:Configuration="Release"
  ```

- Install (Installs to 'installPath' folder)

  ```bash
    cmake --install ${buildTree}
  ```

- Command to run the executable

  ```bash
    ./lib264dec.exe <path of configuration file>
  ```

> ***Using command line in cmd or VS command prompt***

- Configure cmake

  ```bash
    cmake . -B <build directory> -A x64 -DCMAKE_INSTALL_BINDIR:STRING=<build directory>
  ```

- Build using buildtree

  ```bash
    cmake --build ${buildTree} -- -p:Configuration="Release"
  ```

- Install (Installs to 'installPath' folder)

  ```bash
    cmake --install ${buildTree}
  ```

- Command to run the executable

  ```bash
    ./lib264dec.exe <path of configuration file>
  ```

> ***Build using Visual Studio***

- Configure cmake using command line in git bash or cmd or VS cmd

  ```bash
    cmake . -B <build directory> -A x64 -DCMAKE_INSTALL_BINDIR:STRING=<build directory>
  ```

- Open .sln (solution) in Visual Studio

  ```bash
    Use F7 or build using Release/Debug options
  ```

- Command to run the executable

  ```bash
    ./lib264dec.exe <path of configuration file>
  ```

### **Apply clang format**

To apply 'clang-format' to the modified code, please follow the steps below.

- To configure the hooks path locally for the repository

  ```bash
    git config --local core.hooksPath ./hooks
  ```

- To apply the clang-format for the modified code against master

  ```bash
    git clang-format -f master <file>
  ```

### **Guidelines working with lib264 application**

Please refer to the [application guidelines](test/decoder/README.md) for the following processes

- Hardware and Software requirements
- Steps to build and execute
- General Guidelines
- Profiling Guidelines

### **Guidelines working with lib264 API**

Please refer to the [API guidelines](decoder/api/README.md) for the following processes

- APIs of the lib264 decoder
- Data structures and enumerations
- Input/output structure details for Video Control API
- Error/Status Codes
- lib264 codec specific notes

### **Guidelines working with GitHub**

- Please refer to the [guidelines](GUIDELINES.md) for the following processes
- Reporting issues
- Creating Pull Request
- Commit message standards

### **FFmpeg Plugin Support**

An intial version of a FFmpeg plugin is provided along with documentation for integrating the H264 Decoder library and plugin into FFmpeg framework.

For more details, refer to plugin [README](ffmpeg_plugin/)

## **LICENSE**
A BSD 3-Clause-Clear license is applicable. Refer to the [LICENSE](https://github.com/ittiam-systems/lib264/blob/main/LICENSE) file together with [LICENSE2](https://github.com/ittiam-systems/lib264/blob/main/LICENSE2) file.
