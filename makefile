TARGET_NAME := shale
CC = gcc
CFLAGS = -Wall -Werror -gcc

BUILD_DIR := ./build
SRC_DIR := ./src
INCLUDE_DIR := ./include

@(BUILD_DIR)/@(TARGET_NAME):
    $(CC) -c $(CFLAGS) -o $@

clean:
    rm -r $(BUILD_DIR)