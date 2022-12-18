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

01 Verify You Have a CUDA-Capable GPU

```
lspci | grep -i nvidia

wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-ubuntu1804.pin
sudo mv cuda-ubuntu1804.pin /etc/apt/preferences.d/cuda-repository-pin-600
wget https://developer.download.nvidia.com/compute/cuda/12.0.0/local_installers/cuda-repo-ubuntu1804-12-0-local_12.0.0-525.60.13-1_amd64.deb
sudo dpkg -i cuda-repo-ubuntu1804-12-0-local_12.0.0-525.60.13-1_amd64.deb
sudo cp /var/cuda-repo-ubuntu1804-12-0-local/cuda-*-keyring.gpg /usr/share/keyrings/
sudo apt-get update
sudo apt-get -y install cuda
```
02 Install CUDA toolkit from Ubuntu Repository
```
sudo apt install nvidia-cuda-toolkit
```
03 Reboot the system to load the NVIDIA drivers:
```
nvcc --version
```
04 Set up the development environment by modifying the PATH and LD_LIBRARY_PATH variables:
```
export PATH=/usr/local/cuda-12.0/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-12.0/lib64\
                         ${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
```
<h2>Cuda Toolkit installation guide</h2>

01 Install zlib
```
sudo apt-get install zlib1g
```
02 Download cuDNN from Nvidia website. You need to register for a free account.
```
https://developer.nvidia.com/rdp/cudnn-download
```

03 Navigate to your "cudnnpath" directory containing the cuDNN Debian local installer file.

04 Enable the local repository.
```
sudo dpkg -i cudnn-local-repo-${OS}-8.x.x.x_1.0-1_amd64.deb
```

Import the CUDA GPG key.
```
sudo cp /var/cudnn-local-repo-*/cudnn-local-*-keyring.gpg /usr/share/keyrings/
```

Refresh the repository metadata.
```
sudo apt-get update
```

Install the runtime library.
```
sudo apt-get install libcudnn8=8.x.x.x-1+cudaX.Y
```

Install the developer library.
```
sudo apt-get install libcudnn8-dev=8.x.x.x-1+cudaX.Y
```

Install the code samples and the cuDNN library documentation.
```
sudo apt-get install libcudnn8-samples=8.x.x.x-1+cudaX.Y
```
To verify that cuDNN is installed and is running properly, compile the mnistCUDNN sample located in the /usr/src/cudnn_samples_v8 directory in the Debian file.
```
cp -r /usr/src/cudnn_samples_v8/ $HOME
```

Go to the writable path.
```
cd  $HOME/cudnn_samples_v8/mnistCUDNN
```
Compile the mnistCUDNN sample.
```
make clean && make
```

Run the mnistCUDNN sample.
```
./mnistCUDNN
```

If cuDNN is properly installed and running on your Linux system, you will see a message similar to the following:
```
Test passed!
```
