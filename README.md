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
export FACE_CASCADE=/opt/CameraNode/haarcascade_frontalface_default.xml
export NOSE_CASCADE=/opt/CameraNode/haarcascade_mcs_nose.xml
export CSV_FILEPATH=/opt/CameraNode/faces.csv
```
And copy these lines into **~/.bashrc**
###Run the CameraNode
```
$ CameraNode ${FACE_CASCADE} ${NOSE_CASCADE} ${CSV_FILEPATH}
```
## CameraNode with systemd
To start mjpg-streamer and CameraNode application automatically when system start up, we create systemd services to complete this task.
These service stored in systemd folder.
### mjpg-streamer
```
$ sudo cp mjpg-streamerd.service /etc/systemd/system/mjpg-streamerd.service
$ sudo systemctl daemon-reload
$ sudo systemctl start mjpg-streamerd
$ sudo systemctl enable mjpg-streamerd
```
### CameraNode application
```
$ sudo mkdir /etc/CameraNode
$ sudo cp CameraNode.conf /etc/CameraNode/CameraNode.conf
$ sudo cp camera-node.service /usr/lib/systemd/user/camera-node.service
$ sudo systemctl daemon-reload
$ systemctl --user start camera-node
$ systemctl --user enable camera-node
```