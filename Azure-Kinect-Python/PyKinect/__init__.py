from .Enums import *
import numpy as np


class Image:
    def __init__(self, *args, **kwargs):
        pass

    def to_numpy(self, *args) -> np.ndarray:
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

    def get_depth_image(self, *args) -> Image:
        pass

    def get_ir_image(self, *args) -> Image:
        pass


class Device:
    def __init__(self, *args, **kwargs):
        pass

    def get_capture(self, *args) -> Capture:
        pass

    def start_cameras(self, *args) -> bool:
        pass

    def stop_cameras(self, *args) -> None:
        pass


class DeviceConfig:
    def __init__(self):
        pass

    def __repr__(self):
        pass

    def set_image_format(self, *args):
        pass

    def get_image_format(self, *args):
        pass

    def set_color_resolution(self, *args):
        pass

    def get_color_resolution(self, *args):
        pass

    def set_depth_mode(self, *args):
        pass

    def get_depth_mode(self, *args):
        pass

    def set_camera_fps(self, *args):
        pass

    def get_camera_fps(self, *args):
        pass

    def set_synchronized_images_only(self, *args):
        pass

    def get_synchronized_images_only(self, *args):
        pass

    def set_depth_delay_off_color_usec(self, *args):
        pass

    def get_depth_delay_off_color_usec(self, *args):
        pass

    def set_wired_sync_mode(self, *args):
        pass

    def get_wired_sync_mode(self, *args):
        pass

    def set_subordinate_delay_off_master_usec(self, *args):
        pass

    def get_subordinate_delay_off_master_usec(self, *args):
        pass

    def set_disable_streaming_indicator(self, *args):
        pass
    
    def get_disable_streaming_indicator(self, *args):
        pass


from _PyKinect import *
