TOPNAME = mux41
NXDC_FILES = constr/mux41.nxdc	#约束文件路径
INC_PATH ?=	#?=的意义是，INC_PATH如果被未被定义，则为?=后的值，如果被定义过，则保持原来的值
 
VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert
 
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir	#OBJ_DIR = ./build/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)	#BIN = ./build/top
 
default: $(BIN)	#终极目标为default，依赖./build/top
 
$(shell mkdir -p $(BUILD_DIR))
 
# 约束文件
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@
 
# 项目源文件
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
# 在vsrc目录中寻找所有的.v文件，并保存在变量VSRCS中
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
# 在csrc目录中寻找所有的.c/.cc/.cpp文件，并保存在变量CSRCS中
CSRCS += $(SRC_AUTO_BIND)
# 将auto_bind.cpp文件，追加在变量CSRCS中
 
# NVBoard的规则
include $(NVBOARD_HOME)/scripts/nvboard.mk
# 包含NVBoard相关Makelile规则
 
# Verilator的规则
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
 
$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR) 
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))
 
all: default
 
run: $(BIN)
	@$^
 
clean:
	rm -rf $(BUILD_DIR)
 
.PHONY: default all clean run
