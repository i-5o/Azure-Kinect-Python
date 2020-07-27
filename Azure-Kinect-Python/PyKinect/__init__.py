from .Enums import *


class Image:
    def __init__(self, *args, **kwargs):
        pass

    def to_numpy(self, *args):
        pass

    def get_width_pixels(self, *args) -> int:
        pass

    def get_height_pixels(self, *args) -> int:
        pass


class Capture:
    def __init__(self, *args, **kwargs):
        pass

    def get_color_image(self, *args) -> Image:
        pass


class Device:
    def __init__(self, *args, **kwargs):
        pass

    def get_capture(self, *args) -> Capture:
        pass

    def start_cameras(self, *args) -> bool:
        pass

    def stop_cameras(self, *args):
        pass


from _PyKinect import *
