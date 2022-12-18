# ObjectTracking
A repo dedicated to my learning and research of different tracking algorithms 
<h2>OpenCV installation guide</h2>
00 This is installation guide for linux. Before you start the installation make sure you are not in a conda env. (That will cause problems).  

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
