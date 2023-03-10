# 1. Introduction

## 1.1 About this Guide

This document describes how to install and work with lib264 decoder from Ittiam. It also provides brief information on how to build and use the sample application that accompanies this component.

The API exposed by the lib264 decoder is in compliance with Ittiam systems' Video API Standard

## 1.2 Intended Audience

This document is used to explain the user guidelines for lib264 decoder. This is an open-source project licensed under Ittiam Systems.

# 2. Installation

This section provides a brief description on the system requirements and instructions for installing the codec component. It also provides information on building and running the sample test application.

## 2.1 Hardware requirements

| **Configuration** | **Device Details** |
| --- | --- |
| x86\_64/Linux | PC with x86 processor |
| aarch64/Linux | PC with aarch64 processor |
| aarch64/Android | Android Phone with ARM aarch64 Processor |

&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
Table: Hardware Details

## 2.2 Software requirements

| **Configuration** | **Tool-chain** |
| --- | --- |
| x86\_64/Linux | cmake \>= 3.24.0 |
| aarch64/Linux | aarch64\_toolchain.cmake |
| aarch64/Android | android-ndk-r25b and clang |

&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
Table: Tool chain Details

## 2.3 Steps to build and execute

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

## 2.4 Update the configuration file. Details of each parameter is given below

| **Parameter** | **Description** |
| --- | --- |
| --input | Input file |
| --save\_output | 0/1 to disable/enable decoded yuv file dump|
| --num\_frames | Number of frames to be processed. Set to -1 to decode all the frames |
| --output | Output file |
| --chroma\_format | Display chroma format supported formats are YUV\_420P, YUV\_420SP\_UV, YUV\_420SP\_VU, RGB\_565 |
| --share\_display\_buf | To run the decoder in shared mode where decoder shares the reference buffers with display|
| --num\_cores | Number of cores to be used in the codec |
| --loopback | To run the decoder in loopback mode |
| --fps | Stream fps |
| --arch | Give specific architecture to run the executable |

<p align="center">Table: Configuration Parameters</p>

# 3. User Guidelines

## 3.1 General Guidelines

- Copy the stream to be decoded in the same directory and edit the ```test.cfg``` file accordingly
- Copy this directory to a folder on target
- In case of android platform copy the above executable, test clip and the config file to ```/data/local/tmp/``` using adb push and in adb shell, cd to ```/data/local/tmp```
- ```chmod a+x <executable>```
- ```./<executable> test.cfg```

## 3.2 Profiling Guidelines

- Edit the cfg file to dump the decoded yuv
- Run the executable
- Profile summary is printed at the end of decode.
- FPS achieved indicates the number of frames that codec can handle at the current frequency of the target.
