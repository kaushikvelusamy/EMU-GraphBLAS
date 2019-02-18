# Tools
BIN_DIR ?= /usr/local/emu-18.08.1/bin

CC = $(BIN_DIR)/emu-cc
EMUSIM = $(BIN_DIR)/emusim.x
GOBJD = $(BIN_DIR)/gossamer64-objdump
AR = $(BIN_DIR)/gossamer64-ar
RANLIB = $(BIN_DIR)/gossamer64-ranlib

LIB_PATH_1= -I./src
LIB_PATH_2= -I./src/graphblas/platforms/emu_backend
SOURCE=./tc_demo/triangle_count_demo.cpp
INPUTS=./dataset/4x4dataset/dataset_4x4_nnz10.tsv


EXE_NAME = run_emu_tc

DEBUG=0
SIMULATOR=0
HARDWARE=1

ifeq ($(SIMULATOR), 1)
  CFLAGS = -DSIMULATOR
endif
ifeq ($(HARDWARE), 1)
  CFLAGS += -DHARDWARE
endif
ifeq ($(DEBUG), 1)
  CFLAGS += -DDEBUG
endif



.PHONY: all
all:$(EXE_NAME).mwx

%.mwx: tc_demo/triangle_count_demo.cpp
	$(CC) ${CFLAGS} $(LIB_PATH_1) $(LIB_PATH_2) $(SOURCE)  -o $@

run_with: $(EXE_NAME).mwx
	$(EMUSIM) $< $(INPUTS)

run: $(EXE_NAME).mwx
	$(EMUSIM) --ignore_starttiming $< $(INPUTS)

.PHONY: clean
clean:
	rm -f *.o *.mwx *.ll *.s *.sxp *.cdc *.vsf *.hdd *.tqd $(EXE_NAME)

%.tqd: %.mwx
	$(EMUSIM) --capture_timing_queues -o $* $< $(INPUTS)

%.uis: %.mwx
	$(EMUSIM) --output_instruction_count -o $* $< $(INPUTS)
%.visa: %.mwx
	$(EMUSIM) --verbose_isa $< $(INPUTS) > $@

%.trace: %.mwx
	$(EMUSIM) --short_trace $< $(INPUTS) > $@

%.objdump: %.mwx
	$(GOBJD) -Dx $< > $@

%.a:
	$(AR) -rv $@ $^
	$(RANLIB) $@
