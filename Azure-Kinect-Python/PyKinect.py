import numpy as np
from enum import Enum


class ImageFormat(Enum):
    K4A_IMAGE_FORMAT_COLOR_MJPG = 0
    K4A_IMAGE_FORMAT_COLOR_NV12 = 1
    K4A_IMAGE_FORMAT_COLOR_YUY2 = 2
    K4A_IMAGE_FORMAT_COLOR_BGRA32 = 3
    K4A_IMAGE_FORMAT_DEPTH16 = 4
    K4A_IMAGE_FORMAT_IR16 = 5
    K4A_IMAGE_FORMAT_CUSTOM8 = 6
    K4A_IMAGE_FORMAT_CUSTOM16 = 7
    K4A_IMAGE_FORMAT_CUSTOM = 8


class ColorResolution(Enum):
    K4A_COLOR_RESOLUTION_OFF = 0
    K4A_COLOR_RESOLUTION_720P = 1
    K4A_COLOR_RESOLUTION_1080P = 2
    K4A_COLOR_RESOLUTION_1440P = 3
    K4A_COLOR_RESOLUTION_1536P = 4
    K4A_COLOR_RESOLUTION_2160P = 5
    K4A_COLOR_RESOLUTION_3072P = 6


class DepthMode(Enum):
    K4A_DEPTH_MODE_OFF = 0
    K4A_DEPTH_MODE_NFOV_2X2BINNED = 1
    K4A_DEPTH_MODE_NFOV_UNBINNED = 2
    K4A_DEPTH_MODE_WFOV_2X2BINNED = 3
    K4A_DEPTH_MODE_WFOV_UNBINNED = 4
    K4A_DEPTH_MODE_PASSIVE_IR = 5


class Fps(Enum):
    K4A_FRAMES_PER_SECOND_5 = 0
    K4A_FRAMES_PER_SECOND_15 = 1
    K4A_FRAMES_PER_SECOND_30 = 2


class WiredSyncMode(Enum):
    K4A_WIRED_SYNC_MODE_STANDALONE = 0
    K4A_WIRED_SYNC_MODE_MASTER = 1
    K4A_WIRED_SYNC_MODE_SUBORDINATE = 2


class Device:
    def __init__(self, *args, **kwargs):
        pass

    def get_capture(self, *args):
        pass

    def start_cameras(self, *args):
        pass

    def stop_cameras(self, *args):
        pass


class Capture:
    def __init__(self, *args, **kwargs):
        pass

    def get_color_image(self, *args):
        pass
