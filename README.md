# ObjectTracking
A repo dedicated to my learning and research of different tracking algorithms 
<h2>OpenCV installation guide</h2>
This is installation guide for Ubuntu (tested on 20.04). Before you start the installation make sure you are not in a conda env. (That will cause problems).  
<p> </p>
01 Installing required packages and tools

```
sudo apt install -y g++ cmake make git libgtk2.0-dev pkg-config
```
02 Download the source and contrib
```
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```
03 Once the download is complete, create a temporary build directory, and navigate to it.
```
mkdir -p build && cd build
```
Set up the OpenCV build with CMake:
```
cmake ../opencv
```
04 Start the compilation process:
```
make -j6
```
*Modify the ``-j`` flag according to your processor. If you do not know the number of cores in your processor, you can find it by typing ``nproc``.*

05 Install OpenCV with:
```
sudo make install
```

06 That’s it. If you did not encounter any error then OpenCV is installed successfully on your Linux system. The header files are at the location 
```
/usr/local/include/opencv4
```

<h2>Cuda Toolkit installation guide</h2>

``https://docs.nvidia.com/cuda/cuda-quick-start-guide/index.html``

01 Verify You Have a CUDA-Capable GPU

```
lspci | grep -i nvidia
```

02 Install the repository meta-data, update the GPG key, update the apt-get cache, and install CUDA:
```
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-ubuntu1804.pin
sudo mv cuda-ubuntu1804.pin /etc/apt/preferences.d/cuda-repository-pin-600
wget https://developer.download.nvidia.com/compute/cuda/11.8.0/local_installers/cuda-repo-ubuntu1804-11-8-local_11.8.0-520.61.05-1_amd64.deb
sudo dpkg -i cuda-repo-ubuntu1804-11-8-local_11.8.0-520.61.05-1_amd64.deb
sudo cp /var/cuda-repo-ubuntu1804-11-8-local/cuda-*-keyring.gpg /usr/share/keyrings/
sudo apt-get update
sudo apt-get -y install cuda
```

03 Reboot the system to load the NVIDIA drivers:
```
sudo reboot
```

04 Set up the development environment by modifying the PATH and LD_LIBRARY_PATH variables:
```
export PATH=/usr/local/cuda-11.8/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-11.8/lib64\
                         ${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
```

05 Nvidia Cuda dev kit should be installed. Print the version with:
```
nvcc --version
```

<h2> cuDNN installation guide</h2>

``https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html``


01 Download cuDNN from Nvidia website. You need to register for a free account.
```
https://developer.nvidia.com/rdp/cudnn-download
```

02 Navigate to your "cudnnpath" directory containing the cuDNN Debian local installer file.

03 Enable the local repository.
```
sudo dpkg -i cudnn-local-repo-${OS}-8.x.x.x_1.0-1_amd64.deb
```

04 Import the CUDA GPG key.
```
sudo cp /var/cudnn-local-repo-*/cudnn-local-*-keyring.gpg /usr/share/keyrings/
```

05 Refresh the repository metadata.
```
sudo apt-get update
```

06 Install the runtime library.
```
sudo apt-get install libcudnn8=8.x.x.x-1+cudaX.Y
```

07 Install the developer library.
```
sudo apt-get install libcudnn8-dev=8.x.x.x-1+cudaX.Y
```

08 Install the code samples and the cuDNN library documentation.
```
sudo apt-get install libcudnn8-samples=8.x.x.x-1+cudaX.Y
```

09 To verify that cuDNN is installed and is running properly, compile the mnistCUDNN sample located in the /usr/src/cudnn_samples_v8 directory in the Debian file.
```
cp -r /usr/src/cudnn_samples_v8/ $HOME
cd  $HOME/cudnn_samples_v8/mnistCUDNN
make clean && make
./mnistCUDNN
```

If cuDNN is properly installed and running on your Linux system, you will see a message similar to the following:
```
Test passed!
```

<h2>Compile OpenCV with CUDA support</h2>

02 Download the source and contrib
```
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```
03 Once the download is complete, create a temporary build directory, and navigate to it.
```
mkdir -p build && cd build
```
04 Set up the OpenCV build with CMake, I used GUI and set the following parameters:
```
1. with_cuda = 1
2. opencv_dnn_cuda = 1
3. BUILD_opencv_dnn = 1
4. enable_fast_math = 1
5. BUILD_opencv_world = 1
6. opencv_extra_modules_path = "/home/jan/OpenCv/opencv_contrib-4.6.0/modules"

```
05 Click configure and proceed to change following parameters:
```
1. cuda_fast_math = 1
2. cuda_arch_bin = 6.1 (This is depended on the version of your gpu)
3. cmake_configuration_types = Release
```
06 Click generate and move the the build directory

07 Start the compilation process:
```
make -j6
```
*Where ``-j`` stands for number of cores your cpu has*

08 Install OpenCV with:
```
sudo make install
```

09 That’s it. If you did not encounter any error then OpenCV is installed successfully on your Linux system. The header files are at the location 
```
/usr/local/include/opencv4
```
