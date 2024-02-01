# networkedmatrix (C++)

## Hardware
- Waveshare 64x32 2.5mm pitch LED matrix
- Raspberry Pi Zero W

## Building
- (Not sure if needed - might be auto-installed by cpprestsdk) Install [Boost]()

```
sudo apt install libboost-dev
```

- Install [Microsoft's REST API toolkit for C++](https://github.com/microsoft/cpprestsdk)

```
sudo apt-get install libcpprest-dev
```

- Clone https://github.com/hzeller/rpi-rgb-led-matrix in a peer folder to this repo and make it

```
make
```

## Running
- Disable sound module first - see https://github.com/hzeller/rpi-rgb-led-matrix/tree/master?tab=readme-ov-file#bad-interaction-with-sound

```
sudo ./eyes
```
