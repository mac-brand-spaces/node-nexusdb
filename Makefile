# Makefile

# Variables
BIN_DIR := ./bin
NXDB_LIB_DIR := ./nexusdb-lib
NODE_GYP := node-gyp

# Targets
.PHONY: all clean rebuild

all: $(BIN_DIR)/nexusdb.node

$(BIN_DIR)/nexusdb.node: $(NXDB_LIB_DIR)/nexusdb.dll | $(BIN_DIR)
	$(NODE_GYP) configure --arch=x64
	$(NODE_GYP) build --arch=x64
	cp build/Release/nexusdb.node $(BIN_DIR)/nexusdb-x64.node
	$(NODE_GYP) configure --arch=ia32
	$(NODE_GYP) build --arch=ia32
	cp build/Release/nexusdb.node $(BIN_DIR)/nexusdb-x32.node

$(NXDB_LIB_DIR)/nexusdb.dll:
	@if [ ! -d "$(NXDB_LIB_DIR)" ]; then \
		echo "Error: $(NXDB_LIB_DIR) not found. Did you fetch the submodule?"; \
		exit 1; \
	fi
	$(MAKE) -C $(NXDB_LIB_DIR)
	@if [ ! -d "$(BIN_DIR)" ]; then \
		mkdir -p $(BIN_DIR); \
	fi
	cp $(NXDB_LIB_DIR)/Win64/Debug/Project1.dll $(BIN_DIR)/Project1_64.dll
	cp $(NXDB_LIB_DIR)/Win32/Debug/Project1.dll $(BIN_DIR)/Project1_32.dll

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	$(NODE_GYP) clean
	rm -rf $(BIN_DIR)

rebuild: clean all