SHAPES_BLEND := $(wildcard 	*.blend)
SHAPES_GLB := $(SHAPES_BLEND:%.blend=../models/%.glb)

all: $(SHAPES_GLB)

../models/%.glb: %.blend
	@echo "$< → $@"
	@"C:\Program Files\Blender Foundation\Blender 2.91\blender.exe" \
		$< \
		--background \
		--python blend2glb.py \
		-- \
		"$@" \
		1 > /dev/null
