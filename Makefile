SUBMODULE := core
$(info    Compiling submodule '$(SUBMODULE)'...)

BUILD_DIR := build/$(SUBMODULE)

CC      := clang
LD      := ld.lld
TARGET  := $(BUILD_DIR)/mod.elf

LDSCRIPT := mod.ld
CFLAGS   := -target mips -mips2 -mabi=32 -O2 -G0 -mno-abicalls -mno-odd-spreg -mno-check-zero-division \
			-fomit-frame-pointer -ffast-math -fno-unsafe-math-optimizations -fno-builtin-memset \
			-Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-variable \
			-Wno-missing-braces -Wno-unsupported-floating-point-opt -Werror=section
CPPFLAGS := -nostdinc -D_LANGUAGE_C -DMIPS -DF3DEX_GBI_2 -DF3DEX_GBI_PL -DGBI_DOWHILE -DRECOMP_IS_BUILDING_$(SUBMODULE) \
			-I include/recomp -I include/recomp/dummy_headers -I include/libc
LDFLAGS  := -nostdlib -T $(LDSCRIPT) -Map $(BUILD_DIR)/mod.map --unresolved-symbols=ignore-all --emit-relocs -e 0 --no-nmagic -L lib -lgcc_vr4300

C_SRCS := \
	$(wildcard src/core/assert/*.c) \
	$(wildcard src/core/ctype/*.c) \
	$(wildcard src/core/printf/*.c) \
	$(wildcard src/core/stdlib/*.c) \
	$(wildcard src/core/string/*.c) \
	$(wildcard src/core/support/*.c)

C_OBJS := $(addprefix $(BUILD_DIR)/, $(C_SRCS:.c=.o))
C_DEPS := $(addprefix $(BUILD_DIR)/, $(C_SRCS:.c=.d))

OBJECT_DIRS := \
	$(BUILD_DIR)/src/ \
	$(BUILD_DIR)/src/core/ \
	$(BUILD_DIR)/src/core/$(SUBMODULE) \
	$(BUILD_DIR)/src/core/assert \
	$(BUILD_DIR)/src/core/ctype \
	$(BUILD_DIR)/src/core/printf \
	$(BUILD_DIR)/src/core/stdlib \
	$(BUILD_DIR)/src/core/string \
	$(BUILD_DIR)/src/core/support

$(TARGET): $(C_OBJS) $(LDSCRIPT) | $(BUILD_DIR)
	$(LD) $(C_OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR) $(OBJECT_DIRS):
ifeq ($(OS),Windows_NT)
	mkdir $(subst /,\,$@)
else
	mkdir -p $@
endif

$(C_OBJS): $(BUILD_DIR)/%.o : %.c | $(BUILD_DIR) $(BUILD_DIR)/src/ $(OBJECT_DIRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -MMD -MF $(@:.o=.d) -c -o $@

clean:
	rm -rf $(BUILD_DIR)

-include $(C_DEPS)

.PHONY: clean
