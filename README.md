# CameraNode
## Description

## How to build
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## How to configure system and run application
### Create RAM disk for streamer server
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
### Prepare resouces for application
Link all resources to /opt directory
```
$ sudo ln -sf <absolute_link_to_resource_dir> /opt/CameraNode
```
Export the location of face cascade, nose cascade and person training csv file path in resource folder.
```
export FACE_CASCADE=
export NOSE_CASCADE=<nose_cascade_location>
export CSV_FILEPATH=<csv_filepath>
```
Run the CameraNode
```
$ CameraNode ${FACE_CASCADE} ${NOSE_CASCADE} ${CSV_FILEPATH}
```
