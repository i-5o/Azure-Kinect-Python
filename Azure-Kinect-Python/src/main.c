#include <k4a/k4a.h>
#include <stdlib.h>
#include <stdio.h>



void printSerial(k4a_device_t device)
{
    // Get the size of the serial number
    size_t serial_size = 0;
    k4a_device_get_serialnum(device, NULL, &serial_size);

    // Allocate memory for the serial, then acquire it
    char* serial = (char*)malloc(serial_size);
    k4a_device_get_serialnum(device, serial, &serial_size);
    printf("Opened device: %s\n", serial);
    free(serial);
}


int main()
{
    k4a_device_t device = NULL;
    uint32_t device_count = k4a_device_get_installed_count();

    if (device_count != 1)
    {
        printf("Unexpected number of devices found (%d)\n", device_count);
        goto Exit;
    }

    if (K4A_RESULT_SUCCEEDED != k4a_device_open(K4A_DEVICE_DEFAULT, &device))
    {
        printf("Failed to open device\n");
        goto Exit;
    }

    k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
    config.camera_fps = K4A_FRAMES_PER_SECOND_30;
    config.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
    config.color_resolution = K4A_COLOR_RESOLUTION_2160P;

    if (K4A_RESULT_SUCCEEDED != k4a_device_start_cameras(device, &config))
    {
        printf("Failed to start device\n");
        goto Exit;
    }

    k4a_capture_t cap;

    // Capture a depth frame
    switch (k4a_device_get_capture(device, &cap, K4A_WAIT_INFINITE))
    {
    case K4A_WAIT_RESULT_SUCCEEDED:
        break;
    case K4A_WAIT_RESULT_TIMEOUT:
        printf("Timed out waiting for a capture\n");
        goto Exit;
    case K4A_WAIT_RESULT_FAILED:
        printf("Failed to read a capture\n");
        goto Exit;
    }

    k4a_image_t img = k4a_capture_get_color_image(cap);

    printf("Image width: %d\n", k4a_image_get_width_pixels(img));
    printf("Image height: %d\n", k4a_image_get_height_pixels(img));
    printf("Image buffer size: %lu\n", k4a_image_get_size(img));

	exit(0);

Exit:
    exit(1);
}
