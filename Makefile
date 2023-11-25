CC := g++
FLAGS := -std=c++17
MAIN_DIR := src
ALGO_DIR := src/algos

MAIN_FILES := $(wildcard $(MAIN_DIR)/*.cc)
ALGO_FILES := $(wildcard $(ALGO_DIR)/*.cc)

OUT_FILE := pregel

pregel: $(MAIN_FILES) $(ALGO_FILES)
	$(CC) $(FLAGS) $(MAIN_FILES) $(ALGO_FILES) -o $(OUT_FILE)

clean:
	rm -f $(OUT_FILE)
