VERILATOR = verilator
SRC = ../src

synth: $(SRC)/synth.v synth_tb.cpp
	$(VERILATOR) --trace -cc --exe \
	    -I$(SRC) \
	    $^ \
	    -CFLAGS "-g -O3" \
	    --top-module synth
	$(MAKE) -C obj_dir -f Vsynth.mk
	cp obj_dir/Vsynth $@

clean:
	rm -rf obj_dir synth

.PHONY: clean
