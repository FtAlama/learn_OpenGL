APP_NAME := learn_opengl
BUILD_DIR := cmake
CMAKE_FLAGS := -DAPP_NAME=$(APP_NAME)
LSP_CONFIG := .misc

.PHONY: all debug release run clean fclean 

all: debug

debug:
	@if [ ! -f $(BUILD_DIR)/CMakeCache.txt ]; then \
		echo "==> Initial CMake configure (Debug)"; \
		cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON $(CMAKE_FLAGS); \
	else \
		echo "==> CMake already configured — skipping."; \
	fi; \
	mkdir -p $(LSP_CONFIG); \
	cp -f $(BUILD_DIR)/compile_commands.json $(LSP_CONFIG)
	cmake --build $(BUILD_DIR)
	@mv $(BUILD_DIR)/$(APP_NAME) .
	@./$(APP_NAME)

release:
	@echo "==> Forcing clean & release build..."
	@rm -rf $(BUILD_DIR)
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release $(CMAKE_FLAGS)
	@mkdir -p $(LSP_CONFIG) 
	@cp -f $(BUILD_DIR)/compile_commands.json $(LSP_CONFIG)
	cmake --build $(BUILD_DIR)
	@mv $(BUILD_DIR)/$(APP_NAME) .
	@./$(APP_NAME)

run: 
	@./$(APP_NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(LSP_CONFIG) $(APP_NAME)
