#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include <libfreenect.h>

int main(int argc, char **argv) {
    freenect_context *fc;
    freenect_device *fd;

    if (freenect_init(&fc, 0) < 0) {
        printf("failed to init freenect\n");
        exit(1);
    }

    if (freenect_num_devices(fc) < 1) {
        printf("no kinect found\n");
        freenect_shutdown(fc);
        exit(1);
    }

    if (freenect_open_device(fc, &fd, 0) < 0) {
        printf("unable to open device 0\n");
        freenect_shutdown(fc);
        exit(1);
    }

    double want;
    while (1) {
        want = 30.0;
        freenect_set_tilt_degs(fd, want);
        freenect_set_led(fd, LED_RED);
        while (fabs(freenect_get_tilt_degs(freenect_get_tilt_state(fd)) - want) > 1) {
            freenect_update_tilt_state(fd);
            usleep(1000);
        }

        want = -30.0;
        freenect_set_tilt_degs(fd, want);
        freenect_set_led(fd, LED_GREEN);
        while (fabs(freenect_get_tilt_degs(freenect_get_tilt_state(fd)) - want) > 1) {
            freenect_update_tilt_state(fd);
            usleep(1000);
        }
    }

    freenect_close_device(fd);
    freenect_shutdown(fc);
    exit(0);
}
