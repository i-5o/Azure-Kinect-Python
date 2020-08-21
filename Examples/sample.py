import PyKinect as pk


def main():
    device = pk.Device(0)
    device_config = pk.DeviceConfig()
    device_config.set_image_format(pk.ImageFormat.K4A_IMAGE_FORMAT_COLOR_BGRA32)
    device_config.set_color_resolution(pk.ColorResolution.K4A_COLOR_RESOLUTION_2160P)

    print(device_config)
    device.start_cameras(device_config)

    capture = device.get_capture()
    image = capture.get_color_image()

    print(image.get_height_pixels())
    print(image.get_width_pixels())


if __name__ == "__main__":
    main()
