import PyKinect as pk
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import time


def main():
    device = pk.Device(0)
    device_config = pk.DeviceConfig()
    device_config.set_image_format(pk.ImageFormat.K4A_IMAGE_FORMAT_COLOR_BGRA32)
    device_config.set_color_resolution(pk.ColorResolution.K4A_COLOR_RESOLUTION_2160P)
    device_config.set_depth_mode(pk.DepthMode.K4A_DEPTH_MODE_WFOV_2X2BINNED)

    print(device_config)
    device.start_cameras(device_config)
    capture = device.get_capture()

    image = capture.get_color_image()
    npImg = image.to_numpy()[:, :, :3][:, :, ::-1]
    pilImg = Image.fromarray(npImg)
    pilImg.show()

    irimg = capture.get_ir_image()
    npIR = np.log(irimg.to_numpy() + 2)
    plt.imshow(npIR, cmap="gray")
    plt.show()

    depth = capture.get_depth_image()
    npDep = np.sqrt(depth.to_numpy())
    plt.imshow(npDep, cmap="jet")
    plt.show()


if __name__ == "__main__":
    main()
