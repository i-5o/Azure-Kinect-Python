import PyKinect as pk


def main():
    device = pk.Device(0)
    result = device.start_cameras(
        pk.ImageFormat.K4A_IMAGE_FORMAT_COLOR_MJPG,
        pk.ColorResolution.K4A_COLOR_RESOLUTION_2160P,
        pk.DepthMode.K4A_DEPTH_MODE_OFF,
        pk.Fps.K4A_FRAMES_PER_SECOND_30,
        False,
        0,
        pk.WiredSyncMode.K4A_WIRED_SYNC_MODE_STANDALONE,
        0,
        False
    )
    if not result:
        print("Unable to start camera!")

    capture = device.get_capture()
    image = capture.get_color_image()

    print(image.get_height_pixels())
    print(image.get_width_pixels())


if __name__ == "__main__":
    main()
