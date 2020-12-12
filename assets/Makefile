SHAPES_BLEND := $(wildcard 	*.blend)
SHAPES_GLB := $(SHAPES_BLEND:%.blend=../models/%.glb)

all: $(SHAPES_GLB)

../models/%.glb: %.blend
	@echo "$< → $@"
	@/Applications/Blender.app/Contents/MacOS/Blender \
		$< \
		--background \
		--python blend2glb.py \
		-- \
		"$@" \
		1 > /dev/null
