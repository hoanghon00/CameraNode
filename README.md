# CameraNode
## Description

## How to build
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## How to run
Fisrt, create a RAM disk to store output of program
```
$ sudo mkdir /mnt/RAM_disk
```
Then, use **mount** to create a RAM disk.
```
sudo mount -t tmpfs -o size=2m tmpfs /mnt/RAM_disk/
```
To create a RAM disk automatically after every time system boot up, add an entry to **/etc/fstab**
```
tmpfs       /mnt/RAM_disk tmpfs   nodev,nosuid,noexec,nodiratime,size=2M   0 0
```

Copy all resources to /opt directory
```
$ sudo mkdir /opt/CameraNode
$ sudo cp -rf resource/faces /opt/
```
Export the absolute location of face cascade, nose cascade and person training csv file path in resource folder.
```
export FACE_CASCADE=<face_cascade_location>
export NOSE_CASCADE=<nose_cascade_location>
export CSV_FILEPATH=<csv_filepath>
```
Run the CameraNode
```
$ CameraNode ${FACE_CASCADE} ${NOSE_CASCADE} ${CSV_FILEPATH}
```