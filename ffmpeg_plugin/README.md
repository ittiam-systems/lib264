# **Introduction**

FFmpeg plugins provide an efficient and fast way for media application development. Ittiam FFmpeg plugin benefit the developers for application development using the standard FFmpeg APIs.
This document describes steps for integration of i264 Decoder plugin code provided by Ittiam with FFmpeg -- 5.1. The FFmpeg source code is available at <https://git.ffmpeg.org/ffmpeg.git>.

# **Integration of Plugin for Linux**

## **Prerequisite**

Git needs to be installed in host PC. It can be downloaded from the below link: <https://git-scm.com/downloads>.

## **Plugin Integration to FFmpeg**

The i264 Decoder plugin can be integrated into FFmpeg in two methods:
-   Using the patch file
-   Manual integration

### **Integration Using a Patch File**

#### **Applying the Patch**

1.   Build the decoder library by following the steps mentioned in decoder [README](/../../)

2.   Download the FFmpeg source code version 5.1 from <https://git.ffmpeg.org/ffmpeg.git> using the below commands in Git bash.
        ```
        git clone https://git.ffmpeg.org/ffmpeg.git
        cd ffmpeg
        git checkout release/5.1
        ```

3.   Copy the patch file *lib264/ffmpeg_plugin/ffmpeg_ih264d.patch* to *ffmpeg* directory.

4.   To apply the patch *ffmpeg_ih264d*, use the command given below:
        ```
        git apply ffmpeg_ih264d.patch
        ```

5.   As the library *lib264_library.a* is not part of the patch, it needs to be copied to *ffmpeg* folder manually.

6.   Copy *lib264_library.a* from *${buildTree}* directory to *ffmpeg/*.

7.   Move to [Steps for Configure, Build and Execute](#steps-for-configure-build-and-execute).

### **Manual Integration**

#### **Steps for Integrating i264 Decoder Plugin into FFmpeg Framework Manually**

1.  Build the decoder library by following the steps mentioned in decoder [README](/../../)

2.  Download the FFmpeg source code version 5.1 from <https://git.ffmpeg.org/ffmpeg.git> using the below commands in Git bash.
    ```
    git clone https://git.ffmpeg.org/ffmpeg.git
    cd ffmpeg
    git checkout release/5.1
    ```

3.  Copy *lib264_library.a* from *${buildTree}* directory to *ffmpeg/*.

4.  Copy all *C source* files from *ffmpeg_plugin/src/* to *ffmpeg/libavcodec* folder.

5.  Copy *header* files from *ffmpeg_plugin/include/* to *ffmpeg/libavcodec* folder.
    Copy all *header* files from *decoder/api* to *ffmpeg/libavcodec* folder.
    Copy  *header* files from *libthread/include* to *ffmpeg/libavcodec* folder.

6. Add *ih264_decoder_select="ih264d"* in configuration file (File name: *configure* in *ffmpeg/*) under heading *‘# decoders / encoders’* which enables *CONFIG_IH264_DECODER*

7. Search for *EXTRALIBS* tag in configuration file (File name: *configure*) and pass the argument *‘-l264_library -L.’*. The command should look like as below.
    ```
    EXTRALIBS=$extralibs -l264_library -L.
    ```

    This is for linking i264 Decoder library.

8. Add these header files in *<ffmpeg>/libavcodec/Makefile* along with other header files already present.
    ```
    HEADERS = ih264d.h \
              ih264d_plugin.h \
              ithread.h \
              itypedefs.h \
              iv.h \
              ivd.h \
    ```

9.  Add following object file names in *<ffmpeg>/libavcodec/Makefile* under heading *‘#decoders/encoders’* along with others
    ```
    OBJS-$(CONFIG_IH264_DECODER)    += ih264d.o
    ```

10.  Add the below line of code in the file *libavcodec/allcodecs.c* under section '*/\* external libraries \*/*'
        ```
        extern const FFCodec ff_ih264_decoder;
        ```
        It is recommended to add the above line before any other H264 decoder, to ensure Ittiam H264 Decoder is picked up by default for H264 stream decoding. In addition FFmpeg supports forcing a particular codec for encoding and this can be configured as command line argument.
        Ittiam recommends referring https://trac.ffmpeg.org/wiki/CompilationGuide for further information on compilation and setup.

## **Steps for Configure, Build and Execute**

1.  Go to *<ffmpeg>* directory.

2.  Configure *ffmpeg* using below command. No additional options are required for enabling i264 Decoder.
    ```
    ./configure (and additional options...)
    ```
3.  Confirm *CONFIG_IH264_DECODER* are set to 1 in *<ffmpeg>/config.h*

4.  Build *ffmpeg* binaries using following command in *\<ffmpeg\>* folder:
    ```
    make
    ```
    After successful completion of make process, the *ffmpeg* executable with i264 Decoder plugin will be ready to use.


# **Usage of Plugin**

### **i264 Decoder parameters**
- Following command line arguments shows minimum arguments expected for i264 Decoder.
    ```
    ./ffmpeg -c:v ih264d -i <Input Source video for decoder> <Output video YUV>
    ```

### **Sample Usage**
- Any .264 file to default video format
    ```
    ./ffmpeg –c:v ih264d -i input.264 –f rawvideo output.yuv
    ```
- Any .264 file to specific video format
    ```
    ./ffmpeg –c:v ih264d -i input.264 –f rawvideo -pix_fmt yuv420p output.yuv
    ```



