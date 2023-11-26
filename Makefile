CC := g++
# for MacOS semaphores: -D_LIBCPP_DISABLE_AVAILABILITY
FLAGS := -std=c++20 -D_LIBCPP_DISABLE_AVAILABILITY
MAIN_DIR := src
ALGO_DIR := src/algo

MAIN_FILES := $(wildcard $(MAIN_DIR)/*.cc)
ALGO_FILES := $(wildcard $(ALGO_DIR)/*.cc)

# Need dependency to check for changes in headers. 
MAIN_HEADERS := $(wildcard $(MAIN_DIR)/*.hh)
ALGO_HEADERS := $(wildcard $(ALGO_DIR)/*.hh)

OUT_FILE := pregel

pregel: $(MAIN_FILES) $(ALGO_FILES) $(MAIN_HEADERS) $(ALGO_HEADERS)
	$(CC) $(FLAGS) $(MAIN_FILES) $(ALGO_FILES) -o $(OUT_FILE)

clean:
	rm -f $(OUT_FILE)
