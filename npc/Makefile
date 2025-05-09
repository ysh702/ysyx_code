all:
	@echo "Usage: make sim    - Run simulation and generate waveform"
	@echo "       make clean  - Clean build artifacts"

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "[SIM] Starting simulation..."
	
	# 清理旧构建
	rm -rf $(BUILD_DIR) $(WAVEFORM)
	
	# 编译Verilog生成C++模型
	$(VERILATOR) --trace --cc -y $(VSRC_DIR) $(VSRC_DIR)/$(TOP_MODULE).v \
		--exe $(CSRC_DIR)/$(FILE_NAME) --build
	
	# 运行仿真生成波形
	@echo "\n[SIM] Running simulation..."
	./$(BUILD_DIR)/V$(TOP_MODULE)
	
	# 自动打开波形 (可选)
	@echo "\n[SIM] Opening waveform..."
	gtkwave $(WAVEFORM) || true
 
# 清理构建产物
clean:
	rm -rf $(BUILD_DIR) $(WAVEFORM) *.vcd *.fst
 
# 包含上级Makefile配置
include ../Makefile
