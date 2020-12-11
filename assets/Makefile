SHAPES_BLEND := $(wildcard *.blend)
SHAPES_GLB := $(SHAPES_BLEND:%.blend=%.glb)

all: $(SHAPES_GLB)

%.glb: %.blend
	@echo "$< → ../models/$@"
	@/Applications/Blender.app/Contents/MacOS/Blender \
		--background \
		--python blend2glb.py \
		-- \
		"../models/$@" \
		1 > /dev/null
